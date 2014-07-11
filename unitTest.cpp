//#include "Segment.h"
//#include "RBTree.hpp"
#include "ScanLine.h"
void UnitTestSegmengIntersection();
void UnitTestRBTree();
void InitLineList(std::vector<Segment> &lineList);
void UnitTest()
{
	std::vector<Segment> linelist;
	InitLineList(linelist);
	ScanLine scan;
	scan.ScanSchedule(linelist);

	//getchar();
}

int main()
{
	//UnitTestSegmengIntersection();
	//UnitTestRBTree();
	UnitTest();
	return 0;
}

void InitLineList(std::vector<Segment> &lineList)
{
	const int N = 8;
	Segment array[N] = {Segment(1,1,4,4),Segment(2,4,5,1),Segment(1,5,4,8),Segment(4,8,8,4),Segment(5,3,8,6),Segment(8,4,10,6),Segment(9,7,11,5),Segment(11,5,9,3)};//Segment(5,5,8,5)
	for (int i=0; i<N; ++i)
		lineList.push_back(array[i]);
}

void UnitTestEventInsert(std::vector<Segment> &lineList, RBTree<EventNode> &scanEvent)
{
	for (std::vector<Segment>::iterator it=lineList.begin(); it != lineList.end(); ++it) {
	    Point upperPoint = it->GetUpper();
		EventNode *newNode = new EventNode(it->GetUpper());
		EventNode * result = scanEvent.SearchNode(*newNode);
		if (result != NULL) {
		    result->InsertUpperSegment(*it);
		}
		else {  
			newNode->InsertUpperSegment(*it);
		    scanEvent.Insert(newNode);
		}

		Point lowerPoint = it->GetLower();
		newNode = new EventNode(it->GetLower());
		result = scanEvent.SearchNode(*newNode);
		if (result != NULL) 
			result->InsertLowerSegment(*it);
		else {
			newNode->InsertLowerSegment(*it);
		    scanEvent.Insert(newNode);
		}
	}
    scanEvent.InorderTrave();
    std::cout << std::endl << std::endl;
    scanEvent.PreorderTrave();
	std::cout << std::endl<<std::endl;
    
}

void UnitTestRBTree()
{
	RBTree<EventNode> eventQueue;
	
	
	eventQueue.InorderTrave();
	std::cout << std::endl;
	eventQueue.PreorderTrave();
    getchar();
}

void UnitTestSegmengIntersection()
{
	Segment s1(4,8,8,4);//test two segments intersect at upper point
	Segment s2(4,8,1,5);
	Point *inter = s1.Intersection(s2);
	if (inter) {
		inter->PrintCoordinate();
	}

	Segment s3(4,8,8,4);//test two segmengs intersect at lower point 
	Segment s4(8,4,10,6);
	inter = s3.Intersection(s4);
	if (inter)
		inter->PrintCoordinate();

	Segment s5(10,6,8,4); // test two segments intersect at 'y' style
	Segment s6(9,7,11,5);
	inter = s5.Intersection(s6);
	if (inter)
		inter->PrintCoordinate();

	Segment s7(9,7,11,5); //test upper point of one segment intersect lower point of other segment
	Segment s8(11,5,9,3);
	inter = s7.Intersection(s8);
	if (inter)
		inter->PrintCoordinate();
	getchar();
}