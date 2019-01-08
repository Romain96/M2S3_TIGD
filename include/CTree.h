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

#include <vector>

// Component tree class 
class CTree
{
	// attributes
protected:
	CNode *_root;
	std::vector<CNode*> _nodes;

	// Component mapping
	std::vector<int> _m;

	// lowestNode
	std::vector<int> _lowestNode;

	// Disjoined Set for nodes
	UFDSet _unodes;

	// Disjoined Set for trees
	UFDSet _utrees;

	// methods
public:
	CTree() = delete;
	CTree(int size);

	// building the component tree
	void buildComponentTree();

	// internal methods
	CNode __makeNode(int level);
	int __mergeNodes(int node1, int node2);

};

#include "../src/CTree.hxx"

#endif
