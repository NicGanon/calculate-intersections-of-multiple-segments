#include "RBNode.h"


EventNode::EventNode (Point &p):event(p),left(NULL),right(NULL),parent(NULL),color(RED)
{}

bool EventNode::Prior(EventNode &comp)
{
	float thisy = event.GetY();
	float thisx = event.GetX();
	float compy = comp.event.GetY();
	float compx = comp.event.GetX();
	if (thisy > compy)
		return true;
	else if ( abs(thisy-compy) <1e-4f && thisx < compx)
		return true;
	else
		return false;
}

void EventNode::SwapKey(EventNode* realDelNode)
{
	event = realDelNode->event;
	upperSegment = realDelNode->upperSegment;
	interSegment = realDelNode->interSegment;
	lowerSegment = realDelNode->lowerSegment;
}

EventNode* EventNode::SearchNode(EventNode &e)
{
	EventNode *pNode = this;
	while (pNode)
	{
		if (e.Prior(*pNode))
			pNode = pNode->left;
		else if (e==(*pNode))
			break;
		else
			pNode = pNode->right;
	}

	return pNode;
}

void EventNode::UpdateLowerSegment(Segment& src, Segment &dst)
{
	std::vector<Segment>::iterator it = lowerSegment.begin();
	for ( ;it!=lowerSegment.end(); ++it) {
		if (src == *it) {
			*it = dst;
		    break;
		}
	}
}
