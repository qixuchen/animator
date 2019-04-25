#include "CatmullromCurveEvaluator.h"
#include <assert.h>
#include "Mat.h"
#include "Vec.h"

void CatmullromCurveEvaluator::evaluateCurve(const std::vector<Point>& ptvCtrlPts,
	std::vector<Point>& ptvEvaluatedCurvePts,
	const float& fAniLength,
	const bool& bWrap) const
{
	float epsilon = 0.00001f;
	int iCtrlPtCount = ptvCtrlPts.size();
	ptvEvaluatedCurvePts.clear();

	if (!bWrap) {// wrap disabled

		//create a new vector ,add one more points at begin and end as control points
		std::vector<Point> catmullrom;
		catmullrom.assign(ptvCtrlPts.begin(), ptvCtrlPts.end());
		catmullrom.insert(catmullrom.begin(), Point(0, ptvCtrlPts[0].y));
		catmullrom.push_back(Point(fAniLength, ptvCtrlPts[iCtrlPtCount - 1].y));

		float inc = -1.0; //note catmullrom does not guarantee incremental x, use this variable to only return incremental x
		for (int i = 0; i <= (catmullrom.size() - 4); ++i) {
			Point v0, v1, v2, v3;
			v0 = catmullrom[i];
			v1 = catmullrom[i + 1];
			v2 = catmullrom[i + 2];
			v3 = catmullrom[i + 3];


			Mat4f B(-1, 3, -3, 1,
				2, -5, 4, -1,
				-1, 0, 1, 0,
				0, 2, 0, 0);
			Vec4f X(v0.x, v1.x, v2.x, v3.x);
			Vec4f Y(v0.y, v1.y, v2.y, v3.y);
			for (float j = 0; j <= 1.0 + epsilon; j += 1.0 / 20) {
				Vec4f T(pow(j, 3.0), pow(j, 2.0), j, 1);
				float x = T * (1.0 / 2) * B * X;
				float y = T * (1.0 / 2) * B * Y;
				if ( x>inc && x< v2.x) {
					inc = x;
					ptvEvaluatedCurvePts.push_back(Point(x, y));
				}

			}
			ptvEvaluatedCurvePts.push_back(Point(v2.x, v2.y));

		}
		ptvEvaluatedCurvePts.push_back(Point(0, ptvCtrlPts[0].y));
		ptvEvaluatedCurvePts.push_back(Point(fAniLength, ptvCtrlPts[iCtrlPtCount - 1].y));

	}
	else {
		//create a new vector ,add two more points at begin and end respectively as control points
		std::vector<Point> catmullrom;
		catmullrom.assign(ptvCtrlPts.begin(), ptvCtrlPts.end());
		catmullrom.insert(catmullrom.begin(), Point(ptvCtrlPts[iCtrlPtCount - 1].x - fAniLength, ptvCtrlPts[iCtrlPtCount - 1].y));
		catmullrom.insert(catmullrom.begin(), Point(ptvCtrlPts[iCtrlPtCount - 2].x - fAniLength, ptvCtrlPts[iCtrlPtCount - 2].y));
		catmullrom.push_back(Point(ptvCtrlPts[0].x + fAniLength, ptvCtrlPts[0].y));
		catmullrom.push_back(Point(ptvCtrlPts[1].x + fAniLength, ptvCtrlPts[1].y));

		float inc = -1.0;

		for (int i = 0; i <= (catmullrom.size() - 4); ++i) {
			Point v0, v1, v2, v3;
			v0 = catmullrom[i];
			v1 = catmullrom[i + 1];
			v2 = catmullrom[i + 2];
			v3 = catmullrom[i + 3];


			Mat4f B(-1, 3, -3, 1,
				2, -5, 4, -1,
				-1, 0, 1, 0,
				0, 2, 0, 0);
			Vec4f X(v0.x, v1.x, v2.x, v3.x);
			Vec4f Y(v0.y, v1.y, v2.y, v3.y);
			for (float j = 0; j <= 1.0 + epsilon; j += 1.0 / 20) {
				Vec4f T(pow(j, 3.0), pow(j, 2.0), j, 1);
				float x = T * (1.0 / 2) * B * X;
				float y = T * (1.0 / 2) * B * Y;
				if (x > inc && x < v2.x) {
					inc = x;
					ptvEvaluatedCurvePts.push_back(Point(x, y));
				}

			}
			ptvEvaluatedCurvePts.push_back(Point(v2.x, v2.y));

		}
	}
}
