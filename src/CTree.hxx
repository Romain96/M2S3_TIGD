#ifndef __CTREE_HXX__
#define __CTREE_HXX__

#include "../include/CTree.h"

// constructor
// size : size of the image (number of pixels)
CTree::CTree(int size) : 
	_root(nullptr),
	_nodes(size,nullptr),
	_m(size),
	_unodes(size),
	_utrees(size)
{
	// nothing
}

// main method : building the component tree

// internal method : make node
CNode CTree::__makeNode(int level)
{
	return CNode(level);
}

// internal method : merge nodes
int CTree::__mergeNodes(int node1, int node2)
{
	int tmpNode = _unodes.link(node1, node2);
	int tmpNode2;

	if (tmpNode == node2)
	{
		// adding all children of node1 as children of node2
		for (std::vector<CNode*>::iterator it = _nodes[node1]->_children.begin(); it != _nodes[node1]->_children.end(); it++)
		{
			_nodes[node2]->_children.push_back(*it);
		}
		tmpNode2 = node1;
	}
	else
	{
		// adding all children of node as children of node1
		for (std::vector<CNode*>::iterator it = _nodes[node2]->_children.begin(); it != _nodes[node2]->_children.end(); it++)
		{	
			_nodes[node1]->_children.push_back(*it);
		}
		tmpNode2 = node2;
	}

	_nodes[tmpNode]->setArea(_nodes[tmpNode]->getArea() + _nodes[tmpNode2]->getArea());
	_nodes[tmpNode]->setHighest(std::max(_nodes[tmpNode]->getHighest(), _nodes[tmpNode2]->getHighest()));

	return tmpNode;
}

#endif
