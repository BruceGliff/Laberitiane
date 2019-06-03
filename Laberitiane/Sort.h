#pragma once

#include <iostream>

template <typename T>
class Sort
{
	T key_;
	Sort * left_;
	Sort * right_;

public:
	Sort * insert(Sort * p, T key)
	{
		
		if (p == nullptr)
		{
			p = new Sort<T>;
			p->key_ = key;

			p->left_ = nullptr;
			p->right_ = nullptr;
			return p;
		}
		if (key < p->key_) 
		{
			p->left_ = insert(p->left_, key);
		}
		if (key >= p->key_)
		{

			p->right_ = insert(p->right_, key);
		}
		return p;
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

	void print()
	{
		if (left_ != nullptr)
			left_->print();
		//std::cout << key_ << '\n';
		if (right_ != nullptr)
			right_->print();
	}
};

template<>
class Sort<ObjectCore>
{
	ObjectCore * key_;
	Sort * left_;
	Sort * right_;

public:
	Sort * insert(Sort * p, ObjectCore * key)
	{
		if (p == nullptr)
		{
			p = new Sort;
			p->key_ = key;
			p->left_ = nullptr;
			p->right_ = nullptr;
			return p;
		}
		if (key->getY() < p->key_->getY())
			p->left_ = insert(p->left_, key);
		if (key->getY() >= p->key_->getY())
			p->right_ = insert(p->right_, key);
		return p;
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

	void print()
	{
		if (left_ != nullptr)
			left_->print();
		//std::cout << key_->getY() << '\n';
		if (right_ != nullptr)
			right_->print();
	}

	void draw(sf::RenderWindow * window)
	{
		if (left_)
			left_->draw(window);
		key_->draw(window);
		if (right_)
			right_->draw(window);
	}
};