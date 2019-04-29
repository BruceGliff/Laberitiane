#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

template <typename T>
class QSort
{
	T key_;
	unsigned int height_;
	QSort * left_;
	QSort * right_;

	/* HEIGHT WORK */
	unsigned int height(QSort * p);
	int bfactor(QSort * p);
	void fixheight(QSort* p);


	/* BALANCED */
	QSort * rotateright(QSort * p);
	QSort * rotateleft(QSort * q);
	QSort * balance(QSort * p);

	/* FIND MINIMAL NODES */
	QSort * findmin(QSort * p);

public:
	QSort(T key);

	/* DESTROY */
	void free();

	/*  PRINT NODES  */
	void print();

	/* ADDED NODES */
	QSort * insert(QSort * p, T k);

	/* DELETED NODES */
	QSort * removemin(QSort * p);
	QSort * remove(QSort * p, T k);

};
#include "Qsort.hpp"


/*!!!!!!!!!!!!!!!!!!! HEROCODE !!!!!!!!!!!!!!!!!!!*/
/*!!!!!!!!!!!!!!!!!!! HEROCODE !!!!!!!!!!!!!!!!!!!*/
/*!!!!!!!!!!!!!!!!!!! HEROCODE !!!!!!!!!!!!!!!!!!!*/
/*!!!!!!!!!!!!!!!!!!! HEROCODE !!!!!!!!!!!!!!!!!!!*/
/*!!!!!!!!!!!!!!!!!!! HEROCODE !!!!!!!!!!!!!!!!!!!*/
/*!!!!!!!!!!!!!!!!!!! HEROCODE !!!!!!!!!!!!!!!!!!!*/
/*!!!!!!!!!!!!!!!!!!! HEROCODE !!!!!!!!!!!!!!!!!!!*/
/*!!!!!!!!!!!!!!!!!!! HEROCODE !!!!!!!!!!!!!!!!!!!*/
/*!!!!!!!!!!!!!!!!!!! HEROCODE !!!!!!!!!!!!!!!!!!!*/

/* Need ObjectCore class */

template <>
class QSort<ObjectCore>
{
	ObjectCore * key_;
	unsigned int height_;
	QSort * left_;
	QSort * right_;

	/* HEIGHT WORK */
	unsigned int height(QSort * p);
	int bfactor(QSort * p);
	void fixheight(QSort* p);

	/* BALANCED */
	QSort * rotateright(QSort * p);
	QSort * rotateleft(QSort * q);
	QSort * balance(QSort * p);

	/* DELETED NODES */
	QSort * findmin(QSort * p);
	QSort * removemin(QSort * p);
	QSort * remove(QSort * p, ObjectCore * k);

public:
	QSort();
	QSort(ObjectCore * key);

	/* DESTROY */
	void free();

	/*  PRINT NODES  */
	void print();

	/* DRAW */
	void draw(sf::RenderWindow * window);

	/* ADDED NODES */
	QSort * insert(QSort * p, ObjectCore * k);
};
#include "QSortObj.hpp"