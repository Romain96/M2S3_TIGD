#ifndef __CNODE_HXX__
#define __CNODE_HXX__

/*
 * TIDG : mathematical morphology
 * Romain Perrin <romain.perrin@etu.unistra.fr>
 * Maxime Seyer <maxime.seyer@etu.unistra.fr>
 * Université de Strasbourg
 * 2018-2019
 */

#include "../include/CNode.h"

// ctor
CNode::CNode(int level) :
	_level(level),
	_area(1),
	_highest(level),
	_children(0)
{
	// nothing
}

// getters
int CNode::getLevel()
{
	return _level;
}

int CNode::getArea()
{
	return _area;
}

int CNode::getHighest()
{
	return _highest;
}

// setters
void CNode::setLevel(int level)
{
	_level = level;
}

void CNode::setArea(int area)
{
	_area = area;
}

void CNode::setHighest(int highest)
{
	_highest = highest;
}

void CNode::addChild(CNode *node)
{
	_children.push_back(node);
}

#endif
