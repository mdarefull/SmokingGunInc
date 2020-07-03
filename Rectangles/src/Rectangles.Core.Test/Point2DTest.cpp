#include "pch.h"
#include "CppUnitTest.h"

#include <Point2D.h>
using namespace std;

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace SmokingGunInc_Rectangles
{
	

	TEST_CLASS(Point2DTest)
	{
	public:

		TEST_METHOD(ConstructorByCoordinates_InstantiatesNewPoint)
		{
			struct testData
			{
				float x;
				float y;

				testData(float x, float y)
					: x(x), y(y) {}
			} data[] =
			{
				testData(0.f, 0.f),
				testData(1.f, 2.f),
				testData(1.2f, 2.f),
				testData(2.f, 1.5f),
				testData(-0.8f, -3.4f),
			};
			for (size_t i = 0; i < 5; i++)
			{
				// Arrange
				auto test = data[i];
				auto x = test.x;
				auto y = test.y;

				// Act
				auto subject = new Point2D(x, y);

				// Assert
				Assert::AreEqual(x, subject->GetX());
				Assert::AreEqual(y, subject->GetY());
			}
		}

		TEST_METHOD(ToString_ReturnsExpected)
		{
			// Arrange
			auto x = 10.5f;
			auto y = -0.034f;

			wstring expected = L"(10.500000;-0.034000)";

			auto subject = new Point2D(x, y);

			// Act
			auto actual = subject->toString();

			// Assert
			Assert::AreEqual(expected, actual);
		}
	};
}
