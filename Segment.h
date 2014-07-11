#pragma once
#include "Point.h"
class Segment
{
public:
	Segment(int x1, int y1, int x2, int y2);
	Segment(Point p1, Point p2);
	Segment(const Segment &s);
	bool operator<(const Segment &s);
	bool operator==(const Segment &s);
	Point* Intersection(Segment &s);
	Point GetUpper() {return upperEnd;};
	Point GetLower() {return lowerEnd;};
	void SetUpper(const Point &p) {upperEnd = p;};
	bool isEndPoint(const Point &p);
	void Print();
	~Segment(void);
private:
	Point upperEnd;
	Point lowerEnd;
};

