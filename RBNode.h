#pragma once
#include "Segment.h"
enum EventType{UPPER,INTER,LOWER};
class  EventNode 
{
public:
	 EventNode (Point &p);
	
	bool Prior(EventNode &comp);
	void Print() {event.PrintCoordinate();};
	Point GetEvent() {return event;};
	void SwapKey(EventNode* realDelNode);
	
	bool operator<(const EventNode& e) {return event < e.event;};
	bool operator==(const EventNode&e) {return event == e.event;};
	EventNode *SearchNode(EventNode &);
	void InsertUpperSegment(const Segment &s) {upperSegment.push_back(s);};
	void InsertLowerSegment(const Segment &s) {lowerSegment.push_back(s);};
	void InsertInterSegment(const Segment &s) {interSegment.push_back(s);};
	void UpdateLowerSegment(Segment &s,Segment&dst);
	std::vector<Segment> GetUpperSegment () { return upperSegment;};
	std::vector<Segment> GetLowerSegment () { return lowerSegment;};
	std::vector<Segment> GetInterSegment () { return interSegment;};

	void SetEventType(EventType t) {type = t;};
	EventType GetEventType() {return type;};

public:
	EventNode *left;
	EventNode *right;
	EventNode *parent;
 	NodeColor color;
private:
	Point event;
	EventType type;
	std::vector<Segment> upperSegment;
	std::vector<Segment> lowerSegment;
	std::vector<Segment> interSegment;
};

