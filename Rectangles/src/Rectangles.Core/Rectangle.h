#pragma once

#include "Point2D.h"

namespace SmokingGunInc_Rectangles
{
	// TODO [IMPROVE] More constructors could be created to improve the usability of the class:
	//  * A constructor that receives 4 valid coordinates on any order.
	//  * A constructor that receives the Top Left and Bottom Right Corners
	//  * A constructor that receives the Top and Bottom Left corners plus its width.
	//  * A constructor that receives the Top Left and Right corners plus its height.
	//  * Any combination of the above
	//  * Several implicit operators overrides to work with Tuples
	//  * Provide named method as alternative to implicit operators.
	//  * Provide implementation for the Equals and Distinct methods and operators to improve performance.

	/// <summary>
	/// Represents an axis-aligned rectangle defined by a location, a height and a width.
	/// </summary>
	class Rectangle
	{
	private:
		Point2D* location;
		float height;
		float width;
		Point2D* topLeftCorner;
		Point2D* topRightCorner;
		Point2D* bottomRightCorner;
		Point2D* bottomLeftCorner;
	public:
		/// <summary>
		/// Creates a new Rectangle given its location (top left corner), height and width.
		/// </summary>
		/// <param name="location">The location of the rectangle, determined by the coordinates of its top left corner.</param>
		/// <param name="height">The height of the rectangle, determined by the distance between its top side and its bottom side.</param>
		/// <param name="width">The width of the rectangle, determined by the distance between its left side and its right side.</param>
		/// <exception cref="std::invalid_argument height is smaller or equal than 0."></exception>
		/// <exception cref="std::invalid_argument width is smaller or equal than 0."></exception>
		Rectangle(Point2D* location, float height, float width);

		/// <summary>
		/// Creates a new Rectangle given its top left and bottom right corners.
		/// </summary>
		/// <param name="topLeftCorner">The top left corner of the rectangle.</param>
		/// <param name="bottomRightCorner">The bottom right corner of the rectangle.</param>
		/// <exception cref="std::invalid_argument bottomRightCorner is invalid"></exception>
		Rectangle(Point2D* topLeftCorner, Point2D* bottomRightCorner);

		/// <summary>
		/// Copy constructor to create a new Rectangle by value.
		/// </summary>
		/// <param name="rectangle">The Rectangle to copy by value.</param>
		Rectangle(const Rectangle& rectangle);

		/// <summary>
		/// Copy Assignment operator to assign a Rectangle by value.
		/// </summary>
		/// <param name="rectangle">The Rectangle to copy by value.</param>
		/// <returns>A copy of the given rectangle.</returns>
		Rectangle& operator= (const Rectangle& rectangle);

		/// <summary>
		/// Point of origin of the rectangle represented by TopLeftCorner.
		/// </summary>
		inline Point2D* GetLocation() { return location; }

		/// <summary>
		/// Height of the rectangle represented by the distance between BottomLeftCorner and Location.
		/// </summary>
		inline float GetHeight() { return height; }

		/// <summary>
		/// Width of the rectangle represented by the distance between TopLeftCorner and Location.
		/// </summary>
		inline float GetWidth() { return width; }

		/// <summary>
		/// Top Left Corner coordinate of the rectangle. Used to represent the rectangle Location.
		/// </summary>
		/// <remarks>
		/// By definition, contains the smallest coordinates among all corners.
		/// </remarks>
		inline Point2D* GetTopLeftCorner() { return topLeftCorner; }

		/// <summary>
		/// Top Right Corner coordinate of the rectangle. Located at X + Width and same Y units from Location.
		/// </summary>
		inline Point2D* GetTopRightCorner() { return topRightCorner; }

		/// <summary>
		/// Bottom Right Corner coordinate of the rectangle. Located at X + Width and Y + Height units from Location.
		/// </summary>
		inline Point2D* GetBottomRightCorner() { return bottomRightCorner; }

		/// <summary>
		/// Bottom Left Corner coordinate of the rectangle. Located at the same X and Y + Height units from Location.
		/// </summary>
		inline Point2D* GetBottomLeftCorner() { return bottomLeftCorner; }

		/// <summary>
		/// Determines if the provided point is contained within this Rectangle.
		/// If the point is contained in one of the Rectangle sides it is also considered as contained within it.
		/// </summary>
		/// <param name="point">A Point2D</param>
		/// <returns>
		/// true if point is located inside this Rectangle or on one of its sides. false otherwise.
		/// </returns>
		bool Contains(Point2D* point);

		/// <summary>
		/// Determines if the provided rectangle intersects with this Rectangle, including the sides.
		/// </summary>
		/// <remarks>
		/// Two rectangles are considered to intersect if there's a point that is contained on any of the two.
		/// </remarks>
		/// <param name="other">A Rectangle</param>
		/// <returns>
		/// true if the rectangles intersect, false otherwise.
		/// </returns>
		bool Intersects(Rectangle* other);

		/// <summary>
		/// Returns a string representation of the rectangle in the form { Location: (x;y), Height: ##, Width: ##, TopLeftCorner: (x;y), ...
		/// </summary>
		/// <returns>A string representation of the coordinate.</returns>
		std::wstring toString();
	};
}
