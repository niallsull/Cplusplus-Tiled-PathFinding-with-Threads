#include "PathNode.h"


PathNode::PathNode(void)
{
}

PathNode::PathNode(PathNode* next, PathNode* prev, int step,int man,int cos, int x, int y)
{
	target=next;
	previous=prev;
	PathNode::step=step;
	position.x=x;
	position.y=y;
	manhattan=man;
	cost=cost;
}

PathNode::PathNode(const PathNode &source)
{
	manhattan=source.manhattan;
	step=source.step;
	previous=source.previous;
	target=source.target;
	position=source.position;
}

PathNode* PathNode::copy(PathNode &copyFrom)
{
	PathNode* copyTo=new PathNode();
	copyTo->manhattan=copyFrom.manhattan;
	copyTo->position=position;
	copyTo->previous=previous;
	copyTo->step=step;
	copyTo->target=target;

	return copyTo;
}

PathNode::~PathNode(void)
{
}
