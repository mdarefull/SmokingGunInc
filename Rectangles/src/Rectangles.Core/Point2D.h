#pragma once
#include <string>

namespace SmokingGunInc_Rectangles
{
	/// <summary>
	/// Represents a two-dimensional point.
	/// </summary>
	class Point2D
	{
	private:
		float x{ 0 };
		float y{ 0 };

	public:
		/// <summary>
		/// Creates a new Point2D represented by the provided two-dimensional coordinates.
		/// </summary>
		/// <param name="x">Point coordinate on the x-axis.</param>
		/// <param name="y">Point coordinate on the y-axis.</param>
		Point2D(float x, float y);

		/// <summary>
		/// Point coordinate on the x-axis.
		/// </summary>
		inline float GetX() { return x; }

		/// <summary>
		/// Point coordinate on the y-axis.
		/// </summary>
		inline float GetY() { return y; }

		/// <summary>
		/// Returns a string representation of the coordinate in the form of (x;y)
		/// </summary>
		/// <returns>A string representation of the coordinate.</returns>
		std::wstring toString();
	};
}