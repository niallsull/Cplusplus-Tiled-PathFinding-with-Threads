#ifndef SEARCHLIST_H
#define SEARCHLIST_H
#include "PathNode.h"
#include <vector>
using namespace std;

class SearchList
{
public:
	SearchList(void);
	~SearchList(void);

	vector<PathNode*> list;
	bool check(PathNode*);
	void add(PathNode* p);

};

#endif
