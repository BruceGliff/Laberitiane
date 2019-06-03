#include "Qsort.h"

template <typename T>
QSort<T>::QSort(T key) :
	key_(key),
	height_(1),
	left_(0),
	right_(0)
{}

/* HEIGHT WORK */
template <typename T>
unsigned int QSort<T>::height(QSort * p)
{
	return p ? p->height_ : 0;
}

template <typename T>
int QSort<T>::bfactor(QSort * p)
{
	return height(p->right_) - height(p->left_);
}

template <typename T>
void QSort<T>::fixheight(QSort* p)
{
	unsigned int hl = height(p->left_);
	unsigned int hr = height(p->right_);
	p->height_ = (hl > hr ? hl : hr) + 1;
}

/* BALANCED */
template <typename T>
QSort<T> * QSort<T>::rotateright(QSort * p)
{
	QSort * q = p->left_;
	p->left_ = q->right_;
	q->right_ = p;
	fixheight(p);
	fixheight(q);
	return q;
}

template <typename T>
QSort<T> * QSort<T>::rotateleft(QSort * q)
{
	QSort * p = q->right_;
	q->right_ = p->left_;
	p->left_ = q;
	fixheight(q);
	fixheight(p);
	return p;
}

template <typename T>
QSort<T> * QSort<T>::balance(QSort * p)
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

/* FIND MINIMAL NODES */
template <typename T>
QSort<T> * QSort<T>::findmin(QSort * p)
{
	return p->left_ ? findmin(p->left_) : p;
}

/* DESTROY */
template <typename T>
void QSort<T>::free()
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

/*  PRINT NODES  */
template <typename T>
void QSort<T>::print()
{
	if (this->left_)
		this->left_->print();
	//std::cout << key_ << '\n';
	if (this->right_)
		this->right_->print();
}

/* ADDED NODES */
template <typename T>
QSort<T> * QSort<T>::insert(QSort * p, T k)
{
	if (!p) return new QSort(k);
	if (k < p->key_)
		p->left_ = insert(p->left_, k);
	else
		p->right_ = insert(p->right_, k);
	return balance(p);
}

/* DELETED NODES */
template <typename T>
QSort<T> * QSort<T>::removemin(QSort * p)
{
	if (p->left_ == 0)
		return p->right_;
	p->left_ = removemin(p->left_);
	return balance(p);
}

template <typename T>
QSort<T> * QSort<T>::remove(QSort * p, T k)
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


