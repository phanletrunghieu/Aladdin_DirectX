#include "QuadTree.h"

int QuadTree::MAX_LEVEL = 10;
int QuadTree::MAX_OBJECT_IN_REGION = 5;
std::vector<GameObject*> QuadTree::_listDynamicGameObject;

QuadTree::QuadTree(RECT bound, int level)
{
	this->_bound = bound;
	this->_level = level;
}

QuadTree::~QuadTree()
{
	//this->Clear();
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

	_listStaticGameObject.clear();
}

void QuadTree::InsertStaticObject(GameObject * gameObject)
{
	//Insert entity into corresponding nodes
	if (_nodes)
	{
		if (_nodes[0]->IsContain(gameObject))
			_nodes[0]->InsertStaticObject(gameObject);
		if (_nodes[1]->IsContain(gameObject))
			_nodes[1]->InsertStaticObject(gameObject);
		if (_nodes[2]->IsContain(gameObject))
			_nodes[2]->InsertStaticObject(gameObject);
		if (_nodes[3]->IsContain(gameObject))
			_nodes[3]->InsertStaticObject(gameObject);

		return; // Return here to ignore rest.
	}

	//Insert entity into current quadtree
	if (this->IsContain(gameObject))
		_listStaticGameObject.push_back(gameObject);

	//Split and move all objects in list into it’s corresponding nodes
	if (_listStaticGameObject.size() > MAX_OBJECT_IN_REGION && _level < MAX_LEVEL)
	{
		this->Split();

		while (!_listStaticGameObject.empty())
		{
			if (_nodes[0]->IsContain(_listStaticGameObject.back()))
				_nodes[0]->InsertStaticObject(_listStaticGameObject.back());
			if (_nodes[1]->IsContain(_listStaticGameObject.back()))
				_nodes[1]->InsertStaticObject(_listStaticGameObject.back());
			if (_nodes[2]->IsContain(_listStaticGameObject.back()))
				_nodes[2]->InsertStaticObject(_listStaticGameObject.back());
			if (_nodes[3]->IsContain(_listStaticGameObject.back()))
				_nodes[3]->InsertStaticObject(_listStaticGameObject.back());

			_listStaticGameObject.pop_back();
		}
	}
}

void QuadTree::InsertDynamicObject(GameObject * gameObject)
{
	_listDynamicGameObject.push_back(gameObject);
}

void QuadTree::Retrieve(std::vector<GameObject*>& return_objects_list, GameObject * gameObject)
{
	if (!gameObject->IsMovableObject())
	{
		//no check collision between non-movable object & non-movable
		for (auto i = _listDynamicGameObject.begin(); i != _listDynamicGameObject.end(); i++)
		{
			if (gameObject != *i)
				return_objects_list.push_back(*i);
		}
	}
	else
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
			//find static objects
			for (auto i = _listStaticGameObject.begin(); i != _listStaticGameObject.end(); i++)
			{
				if (gameObject != *i)
					return_objects_list.push_back(*i);
			}
		}

		//add dynamic objects
		for (auto i = _listDynamicGameObject.begin(); i != _listDynamicGameObject.end(); i++)
		{
			if (gameObject != *i)
				return_objects_list.push_back(*i);
		}
	}
}

void QuadTree::RemoveStaticObject(GameObject * gameObject)
{
	if (_nodes)
	{
		if (_nodes[0]->IsContain(gameObject))
			_nodes[0]->RemoveStaticObject(gameObject);
		if (_nodes[1]->IsContain(gameObject))
			_nodes[1]->RemoveStaticObject(gameObject);
		if (_nodes[2]->IsContain(gameObject))
			_nodes[2]->RemoveStaticObject(gameObject);
		if (_nodes[3]->IsContain(gameObject))
			_nodes[3]->RemoveStaticObject(gameObject);

		return; // Return here to ignore rest.
	}

	//Insert entity into current quadtree
	if (this->IsContain(gameObject)) {
		for (size_t i = 0; i < _listStaticGameObject.size(); i++)
		{
			if (_listStaticGameObject[i] == gameObject)
			{
				delete _listStaticGameObject[i];
				_listStaticGameObject.erase(_listStaticGameObject.begin() + i);
				i--;
				break;
			}
		}
	}
}

void QuadTree::RemoveDynamicObject(GameObject * gameObject)
{
	for (size_t i = 0; i < _listDynamicGameObject.size(); i++)
	{
		if (_listDynamicGameObject[i] == gameObject)
		{
			delete _listDynamicGameObject[i];
			_listDynamicGameObject.erase(_listDynamicGameObject.begin() + i);
			i--;
			break;
		}
	}
}
