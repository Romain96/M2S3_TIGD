#ifndef __CNODE_H__
#define __CNODE_H__

/*
 * TIDG : mathematical morphology
 * Romain Perrin <romain.perrin@etu.unistra.fr>
 * Maxime Seyer <maxime.seyer@etu.unistra.fr>
 * Université de Strasbourg
 * 2018-2019
 */

// class CNode : Component tree node definition
class CNode
{
	// attributes
protected:
	int _level;
	int _area;
	int _highest;

	// methods
public:
	// ctor
	CNode() = delete;
	CNode(int level);

	// getters
	int getLevel();
	int getArea();
	int getHighest();

	// setters
	void setLevel(int level);
	void setArea(int area);
	void setHighest(int highest);
};

#include "../src/CNode.hxx"

#endif

