#include "pch.h"
#include "Point2D.h"
#include "Rectangle.h"
#include <stdexcept>

using namespace std;

namespace SmokingGunInc_Rectangles
{
	Rectangle::Rectangle(Point2D* location, float height, float width)
	{
		if (width <= 0)
		{
			throw invalid_argument("Width must be a positive number.");
		}

		if (height <= 0)
		{
			throw invalid_argument("Height must be a positive number.");
		}

		this->location = location;
		this->height = height;
		this->width = width;

		auto locationX = this->GetLocation()->GetX();
		auto locationY = this->GetLocation()->GetY();

		this->topLeftCorner = location;
		this->topRightCorner = new Point2D(locationX + width, locationY);
		this->bottomLeftCorner = new Point2D(locationX, locationY + height);
		this->bottomRightCorner = new Point2D(locationX + width, locationY + height);
	}

	Rectangle::Rectangle(Point2D* topLeftCorner, Point2D* bottomRightCorner)
		: Rectangle(topLeftCorner, bottomRightCorner->GetY() - topLeftCorner->GetY(), bottomRightCorner->GetX() - topLeftCorner->GetX()) {}

	Rectangle::Rectangle(const Rectangle& rectangle)
		: Rectangle(rectangle.location, rectangle.height, rectangle.width) {}

	Rectangle& Rectangle::operator= (const Rectangle& rectangle)
	{
		return *this;
	}

	bool Rectangle::Contains(Point2D* point)
	{
		return point->GetX() >= GetTopLeftCorner()->GetX()
			&& point->GetY() >= GetTopLeftCorner()->GetY()
			&& point->GetX() <= GetBottomRightCorner()->GetX()
			&& point->GetY() <= GetBottomRightCorner()->GetY();
	}

	bool Rectangle::Intersects(Rectangle* other)
	{
		return other->GetTopLeftCorner()->GetX() <= GetBottomRightCorner()->GetX()
			&& other->GetTopLeftCorner()->GetY() <= GetBottomRightCorner()->GetY()
			&& other->GetBottomRightCorner()->GetX() >= GetTopLeftCorner()->GetX()
			&& other->GetBottomRightCorner()->GetY() >= GetTopLeftCorner()->GetY();
	}

	wstring Rectangle::toString()
	{
		/// Returns a string representation of the rectangle in the form { Location: (x;y), Height: ##, Width: ##, TopLeftCorner: (x;y), ...
		auto location = L"Location: " + this->GetLocation()->toString();
		auto height = L"Height: " + to_wstring(this->GetHeight());
		auto width = L"Width: " + to_wstring(this->GetWidth());
		auto topLeftCorner = L"TopLeftCorner: " + this->GetTopLeftCorner()->toString();
		auto topRightCorner = L"TopRightCorner: " + this->GetTopRightCorner()->toString();
		auto bottomRightCorner = L"BottomRightCorner: " + this->GetBottomRightCorner()->toString();
		auto bottomLeftCorner = L"BottomLeftCorner: " + this->GetBottomLeftCorner()->toString();

		return location
			+ L", " + height
			+ L", " + width
			+ L", " + topLeftCorner
			+ L", " + topRightCorner
			+ L", " + bottomRightCorner
			+ L", " + bottomLeftCorner;
	}
}
