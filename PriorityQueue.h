#ifndef PRIORITYQUEUE_H
#define PRIORITYQUEUE_H
#include <vector>
#include "PathNode.h"
#include "SearchList.h"
using namespace std;

class PriorityQueue
{
public:
	PriorityQueue(void);
	~PriorityQueue(void);

	vector<PathNode*> queue;

	PathNode* nextNode();
	void AddNode(PathNode*);
	int currentSize;
	vector<PathNode*> closedList;
	//SearchList* sl;

};

#endif
