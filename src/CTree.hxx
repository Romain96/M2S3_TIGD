#ifndef __CTREE_HXX__
#define __CTREE_HXX__

/*
 * TIDG : mathematical morphology
 * Romain Perrin <romain.perrin@etu.unistra.fr>
 * Maxime Seyer <maxime.seyer@etu.unistra.fr>
 * Université de Strasbourg
 * 2018-2019
 */

#include "../include/CTree.h"

#include <queue>
#include <vector>

using namespace LibTIM;

// constructor
// size : size of the image (number of pixels)
CTree::CTree(Image<U8>& img) :
	_img(img),
	_size(img.getSizeX()*img.getSizeY()),
	_width(img.getSizeX()),
	_root(nullptr),
	_nodes(_size,nullptr),
	_m(_size),
	_unodes(_size, _width),
	_utrees(_size, _width)
{
	// nothing
}

// custom Pixel comparator : criteria is on grey intensity
struct PixelComparator
{
	bool operator() (Pixel p1, Pixel p2)
	{
		return p1.getValue() <= p2.getValue();
	}
};

// main method : building the component tree
void CTree::buildComponentTree()
{
	// sorting all points in decreasing order of level
	std::priority_queue<Pixel, std::vector<Pixel>, PixelComparator> pixels;

	// iterating on all pixels of the image and storing them in
	// decreasing order of intensity
	for (unsigned short i = 0; i < _img.getSizeX(); i++)
	{
		for (unsigned short j = 0; j < _img.getSizeY(); j++)
		{
			pixels.push(Pixel(i, j, _img(i,j)));
		}
	}

	std::cout << "pixels size : " << pixels.size() << std::endl;

}

// internal method : make node
CNode CTree::__makeNode(int level)
{
	return CNode(level);
}

// internal method : merge nodes
Pixel CTree::__mergeNodes(Pixel node1, Pixel node2)
{
	Pixel tmpNode = _unodes.link(node1, node2);
	Pixel tmpNode2;

	if (tmpNode == node2)
	{
		// adding all children of node1 as children of node2
		for (std::vector<CNode*>::iterator it = _nodes[node1.getX() * _width + node1.getY()]->_children.begin();
			it != _nodes[node1.getX() * _width + node1.getY()]->_children.end(); it++)
		{
			_nodes[node2.getX() * _width + node2.getY()]->_children.push_back(*it);
		}
		tmpNode2 = node1;
	}
	else
	{
		// adding all children of node as children of node1
		for (std::vector<CNode*>::iterator it = _nodes[node2.getX() * _width + node2.getY()]->_children.begin();
			it != _nodes[node2.getX() * _width + node2.getY()]->_children.end(); it++)
		{
			_nodes[node1.getX() * _width + node1.getY()]->_children.push_back(*it);
		}
		tmpNode2 = node2;
	}

	_nodes[tmpNode.getX() * _width + tmpNode.getY()]->setArea(
		_nodes[tmpNode.getX() * _width + tmpNode.getY()]->getArea() +
		_nodes[tmpNode2.getX() * _width + tmpNode2.getY()]->getArea());

	_nodes[tmpNode.getX() * _width + tmpNode.getY()]->setHighest(
		std::max(
			_nodes[tmpNode.getX() * _width + tmpNode.getY()]->getHighest(),
			_nodes[tmpNode2.getX() * _width + tmpNode2.getY()]->getHighest()));

	return tmpNode;
}

#endif
