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

public:
	QSort(T key) :
		key_(key),
		height_(1),
		left_(0),
		right_(0)
	{}

	/* HEIGHT WORK */
	unsigned int height(QSort * p)
	{
		return p ? p->height_ : 0;
	}

	int bfactor(QSort * p)
	{
		return height(p->right_) - height(p->left_);
	}

	void fixheight(QSort* p)
	{
		unsigned int hl = height(p->left_);
		unsigned int hr = height(p->right_);
		p->height_ = (hl > hr ? hl : hr) + 1;
	}


	/* BALANCED */
	QSort * rotateright(QSort * p)
	{
		QSort * q = p->left_;
		p->left_ = q->right_;
		q->right_ = p;
		fixheight(p);
		fixheight(q);
		return q;
	}

	QSort * rotateleft(QSort * q)
	{
		QSort * p = q->right_;
		q->right_ = p->left_;
		p->left_ = q;
		fixheight(q);
		fixheight(p);
		return p;
	}

	QSort * balance(QSort * p)
	{
		fixheight(p);
		if (bfactor(p) == 2)
		{
			if (bfactor(p->right_) < 0)
				p->right_ = rotateright(p->right_);
			return rotateleft(p);
		}
		if (bfactor(p) == -2)
		{
			if (bfactor(p->left_) > 0)
				p->left_ = rotateleft(p->left_);
			return rotateright(p);
		}
		return p;
	}

	/* ADDED NODES */
	QSort * insert(QSort * p, T k)
	{
		if (!p) return new QSort(k);
		if (k < p->key_)
			p->left_ = insert(p->left_, k);
		else
			p->right_ = insert(p->right_, k);
		return balance(p);
	}

	/*  PRINT NODES  */
	void print()
	{
		if (this->left_)
			this->left_->print();
		std::cout << key_  << '\n';
		if (this->right_)
			this->right_->print();
	}

	/* DELETED NODES */
	QSort * findmin(QSort * p)
	{
		return p->left_ ? findmin(p->left_) : p;
	}

	QSort * removemin(QSort * p)
	{
		if (p->left_ == 0)
			return p->right_;
		p->left_ = removemin(p->left_);
		return balance(p);
	}

	QSort * remove(QSort * p, T k)
	{
		if (!p) return 0;
		if (k < p->key_)
			p->left_ = remove(p->left_, k);
		else if (k > p->key_)
			p->right_ = remove(p->right_, k);
		else
		{
			QSort * q = p->left_;
			QSort * r = p->right_;
			delete p;
			if (!r) return q;
			QSort * min = findmin(r);
			min->right_ = removemin(r);
			min->left_ = q;
			return balance(min);
		}
		return balance(p);
	}

	void free()
	{
		if (left_ != nullptr)
		{
			left_->free();
		}
		if (right_ != nullptr)
		{
			right_->free();
		}
		delete this;
	}

};


/*!!!!!!!!!!!!!!!!!!! HEROCODE !!!!!!!!!!!!!!!!!!!*/
/*!!!!!!!!!!!!!!!!!!! HEROCODE !!!!!!!!!!!!!!!!!!!*/
/*!!!!!!!!!!!!!!!!!!! HEROCODE !!!!!!!!!!!!!!!!!!!*/
/*!!!!!!!!!!!!!!!!!!! HEROCODE !!!!!!!!!!!!!!!!!!!*/
/*!!!!!!!!!!!!!!!!!!! HEROCODE !!!!!!!!!!!!!!!!!!!*/
/*!!!!!!!!!!!!!!!!!!! HEROCODE !!!!!!!!!!!!!!!!!!!*/
/*!!!!!!!!!!!!!!!!!!! HEROCODE !!!!!!!!!!!!!!!!!!!*/
/*!!!!!!!!!!!!!!!!!!! HEROCODE !!!!!!!!!!!!!!!!!!!*/
/*!!!!!!!!!!!!!!!!!!! HEROCODE !!!!!!!!!!!!!!!!!!!*/

template <>
class QSort<ObjectCore>
{
	ObjectCore * key_;
	unsigned int height_;
	QSort * left_;
	QSort * right_;

public:
	QSort() :
		key_(nullptr),
		height_(0),
		left_(0),
		right_(0)
	{}

	QSort(ObjectCore * key) :
		key_(key),
		height_(1),
		left_(0),
		right_(0)
	{}

	/* HEIGHT WORK */
	unsigned int height(QSort * p)
	{
		return p ? p->height_ : 0;
	}

	int bfactor(QSort * p)
	{
		return height(p->right_) - height(p->left_);
	}

	void fixheight(QSort* p)
	{
		unsigned int hl = height(p->left_);
		unsigned int hr = height(p->right_);
		p->height_ = (hl > hr ? hl : hr) + 1;
	}


	/* BALANCED */
	QSort * rotateright(QSort * p)
	{
		QSort * q = p->left_;
		p->left_ = q->right_;
		q->right_ = p;
		fixheight(p);
		fixheight(q);
		return q;
	}

	QSort * rotateleft(QSort * q)
	{
		QSort * p = q->right_;
		q->right_ = p->left_;
		p->left_ = q;
		fixheight(q);
		fixheight(p);
		return p;
	}

	QSort * balance(QSort * p)
	{
		fixheight(p);
		if (bfactor(p) == 2)
		{
			if (bfactor(p->right_) < 0)
				p->right_ = rotateright(p->right_);
			return rotateleft(p);
		}
		if (bfactor(p) == -2)
		{
			if (bfactor(p->left_) > 0)
				p->left_ = rotateleft(p->left_);
			return rotateright(p);
		}
		return p;
	}

	/* ADDED NODES */
	QSort * insert(QSort * p, ObjectCore * k)
	{
		if (!p) return new QSort(k);
		if (k->getY() < p->key_->getY())
			p->left_ = insert(p->left_, k);
		else
			p->right_ = insert(p->right_, k);
		return balance(p);
	}

	/*  PRINT NODES  */
	void print()
	{
		if (this->left_)
			this->left_->print();
		std::cout << key_->getY() << '\n';
		if (this->right_)
			this->right_->print();
	}

	/* DRAW */
	void draw(sf::RenderWindow * window)
	{
		if (left_)
			left_->draw(window);
		key_->draw(window);
		if (right_)
			right_->draw(window);
	}

	/* DELETED NODES */
	QSort * findmin(QSort * p)
	{
		return p->left_ ? findmin(p->left_) : p;
	}

	QSort * removemin(QSort * p)
	{
		if (p->left_ == 0)
			return p->right_;
		p->left_ = removemin(p->left_);
		return balance(p);
	}

	QSort * remove(QSort * p, ObjectCore * k)
	{
		if (!p) return 0;
		if (k->getY() < p->key_->getY())
			p->left_ = remove(p->left_, k);
		else if (k > p->key_)
			p->right_ = remove(p->right_, k);
		else
		{
			QSort * q = p->left_;
			QSort * r = p->right_;
			delete p;
			if (!r) return q;
			QSort * min = findmin(r);
			min->right_ = removemin(r);
			min->left_ = q;
			return balance(min);
		}
		return balance(p);
	}

	void free()
	{
		if (left_ != nullptr)
		{
			left_->free();
		}
		if (right_ != nullptr)
		{
			right_->free();
		}
		delete this;
	}

};