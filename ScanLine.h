#pragma once
#include "RBTree.hpp"
class ScanLine {
	public:
        void ScanSchedule(std::vector<Segment> &lineList);  
		void InitEventQueue(std::vector<Segment> &lineList);
		void HandleEvent();
		void FindIntersectionEvent(Segment l1, Segment l2);
		void HandleUpperEvent();
		void HandleLowerEvent();
		void HandleInterEvent();
	    void DeleteStateCase(StateNode* delNode);
		void InsertStateCase(StateNode* newNode);
		void PrintInterPoint();
		void Fileter();
	private:
		EventNode *curEvent;
		RBTree<EventNode> eventQueue ;
		RBTree<StateNode> stateStructure;
		//std::set<Point> interPoint;
		std::vector<Point> interPoint;

};
