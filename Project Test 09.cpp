//============================================================================
// Name        : Project.cpp
// Author      : Jacques Visser
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "GameObject.h"
using namespace std;

#include <gtest/gtest.h>


//------------------------------------------------------------------------------
//						Coordinate
//------------------------------------------------------------------------------
TEST(Coordinate, Construction)
{
	Coordinate testCoord(3,4);
}

TEST(Coordinate, IncrementOperator)
{
	//tests setters implicitly
	Coordinate testCoord{3, 4};
	testCoord += Coordinate{2, 1};

	EXPECT_EQ(5, testCoord.x());
	EXPECT_EQ(5, testCoord.y());
}

TEST(Coordinate, DecrementOperator)
{
	Coordinate testCoord{3, 4};
	testCoord -= Coordinate{3, 4};

	EXPECT_EQ(0, testCoord.x());
	EXPECT_EQ(0, testCoord.y());
}

TEST(Coordinate, EqualityOperator)
{
	Coordinate testCoord0(1,1);
	Coordinate testCoord1(1,1);
	EXPECT_TRUE(testCoord0 == testCoord1);
}

TEST(Coordinate, GreaterThanOperator)
{
	Coordinate testCoord0(2,1);
	Coordinate testCoord1(1,1);
	EXPECT_TRUE(testCoord0 > testCoord1);

	testCoord0 = Coordinate{2,1};
	testCoord1 = Coordinate{1,3};
	EXPECT_FALSE(testCoord0 > testCoord1);
}

TEST(Coordinate, SmallerThanOperator)
{
	Coordinate testCoord0(2,1);
	Coordinate testCoord1(1,1);
	EXPECT_FALSE(testCoord0 < testCoord1);

	testCoord0 = Coordinate{2,1};
	testCoord1 = Coordinate{1,3};
	EXPECT_TRUE(testCoord0 < testCoord1);
}

TEST(Coordinate, GreaterThanFloatOperator)
{
	Coordinate testCoord0(2,1);
	float testFloat{1};
	EXPECT_TRUE(testCoord0 > testFloat);

	testFloat = 5;
	EXPECT_FALSE(testCoord0 > testFloat);
}

TEST(Coordinate, SmallerThanFloatOperator)
{
	Coordinate testCoord0(2,1);
	float testFloat{5};
	EXPECT_TRUE(testCoord0 < testFloat);

	testFloat = 1;
	EXPECT_FALSE(testCoord0 < testFloat);
}

TEST(Coordinate, Addition)
{
	Coordinate testCoord0(1,1);
	Coordinate testCoord1(2,2);
	Coordinate testCoord2(3,3);
	EXPECT_EQ(testCoord2, (testCoord0 + testCoord1));
}

TEST(Coordinate, Subraction)
{
	Coordinate testCoord0(1,1);
	Coordinate testCoord1(2,2);
	Coordinate testCoord2(-1,-1);
	EXPECT_EQ(testCoord2, (testCoord0 - testCoord1));
}

TEST(Coordinate, DotProduct)
{
	Coordinate testCoord0(4,4);
	Coordinate testCoord1(2,2);
	float dot = 16.0f;
	EXPECT_EQ(dot, (testCoord0 * testCoord1));
}

TEST(Coordinate, Angle)
{
	float angle = 4.3;
	float magnitude = 3;

	float x = magnitude*cos(angle);
	float y = magnitude*sin(angle);

	Coordinate testCoord{x,y};

	EXPECT_EQ(angle, testCoord.angle());
}

TEST(Coordinate, MagnitudeSquared)
{
	float angle = 4.3;
	float magnitude = 3;

	float x = magnitude*cos(angle);
	float y = magnitude*sin(angle);

	Coordinate testCoord{x,y};

	EXPECT_EQ(magnitude*magnitude, testCoord.magSquared());
}

TEST(Coordinate, Magnitude)
{
	float angle = 4.3;
	float magnitude = 3;

	float x = magnitude*cos(angle);
	float y = magnitude*sin(angle);

	Coordinate testCoord{x,y};

	EXPECT_EQ(magnitude, testCoord.magnitude());
}

TEST(Coordinate, Rotate)
{
	Coordinate center{1,1};
	Coordinate coord{0,1};

	coord.rotate(PI/2, center);

	Coordinate comparCoord{1,2};
	EXPECT_EQ(comparCoord, coord);
}


//------------------------------------------------------------------------------
//					Line
//------------------------------------------------------------------------------
TEST(Line, Construction)
{
	std::shared_ptr<Coordinate> tC0{new Coordinate{0,0}};
	std::shared_ptr<Coordinate> tC1{new Coordinate{1,1}};
	Line lin{tC0, tC1};
}

TEST(Line, Length)
{
	std::shared_ptr<Coordinate> tC0{new Coordinate{0,0}};
	std::shared_ptr<Coordinate> tC1{new Coordinate{1,1}};
	Line lin{tC0, tC1};
	EXPECT_EQ(sqrt(2), lin.length());
}

TEST(Line, isBelowLineTrue)
{
	std::shared_ptr<Coordinate> tC0{new Coordinate{0,0}};
	std::shared_ptr<Coordinate> tC1{new Coordinate{1,1}};
	Line lin{tC0, tC1};

	std::shared_ptr<Coordinate> tC2{new Coordinate{0.5,0.25}};
	EXPECT_TRUE(lin.isBelow(tC2));
}

TEST(Line, isBelowLineFalse)
{
	std::shared_ptr<Coordinate> tC0{new Coordinate{0,0}};
	std::shared_ptr<Coordinate> tC1{new Coordinate{1,1}};
	Line lin{tC0, tC1};

	std::shared_ptr<Coordinate> tC2{new Coordinate{0.5,1}};
	EXPECT_FALSE(lin.isBelow(tC2));
}


//------------------------------------------------------------------------------
//				Triangle
//------------------------------------------------------------------------------
TEST(Triangle, Creation)
{
	std::shared_ptr<Coordinate> tC0{new Coordinate{0,0}};
	std::shared_ptr<Coordinate> tC1{new Coordinate{1,1}};
	std::shared_ptr<Coordinate> tC2{new Coordinate{0,1}};

	Triangle testTri{tC0, tC1, tC2};
}

TEST(Triangle, isInside)
{
	std::shared_ptr<Coordinate> tC0{new Coordinate{0,0}};
	std::shared_ptr<Coordinate> tC1{new Coordinate{1,1}};
	std::shared_ptr<Coordinate> tC2{new Coordinate{0,1}};

	std::shared_ptr<Coordinate> tC3{new Coordinate{0.5,0.5}};
	std::shared_ptr<Coordinate> tC4{new Coordinate{2,2}};

	Triangle testTri{tC0, tC1, tC2};

	EXPECT_TRUE(testTri.isInside(tC3));
	EXPECT_FALSE(testTri.isInside(tC4));
}

TEST(Triangle, coordsInsideTriangle_VecOfCoords)
{
	std::shared_ptr<Coordinate> tC0{new Coordinate{0,0}};
	std::shared_ptr<Coordinate> tC1{new Coordinate{1,1}};
	std::shared_ptr<Coordinate> tC2{new Coordinate{0,1}};

	std::shared_ptr<Coordinate> tC3{new Coordinate{2,0}};
	std::shared_ptr<Coordinate> tC4{new Coordinate{0.2,0.2}};
	std::shared_ptr<Coordinate> tC5{new Coordinate{0.5,0.5}};

	vector<shared_ptr<Coordinate>> _coords;
	_coords.push_back(tC3);
	_coords.push_back(tC4);
	_coords.push_back(tC5);

	Triangle testTri{tC0, tC1, tC2};

	EXPECT_EQ(2, testTri.coordsInside(_coords));
}

TEST(Triangle, coordsInsideTriangle_VecOfTriangles)
{
	std::shared_ptr<Coordinate> t0C0{new Coordinate{0,0}};
	std::shared_ptr<Coordinate> t0C1{new Coordinate{5,5}};
	std::shared_ptr<Coordinate> t0C2{new Coordinate{0,5}};
	std::shared_ptr<Triangle> t0{new Triangle{t0C0, t0C1, t0C2}};

	std::shared_ptr<Coordinate> t1C0{new Coordinate{0.5, 0.5}};
	std::shared_ptr<Coordinate> t1C1{new Coordinate{1, 1}};
	std::shared_ptr<Coordinate> t1C2{new Coordinate{0.5, 1}};
	std::shared_ptr<Triangle> t1{new Triangle{t1C0, t1C1, t1C2}};

	std::shared_ptr<Coordinate> t2C0{new Coordinate{0.3, 0.3}};
	std::shared_ptr<Coordinate> t2C1{new Coordinate{5,6}};
	std::shared_ptr<Coordinate> t2C2{new Coordinate{2,0}};
	std::shared_ptr<Triangle> t2{new Triangle{t2C0, t2C1, t2C2}};

	std::vector<std::shared_ptr<Triangle>> tris;
	tris.push_back(t1);
	tris.push_back(t2);

	EXPECT_EQ(4, t0->coordsInside(tris));
}

TEST(Triangle, Move)
{
	Coordinate c0{0,0};
	Coordinate c1{5,5};
	Coordinate c2{0,5};
	std::shared_ptr<Coordinate> t0C0{new Coordinate{c0}};
	std::shared_ptr<Coordinate> t0C1{new Coordinate{c1}};
	std::shared_ptr<Coordinate> t0C2{new Coordinate{c2}};
	std::shared_ptr<Triangle> t0{new Triangle{t0C0, t0C1, t0C2}};

	Coordinate dPos{1,1};

	t0->move(dPos);

	EXPECT_EQ(dPos+c0, *(t0->getCoordinate(0)));
	EXPECT_EQ(dPos+c1, *(t0->getCoordinate(1)));
	EXPECT_EQ(dPos+c2, *(t0->getCoordinate(2)));
}

TEST(Triangle, Rotate)
{
	Coordinate center{3,3};
	float angle{3};

	Coordinate c0{0,0};
	Coordinate c1{5,5};
	Coordinate c2{0,5};
	std::shared_ptr<Coordinate> t0C0{new Coordinate{c0}};
	std::shared_ptr<Coordinate> t0C1{new Coordinate{c1}};
	std::shared_ptr<Coordinate> t0C2{new Coordinate{c2}};
	std::shared_ptr<Triangle> t0{new Triangle{t0C0, t0C1, t0C2}};

	t0->rotate(angle, center);
	c0.rotate(angle, center);
	c1.rotate(angle, center);
	c2.rotate(angle, center);

	EXPECT_EQ(c0, *(t0->getCoordinate(0)));
	EXPECT_EQ(c1, *(t0->getCoordinate(1)));
	EXPECT_EQ(c2, *(t0->getCoordinate(2)));
}

//------------------------------------------------------------------------------
//					GameObject
//------------------------------------------------------------------------------
TEST(GameObject, Construction)
{
	GameObject testGO{1};
}

TEST(GameObject, addTriangle)
{
	shared_ptr<Coordinate> tC0{new Coordinate{0,0}};
	shared_ptr<Coordinate> tC1{new Coordinate{1,1}};
	shared_ptr<Coordinate> tC2{new Coordinate{0,1}};
	shared_ptr<Triangle> testTri{new Triangle{tC0, tC1, tC2}};

	GameObject testGO{1};
	testGO.addTriangle(testTri);
}

//TEST(GameObject, Move)
//{
//	Coordinate c0{0,0};
//	Coordinate c1{5,5};
//	Coordinate c2{0,5};
//
//	shared_ptr<Coordinate> tC0{new Coordinate{c0}};
//	shared_ptr<Coordinate> tC1{new Coordinate{c1}};
//	shared_ptr<Coordinate> tC2{new Coordinate{c2}};
//	shared_ptr<Triangle> testTri{new Triangle{tC0, tC1, tC2}};
//
//	GameObject tGO{1};
//	tGO.addTriangle(testTri);
//
//	Coordinate dPos{1,1};
//	tGO.move(dPos);
//
//	EXPECT_EQ(c0 + dPos, *(tGO._triangles[0]->getCoordinate(0)));
//	EXPECT_EQ(c1 + dPos, *(tGO._triangles[0]->getCoordinate(1)));
//	EXPECT_EQ(c2 + dPos, *(tGO._triangles[0]->getCoordinate(2)));
//}

//TEST(GameObject, Rotate)
//{
//	float angle{3};
//
//	Coordinate c0{0,0};
//	Coordinate c1{5,5};
//	Coordinate c2{0,5};
//	std::shared_ptr<Coordinate> t0C0{new Coordinate{c0}};
//	std::shared_ptr<Coordinate> t0C1{new Coordinate{c1}};
//	std::shared_ptr<Coordinate> t0C2{new Coordinate{c2}};
//	std::shared_ptr<Triangle> t0{new Triangle{t0C0, t0C1, t0C2}};
//
//	GameObject tGO{1};
//	tGO.addTriangle(t0);
//	Coordinate center{tGO.getCenter()};
//
//	tGO.rotate(angle);
//	c0.rotate(angle, center);
//	c1.rotate(angle, center);
//	c2.rotate(angle, center);
//
//	EXPECT_EQ(c0, *(tGO._triangles[0]->getCoordinate(0)));
//	EXPECT_EQ(c1, *(tGO._triangles[0]->getCoordinate(1)));
//	EXPECT_EQ(c2, *(tGO._triangles[0]->getCoordinate(2)));
//}





