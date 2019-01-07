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
	if (find(x) != -1)
	{
		// adding x to DS only if not already inside
		_parents[x] = x;
		_ranks[x] = 0;
	}
}

int UFDSet::find(int x)
{
	if (x == _parents[x])
		return x;
	return find(_parents[x]);
}

int UFDSet::link(int x, int y)
{
	x = find(x);
	y = find(y);

	if (x != y)
	{
		if (_ranks[x] < _ranks[y])
		{

		}
		if (_ranks[x] == _ranks[y])
		{
			_ranks[x]++;
		}
		_parents[y] = x;
	}
}

#endif

