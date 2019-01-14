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
UFDSet::UFDSet(size_t size, unsigned int width) :
	_parents(size),
	_ranks(size),
	_pixels(size),
	_width(width)
{
	// nothing
}

// methods (Tarjan's union-find)
void UFDSet::makeSet(Pixel x)
{
	_pixels[x.getX() * _width + x.getY()] = x;
	_parents[x.getX() * _width + x.getY()] = x.getX() * _width + x.getY();
	_ranks[x.getX() * _width + x.getY()] = 0;
}

Pixel UFDSet::find(Pixel x)
{
	if (x.getX() * _width + x.getY() == _parents[x.getX() * _width + x.getY()])
		return x;
	return find(_pixels[_parents[x.getX() * _width + x.getY()]]);
}

Pixel UFDSet::link(Pixel x, Pixel y)
{
	// find canonical element
	x = find(x);
	y = find(y);

	if (x != y)
	{
		if (_ranks[x.getX() * _width + x.getY()] < _ranks[y.getX() * _width + y.getY()])
		{
			// swapping all three buffers (_pixels, _ranks, _parents)
			_pixels[x.getX() * _width + x.getY()] = y;
			_pixels[y.getX() * _width + y.getY()] = x;

			int indexParent = _parents[x.getX() * _width + x.getY()];
			_parents[x.getX() * _width + x.getY()] = _parents[y.getX() * _width + y.getY()];
			_parents[y.getX() * _width + y.getY()] = indexParent;

			int indexRank = _ranks[x.getX() * _width + x.getY()];
			_ranks[x.getX() * _width + x.getY()] = _ranks[y.getX() * _width + y.getY()];
			_ranks[y.getX() * _width + y.getY()] = indexRank;
		}
		_parents[y.getX() * _width + y.getY()] = x.getX() * _width + x.getY();
		if (_ranks[x.getX() * _width + x.getY()] == _ranks[y.getX() * _width + y.getY()])
		{
			_ranks[x.getX() * _width + x.getY()]++;
		}
	}
}

#include <iostream>

// debug : self display all relations
void UFDSet::selfDisplay()
{
	for (int i = 0; i < _pixels.size(); i++)
	{
		std::cout << "Pixel " << i << " : ("
		<< static_cast<int>(_pixels[i].getX()) << ","
		<< static_cast<int>(_pixels[i].getY()) << ","
		<< static_cast<int>(_pixels[i].getValue())
		<< ") : parent ("
		<< static_cast<int>(_pixels[_parents[i]].getX()) << ","
		<< static_cast<int>(_pixels[_parents[i]].getY()) << ","
		<< static_cast<int>(_pixels[_parents[i]].getValue())
		<< ") rank = " << _ranks[i] << std::endl;
	}
}

#endif
