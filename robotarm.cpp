// The sample robotarm model.  You should build a file
// very similar to this for when you make your model.
#pragma warning (disable : 4305)
#pragma warning (disable : 4244)
#pragma warning(disable : 4786)

#include "modelerview.h"
#include "modelerapp.h"
#include "modelerdraw.h"
#include "particleSystem.h"


#include <FL/gl.h>
#include <stdlib.h>

#define M_DEFAULT 2.0f
#define M_OFFSET 3.0f
#define P_OFFSET 0.3f
#define MAX_VEL 200
#define MIN_STEP 0.1
#define VAL(x) (ModelerApplication::Instance()->GetControlValue(x))
#define COLOR_RED		1.0f, 0.0f, 0.0f
#define COLOR_GREEN		0.0f, 1.0f, 0.0f
#define COLOR_BLUE		0.0f, 0.0f, 1.0f

enum SampleModelControls
{
	XPOS=0, YPOS, ZPOS, ROTATE, LEFTUPPERROTATE, RIGHTUPPERROTATE, DETAILS, FRAME_ALL, NUMCONTROLS
};

class SampleModel : public ModelerView
{
public:
	SampleModel(int x, int y, int w, int h, char *label)
		: ModelerView(x, y, w, h, label), leftIncrement(1), rightIncrement(-1), rotationIncrement(1) { }

	virtual void draw();
private:
	int leftIncrement;
	int rightIncrement;
	int rotationIncrement;
};

// We need to make a creator function, mostly because of
// nasty API stuff that we'd rather stay away from.
ModelerView* createSampleModel(int x, int y, int w, int h, char *label)
{
	return new SampleModel(x, y, w, h, label);
}

// We are going to override (is that the right word?) the draw()
// method of ModelerView to draw out SampleModel
void SampleModel::draw()
{
	// This call takes care of a lot of the nasty projection 
	// matrix stuff.  Unless you want to fudge directly with the 
	// projection matrix, don't bother with this ...

	ModelerView::draw();




	// draw the floor	
	setAmbientColor(.1f, .1f, .1f);
	setDiffuseColor(COLOR_RED);
	glPushMatrix();
	glTranslated(-5, 0, -5);
	drawBox(10, 0.01f, 10);
	glPopMatrix();



	setAmbientColor(.1f, .1f, .1f);
	setDiffuseColor(COLOR_GREEN);
	setSpecularColor(0.4, 1, 0.4);
	setShininess(30);
	glPushMatrix();
	glTranslated(VAL(XPOS), VAL(YPOS), VAL(ZPOS));
	//draw the troso
	glPushMatrix();
	glTranslated(-1.1, 3.4, -0.8);
	drawBox(2.2, 3.1, 1.6);
	glTranslated(1.05, -0.2, 0.7);
	drawBox(0.2, 0.2, 0.2);
	glPopMatrix();

	//draw the beam
	glPushMatrix();
	glTranslated(0, 3.0, 0);
	glRotated(VAL(ROTATE), 0.0, 1.0, 0.0);
	glRotated(90, 0.0, 1.0, 0.0);
	glTranslated(0, 0, -1.25);
	if (VAL(DETAILS) >= 1) {
		drawCylinder(2.4, 0.25, 0.25);
	}
	//draw the left upper arm
	glPushMatrix();
	if (VAL(DETAILS) >= 2)
		drawCylinder(0.2, 0.3, 0.3);
	glTranslated(0.0, 0.0, 0.1);
	glRotated(-90, 0.0, 1.0, 0.0);
	glRotated(VAL(LEFTUPPERROTATE), 1.0, 0.0, 0.0);
	glRotated(115, 1.0, 0.0, 0.0);
	if (VAL(DETAILS) >= 2)
		drawCylinder(1.0, 0.2, 0.3);
	glTranslated(0, 0, 1.2);

	//draw the left lower arm
	glPushMatrix();
	if (VAL(DETAILS) >= 3)
		drawSphere(0.25);
	glRotated(-65, 1.0, 0.0, 0.0);
	if (VAL(DETAILS) >= 3)
		drawCylinder(1.85, 0.2, 0.3);
	glTranslated(0.0, 0.0, 1.85);

	//draw the left hand 
	glPushMatrix();
	if (VAL(DETAILS) >= 4)
		drawSphere(0.2);
	glTranslated(-0.25, -0.05, 0);
	if (VAL(DETAILS) >= 4)
		drawBox(0.1, 0.2, 0.5);
	glTranslated(0.4, 0, 0);
	if (VAL(DETAILS) >= 4)
		drawBox(0.1, 0.2, 0.5);
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();

	glTranslated(0, 0, 2.4);
	//draw the right upper arm
	glPushMatrix();
	if (VAL(DETAILS) >= 2)
		drawCylinder(0.2, 0.3, 0.3);
	glTranslated(0.0, 0.0, 0.1);
	glRotated(-90, 0.0, 1.0, 0.0);
	glRotated(VAL(RIGHTUPPERROTATE), 1.0, 0.0, 0.0);
	glRotated(115, 1.0, 0.0, 0.0);
	if (VAL(DETAILS) >= 2)
		drawCylinder(1.0, 0.2, 0.3);
	glTranslated(0, 0, 1.2);

	//draw the right lower arm
	glPushMatrix();
	if (VAL(DETAILS) >= 3)
		drawSphere(0.25);
	glRotated(-65, 1.0, 0.0, 0.0);
	if (VAL(DETAILS) >= 3)
		drawCylinder(1.85, 0.2, 0.3);
	glTranslated(0.0, 0.0, 1.85);

	//draw the right hand 
	glPushMatrix();
	if (VAL(DETAILS) >= 4)
		drawSphere(0.2);
	glTranslated(-0.25, -0.05, 0);
	if (VAL(DETAILS) >= 4)
		drawBox(0.1, 0.2, 0.5);
	glTranslated(0.4, 0, 0);
	if (VAL(DETAILS) >= 4)
		drawBox(0.1, 0.2, 0.5);
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();

	glPopMatrix();
	glPopMatrix();
	endDraw();
}


int main()
{
	ModelerControl controls[NUMCONTROLS];
	controls[XPOS] = ModelerControl("X Position", -10, 10, 0.1f, 0);
	controls[YPOS] = ModelerControl("Y Position", 0, 10, 0.1f, 0);
	controls[ZPOS] = ModelerControl("Z Position", -10, 10, 0.1f, 0);
	controls[ROTATE] = ModelerControl("Rotate", -135, 135, 1, 0);
	controls[LEFTUPPERROTATE] = ModelerControl("Left Upper Arm", -100, 60, 1, -20);
	controls[RIGHTUPPERROTATE] = ModelerControl("Right Upper Arm", -100, 60, 1, -20);
	controls[DETAILS] = ModelerControl("Level of details", 0, 4, 1, 4);
	controls[FRAME_ALL] = ModelerControl("Frame all", 0, 1, 1, 0);
    


	// You should create a ParticleSystem object ps here and then
	// call ModelerApplication::Instance()->SetParticleSystem(ps)
	// to hook it up to the animator interface.

    ModelerApplication::Instance()->Init(&createSampleModel, controls, NUMCONTROLS);

    return ModelerApplication::Instance()->Run();
}




/*

// This is a list of the controls for the RobotArm
// We'll use these constants to access the values
// of the controls from the user interface.
enum RobotArmControls
{
	BASE_ROTATION=0, LOWER_TILT, UPPER_TILT, CLAW_ROTATION,
		BASE_LENGTH, LOWER_LENGTH, UPPER_LENGTH, PARTICLE_COUNT, NUMCONTROLS,
};


void ground(float h);
void base(float h);
void rotation_base(float h);
void lower_arm(float h);
void upper_arm(float h);
void claw(float h);
void y_box(float h);

// To make a RobotArm, we inherit off of ModelerView
class RobotArm : public ModelerView
{
public:
	RobotArm(int x, int y, int w, int h, char *label)
		: ModelerView(x,y,w,h,label) {}
	virtual void draw();
};

// We need to make a creator function, mostly because of
// nasty API stuff that we'd rather stay away from.
ModelerView* createRobotArm(int x, int y, int w, int h, char *label)
{
	return new RobotArm(x,y,w,h,label);
}

// We'll be getting the instance of the application a lot;
// might as well have it as a macro.





// We are going to override (is that the right word?) the draw()
// method of ModelerView to draw out RobotArm
void RobotArm::draw()
{

	float theta = VAL( BASE_ROTATION );
	float phi = VAL( LOWER_TILT );
	float psi = VAL( UPPER_TILT );
	float cr = VAL( CLAW_ROTATION );
	float h1 = VAL( BASE_LENGTH );
	float h2 = VAL( LOWER_LENGTH );
	float h3 = VAL( UPPER_LENGTH );
	float pc = VAL( PARTICLE_COUNT );


	// This call takes care of a lot of the nasty projection
	// matrix stuff
	ModelerView::draw();

	static GLfloat lmodel_ambient[] = {0.4,0.4,0.4,1.0};

	// define the model

	ground(-0.2);

	base(0.8);

	glTranslatef( 0.0, 0.8, 0.0 );			// move to the top of the base
	glRotatef( theta, 0.0, 1.0, 0.0 );		// turn the whole assembly around the y-axis.
	rotation_base(h1);						// draw the rotation base

	glTranslatef( 0.0, h1, 0.0 );			// move to the top of the base
	glRotatef( phi, 0.0, 0.0, 1.0 );		// rotate around the z-axis for the lower arm
	glTranslatef( -0.1, 0.0, 0.4 );
	lower_arm(h2);							// draw the lower arm

	glTranslatef( 0.0, h2, 0.0 );			// move to the top of the lower arm
	glRotatef( psi, 0.0, 0.0, 1.0 );		// rotate  around z-axis for the upper arm
	upper_arm(h3);							// draw the upper arm

	glTranslatef( 0.0, h3, 0.0 );
	glRotatef( cr, 0.0, 0.0, 1.0 );
	claw(1.0);

	//** DON'T FORGET TO PUT THIS IN YOUR OWN CODE
	endDraw();
}

void ground(float h)
{
	glDisable(GL_LIGHTING);
	glColor3f(0.65,0.45,0.2);
	glPushMatrix();
	glScalef(30,0,30);
	y_box(h);
	glPopMatrix();
	glEnable(GL_LIGHTING);
}

void base(float h) {
	setDiffuseColor( 0.25, 0.25, 0.25 );
	setAmbientColor( 0.25, 0.25, 0.25 );
	glPushMatrix();
		glPushMatrix();
			glTranslatef(1.0, h / 2.0, 0.75);
			drawCylinder(0.25, h / 2.0, h / 2.0);
		glPopMatrix();
		glPushMatrix();
			glTranslatef(1.0, h / 2.0, -1.0);
			drawCylinder(0.25, h / 2.0, h / 2.0);
		glPopMatrix();
		glPushMatrix();
			glTranslatef(-1.0, h / 2.0, 0.75);
			drawCylinder(0.25, h / 2.0, h / 2.0);
		glPopMatrix();
		glPushMatrix();
			glTranslatef(-1.0, h / 2.0, -1.0);
			drawCylinder(0.25, h / 2.0, h / 2.0);
		glPopMatrix();
	glScalef(4.0f, h, 4.0f);
	y_box(1.0f);
	glPopMatrix();
}

void rotation_base(float h) {
	setDiffuseColor( 0.85, 0.75, 0.25 );
	setAmbientColor( 0.95, 0.75, 0.25 );
	glPushMatrix();
		glPushMatrix();
			glScalef(4.0, h, 4.0);
			y_box(1.0f); // the rotation base
		glPopMatrix();
		setDiffuseColor( 0.15, 0.15, 0.65 );
		setAmbientColor( 0.15, 0.15, 0.65 );
		glPushMatrix();
			glTranslatef(-0.5, h, -0.6);
			glScalef(2.0, h, 1.6);
			y_box(1.0f); // the console
		glPopMatrix();
		setDiffuseColor( 0.65, 0.65, 0.65 );
		setAmbientColor( 0.65, 0.65, 0.65 );
		glPushMatrix();
			glTranslatef( 0.5, h, 0.6 );
			glRotatef( -90.0, 1.0, 0.0, 0.0 );
			drawCylinder( h, 0.05, 0.05 ); // the pipe
		glPopMatrix();
	glPopMatrix();
}

void lower_arm(float h) {					// draw the lower arm
	setDiffuseColor( 0.85, 0.75, 0.25 );
	setAmbientColor( 0.95, 0.75, 0.25 );
	y_box(h);
}

void upper_arm(float h) {					// draw the upper arm
	setDiffuseColor( 0.85, 0.75, 0.25 );
	setAmbientColor( 0.95, 0.75, 0.25 );
	glPushMatrix();
	glScalef( 1.0, 1.0, 0.7 );
	y_box(h);
	glPopMatrix();
}

void claw(float h) {
	setDiffuseColor( 0.25, 0.25, 0.85 );
	setAmbientColor( 0.25, 0.25, 0.85 );

	glBegin( GL_TRIANGLES );

	glNormal3d( 0.0, 0.0, 1.0);		// +z side
	glVertex3d( 0.5, 0.0, 0.5);
	glVertex3d(-0.5, 0.0, 0.5);
	glVertex3d( 0.5,   h, 0.5);

	glNormal3d( 0.0, 0.0, -1.0);	// -z side
	glVertex3d( 0.5, 0.0, -0.5);
	glVertex3d(-0.5, 0.0, -0.5);
	glVertex3d( 0.5,   h, -0.5);

	glEnd();

	glBegin( GL_QUADS );

	glNormal3d( 1.0,  0.0,  0.0);	// +x side
	glVertex3d( 0.5, 0.0,-0.5);
	glVertex3d( 0.5, 0.0, 0.5);
	glVertex3d( 0.5,   h, 0.5);
	glVertex3d( 0.5,   h,-0.5);

	glNormal3d( 0.0,-1.0, 0.0);		// -y side
	glVertex3d( 0.5, 0.0, 0.5);
	glVertex3d( 0.5, 0.0,-0.5);
	glVertex3d(-0.5, 0.0,-0.5);
	glVertex3d(-0.5, 0.0, 0.5);

	glEnd();
}

void y_box(float h) {

	glBegin( GL_QUADS );

	glNormal3d( 1.0 ,0.0, 0.0);			// +x side
	glVertex3d( 0.25,0.0, 0.25);
	glVertex3d( 0.25,0.0,-0.25);
	glVertex3d( 0.25,  h,-0.25);
	glVertex3d( 0.25,  h, 0.25);

	glNormal3d( 0.0 ,0.0, -1.0);		// -z side
	glVertex3d( 0.25,0.0,-0.25);
	glVertex3d(-0.25,0.0,-0.25);
	glVertex3d(-0.25,  h,-0.25);
	glVertex3d( 0.25,  h,-0.25);

	glNormal3d(-1.0, 0.0, 0.0);			// -x side
	glVertex3d(-0.25,0.0,-0.25);
	glVertex3d(-0.25,0.0, 0.25);
	glVertex3d(-0.25,  h, 0.25);
	glVertex3d(-0.25,  h,-0.25);

	glNormal3d( 0.0, 0.0, 1.0);			// +z side
	glVertex3d(-0.25,0.0, 0.25);
	glVertex3d( 0.25,0.0, 0.25);
	glVertex3d( 0.25,  h, 0.25);
	glVertex3d(-0.25,  h, 0.25);

	glNormal3d( 0.0, 1.0, 0.0);			// top (+y)
	glVertex3d( 0.25,  h, 0.25);
	glVertex3d( 0.25,  h,-0.25);
	glVertex3d(-0.25,  h,-0.25);
	glVertex3d(-0.25,  h, 0.25);

	glNormal3d( 0.0,-1.0, 0.0);			// bottom (-y)
	glVertex3d( 0.25,0.0, 0.25);
	glVertex3d(-0.25,0.0, 0.25);
	glVertex3d(-0.25,0.0,-0.25);
	glVertex3d( 0.25,0.0,-0.25);

	glEnd();
}*/