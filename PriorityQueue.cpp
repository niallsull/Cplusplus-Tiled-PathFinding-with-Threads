#include "PriorityQueue.h"


PriorityQueue::PriorityQueue(void)
{
	currentSize=0;
	queue.push_back(NULL);
	//sl=new SearchList();
}


PriorityQueue::~PriorityQueue(void)
{
}

void PriorityQueue::AddNode(PathNode* p)
{
	bool found=false;

	//if(found==false){
	for(int i=0;i<closedList.size();i++)
	{
		if( ((closedList.at(i)->position.x) =(p->position.x)) && ((closedList.at(i)->position.y) ==(p->position.y)) )
		{
			found=true;
			i=closedList.size()+2;
		}
	}

	if(found==false)
	{
		closedList.push_back(p);
		currentSize++;

		// check if seen already
		if(currentSize>=queue.size())
		{
			queue.push_back(p);
			queue.at(currentSize)=p;
		}

		else
		{
			queue.at(currentSize)=p;
		}


		int subsize=currentSize;

		while(  (subsize/2>0) && ((queue.at(subsize)->manhattan + queue.at(subsize)->step) < (queue.at(subsize/2)->manhattan +queue.at(subsize)->step))  )
		{
			PathNode* temporory=queue.at(subsize);
			queue.at(subsize)=queue.at(subsize/2);
			queue.at(subsize/2)=temporory;
			
			subsize=subsize/2;;
			//delete temporory;
		}
	}

}
PathNode* PriorityQueue::nextNode()
{

	PathNode* returnNode=queue.at(1);

	queue.at(1)=queue.at(currentSize);
	queue.at(currentSize)=NULL;
	currentSize--;

	int subsize=1;

	while((subsize*2<currentSize) && ( ( (queue.at(subsize)->manhattan + queue.at(subsize)->step) >  (queue.at(subsize*2)->manhattan + queue.at(subsize*2)->step) ) || ( (queue.at(subsize)->manhattan + queue.at(subsize)->step) >  (queue.at((subsize*2)+1)->manhattan + queue.at((subsize*2)+1)->step) ) ) )
	{
		if( ( (queue.at((subsize*2)+1)->manhattan + queue.at((subsize*2)+1)->step) >=  (queue.at(subsize*2)->manhattan + queue.at(subsize*2)->step) )  && ((subsize*2)+1 <= currentSize) )
		{
			PathNode* temp = queue.at(subsize);
			queue.at(subsize)=queue.at(subsize*2);
			queue.at(subsize*2)=temp;
			subsize=subsize*2;
			
		}

		else if( ( (queue.at((subsize*2)+1)->manhattan + queue.at((subsize*2)+1)->step) <  (queue.at(subsize*2)->manhattan + queue.at(subsize*2)->step) )  && ((subsize*2)+1 <= currentSize) )
		{
			PathNode* temp = queue.at(subsize);
			queue.at(subsize)=queue.at((subsize*2)+1);
			queue.at((subsize*2)+1)=temp;
			subsize=subsize*2;
		}

		if(subsize*2==currentSize)
		{
			if( (queue.at(subsize)->manhattan + queue.at(subsize)->step)  >  (queue.at(currentSize)->manhattan + queue.at(currentSize)->step) ) 
			{
				PathNode* p=queue.at(subsize);
				queue.at(subsize)=queue.at(currentSize);
				queue.at(subsize)=p;
				subsize=currentSize;
			}
			subsize=currentSize*2;
		}

	}

	return returnNode;
}

