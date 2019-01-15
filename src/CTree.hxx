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
#include <fstream>

using namespace LibTIM;

// constructor
// size : size of the image (number of pixels)
CTree::CTree(Image<U8>& img) :
	_img(img),
	_root(nullptr),
	_nodes(img.getSizeX() * img.getSizeY(),nullptr),
	_componentMapping(img.getSizeX() * img.getSizeY()),
	_lowestNode(img.getSizeX() * img.getSizeY()),
	_unodes(img.getSizeX() * img.getSizeY()),
	_utrees(img.getSizeX() * img.getSizeY())
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
	// image size
	int size = _img.getSizeX() * _img.getSizeY();
	// image _width
	int width = _img.getSizeX();

	// sorting all points in decreasing order of level
	std::priority_queue<Pixel, std::vector<Pixel>, PixelComparator> pixels;
	std::map<unsigned int, bool> processed;

	// iterating on all pixels of the image and storing them in
	// decreasing order of intensity
	for (int i = 0; i < _img.getSizeX(); i++)
	{
		for (int j = 0; j < _img.getSizeY(); j++)
		{
			Pixel p(i,j,_img(i,j));
			int index = j * width + i;

			// adding to the ordered queue
			pixels.push(Pixel(i, j, _img(i,j)));

			// for each pixel :
			// MakeSet(tree) of P
			// MakeSet(node) of P
			// nodes[P] = MakeNode(F(P))
			// lowestNode[P] = P
			//std::cout << index << std::endl;
			_utrees.makeSet(index);
			_unodes.makeSet(index);
			_nodes[index] = __makeNode(static_cast<int>(p.getValue()));
			_lowestNode[index] = index;

			processed[index] = false;
		}
	}

	// for each P in decreasing order of intensity
	while (!pixels.empty())
	{
		Pixel p = pixels.top();
		pixels.pop();
		int index = p.getY() * width + p.getX();

		processed[index] = true;

		int curTree = _utrees.find(index);
		int curNode = _unodes.find(_lowestNode[curTree]);

		// retrieving all already processed neighbours of p with intensity lower of equal to p
		std::vector<Pixel> neighbours = __findAlreadyProcessedNeighboursLE(p, processed);

		for (std::vector<Pixel>::iterator it = neighbours.begin(); it != neighbours.end(); it++)
		{
			int adjTree = _utrees.find((*it).getY() * width + (*it).getX());
			int adjNode = _unodes.find(_lowestNode[adjTree]);

			if (curNode != adjNode)
			{
				if (_nodes[curNode]->getLevel() == _nodes[adjNode]->getLevel())
				{
					curNode = __mergeNodes(adjNode, curNode);
				}
				else
				{
					// curnode level < adjnode level
					_nodes[curNode]->addChild(_nodes[adjNode]);

					_nodes[curNode]->setArea(_nodes[curNode]->getArea() + _nodes[adjNode]->getArea());

					_nodes[curNode]->setHighest(std::max(_nodes[curNode]->getHighest(),_nodes[adjNode]->getHighest()));
				}
				curTree = _utrees.link(adjTree, curTree);
				_lowestNode[curTree] = curNode;
			}
		}
	}

	_root = _nodes[_lowestNode[_utrees.find(_unodes.find(0))]];

	for (int i = 0; i < _img.getSizeX(); i++)
	{
		for (int j = 0; j < _img.getSizeY(); j++)
		{
			_componentMapping[j * width + i] = _unodes.find(j * width + i);
		}
	}

	//this->__print(this->_root);

}



void CTree::saveDOT(std::string filename)
{
	std::ofstream outfile(filename, std::ios_base::trunc | std::ios_base::binary);

	outfile << "digraph {\n";

	// using a queue to process nodes in a width-first fashion
	std::queue<CNode*> fifo;
	fifo.push(_root);

	while (!fifo.empty())
	{
		CNode *n = fifo.front();
		fifo.pop();

		for (std::vector<CNode*>::iterator it = n->_children.begin(); it != n->_children.end(); it++)
		{
			// writing all father/son relations
			outfile << "\t" << "\"ID : " << n->getID()
				<< "\\n level = " << n->getLevel()
				<< "\\n area = " << n->getArea()
				<< "\\n highest = " << n->getHighest()
				<< "\" -> \"ID : " << (*it)->getID()
				<< "\\n level = " << (*it)->getLevel()
				<< "\\n area = " << (*it)->getArea()
				<< "\\n highest = " << (*it)->getHighest()
				<< "\";\n";

			// and adding all sons to the queue to be processed afterwards
			fifo.push(*it);
		}
	}

	outfile << "}\n";
	outfile.close();
}

// test : printing tree
void CTree::__print(CNode *node)
{
	std::cout << "level : " << node->getLevel() << std::endl;
	std::cout << "area : " << node->getArea() << std::endl;
	std::cout << "highest : " << node->getHighest() << std::endl;

	for (std::vector<CNode*>::iterator it = node->_children.begin(); it != node->_children.end(); it++)
	{
		__print(*it);
	}
}

// internal method : make node
CNode* CTree::__makeNode(int level)
{
	return new CNode(level);
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
	_nodes[tmpNode]->setHighest(std::max(_nodes[tmpNode]->getHighest(),_nodes[tmpNode2]->getHighest()));

	return tmpNode;
}

// returns a list of all already processed neighbours of a pixel p
// with lower of equal intensity using the 8-connexity
std::vector<Pixel> CTree::__findAlreadyProcessedNeighboursLE(Pixel p, std::map<unsigned int, bool>& list)
{
	std::vector<Pixel> res;
	unsigned int x = p.getX();
	unsigned int y = p.getY();
	unsigned char value = p.getValue();

	// adding top left corner
	if (x != 0 && y != 0 && list[x-1,y-1] && _img(x-1,y-1) >= value)
		res.push_back(Pixel(x-1, y-1, _img(x-1, y-1)));

	// adding top right corner
	if (x != _img.getSizeX()-1 && y != 0 && list[x+1,y-1] && _img(x+1,y-1) >= value)
		res.push_back(Pixel(x+1, y-1, _img(x+1, y-1)));

	// adding bottom left corner
	if (x != 0 && y != _img.getSizeY()-1 && list[x-1,y+1] && _img(x-1,y+1) >= value)
		res.push_back(Pixel(x-1, y+1, _img(x-1, y+1)));

	// adding bottom right corner
	if (x != _img.getSizeX()-1 && y != _img.getSizeY()-1 && list[x+1,y+1] && _img(x+1,y+1) >= value)
		res.push_back(Pixel(x+1, y+1, _img(x+1, y+1)));

	// adding top pixel
	if (y != 0  && list[x,y-1] && _img(x,y-1) >= value)
		res.push_back(Pixel(x, y-1, _img(x, y-1)));

	// adding bottom pixel
	if (y != _img.getSizeY()-1 && list[x,y+1] && _img(x,y+1) >= value)
		res.push_back(Pixel(x, y+1, _img(x, y+1)));

	// adding left pixel
	if (x != 0 && list[x-1,y] && _img(x-1,y) >= value)
		res.push_back(Pixel(x-1, y, _img(x-1, y)));

	// adding right pixel
	if (x != _img.getSizeX()-1 && list[x+1,y] && _img(x+1,y) >= value)
		res.push_back(Pixel(x+1, y, _img(x+1, y)));

	return res;
}

#endif
