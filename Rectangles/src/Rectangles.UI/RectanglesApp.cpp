#include "RectanglesApp.h"

#include <iostream>
#include <map>
#include <Point2D.h>
#include <Rectangle.h>
#include <string>
#include<vector>

using namespace std;

namespace SmokingGunInc_Rectangles
{
	void RectanglesApp::run() {
		cout << "Welcome to the Rectangles Game Program...\r\n";
		cout << "Your options are:\r\n";
		cout << "0: Create a new rectangle.\r\n";
		cout << "1: Print the list of existing rectangles.\r\n";
		cout << "2: Reset the list of rectangles.\r\n";
		cout << "3: Determine if an existing rectangle contains a given point.\r\n";
		cout << "4: Determine if 2 existing rectangles intersect with each other.\r\n";

		while (true)
		{
			try
			{
				cout << "--------------------------------------------------------------------------\r\n\r\n";
				cout << "Select your option: ";

				string line;
				cin >> line;

				int option;
				try
				{
					option = stoi(line);
				}
				catch (exception)
				{
					cout << "Invalid option! Try again!\r\n";
					continue;
				}

				switch (option)
				{
				case 0:
					createRectangle();
					break;
				case 1:
					printRectangles();
					break;
				case 2:
					resetRectangles();
					break;
				case 3:
					checkContainsPoint();
					break;
				case 4:
					checkIntersects();
					break;
				default:
					cout << "Option value: \"" << option << "\" not supported. Try again!\r\n";
				}
			}
			catch (exception)
			{
				cout << "Oops! An unexpected error occurred :(. Please be nicer next time ;)\r\n";
			}
		}
	}

	void RectanglesApp::createRectangle()
	{
		cout << "Enter the new rectangle as in: \"name x;y height width\" OR \"name x1;y1 x2;y2\"\r\n";
		cout << "Example: myNewRectangle 10;10 20.2;20.5\r\n";
		cout << "Enter your value: ";

		string line;
		cin >> line;

		auto items = split(line, ' ');

		switch (items.size())
		{
		case 3:
			buildRectangleByCoordinates(items[0], items[1], items[2]);
			break;
		case 4:
			buildRectangleByLocation(items[0], items[1], items[2], items[3]);
			break;
		default:
			cout << "Invalid definition. A rectangle definition must have exactly 3 or 4 space separated sections. Try again!\r\n";
			break;
		}
	}
	void RectanglesApp::buildRectangleByCoordinates(string name, string topLeftCornerSection, string bottomRightCornerSection)
	{
		Point2D* topLeftCorner;
		if (!tryParseCoordinate(topLeftCornerSection, &topLeftCorner))
		{
			cout << "Invalid definition. The top left corner coordinates must be in the form of \"x;y\" where both values are valid float number. Try again!\r\n";
			return;
		}

		Point2D* bottomRightCorner;
		if (!tryParseCoordinate(bottomRightCornerSection, &bottomRightCorner))
		{
			cout << "Invalid definition. The bottom right corner coordinates must be in the form of \"x;y\" where both values are valid float number. Try again!\r\n";
			return;
		}

		try
		{
			auto rectangle = new Rectangle(topLeftCorner, bottomRightCorner);
			Rectangles[name] = rectangle;
			cout << "Rectangle Successfully created:\r\n";
			cout << "Name: " << name << " - Rectangle: { " << rectangle->toString() << " }\r\n";
		}
		catch (invalid_argument ex)
		{
			cout << "Invalid rectangle definition \"" << ex.what() << "\". Try again!\r\n";
		}
	}
	void RectanglesApp::buildRectangleByLocation(string name, string locationSection, string heightSection, string widthSection)
	{
		Point2D* location;
		if (!tryParseCoordinate(locationSection, &location))
		{
			cout << "Invalid definition. The location coordinates must be in the form of \"x;y\" where both values are valid float number. Try again!\r\n";
			return;
		}

		float height;
		try
		{
			height = stof(heightSection);
		}
		catch (exception)
		{
			cout << "Invalid definition. The height section must be a valid float number. Try again!\r\n";
			return;
		}

		float width;
		try
		{
			width = stof(widthSection);
		}
		catch (exception)
		{
			cout << "Invalid definition. The width section must be a valid float number. Try again!\r\n";
			return;
		}

		try
		{
			auto rectangle = new Rectangle(location, height, width);
			cout << "Rectangle Successfully created:\r\n";
			cout << "Name: " << name << " - Rectangle: { " << rectangle->toString() << " }\r\n";
		}
		catch (invalid_argument ex)
		{
			cout << "Invalid rectangle definition \"" << ex.what() << "\". Try again!\r\n";
		}
	}

	void RectanglesApp::printRectangles()
	{
		for (map<string, Rectangle*>::iterator it = Rectangles.begin(); it != Rectangles.end(); it++)
		{
			cout << it->first << " = " << it->second->toString() << "\r\n";
		}
	}

	void RectanglesApp::checkContainsPoint()
	{
		cout << "Enter an existing rectangle name and a new point as in: \"name x;y\"\r\n";
		cout << "Example: existingRectangle 15;15\r\n";
		cout << "Enter your value: ";

		string line;
		cin >> line;

		auto items = split(line, ' ');
		if (items.size() != 2)
		{
			cout << "Invalid instruction. A valid instruction must have exactly 2 space separated sections. Try again!\r\n";
			return;
		}

		auto it = Rectangles.find(items[0]);
		if (it == Rectangles.end())
		{
			cout << "Invalid instruction. The specified rectangle doesn't exist. Create it first!\r\n";
		}
		auto rectangle = it->second;

		Point2D* point;
		if (!tryParseCoordinate(items[1], &point))
		{
			cout << "Invalid instruction. The point coordinates must be in the form of \"x;y\" where both values are valid float number. Try again!\r\n";
			return;
		}

		cout << "The point is " << (rectangle->Contains(point) ? "" : "NOT ") << "contained in the rectangle!\r\n";
	}

	void RectanglesApp::checkIntersects()
	{
		cout << "Enter two existing rectangle names as in: \"name1 name2\"\r\n";
		cout << "Example: existingRectangleA existingRectangleB\r\n";
		cout << "Enter your value: ";

		string line;
		cin >> line;

		auto items = split(line, ' ');
		if (items.size() != 2)
		{
			cout << "Invalid instruction. A valid instruction must have exactly 2 space separated sections. Try again!\r\n";
			return;
		}

		auto it = Rectangles.find(items[0]);
		if (it == Rectangles.end())
		{
			cout << "Invalid instruction. The first specified rectangle doesn't exist. Create it first!\r\n";
		}
		auto rectangleA = it->second;

		it = Rectangles.find(items[1]);
		if (it == Rectangles.end())
		{
			cout << "Invalid instruction. The second specified rectangle doesn't exist. Create it first!\r\n";
		}
		auto rectangleB = it->second;

		cout << "The provided rectangles " << (rectangleA->Intersects(rectangleB) ? "" : "DO NOT ") << "intersect!\r\n";
	}

	void RectanglesApp::resetRectangles()
	{
		Rectangles.empty();
	}

	bool RectanglesApp::tryParseCoordinate(string coordinatesSection, Point2D** point)
	{
		auto coordinatesValues = split(coordinatesSection, ';');
		if (coordinatesValues.size() != 2)
		{
			return false;
		}

		float x;
		float y;
		try
		{
			x = stof(coordinatesValues[0]);
			y = stof(coordinatesValues[1]);
		}
		catch (exception)
		{
			return false;
		}

		*point = new Point2D(x, y);
		return true;
	}
	vector<string> RectanglesApp::split(const string& str, const char delim)
	{
		vector<string> tokens;
		size_t prev = 0;

		auto pos = str.find(delim, prev);
		while (pos != string::npos)
		{
			auto token = str.substr(prev, pos - prev);
			tokens.push_back(token);

			prev = pos + 1;
			pos = str.find(delim, prev);
		}
		return tokens;
	}
}
