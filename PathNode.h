#pragma once
class PathNode
{
public:
	struct Vector2
	{
		int x;
		int y;
	};

public:
	PathNode(void);
	~PathNode(void);
	PathNode(PathNode*,PathNode*,int,int,int, int,int);
	PathNode* copy(PathNode &p);
	PathNode(const PathNode &source);

	PathNode* target;
	PathNode* previous;
	int step;
	int manhattan;
	int cost;
	Vector2 position;

};

