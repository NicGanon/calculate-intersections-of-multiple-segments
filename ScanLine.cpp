#include "ScanLine.h"


void ScanLine::InitEventQueue(std::vector<Segment>& lineList)
{
	std::cout<< "this is innit event queue" << std::endl;
	for (std::vector<Segment>::iterator it=lineList.begin(); it!=lineList.end(); ++it) {
	    Point upperPoint = it->GetUpper();
		EventNode* newNode = new EventNode(it->GetUpper());
		EventNode *sameEvent = eventQueue.SearchNode(*newNode);
		
		if (sameEvent) 
			sameEvent->InsertUpperSegment(*it);
		else {
		    newNode->InsertUpperSegment(*it);
			eventQueue.Insert(newNode);
		}
		Point lowerPoint = it->GetLower();
		newNode = new EventNode(it->GetLower());
		sameEvent = eventQueue.SearchNode(*newNode);
		if (sameEvent)
			sameEvent->InsertLowerSegment(*it);
		else {
		    newNode->InsertLowerSegment(*it);
			eventQueue.Insert(newNode);
		}
	}
}
void ScanLine::HandleUpperEvent()
{
	//std::cout<< "upper event: ";
	//curEvent->GetEvent().PrintCoordinate();
	//std::cout << std::endl;
	std::vector<Segment> &list = curEvent->GetUpperSegment();

	for (std::vector<Segment>::iterator it=list.begin(); it!=list.end(); ++it) {
        StateNode* newNode = new StateNode(*it);
		stateStructure.Insert(newNode);
        
		InsertStateCase(newNode);
	}
}


void ScanLine::FindIntersectionEvent(Segment l1, Segment l2)
{
	//cout << "find intersection event between "<<endl;  l1.Print(); l2.Print();

	Point *inter = l1.Intersection(l2);
	if (inter!=NULL) {
        if (inter->GetY() > curEvent->GetEvent().GetY())
		    return;
		if (curEvent->GetEventType() == INTER && inter->GetY() == curEvent->GetEvent().GetY())
			return;
	    
		interPoint.push_back(*inter);
		if (inter->GetY() == curEvent->GetEvent().GetY() && l1.isEndPoint(*inter) && l2.isEndPoint(*inter))
			return;
        
		EventNode *interEvent = new EventNode(*inter);
		EventNode *same = eventQueue.SearchNode(*interEvent);
		if (same) {
		    same->InsertInterSegment(l1);
		    same->InsertInterSegment(l2);
		}
		else {
			interEvent->InsertInterSegment(l1);
		    interEvent->InsertInterSegment(l2);
		    eventQueue.Insert(interEvent);
		}
	}
}

void ScanLine::HandleLowerEvent()
{
	//std::cout<< "lower event: ";
	//curEvent->GetEvent().PrintCoordinate();
	//std::cout << std::endl;
	std::vector<Segment> &list = curEvent->GetLowerSegment();
	
	for (std::vector<Segment>::iterator it=list.begin(); it!=list.end(); ++it) {
		StateNode lowerSegment(*it);
		StateNode *endState = stateStructure.SearchNode(lowerSegment);
		
		DeleteStateCase(endState);
		stateStructure.Delete(endState);
	
    }
}

void ScanLine::HandleInterEvent()
{
	//std::cout<< "inter event: ";
	//curEvent->GetEvent().PrintCoordinate();
	//std::cout << std::endl;
	std::vector<Segment> interList(curEvent->GetInterSegment());
	for (std::vector<Segment>::iterator it=interList.begin(); it!=interList.end(); ++it) {
		
		StateNode interSegment(*it);
		StateNode *interLine = stateStructure.SearchNode(interSegment);
		Segment tmp(interLine->GetSegment());
		DeleteStateCase(interLine);   //������������߶δ�״̬�ռ�ɾ������������ǰ���ͺ��
		stateStructure.Delete(interLine);
		
		Point lower = tmp.GetLower();
		EventNode lowerPoint(lower);
		EventNode *lowerEvent = eventQueue.SearchNode(lowerPoint);
		std::vector<Segment> lowerList = lowerEvent->GetLowerSegment();
		for (std::vector<Segment>::iterator ie=lowerList.begin(); ie!=lowerList.end();++ie) {//ȥ�¼�������Ѱ�Ҿ����˽�����߶ε��¶˵��¼�
			if (tmp==(*ie)) {                                                               //����Ӧ�߶μ���
				ie->SetUpper(curEvent->GetEvent());
				lowerEvent->UpdateLowerSegment(tmp,*ie);
				break;
			}
		}

		tmp.SetUpper(curEvent->GetEvent());
		StateNode *newState = new StateNode(tmp);
		stateStructure.Insert(newState);//���޸Ĺ����߶β���״̬�ռ䣬��������ǰ���ͺ��
		InsertStateCase(newState);
	}
}
void ScanLine::InsertStateCase(StateNode *newNode)
{
	
	StateNode *pre = stateStructure.Precusor(newNode);
	
	if (pre) {
		
		FindIntersectionEvent(pre->GetSegment(), newNode->GetSegment());
	}
	StateNode *suc = stateStructure.Successor(newNode);
	
	if (suc) {
		
		FindIntersectionEvent(newNode->GetSegment(),suc->GetSegment());
	}
}
void ScanLine::DeleteStateCase(StateNode *delNode)
{
	StateNode *pre = stateStructure.Precusor(delNode);
	StateNode *suc = stateStructure.Successor(delNode);
	if (pre && suc)
		FindIntersectionEvent(pre->GetSegment(),suc->GetSegment());
}
void ScanLine::ScanSchedule(std::vector<Segment>& lineList)
{
	std::cout << "this is schedule" << std::endl;
	InitEventQueue(lineList); //initiale event queueu, insert all upper and lower point of all line into event queueu
    
	while (!eventQueue.Empty()) {
		
		curEvent = eventQueue.MinNode();
       
		if (!curEvent->GetUpperSegment().empty()) { //cur is upper point event
			curEvent->SetEventType(UPPER);
			HandleUpperEvent();
		}
        
		if (!curEvent->GetInterSegment().empty())  { //cur is intersection point event
			curEvent->SetEventType(INTER);
			HandleInterEvent();
		}

		if (!curEvent->GetLowerSegment().empty())  {  //cur is lower point event
			curEvent->SetEventType(LOWER);
			HandleLowerEvent();
		}

		eventQueue.Delete(curEvent);
		
	}	

	for(std::vector<Point>::iterator it = interPoint.begin(); it!=interPoint.end(); ++it)
		it->PrintCoordinate();
	getchar();
}
