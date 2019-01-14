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
CTree::CTree(Image<U8>& img, unsigned int size, unsigned int width) :
	_img(img),
	_size(size),
	_width(width),
	_root(nullptr),
	_nodes(size, nullptr),
	_m(size),
	_lowestNode(size),
	_unodes(size, width),
	_utrees(size, width),
	_alreadyProcessed(size, false)
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
			Pixel p(i,j,_img(i,j));

			// adding to the ordered queue
			pixels.push(Pixel(i, j, _img(i,j)));

			// for each pixel :
			// MakeSet(tree) of P
			// MakeSet(node) of P
			// nodes[P] = MakeNode(F(P))
			// lowestNode[P] = P
			_utrees.makeSet(p);
			_unodes.makeSet(p);
			_nodes[i * _width + j] = __makeNode(p.getValue());
			_lowestNode[i * _width + j] = p;
		}
	}

	// for each P in decreasing order of intensity
	while (!pixels.empty())
	{
		Pixel p = pixels.top();
		pixels.pop();

		Pixel curTree = _utrees.find(p);
		Pixel curNode = _unodes.find(_lowestNode[curTree.getX() * _width + curTree.getY()]);

		// retrieving all already processed neighbours of p with intensity lower of equal to p
		std::vector<Pixel> neighbours = __findAlreadyProcessedNeighboursLE(p);

		// p has been processed
		_alreadyProcessed[p.getX() * _width + p.getY()] = true;
	}

}

// internal method : make node
CNode* CTree::__makeNode(int level)
{
	return new CNode(level);
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

// returns a list of all already processed neighbours of a pixel p
// with lower of equal intensity using the 8-connexity
std::vector<Pixel> CTree::__findAlreadyProcessedNeighboursLE(Pixel p)
{
	std::vector<Pixel> res;
	unsigned short x = p.getX();
	unsigned short y = p.getY();
	unsigned char value = p.getValue();

	// adding top left corner
	if (x != 0 && y != 0 && _alreadyProcessed[x-1,y-1] && _img(x-1,y-1) >= value)
		res.push_back(Pixel(x-1, y-1, _img(x-1, y-1)));

	// adding top right corner
	if (x != _img.getSizeX()-1 && y != 0 && _alreadyProcessed[x+1,y-1] && _img(x+1,y-1) >= value)
		res.push_back(Pixel(x+1, y-1, _img(x+1, y-1)));

	// adding bottom left corner
	if (x != 0 && y != _img.getSizeY()-1 && _alreadyProcessed[x-1,y+1] && _img(x-1,y+1) >= value)
		res.push_back(Pixel(x-1, y+1, _img(x-1, y+1)));

	// adding bottom right corner
	if (x != _img.getSizeX()-1 && y != _img.getSizeY()-1 && _alreadyProcessed[x+1,y+1] && _img(x+1,y+1) >= value)
		res.push_back(Pixel(x+1, y+1, _img(x+1, y+1)));

	// adding top pixel
	if (y != 0  && _alreadyProcessed[x,y-1] && _img(x,y-1) >= value)
		res.push_back(Pixel(x, y-1, _img(x, y-1)));

	// adding bottom pixel
	if (y != _img.getSizeY()-1 && _alreadyProcessed[x,y+1] && _img(x,y+1) >= value)
		res.push_back(Pixel(x, y+1, _img(x, y+1)));

	// adding left pixel
	if (x != 0 && _alreadyProcessed[x-1,y] && _img(x-1,y) >= value)
		res.push_back(Pixel(x-1, y, _img(x-1, y)));

	// adding right pixel
	if (y != 0 && _alreadyProcessed[x+1,y] && _img(x+1,y) >= value)
		res.push_back(Pixel(x+1, y, _img(x+1, y)));

	return res;
}

#endif
