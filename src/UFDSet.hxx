#ifndef __UFDSET_HXX__
#define __UFDSET_HXX__

/*
 * TIDG : mathematical morphology
 * Romain Perrin <romain.perrin@etu.unistra.fr>
 * Maxime Seyer <maxime.seyer@etu.unistra.fr>
 * Université de Strasbourg
 * 2018-2019
 */

#include "../include/UFDSet.h"

// ctor
UFDSet::UFDSet(size_t size) :
	_parents(size),
	_ranks(size)
{
	// nothing
}

// methods (Tarjan's union-find)
void UFDSet::makeSet(int x)
{
	_parents[x] = x;
	_ranks[x] = 0;
}
#include <iostream>
int UFDSet::find(int x)
{
	//std::cout << "\tfind : " << x << ", parent : " << _parents[x] << std::endl;
	if (_parents[x] != x)
	{
		_parents[x] = find(_parents[x]);
	}
	return _parents[x];
}

int UFDSet::link(int x, int y)
{
/*	if (_ranks[x] > _ranks[y])
	{
		int p = _parents[x];
		_parents[x] = y;
		_parents[y] = p;

		int r = _ranks[x];
		_ranks[x] = _ranks[y];
		_ranks[y] = r;
	}*/

	if (_ranks[x] == _ranks[y])
	{
		_ranks[y] += 1;
	}

	_parents[x] = y;
	return y;
}

#include <iostream>

// debug : self display all relations
void UFDSet::selfDisplay()
{
	for (int i = 0; i < _parents.size(); i++)
	{
		std::cout << "Pixel " << i << ", parent : " << _parents[i] << ", rank : " << _ranks[i] << std::endl;
	}
}

#endif
