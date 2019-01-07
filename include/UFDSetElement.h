#ifndef __UFDSETELEMENT_H__
#define __UFDSETELEMENT_H__

/*
 * TIDG : mathematical morphology
 * Romain Perrin <romain.perrin@etu.unistra.fr>
 * Maxime Seyer <maxime.seyer@etu.unistra.fr>
 * Université de Strasbourg
 * 2018-2019
 */

// class UFDSet : Tarjan's Union-Find algorithm
// disjoined set element class
template <typename T>
class UFDSetElement
{
	// attributes
protected:
	T _element;
	UFDSetElement<T> *_parent;
	int _rank;

	// methods
public:
	UFDSetElement(T x);

	// getters
	T getElement();
	UFDSetElement<T>* getParent();
	int getRank();

	// setters
	void setElement(T x);
	void setParent(UFDSetElement<T> *parent);
	void setRank(int rank);

};

#include "../src/UFDSetElement.hxx"

#endif

