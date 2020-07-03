#include "pch.h"
#include "Point2D.h"

using namespace std;

namespace SmokingGunInc_Rectangles
{
	Point2D::Point2D(float x, float y)
		: x(x), y(y) {}

	wstring Point2D::toString()
	{
		auto x = to_wstring(this->GetX());
		auto y = to_wstring(this->GetY());
		return L"(" + x + L";" + y + L")";
	}
}
