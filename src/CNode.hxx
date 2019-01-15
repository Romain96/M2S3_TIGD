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

int CNode::_cpt = 0;

// ctor
CNode::CNode(int level) :
	_level(level),
	_area(1),
	_highest(level),
	_children(0)
{
	// unique ID
	_id = _cpt++;
}

// getters
int CNode::getID()
{
	return _id;
}

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
void CNode::setID(int id)
{
	_id = id;
}

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
