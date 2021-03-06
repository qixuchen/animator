#include "BezierCurveEvaluator.h"
#include <assert.h>
#include "mat.h"
#include "vec.h"
#include <cmath>

void BezierCurveEvaluator::evaluateCurve(const std::vector<Point>& ptvCtrlPts,
	std::vector<Point>& ptvEvaluatedCurvePts,
	const float& fAniLength,
	const bool& bWrap) const
{
	int iCtrlPtCount = ptvCtrlPts.size();
	ptvEvaluatedCurvePts.clear();

	for (int i = 0; i < (iCtrlPtCount-1) / 3; ++i) {
		Point v0, v1, v2, v3;
		v0 = ptvCtrlPts[3*i];
		v1 = ptvCtrlPts[3*i + 1];
		v2 = ptvCtrlPts[3*i + 2];
		v3 = ptvCtrlPts[3*i + 3];


		Mat4f B(-1, 3, -3, 1,
			    3, -6, 3, 0,
				-3, 3, 0, 0,
			    1, 0, 0, 0);
		Vec4f X(v0.x, v1.x, v2.x, v3.x);
		Vec4f Y(v0.y, v1.y, v2.y, v3.y);
;		for (float j = 0; j <= 1; j += 1.0 / 20) {
			Vec4f T(pow(j, 3.0), pow(j, 2.0), j, 1);
			float x = T * B * X;
			float y = T * B * Y;
			ptvEvaluatedCurvePts.push_back(Point(x, y));
		}

	}
	// This part deals with wrap
	if (!bWrap) {
		for (int i = 3 * ((iCtrlPtCount - 1) / 3); i < iCtrlPtCount; i++) {
			ptvEvaluatedCurvePts.push_back(Point(ptvCtrlPts[i].x, ptvCtrlPts[i].y));
		}

		float x = 0.0;
		float y1 = ptvCtrlPts[0].y;
		ptvEvaluatedCurvePts.push_back(Point(x, y1));

		x = fAniLength;
		float y2 = ptvCtrlPts[iCtrlPtCount - 1].y;

		ptvEvaluatedCurvePts.push_back(Point(x, y2));
	}
	else { // wrap enabled
		if (iCtrlPtCount % 3 != 0) {

			for (int i = 3 * ((iCtrlPtCount - 1) / 3); i < iCtrlPtCount; i++) { // the points remaining are not enough to form a bezier curve
				ptvEvaluatedCurvePts.push_back(Point(ptvCtrlPts[i].x, ptvCtrlPts[i].y));
			}

			float x = 0.0;
			float y1 = (ptvCtrlPts[0].y * (fAniLength - ptvCtrlPts[iCtrlPtCount - 1].x) +
					ptvCtrlPts[iCtrlPtCount - 1].y * ptvCtrlPts[0].x) /
					(ptvCtrlPts[0].x + fAniLength - ptvCtrlPts[iCtrlPtCount - 1].x);
			ptvEvaluatedCurvePts.push_back(Point(x, y1));

			x = fAniLength;
			float y2 = y1;

			ptvEvaluatedCurvePts.push_back(Point(x, y2));
		}
		else {
			Mat4f B(-1, 3, -3, 1,
				3, -6, 3, 0,
				-3, 3, 0, 0,
				1, 0, 0, 0);
			//right side

			Point v0, v1, v2, v3;
			v0 = ptvCtrlPts[iCtrlPtCount-3];
			v1 = ptvCtrlPts[iCtrlPtCount-2];
			v2 = ptvCtrlPts[iCtrlPtCount-1];
			v3 = ptvCtrlPts[0];
			v3.x += fAniLength;

			Vec4f X(v0.x, v1.x, v2.x, v3.x);
			Vec4f Y(v0.y, v1.y, v2.y, v3.y);
			for (float j = 0; j <= 1; j += 1.0 / 20) {
				Vec4f T(pow(j, 3.0), pow(j, 2.0), j, 1);
				float x = T * B * X;
				float y = T * B * Y;
				ptvEvaluatedCurvePts.push_back(Point(x, y));
			}

			//left side
			v0 = ptvCtrlPts[iCtrlPtCount - 3];
			v1 = ptvCtrlPts[iCtrlPtCount - 2];
			v2 = ptvCtrlPts[iCtrlPtCount - 1];
			v3 = ptvCtrlPts[0];
			v0.x -= fAniLength;
			v1.x -= fAniLength;
			v2.x -= fAniLength;

			X = Vec4f(v0.x, v1.x, v2.x, v3.x);
			Y = Vec4f(v0.y, v1.y, v2.y, v3.y);
			for (float j = 0; j <= 1; j += 1.0 / 20) {
				Vec4f T(pow(j, 3.0), pow(j, 2.0), j, 1);
				float x = T * B * X;
				float y = T * B * Y;
				ptvEvaluatedCurvePts.push_back(Point(x, y));
			}
		}
	}
}
