#pragma once

#include <map>
#include <Point2D.h>
#include <Rectangle.h>
#include <string>

namespace SmokingGunInc_Rectangles
{
	class RectanglesApp {
	private:
		map<string, Rectangle*> Rectangles;

		void createRectangle();
		void buildRectangleByCoordinates(string name, string topLeftCornerSection, string bottomRightCornerSection);
		void buildRectangleByLocation(string name, string locationSection, string heightSection, string widthSection);
		void printRectangles();
		void checkContainsPoint();
		void checkIntersects();
		void resetRectangles();
		bool tryParseCoordinate(string coordinatesSection, Point2D** point);
		vector<string> split(const string& str, const char delim);
	public:
		void run();
	};
}