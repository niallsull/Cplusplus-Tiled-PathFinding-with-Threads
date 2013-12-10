#include "SearchList.h"


SearchList::SearchList(void)
{
	//list = new vector<whatever*>();
}


SearchList::~SearchList(void)
{
}

bool SearchList::check(PathNode* p)
{
	for(int i=0;i<list.size();i++)
	{
		if( ((list.at(i)->position.x) =(p->position.x)) && ((list.at(i)->position.y) ==(p->position.y)) )
		{
			return true;
		}

	}
	
	list.push_back(p);

	return false;
}

void SearchList::add(PathNode* p)
{
	list.push_back(p);
}
