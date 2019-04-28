#include "BSplineCurveEvaluator.h"
#include <assert.h>
#include "Mat.h"
#include "Vec.h"

void BSplineCurveEvaluator::evaluateCurve(const std::vector<Point>& ptvCtrlPts,
	std::vector<Point>& ptvEvaluatedCurvePts,
	const float& fAniLength,
	const bool& bWrap) const
{
	int iCtrlPtCount = ptvCtrlPts.size();
	ptvEvaluatedCurvePts.clear();

	for (int i = 0; i <= (iCtrlPtCount - 4); ++i) {
		Point v0, v1, v2, v3;
		v0 = ptvCtrlPts[i];
		v1 = ptvCtrlPts[i + 1];
		v2 = ptvCtrlPts[i + 2];
		v3 = ptvCtrlPts[i + 3];


		Mat4f B(-1, 3, -3, 1,
			3, -6, 3, 0,
			-3, 0, 3, 0,
			1, 4, 1, 0);
		Vec4f X(v0.x, v1.x, v2.x, v3.x);
		Vec4f Y(v0.y, v1.y, v2.y, v3.y);
		for (float j = 0; j <= 1; j += 1.0 / 20) {
			Vec4f T(pow(j, 3.0), pow(j, 2.0), j, 1);
			float x = T * (1.0 / 6) * B * X;
			float y = T * (1.0 / 6) * B * Y;
			ptvEvaluatedCurvePts.push_back(Point(x, y));
		}

	}

	if (!bWrap) { // Wrap disabled
		ptvEvaluatedCurvePts.push_back(Point(0, ptvCtrlPts[0].y));
		ptvEvaluatedCurvePts.push_back(Point(fAniLength, ptvCtrlPts[iCtrlPtCount - 1].y));
	}
	else { // wrap enabled
		Mat4f B(-1, 3, -3, 1,
				3, -6, 3, 0,
				-3, 0, 3, 0,
				1, 4, 1, 0);
		Vec4f X,Y;

		//right side
		Point v0, v1, v2, v3;
		if (iCtrlPtCount >= 3) {
			v0 = ptvCtrlPts[iCtrlPtCount - 3];
			v1 = ptvCtrlPts[iCtrlPtCount - 2];
			v2 = ptvCtrlPts[iCtrlPtCount - 1];
			v3 = ptvCtrlPts[0];
			v3.x += fAniLength;

			X = Vec4f(v0.x, v1.x, v2.x, v3.x);
			Y = Vec4f(v0.y, v1.y, v2.y, v3.y);
			for (float j = 0; j <= 1; j += 1.0 / 20) {
				Vec4f T(pow(j, 3.0), pow(j, 2.0), j, 1);
				float x = T * (1.0 / 6) * B * X;
				float y = T * (1.0 / 6) * B * Y;
				ptvEvaluatedCurvePts.push_back(Point(x, y));
			}
		}
		v0 = ptvCtrlPts[iCtrlPtCount - 2];
		v1 = ptvCtrlPts[iCtrlPtCount - 1];
		v2 = ptvCtrlPts[0];
		v3 = ptvCtrlPts[1];
		v2.x += fAniLength;
		v3.x += fAniLength;

		X = Vec4f(v0.x, v1.x, v2.x, v3.x);
		Y = Vec4f(v0.y, v1.y, v2.y, v3.y);
		for (float j = 0; j <= 1; j += 1.0 / 20) {
			Vec4f T(pow(j, 3.0), pow(j, 2.0), j, 1);
			float x = T * (1.0 / 6) * B * X;
			float y = T * (1.0 / 6) * B * Y;
			ptvEvaluatedCurvePts.push_back(Point(x, y));
		}


		//left side
		if (iCtrlPtCount >= 3) {
			v0 = ptvCtrlPts[iCtrlPtCount - 1];
			v1 = ptvCtrlPts[0];
			v2 = ptvCtrlPts[1];
			v3 = ptvCtrlPts[2];
			v0.x -= fAniLength;

			X = Vec4f(v0.x, v1.x, v2.x, v3.x);
			Y = Vec4f(v0.y, v1.y, v2.y, v3.y);
			for (float j = 0; j <= 1; j += 1.0 / 20) {
				Vec4f T(pow(j, 3.0), pow(j, 2.0), j, 1);
				float x = T * (1.0 / 6) * B * X;
				float y = T * (1.0 / 6) * B * Y;
				ptvEvaluatedCurvePts.push_back(Point(x, y));
			}
		}

		v0 = ptvCtrlPts[iCtrlPtCount - 2];
		v1 = ptvCtrlPts[iCtrlPtCount - 1];
		v2 = ptvCtrlPts[0];
		v3 = ptvCtrlPts[1];
		v0.x -= fAniLength;
		v1.x -= fAniLength;

		X = Vec4f(v0.x, v1.x, v2.x, v3.x);
		Y = Vec4f(v0.y, v1.y, v2.y, v3.y);
		for (float j = 0; j <= 1; j += 1.0 / 20) {
			Vec4f T(pow(j, 3.0), pow(j, 2.0), j, 1);
			float x = T * (1.0 / 6) * B * X;
			float y = T * (1.0 / 6) * B * Y;
			ptvEvaluatedCurvePts.push_back(Point(x, y));
		}

		if (iCtrlPtCount == 2) {
			v0 = ptvCtrlPts[1];
			v1 = ptvCtrlPts[0];
			v2 = ptvCtrlPts[1];
			v3 = ptvCtrlPts[0];
			v0.x -= fAniLength;
			v3.x += fAniLength;

			X = Vec4f(v0.x, v1.x, v2.x, v3.x);
			Y = Vec4f(v0.y, v1.y, v2.y, v3.y);
			for (float j = 0; j <= 1; j += 1.0 / 20) {
				Vec4f T(pow(j, 3.0), pow(j, 2.0), j, 1);
				float x = T * (1.0 / 6) * B * X;
				float y = T * (1.0 / 6) * B * Y;
				ptvEvaluatedCurvePts.push_back(Point(x, y));
			}
		}
	}
}
