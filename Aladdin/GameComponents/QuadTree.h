#pragma once

#include <vector>
#include <algorithm>
#include "../GameObjects/GameObject.h"

class QuadTree
{
protected:
	static int MAX_OBJECT_IN_REGION;
	static int MAX_LEVEL;

	RECT _bound;
	int _level;
	QuadTree **_nodes;
	std::vector<GameObject*> _listStaticGameObject;
	static std::vector<GameObject*> _listDynamicGameObject;

	bool IsContain(GameObject *gameObject);
	void Split();
public:
	QuadTree(RECT bound, int level = 1);
	~QuadTree();
	void Clear();
	void InsertStaticObject(GameObject *gameObject);
	static void InsertDynamicObject(GameObject *gameObject);
	void Retrieve(std::vector<GameObject*> &gameObjectsOut, GameObject *gameObject);
};

