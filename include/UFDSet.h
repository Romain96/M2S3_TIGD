#ifndef __UFDSET_H__
#define __UFDSET_H__

/*
 * TIDG : mathematical morphology
 * Romain Perrin <romain.perrin@etu.unistra.fr>
 * Maxime Seyer <maxime.seyer@etu.unistra.fr>
 * Université de Strasbourg
 * 2018-2019
 */

#include "../include/Pixel.h"
#include <vector>

// class UFDSet : Tarjan's Union-Find algorithm
// disjoined set class
class UFDSet
{
	// attributes
protected:
	// storing parents relations as a global array
	std::vector<int> _parents;
	// storing ranks as a global array
	std::vector<int> _ranks;

	// methods
public:
	// ctor
	UFDSet() = delete;
	UFDSet(size_t size);

	// methods
	void makeSet(int x);
	int find(int x);
	int link(int x, int y);

	// debug
	void selfDisplay();

};

#include "../src/UFDSet.hxx"

#endif
