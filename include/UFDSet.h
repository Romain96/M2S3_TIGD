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
	// storing pixels
	std::vector<Pixel> _pixels;

	// image width used to compute indices
	unsigned int _width;

	// methods
public:
	// ctor
	UFDSet() = delete;
	UFDSet(size_t size, unsigned int width);

	// methods
	void makeSet(Pixel x);
	Pixel find(Pixel x);
	Pixel link(Pixel x, Pixel y);

	// debug
	void selfDisplay();

};

#include "../src/UFDSet.hxx"

#endif
