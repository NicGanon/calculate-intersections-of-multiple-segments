#include "Segment.h"


Segment::Segment(int x1, int y1, int x2, int y2): upperEnd(x1,y1), lowerEnd(x2,y2)
{
	if (upperEnd.GetY() < lowerEnd.GetY())
		std::swap(upperEnd, lowerEnd);
}

Segment::Segment(Point p1, Point p2): upperEnd(p1), lowerEnd(p2)
{
	if (upperEnd.GetY() < lowerEnd.GetY())
		std::swap(upperEnd,lowerEnd);
}

Segment::Segment(const Segment &s)
{
	upperEnd = s.upperEnd;
	lowerEnd = s.lowerEnd;
}

bool Segment::operator<(const Segment &s)
{
	if (upperEnd < s.upperEnd || (upperEnd == s.upperEnd && lowerEnd < s.lowerEnd))
		return true;
	else
		return false;
}

bool Segment::operator==(const Segment &s)
{
	if (upperEnd == s.upperEnd && lowerEnd == s.lowerEnd)
		return true;
	else
		return false;
}

Point* Segment::Intersection(Segment &s)
{
	Point *inter = NULL;
    Point p1 = GetUpper();
	Point p2 = GetLower();
	Point p3 = s.GetUpper();
   	Point p4 = s.GetLower();
    
	if (p1 == p4)
	{
		inter = new Point(p1);
		return inter;
	}
	else if (p2 == p3) {
		inter = new Point(p2);
	    return inter;
	}


	if (p1 > p2)
		std::swap(p1,p2);
    if (p3 > p4)
        std::swap(p3,p4);
	Point v1(p2.GetX() - p1.GetX(), p2.GetY() - p1.GetY());
	Point v2(p4.GetX() - p3.GetX(), p4.GetY() - p3.GetY());

	float corss = v1^v2;

	if (p1 > p3) {
	    std::swap(p1,p3);
		std::swap(p2,p4);
		std::swap(v1,v2);
		corss = v1^v2;
	}
	float ymax1=p1.GetY();
	float ymin1=p2.GetY();
	float ymax2=p3.GetY();
	float ymin2=p4.GetY();
	if (ymax1<ymin1)
		std::swap(ymax1,ymin1);
	if (ymax2<ymin2)
		std::swap(ymax2,ymin2);

	if (p1.GetX() > p4.GetX() || p2.GetX() < p3.GetX() ||ymax1<ymin2 || ymin1>ymax2)
		return inter;
	Point vs1(p1.GetX() - p3.GetX(), p1.GetY() - p3.GetY());
	Point vs2(p2.GetX() - p3.GetX(), p2.GetY() - p3.GetY());
	Point vt1(p3.GetX() - p1.GetX(), p3.GetY() - p1.GetY());
	Point vt2(p4.GetX() - p1.GetX(), p4.GetY() - p1.GetY());
	float s1v2 = vs1^v2;
	float s2v2 = vs2^v2;
	float t1v1 = vt1^v1;
	float t2v1 = vt2^v1;
	//根据外积结果判定否交于线上
	
	if ( (s1v2-0)<1e-4f && p4 > p1 && p1 > p3) {
		inter = new Point(p1);
	}
	if ( (s2v2-0)<1e-4f && p4 > p2 && p2 > p3) {
		inter = new Point(p2);
	}
	if ( (t1v1-0)<1e-4f && p2 > p3 && p3 > p1) {
		inter = new Point(p3);
	}
    if ( (t2v1-0)<1e-4f && p2 > p4 && p4 > p1) {
		inter = new Point(p4);
	} 

	if(s1v2 * s2v2 > 0 || t1v1 * t2v1 > 0) {
		return inter;
	} 
	else {
        inter = new Point();
	    int ConA = p1.GetX() * v1.GetY() - p1.GetY() * v1.GetX();
											
	    int ConB = p3.GetX() * v2.GetY() - p3.GetY() * v2.GetX();
											
	//计算行列式D1和D2的值，除以系数行列式的值，得到交点坐标
											
        float x = (ConB * v1.GetX() - ConA * v2.GetX()) / corss;
		inter->SetX(x);

        float y = (ConB * v1.GetY() - ConA * v2.GetY()) / corss;
		inter->SetY(y);
	}
	return inter;
}

bool Segment::isEndPoint(const Point &p)
{
	if (upperEnd == p|| lowerEnd == p)
		return true;
	else
		return false;
}

void Segment::Print()
{
	upperEnd.PrintCoordinate();
	lowerEnd.PrintCoordinate();
}

Segment::~Segment(void)
{
}
