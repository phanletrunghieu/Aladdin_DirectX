#include "QuadTree.h"

int QuadTree::MAX_LEVEL = 5;
int QuadTree::MAX_OBJECT_IN_REGION = 5;

QuadTree::QuadTree(RECT bound, int level)
{
	this->_bound = bound;
	this->_level = level;
}

QuadTree::~QuadTree()
{
	this->Clear();
}

bool QuadTree::IsContain(GameObject * gameObject)
{
	RECT bound = gameObject->GetBound();
	return !(bound.right < _bound.left ||
		bound.bottom < _bound.top ||
		bound.left > _bound.right ||
		bound.top > _bound.bottom);
}

void QuadTree::Split()
{
	//split current node into 4 nodes
	_nodes = new QuadTree*[4];

	int width = (_bound.right - _bound.left) / 2;
	int height = (_bound.bottom - _bound.top) / 2;

	RECT childRect;

	//top left
	childRect.left = _bound.left;
	childRect.right = _bound.left + width;
	childRect.top = _bound.top;
	childRect.bottom = _bound.top + height;
	_nodes[0] = new QuadTree(childRect, _level + 1);

	//top right
	childRect.right = _bound.right;
	childRect.left = _bound.right - width;
	childRect.top = _bound.top;
	childRect.bottom = _bound.top + height;
	_nodes[1] = new QuadTree(childRect, _level + 1);

	//bottom left
	childRect.left = _bound.left;
	childRect.right = _bound.left + width;
	childRect.bottom = _bound.bottom;
	childRect.top = _bound.bottom - height;
	_nodes[2] = new QuadTree(childRect, _level + 1);

	//bottom right
	childRect.right = _bound.right;
	childRect.left = _bound.right - width;
	childRect.bottom = _bound.bottom;
	childRect.top = _bound.bottom - height;
	_nodes[3] = new QuadTree(childRect, _level + 1);
}

void QuadTree::Clear()
{
	if (_nodes)
	{
		for (size_t i = 0; i < 4; i++)
		{
			if (_nodes[i])
			{
				_nodes[i]->Clear();
				delete _nodes[i];
				_nodes[i] = NULL;
			}
		}
		delete[] _nodes;
	}

	_listGameObject.clear();
}

void QuadTree::Insert(GameObject * gameObject)
{
	//Insert entity into corresponding nodes
	if (_nodes)
	{
		if (_nodes[0]->IsContain(gameObject))
			_nodes[0]->Insert(gameObject);
		if (_nodes[1]->IsContain(gameObject))
			_nodes[1]->Insert(gameObject);
		if (_nodes[2]->IsContain(gameObject))
			_nodes[2]->Insert(gameObject);
		if (_nodes[3]->IsContain(gameObject))
			_nodes[3]->Insert(gameObject);

		return; // Return here to ignore rest.
	}

	//Insert entity into current quadtree
	if (this->IsContain(gameObject))
		_listGameObject.push_back(gameObject);

	//Split and move all objects in list into it’s corresponding nodes
	if (_listGameObject.size() > MAX_OBJECT_IN_REGION && _level < MAX_LEVEL)
	{
		this->Split();

		while (!_listGameObject.empty())
		{
			if (_nodes[0]->IsContain(_listGameObject.back()))
				_nodes[0]->Insert(_listGameObject.back());
			if (_nodes[1]->IsContain(_listGameObject.back()))
				_nodes[1]->Insert(_listGameObject.back());
			if (_nodes[2]->IsContain(_listGameObject.back()))
				_nodes[2]->Insert(_listGameObject.back());
			if (_nodes[3]->IsContain(_listGameObject.back()))
				_nodes[3]->Insert(_listGameObject.back());

			_listGameObject.pop_back();
		}
	}
}

void QuadTree::Retrieve(std::vector<GameObject*>& return_objects_list, GameObject * gameObject)
{
	if (_nodes)
	{
		if (_nodes[0]->IsContain(gameObject))
			_nodes[0]->Retrieve(return_objects_list, gameObject);
		if (_nodes[1]->IsContain(gameObject))
			_nodes[1]->Retrieve(return_objects_list, gameObject);
		if (_nodes[2]->IsContain(gameObject))
			_nodes[2]->Retrieve(return_objects_list, gameObject);
		if (_nodes[3]->IsContain(gameObject))
			_nodes[3]->Retrieve(return_objects_list, gameObject);

		//TODO: remove duplicate
		std::sort(return_objects_list.begin(), return_objects_list.end());
		auto last = std::unique(return_objects_list.begin(), return_objects_list.end());
		return_objects_list.erase(last, return_objects_list.end());

		return; // Return here to ignore rest.
	}

	//Add all entities in current region into return_objects_list
	if (this->IsContain(gameObject))
	{
		for (auto i = _listGameObject.begin(); i != _listGameObject.end(); i++)
		{
			if (gameObject != *i)
				return_objects_list.push_back(*i);
		}
	}
}
