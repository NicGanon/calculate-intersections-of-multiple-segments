#pragma once
#include "Segment.h"
class StateNode
{
public:
	StateNode (Segment &s):segment_(s),left(NULL),right(NULL),parent(NULL),color(RED){};
	
	bool Prior(StateNode &comp){return this->operator<(comp);};
	void Print() {segment_.Print();};
	bool operator<(const StateNode& e) {return segment_ < e.segment_;};
	bool operator==(const StateNode&e) {return segment_ == e.segment_;};
	Segment GetSegment() {return segment_;};
	void SwapKey(StateNode* realDelNode) {segment_ = realDelNode->segment_;};
	StateNode *SearchNode(StateNode&);

public:
	StateNode *left;
	StateNode *right;
	StateNode *parent;
 	NodeColor color;
private:
	Segment segment_;
};

