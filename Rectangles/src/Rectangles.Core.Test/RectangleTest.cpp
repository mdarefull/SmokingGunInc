#include "pch.h"
#include "CppUnitTest.h"

#include <Point2D.h>
#include <Rectangle.h>
using namespace SmokingGunInc_Rectangles;

using namespace std;

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace SmokingGunInc_Rectangles
{
	void assertEquals(Point2D* expected, Point2D* actual)
	{
		Assert::AreEqual(expected->GetX(), actual->GetX());
		Assert::AreEqual(expected->GetY(), actual->GetY());
	}
	void assertEquivalents(Rectangle* expected, Rectangle* actual)
	{
		assertEquals(expected->GetLocation(), actual->GetLocation());
		assertEquals(expected->GetTopLeftCorner(), actual->GetTopLeftCorner());
		Assert::AreEqual(expected->GetHeight(), actual->GetHeight());
		Assert::AreEqual(expected->GetWidth(), actual->GetWidth());
		assertEquals(expected->GetTopRightCorner(), actual->GetTopRightCorner());
		assertEquals(expected->GetBottomRightCorner(), actual->GetBottomRightCorner());
		assertEquals(expected->GetBottomLeftCorner(), actual->GetBottomLeftCorner());
	}

	TEST_CLASS(RectangleTest)
	{
	public:

#pragma region Constructor
		TEST_METHOD(ConstructorByLocationHeightAndWidth_InstantiatesNewRectangle)
		{
			struct testData
			{
				Point2D* location;
				float height;
				float width;

				testData(Point2D* location, float height, float width)
					: location(location), height(height), width(width) {}
			} data[] =
			{
				testData(new Point2D(0.f, 0.f), 1.f, 1.f),
				testData(new Point2D(1.f, 2.f), 0.5f, 3.f),
				testData(new Point2D(1.2f, 2.f), 10.f, 0.8f),
			};
			for (size_t i = 0; i < 3; i++)
			{
				// Arrange
				auto test = data[i];
				auto location = test.location;
				auto height = test.height;
				auto width = test.width;

				auto expectedTopRightCorner = new Point2D(location->GetX() + width, location->GetY());
				auto expectedBottomRightCorner = new Point2D(location->GetX() + width, location->GetY() + height);
				auto expectedBottomLeftCorner = new Point2D(location->GetX(), location->GetY() + height);

				// Act
				auto subject = new Rectangle(location, height, width);

				// Assert
				assertEquals(location, subject->GetLocation());
				assertEquals(location, subject->GetTopLeftCorner());
				Assert::AreEqual(height, subject->GetHeight());
				Assert::AreEqual(width, subject->GetWidth());
				assertEquals(expectedTopRightCorner, subject->GetTopRightCorner());
				assertEquals(expectedBottomRightCorner, subject->GetBottomRightCorner());
				assertEquals(expectedBottomLeftCorner, subject->GetBottomLeftCorner());
			}
		}

		TEST_METHOD(ConstructorByLocationHeightAndWidth_InvalidHeight_ArgumentException)
		{
			struct testData
			{
				float height;

				testData(float height)
					: height(height) {}
			} data[] =
			{
				testData(0.f),
				testData(-1.f),
				testData(-0.01f),
			};
			for (size_t i = 0; i < 3; i++)
			{
				// Arrange
				auto height = data[i].height;

				auto location = new Point2D(1, 2);

				try
				{
					// Act
					new Rectangle(location, height, 1);
				}
				catch (const std::invalid_argument& ex)
				{
					// Assert
					Assert::AreEqual("Height must be a positive number.", ex.what());
					return;
				}

				Assert::Fail();
			}
		}

		TEST_METHOD(ConstructorByLocationHeightAndWidth_InvalidWidth_ArgumentException)
		{
			struct testData
			{
				float width;

				testData(float width)
					: width(width) {}
			} data[] =
			{
				testData(0.f),
				testData(-1.f),
				testData(-0.01f),
			};
			for (size_t i = 0; i < 3; i++)
			{
				// Arrange
				auto width = data[i].width;

				auto location = new Point2D(1, 2);

				try
				{
					// Act
					new Rectangle(location, 1, width);
				}
				catch (const std::invalid_argument& ex)
				{
					// Assert
					Assert::AreEqual("Width must be a positive number.", ex.what());
					return;
				}

				Assert::Fail();
			}
		}

		TEST_METHOD(ConstructorByCoordinates_InstantiatesNewRectangle)
		{
			struct testData
			{
				Point2D* topLeft;
				Point2D* bottomRight;

				testData(Point2D* topLeft, Point2D* bottomRight)
					: topLeft(topLeft), bottomRight(bottomRight) {}
			} data[] =
			{
				testData(new Point2D(0.f, 0.f), new Point2D(1.f, 1.f)),
				testData(new Point2D(0.f, 0.f), new Point2D(0.1f, 0.1f)),
				testData(new Point2D(-5.f, -5.f), new Point2D(0.f, 0.f)),
				testData(new Point2D(0.1f, 0.1f), new Point2D(0.2f, 0.2f)),
				testData(new Point2D(-0.1f, 0.1f), new Point2D(-0.05f, 0.15f))
			};
			for (size_t i = 0; i < 5; i++)
			{
				// Arrange
				auto topLeft = data[i].topLeft;
				auto bottomRight = data[i].bottomRight;

				auto expectedLocation = topLeft;
				auto expectedHeight = bottomRight->GetY() - topLeft->GetY();
				auto expectedWidth = bottomRight->GetX() - topLeft->GetX();
				auto expectedTopRightCorner = new Point2D(expectedLocation->GetX() + expectedWidth, expectedLocation->GetY());
				auto expectedBottomLeftCorner = new Point2D(expectedLocation->GetX(), expectedLocation->GetY() + expectedHeight);

				// Act
				auto subject = new Rectangle(topLeft, bottomRight);

				// Assert
				assertEquals(topLeft, subject->GetTopLeftCorner());
				assertEquals(bottomRight, subject->GetBottomRightCorner());

				assertEquals(expectedLocation, subject->GetLocation());
				Assert::AreEqual(expectedHeight, subject->GetHeight());
				Assert::AreEqual(expectedWidth, subject->GetWidth());
				assertEquals(expectedTopRightCorner, subject->GetTopRightCorner());
				assertEquals(expectedBottomLeftCorner, subject->GetBottomLeftCorner());
			}
		}

		TEST_METHOD(ConstructorByLocationHeightAndWidth_InvalidBottomRight_ArgumentException)
		{
			struct testData
			{
				Point2D* bottomRight;

				testData(Point2D* bottomRight)
					: bottomRight(bottomRight) {}
			} data[] =
			{
				testData(new Point2D(1.f, 2.f)),
				testData(new Point2D(1.f, 1.f)),
				testData(new Point2D(0.f, 2.f)),
				testData(new Point2D(2.f, 0.f)),
				testData(new Point2D(0.9f, 1.1f)),
				testData(new Point2D(1.1f, 0.9f)),
			};
			for (size_t i = 0; i < 6; i++)
			{
				// Arrange
				auto topRight = new Point2D(1, 1);
				auto bottomRight = data[i].bottomRight;

				try
				{
					new Rectangle(topRight, bottomRight);
				}
				catch (const std::invalid_argument&)
				{
					return;
				}

				Assert::Fail();
			}
		}

		TEST_METHOD(ConstructorByRectangle_InstantiatesNewRectangle)
		{
			struct testData
			{
				Rectangle* rectangle;

				testData(float x, float y, float height, float width)
					: rectangle(new Rectangle(new Point2D(x, y), height, width)) {}
			} data[] =
			{
				testData(0.f, 0.f, 1.f, 1.f),
				testData(1.f, 2.f, 0.5f, 3.0f),
				testData(1.2f, 2.f, 10.f, 0.8f),
			};
			for (size_t i = 0; i < 3; i++)
			{
				// Arrange
				auto rectangle = data[i].rectangle;

				// Act
				auto subject = new Rectangle(*rectangle);

				// Assert
				Assert::IsFalse(rectangle == subject);
				assertEquivalents(rectangle, subject);
			}
		}

		TEST_METHOD(AssignOperator_InstantiatesNewRectangle)
		{
			struct testData
			{
				Rectangle* rectangle;

				testData(float x, float y, float height, float width)
					: rectangle(new Rectangle(new Point2D(x, y), height, width)) {}
			} data[] =
			{
				testData(0.f, 0.f, 1.f, 1.f),
				testData(1.f, 2.f, 0.5f, 3.0f),
				testData(1.2f, 2.f, 10.f, 0.8f),
			};
			for (size_t i = 0; i < 3; i++)
			{
				// Arrange
				auto rectangle = data[i].rectangle;

				// Act
				auto subject = rectangle;

				// Assert
				Assert::IsFalse(&rectangle == &subject);
				assertEquivalents(rectangle, subject);
			}
		}

#pragma endregion

#pragma region Contains
		TEST_METHOD(Contains_InsideRectangle_True)
		{
			struct testData
			{
				Rectangle* rectangle;
				Point2D* point;

				testData(float x1, float y1, float x2, float y2, float x, float y)
					: rectangle(new Rectangle(new Point2D(x1, y1), new Point2D(x2, y2))), point(new Point2D(x, y)) {}
			} data[] =
			{
				testData(0.f, 0.f, 2.f, 2.f, 1.f, 1.f),
				testData(0.f, 0.f, 1.f, 1.f, 0.5f, 0.5f),
				testData(0.f, 0.f, 2.f, 2.f, 0.001f, 0.001f),
				testData(-1.f, -1.f, 0.f, 0.f, -0.5f, -0.5f),
				testData(0.f, 0.f, 2.f, 2.f, 1.f, 1.5f),
				testData(0.f, 0.f, 2.f, 2.f, 1.5f, 1.f),
			};
			for (size_t i = 0; i < 6; i++)
			{
				// Arrange
				auto point = data[i].point;
				auto subject = data[i].rectangle;

				// Act
				auto result = subject->Contains(point);

				// Assert
				Assert::IsTrue(result);
			}
		}

		TEST_METHOD(Contains_OnOneOfItsSides_True)
		{
			struct testData
			{
				Point2D* point;

				testData(float x, float y)
					: point(new Point2D(x, y)) {}
			} data[] =
			{
				testData(0.f, 0.f),
				testData(1.f, 0.f),
				testData(2.f, 0.f),
				testData(2.f, 1.f),
				testData(2.f, 2.f),
				testData(2.f, 2.),
				testData(0.f, 2.),
				testData(0.f, 1.),
			};
			for (size_t i = 0; i < 8; i++)
			{
				// Arrange
				auto point = data[i].point;
				auto subject = new Rectangle(new Point2D(0.f, 0.f), new Point2D(2.f, 2.f));

				// Act
				auto result = subject->Contains(point);

				// Assert
				Assert::IsTrue(result);
			}
		}

		TEST_METHOD(Contains_OutsideRectangle_False)
		{
			struct testData
			{
				Point2D* point;

				testData(float x, float y)
					: point(new Point2D(x, y)) {}
			} data[] =
			{
				testData(-0.001f, 0.f),
				testData(0.f, -0.001f),
				testData(-10.f, 0.f),
				testData(0.f, -10.f),
				testData(1.f, -0.001f),
				testData(1.f, -10.f),
				testData(2.f, -10.f),
				testData(2.f, -0.001f),
				testData(12.f, 0.f),
				testData(2.001f, 0.f),
				testData(2.001f, 1.f),
				testData(12.f, 1.f),
				testData(2.001f, 2.f),
				testData(12.f, 2.f),
				testData(2.f, 2.001f),
				testData(2.f, 12.f),
				testData(1.f, 2.001f),
				testData(1.f, 12.f),
				testData(0.f, 2.001f),
				testData(0.f, 12.f),
				testData(-0.001f, 2.f),
				testData(-10.f, 2.f),
				testData(-0.001f, 1.f),
				testData(-10.f, 1.f),
			};
			for (size_t i = 0; i < 24; i++)
			{
				// Arrange
				auto point = data[i].point;
				auto subject = new Rectangle(new Point2D(0.f, 0.f), new Point2D(2.f, 2.f));

				// Act
				auto result = subject->Contains(point);

				// Assert
				Assert::IsFalse(result);
			}
		}

#pragma endregion

#pragma region Intersects
		TEST_METHOD(Intersects_TouchesASide_True)
		{
			struct testData
			{
				Rectangle* rectangleB;

				testData(float x1, float y1, float x2, float y2)
					: rectangleB(new Rectangle(new Point2D(x1, y1), new Point2D(x2, y2))) {}
			} data[] =
			{
				// B is above A
				testData(12.f, 4.f, 14.f, 10.f),
				testData(6.f, 4.f, 10.f, 10.f),
				testData(20.f, 4.f, 30.f, 10.f),
				testData(6.f, 4.f, 14.f, 10.f),
				testData(12.f, 4.f, 22.f, 10.f),
				testData(6.f, 4.f, 30.f, 10.f),

				// B is to the right of A
				testData(20.f, 12.f, 30.f, 14.f),
				testData(20.f, 6.f, 30.f, 10.f),
				testData(20.f, 6.f, 30.f, 14.f),
				testData(20.f, 12.f, 30.f, 22.f),
				testData(20.f, 6.f, 30.f, 30.f),

				// B is below A
				testData(12.f, 20.f, 14.f, 30.f),
				testData(6.f, 20.f, 10.f, 30.f),
				testData(6.f, 20.f, 14.f, 30.f),
				testData(12.f, 20.f, 22.f, 30.f),
				testData(6.f, 20.f, 30.f, 30.f),

				// B is to the left of A
				testData(4.f, 12.f, 10.f, 14.f),
				testData(4.f, 6.f, 10.f, 10.f),
				testData(4.f, 20.f, 10.f, 30.f),
				testData(4.f, 6.f, 10.f, 14.f),
				testData(4.f, 12.f, 10.f, 22.f),
				testData(4.f, 6.f, 10.f, 30.f),

				// Corner touches
				testData(0.f, 0.f, 10.f, 10.f),
				testData(20.f, 0.f, 30.f, 10.f),
				testData(20.f, 20.f, 30.f, 30.f),
				testData(0.f, 20.f, 10.f, 30.f),
			};
			for (size_t i = 0; i < 6; i++)
			{
				// Arrange
				auto subjectA = new Rectangle(new Point2D(10.f, 10.f), new Point2D(20.f, 20.f));
				auto subjectB = data[i].rectangleB;

				// Act
				auto resultA = subjectA->Intersects(subjectB);
				auto resultB = subjectB->Intersects(subjectA);

				// Assert
				Assert::IsTrue(resultA);
				Assert::IsTrue(resultB);
			}
		}

		TEST_METHOD(Intersects_Overlaps_True)
		{
			struct testData
			{
				Rectangle* rectangleB;

				testData(float x1, float y1, float x2, float y2)
					: rectangleB(new Rectangle(new Point2D(x1, y1), new Point2D(x2, y2))) {}
			} data[] =
			{
				// B above A
				testData(0.f, 0.f, 30.f, 10.f),
				testData(0.f, 0.f, 15.f, 10.f),
				testData(15.f, 0.f, 30.f, 10.f),
				testData(12.f, 0.f, 18.f, 10.f),

				// B to the right of A
				testData(10.f, 0.f, 30.f, 30.f),
				testData(10.f, 0.f, 30.f, 15.f),
				testData(10.f, 15.f, 30.f, 30.f),
				testData(10.f, 12.f, 30.f, 18.f),

				// B below A
				testData(0.f, 10.f, 30.f, 30.f),
				testData(0.f, 10.f, 15.f, 30.f),
				testData(15.f, 10.f, 30.f, 30.f),
				testData(12.f, 10.f, 18.f, 30.f),

				// B to the left of A
				testData(0.f, 0.f, 10.f, 30.f),
				testData(0.f, 0.f, 10.f, 15.f),
				testData(0.f, 15.f, 10.f, 30.f),
				testData(0.f, 12.f, 10.f, 18.f),
			};
			for (size_t i = 0; i < 6; i++)
			{
				// Arrange
				auto subjectA = new Rectangle(new Point2D(10.f, 10.f), new Point2D(20.f, 20.f));
				auto subjectB = data[i].rectangleB;

				// Act
				auto resultA = subjectA->Intersects(subjectB);
				auto resultB = subjectB->Intersects(subjectA);

				// Assert
				Assert::IsTrue(resultA);
				Assert::IsTrue(resultB);
			}
		}

		TEST_METHOD(Intersects_FullyContained_True)
		{
			// Arrange
			auto subjectA = new Rectangle(new Point2D(10.f, 10.f), new Point2D(20.f, 20.f));
			auto subjectB = new Rectangle(new Point2D(12.f, 12.f), new Point2D(14.f, 14.f));

			// Act
			auto resultA = subjectA->Intersects(subjectB);
			auto resultB = subjectB->Intersects(subjectA);

			// Assert
			Assert::IsTrue(resultA);
			Assert::IsTrue(resultB);
		}

		TEST_METHOD(Intersects_Equals_True)
		{
			// Arrange
			auto subjectA = new Rectangle(new Point2D(10.f, 10.f), new Point2D(20.f, 20.f));
			auto subjectB = new Rectangle(*subjectA);

			// Act
			auto resultA = subjectA->Intersects(subjectB);
			auto resultB = subjectB->Intersects(subjectA);

			// Assert
			Assert::IsTrue(resultA);
			Assert::IsTrue(resultB);
		}

		TEST_METHOD(Intersects_OutsideRectangle_False)
		{
			struct testData
			{
				Rectangle* rectangleB;

				testData(float x1, float y1, float x2, float y2)
					: rectangleB(new Rectangle(new Point2D(x1, y1), new Point2D(x2, y2))) {}
			} data[] =
			{
				// B is above A
				testData(12.f, 4.f, 14.f, 9.9999f),
				testData(6.f, 4.f, 14.f, 9.9999f),
				testData(12.f, 4.f, 22.f, 9.9999f),
				testData(6.f, 4.f, 9.999f, 9.9999f),
				testData(20.0001f, 4.f, 24.f, 9.9999f),

				// B is to the right of A
				testData(12.f, 20.0001f, 14.f, 28.f),
				testData(6.f, 20.0001f, 14.f, 28.f),
				testData(12.f, 20.0001f, 22.f, 28.f),
				testData(6.f, 20.0001f, 9.999f, 28.f),
				testData(20.0001f, 20.0001f, 24.f, 28.f),

				// B is below A
				testData(20.0001f, 12.f, 28.f, 14.f),
				testData(20.0001f, 6.f, 28.f, 14.f),
				testData(20.0001f, 12.f, 28.f, 22.f),
				testData(20.0001f, 6.f, 28.f, 9.999f),
				testData(20.0001f, 20.0001f, 28.f, 24.f),

				// B is to the left of A
				testData(4.f, 12.f, 9.9999f, 14.f),
				testData(4.f, 6.f, 9.9999f, 14.f),
				testData(4.f, 12.f, 9.9999f, 22.f),
				testData(4.f, 6.f, 9.999f, 9.9999f),
				testData(4.f, 20.0001f, 9.9999f, 24.f),
			};
			for (size_t i = 0; i < 6; i++)
			{
				// Arrange
				auto subjectA = new Rectangle(new Point2D(10.f, 10.f), new Point2D(20.f, 20.f));
				auto subjectB = data[i].rectangleB;

				// Act
				auto resultA = subjectA->Intersects(subjectB);
				auto resultB = subjectB->Intersects(subjectA);

				// Assert
				Assert::IsFalse(resultA);
				Assert::IsFalse(resultB);
			}
		}

		//[Theory]
		
#pragma endregion

		TEST_METHOD(ToString_ReturnsExpected)
		{
			// Arrange
			auto subject = new Rectangle(new Point2D(10.f, 10.f), new Point2D(20.f, 20.f));

			wstring expected = L"Location: (10.000000;10.000000), Height: 10.000000, Width: 10.000000, TopLeftCorner: (10.000000;10.000000), TopRightCorner: (20.000000;10.000000), BottomRightCorner: (20.000000;20.000000), BottomLeftCorner: (10.000000;20.000000)";

			// Act
			auto actual = subject->toString();

			// Assert
			Assert::AreEqual(expected, actual);
		}
	};
}
