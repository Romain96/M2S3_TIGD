#ifndef __UFDSETELEMENT_HXX__
#define __UFDSETELEMENT_HXX__

/*
 * TIDG : mathematical morphology
 * Romain Perrin <romain.perrin@etu.unistra.fr>
 * Maxime Seyer <maxime.seyer@etu.unistra.fr>
 * Université de Strasbourg
 * 2018-2019
 */

#include "../include/UFDSetElement.h"

// constructor
template <typename T>
UFDSetElement<T>::UFDSetElement(T x) : 
	_element(x),
	_parent(this),
	_rank(0)
{
	// nothing
}

// getters
template <typename T>
T UFDSetElement<T>::getElement()
{
	return _element;
}

template <typename T>
UFDSetElement<T> *UFDSetElement<T>::getParent()
{
	return _parent;
}

template <typename T>
int UFDSetElement<T>::getRank()
{
	return _rank;
}

// setters
template <typename T>
void UFDSetElement<T>::setElement(T x)
{
	_element = x;
}

template <typename T>
void UFDSetElement<T>::setParent(UFDSetElement<T> *parent)
{
	_parent = parent;
}

template <typename T>
void UFDSetElement<T>::setRank(int rank)
{
	_rank = rank;
}

#endif
