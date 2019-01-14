#ifndef __CTREE_H__
#define __CTREE_H__

/*
 * TIDG : mathematical morphology
 * Romain Perrin <romain.perrin@etu.unistra.fr>
 * Maxime Seyer <maxime.seyer@etu.unistra.fr>
 * Université de Strasbourg
 * 2018-2019
 */

#include "../include/CNode.h"
#include "../include/UFDSet.h"
#include "../libtim/Common/Types.h"
#include "../libtim/Common/Image.h"

#include <vector>

using namespace LibTIM;

// Component tree class
class CTree
{
	// attributes
protected:
	Image<U8> _img;
	unsigned int _size;
	unsigned int _width;

	CNode *_root;
	std::vector<CNode*> _nodes;

	// Component mapping
	std::vector<int> _m;

	// lowestNode
	std::vector<Pixel> _lowestNode;

	// Disjoined Set for nodes
	UFDSet _unodes;

	// Disjoined Set for trees
	UFDSet _utrees;

	// already processed pixels
	std::vector<bool> _alreadyProcessed;

	// methods
public:
	CTree() = delete;
	CTree(Image<U8>& img, unsigned int size, unsigned int width);

	// building the component tree
	void buildComponentTree();

	// internal methods
	CNode* __makeNode(int level);
	Pixel __mergeNodes(Pixel node1, Pixel node2);
	std::vector<Pixel> __findAlreadyProcessedNeighboursLE(Pixel p);

};

#include "../src/CTree.hxx"

#endif
