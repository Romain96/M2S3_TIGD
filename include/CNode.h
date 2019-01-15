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
private:
	static int _cpt;
protected:
	int _id;
	int _level;
	int _area;
	int _highest;

public:
	std::vector<CNode*> _children;

	// methods
public:
	// ctor
	CNode() = delete;
	CNode(int level);

	// getters
	int getID();
	int getLevel();
	int getArea();
	int getHighest();

	// setters
	void setID(int id);
	void setLevel(int level);
	void setArea(int area);
	void setHighest(int highest);

	// method
	void addChild(CNode *node);
};

#include "../src/CNode.hxx"

#endif
