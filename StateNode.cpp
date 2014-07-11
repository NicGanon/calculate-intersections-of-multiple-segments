#include "StateNode.h"

StateNode* StateNode::SearchNode(StateNode& s)
{
	StateNode *pNode = this;
	while (pNode) {
		if (s < *pNode)
			pNode = pNode->left;
		else if (s == *pNode)
			break;
		else
			pNode = pNode->right;
	}

	return pNode;
}
