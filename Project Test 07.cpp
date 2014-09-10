//============================================================================
// Name        : Project.cpp
// Author      : Jacques Visser
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <gtest/gtest.h>
#include "GameObject.h"
using namespace std;


//------------------------------------------------------------------------------
//				VectorQuantity
//------------------------------------------------------------------------------
TEST(VectorQuantity, get_angle)
{
	float angle = 5.65;
	float mag = 2.12;

	VectorQuantity testVec{angle, mag};

	EXPECT_EQ(angle, testVec.getAngle());
}







//------------------------------------------------------------------------------
//				Polygon
//------------------------------------------------------------------------------
TEST(Polygon, Construction_01)
{
	Polygon testPoly{};
}

TEST(Polygon, Adding_coordinates)
{
	Polygon testPoly{};
	shared_ptr<Coordinate> testCoordPtr(new Coordinate(1,1));
	testPoly.addCoordinate(testCoordPtr);
}

TEST(Polygon, Adding_Vertices)
{
	//Tests polymorphism of coordinate-vertex structure
	Polygon testPoly{};
	shared_ptr<Vertex> testVertPtr(new Vertex(1,1));
	testPoly.addCoordinate(testVertPtr);
}

TEST(Polygon, Get_Coordinate)
{
	Polygon testPoly{};
	shared_ptr<Coordinate> testCoordPtr1(new Coordinate(1,1));
	testPoly.addCoordinate(testCoordPtr1);
	shared_ptr<Coordinate> testCoordPtr2(new Coordinate(1,1));
	testPoly.addCoordinate(testCoordPtr2);

	EXPECT_EQ(testCoordPtr2, testPoly.getCoordinateAt(1));
}

TEST(Polygon, Get_invalid_Coordinate_01)
{
	Polygon testPoly{};
	shared_ptr<Coordinate> testCoordPtr1(new Coordinate(1,1));
	testPoly.addCoordinate(testCoordPtr1);
	shared_ptr<Coordinate> testCoordPtr2(new Coordinate(1,1));
	testPoly.addCoordinate(testCoordPtr2);

	EXPECT_THROW(testPoly.getCoordinateAt(2), Index_exceeds_Polygon_coordinates);
}


//------------------------------------------------------------------------------
//				Line
//------------------------------------------------------------------------------
TEST(Line, Construction)
{
	shared_ptr<Coordinate> testCoordPtr1(new Coordinate(1,1));
	shared_ptr<Coordinate> testCoordPtr2(new Coordinate(2,2));
	Line testLine{testCoordPtr1, testCoordPtr2};
}

TEST(Line, Get_invalid_Coodinate)
{
	shared_ptr<Coordinate> testCoordPtr1(new Coordinate(1,1));
	shared_ptr<Coordinate> testCoordPtr2(new Coordinate(2,2));
	Line testLine{testCoordPtr1, testCoordPtr2};
	EXPECT_THROW(testLine.getCoordinateAt(2), Index_exceeds_max_coordinates);
}

TEST(Line, Get_valid_Coordinate_00)
{
	shared_ptr<Coordinate> testCoordPtr0(new Coordinate(1,1));
	shared_ptr<Coordinate> testCoordPtr1(new Coordinate(2,2));
	Line testLine{testCoordPtr0, testCoordPtr1};
	EXPECT_EQ(testLine.getCoordinateAt(1), testCoordPtr1);
}

TEST(Line, Get_valid_Coordinate_01)
{
	shared_ptr<Coordinate> testCoordPtr0(new Coordinate(1,1));
	shared_ptr<Coordinate> testCoordPtr1(new Coordinate(2,2));
	Line testLine{testCoordPtr0, testCoordPtr1};
	EXPECT_EQ(testLine.getCoordinateAt(0), testCoordPtr0);
}

TEST(Line, Get_slope)
{
	shared_ptr<Coordinate> testCoordPtr0(new Coordinate(1,1));
	shared_ptr<Coordinate> testCoordPtr1(new Coordinate(2,2));
	Line testLine{testCoordPtr0, testCoordPtr1};

	EXPECT_EQ(testLine.getSlope(), 1);
}

TEST(Line, get_Y_intercept)
{
	shared_ptr<Coordinate> testCoordPtr0(new Coordinate(1,1));
	shared_ptr<Coordinate> testCoordPtr1(new Coordinate(2,2));
	Line testLine{testCoordPtr0, testCoordPtr1};

	EXPECT_EQ(testLine.getYIntercept(), 0.0f);
}

TEST(Line, get_Y_value_for_given_X_value)
{
	shared_ptr<Coordinate> testCoordPtr0(new Coordinate(1,1));
	shared_ptr<Coordinate> testCoordPtr1(new Coordinate(2,2));
	Line testLine{testCoordPtr0, testCoordPtr1};

	EXPECT_EQ(testLine.getYval(3.3f), 3.3f);
}

TEST(Line, is_coord_precisely_on_line)
{
	shared_ptr<Coordinate> testCoordPtr0(new Coordinate(1,1));
	shared_ptr<Coordinate> testCoordPtr1(new Coordinate(2,2));
	Line testLine{testCoordPtr0, testCoordPtr1};

	shared_ptr<Coordinate> testCoordPtr2(new Coordinate(3,3));

	EXPECT_TRUE(testLine.isOnLine(testCoordPtr2,0));
}

TEST(Line, is_coord_roughly_on_line)
{
	shared_ptr<Coordinate> testCoordPtr0(new Coordinate(1,1));
	shared_ptr<Coordinate> testCoordPtr1(new Coordinate(2,2));
	Line testLine{testCoordPtr0, testCoordPtr1};

	shared_ptr<Coordinate> testCoordPtr2(new Coordinate(3,4));

	EXPECT_TRUE(testLine.isOnLine(testCoordPtr2,1));
}

TEST(Line, is_coord_not_on_line)
{
	shared_ptr<Coordinate> testCoordPtr0(new Coordinate(1,1));
	shared_ptr<Coordinate> testCoordPtr1(new Coordinate(2,2));
	Line testLine{testCoordPtr0, testCoordPtr1};

	shared_ptr<Coordinate> testCoordPtr2(new Coordinate(3,8));

	EXPECT_FALSE(testLine.isOnLine(testCoordPtr2,1));
}

TEST(Line, is_below_false)
{
	shared_ptr<Coordinate> testCoordPtr0(new Coordinate(1,1));
	shared_ptr<Coordinate> testCoordPtr1(new Coordinate(2,2));
	Line testLine{testCoordPtr0, testCoordPtr1};

	shared_ptr<Coordinate> testCoordPtr2(new Coordinate(1,8));

	EXPECT_FALSE(testLine.isBelowLine(testCoordPtr2));
}

TEST(Line, is_below_true)
{
	shared_ptr<Coordinate> testCoordPtr0(new Coordinate(1,1));
	shared_ptr<Coordinate> testCoordPtr1(new Coordinate(2,2));
	Line testLine{testCoordPtr0, testCoordPtr1};

	shared_ptr<Coordinate> testCoordPtr2(new Coordinate(1,0.5));

	EXPECT_TRUE(testLine.isBelowLine(testCoordPtr2));
}


//------------------------------------------------------------------------------
//				Triangle
//------------------------------------------------------------------------------
TEST(Triangle, Construction)
{
	shared_ptr<Coordinate> tCP0(new Coordinate(1,1));
	shared_ptr<Coordinate> tCP1(new Coordinate(2,2));
	shared_ptr<Coordinate> tCP2(new Coordinate(0,2));
	Triangle testTri{tCP0, tCP1, tCP2};
}

TEST(Triangle, getLine_01)
{
	shared_ptr<Coordinate> tCP0(new Coordinate(1,1));
	shared_ptr<Coordinate> tCP1(new Coordinate(2,2));
	shared_ptr<Coordinate> tCP2(new Coordinate(0,2));
	Triangle testTri{tCP0, tCP1, tCP2};

	shared_ptr<Line> testLine{new Line{tCP0,tCP1}};

	EXPECT_EQ((*testLine), (*testTri.getLine(0)));
}

TEST(Triangle, get_opposing_Coordinate)
{
	shared_ptr<Coordinate> tCP0(new Coordinate(1,1));
	shared_ptr<Coordinate> tCP1(new Coordinate(2,2));
	shared_ptr<Coordinate> tCP2(new Coordinate(0,2));
	Triangle testTri{tCP0, tCP1, tCP2};

	auto opCoor = testTri.getOpposingCoord(2);

	EXPECT_EQ((*opCoor), (*tCP0));
}

TEST(Triangle, is_opposing_Coord_below)
{
	shared_ptr<Coordinate> tCP0(new Coordinate(1,1));
	shared_ptr<Coordinate> tCP1(new Coordinate(2,2));
	shared_ptr<Coordinate> tCP2(new Coordinate(0,2));
	Triangle testTri{tCP0, tCP1, tCP2};

	int line = 2;
	auto opCoor = testTri.getOpposingCoord(line);
	auto lin = testTri.getLine(line);
	EXPECT_TRUE(lin->isBelowLine(opCoor));
}

TEST(Triangle, is_inside_using_isBelowLine)
{
	shared_ptr<Coordinate> tCP0(new Coordinate(0,0));
	shared_ptr<Coordinate> tCP1(new Coordinate(2,2));
	shared_ptr<Coordinate> tCP2(new Coordinate(2,0));
	Triangle testTri{tCP0, tCP1, tCP2};

	shared_ptr<Coordinate> insideCPtr(new Coordinate(1,0.5));

	int line = 1;
	auto opCoor = testTri.getOpposingCoord(line);
	auto lin = testTri.getLine(line);

	EXPECT_EQ(lin->isBelowLine(opCoor), lin->isBelowLine(insideCPtr));
}

TEST(Triangle, is_inside)
{
	shared_ptr<Coordinate> tCP0(new Coordinate(0,0));
	shared_ptr<Coordinate> tCP1(new Coordinate(2,2));
	shared_ptr<Coordinate> tCP2(new Coordinate(2,0));
	Triangle testTri{tCP0, tCP1, tCP2};

	shared_ptr<Coordinate> insideCPtr(new Coordinate(1,0.5));

	EXPECT_TRUE(testTri.isInside(insideCPtr));
}


//------------------------------------------------------------------------------
//				GameObject
//------------------------------------------------------------------------------
TEST(GameObject, Construction)
{
	GameObject gO{};
}

