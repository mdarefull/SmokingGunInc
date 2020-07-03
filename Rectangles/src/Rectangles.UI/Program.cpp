
#include <iostream>
#include <map>
#include <Point2D.h>
#include <Rectangle.h>
#include <string>
#include<vector>

using namespace SmokingGunInc_Rectangles;

using namespace std;


map<wstring, Rectangle*> Rectangles = {};
void createRectangle();
void buildRectangleByCoordinates(wstring name, wstring topLeftCornerSection, wstring bottomRightCornerSection);
void buildRectangleByLocation(wstring name, wstring locationSection, wstring heightSection, wstring widthSection);
void printRectangles();
void checkContainsPoint();
void checkIntersects();
void resetRectangles();
bool tryParseCoordinate(wstring coordinatesSection, Point2D** point);
vector<wstring> split(const wstring& str, const char delim);

int main()
{
	wcout  << "Welcome to the Rectangles Game Program...\r\n";
	wcout  << "Your options are:\r\n";
	wcout  << "0: Create a new rectangle.\r\n";
	wcout  << "1: Print the list of existing rectangles.\r\n";
	wcout  << "2: Reset the list of rectangles.\r\n";
	wcout  << "3: Determine if an existing rectangle contains a given point.\r\n";
	wcout  << "4: Determine if 2 existing rectangles intersect with each other.\r\n";

	while (true)
	{
		try
		{
			wcout  << "--------------------------------------------------------------------------\r\n\r\n";
			wcout  << "Select your option: ";

			wstring line;
			getline(wcin, line);

			int option;
			try
			{
				option = stoi(line);
			}
			catch (exception)
			{
				wcout  << "Invalid option! Try again!\r\n";
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
				wcout  << "Option value: \"" << option << "\" not supported. Try again!\r\n";
			}
		}
		catch (exception)
		{
			wcout  << "Oops! An unexpected error occurred :(. Please be nicer next time ;)\r\n";
		}
	}

	return 0;
}

void createRectangle()
{
	wcout  << "Enter the new rectangle as in: \"name x;y height width\" OR \"name x1;y1 x2;y2\"\r\n";
	wcout  << "Example: myNewRectangle 10;10 20.2;20.5\r\n";
	wcout  << "Enter your value: ";

	wstring line;
	getline(wcin, line);

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
		wcout  << "Invalid definition. A rectangle definition must have exactly 3 or 4 space separated sections. Try again!\r\n";
		break;
	}
}
void buildRectangleByCoordinates(wstring name, wstring topLeftCornerSection, wstring bottomRightCornerSection)
{
	Point2D* topLeftCorner;
	if (!tryParseCoordinate(topLeftCornerSection, &topLeftCorner))
	{
		wcout  << "Invalid definition. The top left corner coordinates must be in the form of \"x;y\" where both values are valid float number. Try again!\r\n";
		return;
	}

	Point2D* bottomRightCorner;
	if (!tryParseCoordinate(bottomRightCornerSection, &bottomRightCorner))
	{
		wcout  << "Invalid definition. The bottom right corner coordinates must be in the form of \"x;y\" where both values are valid float number. Try again!\r\n";
		return;
	}

	try
	{
		auto rectangle = new Rectangle(topLeftCorner, bottomRightCorner);
		Rectangles[name] = rectangle;
		wcout << "Rectangle Successfully created:\r\n";
		wcout << "Name: " << name << " - Rectangle: { " << rectangle->toString() << " }\r\n";
	}
	catch (invalid_argument ex)
	{
		wcout  << "Invalid rectangle definition \"" << ex.what() << "\". Try again!\r\n";
	}
}
void buildRectangleByLocation(wstring name, wstring locationSection, wstring heightSection, wstring widthSection)
{
	Point2D* location;
	if (!tryParseCoordinate(locationSection, &location))
	{
		wcout  << "Invalid definition. The location coordinates must be in the form of \"x;y\" where both values are valid float number. Try again!\r\n";
		return;
	}

	float height;
	try
	{
		height = stof(heightSection);
	}
	catch (exception)
	{
		wcout  << "Invalid definition. The height section must be a valid float number. Try again!\r\n";
		return;
	}

	float width;
	try
	{
		width = stof(widthSection);
	}
	catch (exception)
	{
		wcout  << "Invalid definition. The width section must be a valid float number. Try again!\r\n";
		return;
	}

	try
	{
		auto rectangle = new Rectangle(location, height, width);
		wcout  << "Rectangle Successfully created:\r\n";
		wcout  << "Name: " << name << " - Rectangle: { " << rectangle->toString() << " }\r\n";
	}
	catch (invalid_argument ex)
	{
		wcout  << "Invalid rectangle definition \"" << ex.what() << "\". Try again!\r\n";
	}
}

void printRectangles()
{
	for (map<wstring, Rectangle*>::iterator it = Rectangles.begin(); it != Rectangles.end(); it++)
	{
		wcout  << it->first << " = " << it->second->toString() << "\r\n";
	}
}

void checkContainsPoint()
{
	wcout  << "Enter an existing rectangle name and a new point as in: \"name x;y\"\r\n";
	wcout  << "Example: existingRectangle 15;15\r\n";
	wcout  << "Enter your value: ";

	wstring line;
	getline(wcin, line);

	auto items = split(line, ' ');
	if (items.size() != 2)
	{
		wcout  << "Invalid instruction. A valid instruction must have exactly 2 space separated sections. Try again!\r\n";
		return;
	}

	auto it = Rectangles.find(items[0]);
	if (it == Rectangles.end())
	{
		wcout  << "Invalid instruction. The specified rectangle doesn't exist. Create it first!\r\n";
	}
	auto rectangle = it->second;

	Point2D* point;
	if (!tryParseCoordinate(items[1], &point))
	{
		wcout  << "Invalid instruction. The point coordinates must be in the form of \"x;y\" where both values are valid float number. Try again!\r\n";
		return;
	}

	wcout  << "The point is " << (rectangle->Contains(point) ? "" : "NOT ") << "contained in the rectangle!\r\n";
}

void checkIntersects()
{
	wcout  << "Enter two existing rectangle names as in: \"name1 name2\"\r\n";
	wcout  << "Example: existingRectangleA existingRectangleB\r\n";
	wcout  << "Enter your value: ";

	wstring line;
	getline(wcin, line);

	auto items = split(line, ' ');
	if (items.size() != 2)
	{
		wcout  << "Invalid instruction. A valid instruction must have exactly 2 space separated sections. Try again!\r\n";
		return;
	}

	auto it = Rectangles.find(items[0]);
	if (it == Rectangles.end())
	{
		wcout  << "Invalid instruction. The first specified rectangle doesn't exist. Create it first!\r\n";
	}
	auto rectangleA = it->second;

	it = Rectangles.find(items[1]);
	if (it == Rectangles.end())
	{
		wcout  << "Invalid instruction. The second specified rectangle doesn't exist. Create it first!\r\n";
	}
	auto rectangleB = it->second;

	wcout  << "The provided rectangles " << (rectangleA->Intersects(rectangleB) ? "" : "DO NOT ") << "intersect!\r\n";
}

void resetRectangles()
{
	auto _ = Rectangles.empty();
}

bool tryParseCoordinate(wstring coordinatesSection, Point2D** point)
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
vector<wstring> split(const wstring& str, const char delim)
{
	vector<wstring> tokens;
	size_t prev = 0;

	auto pos = str.find(delim);
	while (prev <= str.length())
	{
		if (pos == wstring::npos) {
			pos = str.length();
		}

		auto token = str.substr(prev, pos - prev);
		tokens.push_back(token);

		prev = pos + 1;
		pos = str.find(delim, prev);
	}
	return tokens;
}
