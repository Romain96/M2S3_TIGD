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
#include <map>
#include <string>

using namespace LibTIM;

// Component tree class
class CTree
{
	// attributes
protected:
	Image<U8> _img;

	CNode* _root;
	std::vector<CNode*> _nodes;
	std::vector<int> _componentMapping;
	std::vector<int> _lowestNode;
	UFDSet _unodes;
	UFDSet _utrees;

	// methods
public:
	CTree() = delete;
	CTree(Image<U8>& img);

	// building the component tree
	void buildComponentTree();

	// writing the result in a DOT file
	void saveDOT(std::string filename);

	// internal methods
	CNode* __makeNode(int level);
	int __mergeNodes(int node1, int node2);
	std::vector<Pixel> __findAlreadyProcessedNeighboursLE(Pixel p, std::map<unsigned int, bool>& list);
	void __print(CNode *node);

};

#include "../src/CTree.hxx"

#endif
