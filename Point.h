#pragma once
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <cmath>
enum NodeColor {RED, BLACK};

class Point
{
public:
	Point():x_(0),y_(0) {};
	Point(float x, float y) : x_(x), y_(y) {};
	Point(const Point& p) { x_ = p.x_; y_ = p.y_;};
	float GetX() {return x_;};
	float GetY() {return y_;};
	void SetX(float x) {x_ = x;};
	void SetY(float y) {y_ = y;};
	float operator^(const Point &p);
	bool operator>(const Point &p);
	bool operator<(const Point &p);
	bool operator==(const Point &p);
	void PrintCoordinate() {std::cout << " ("<<x_<<","<<y_<<")  ";};
	~Point(void){};
private:
	float x_;
	float y_;
};

