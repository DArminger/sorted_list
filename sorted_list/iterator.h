#pragma once

template<typename T>
class iterator
{
public:
	iterator() : current_node{ nullptr } {}
	iterator(node<T>* start) : current_node{ start } {}
	iterator(iterator const& copy)
	{
		this->current_node = copy.current_node;
	}

	virtual ~iterator() {}
	virtual iterator& operator=(const iterator& other)
	{
		this->current_node = other.current_node;
		return *this;
	}

	virtual bool operator==(const iterator& other) const
	{
		//Werte vergleichen fand ich hier keine Loesung, wegen dem one past end für den end iterator (nullptr deref).
		return current_node == other.current_node;
	}

	virtual bool operator!=(const iterator& other) const
	{
		return !(*this == other);
	}

	virtual T& operator*() const
	{
		return current_node->value;
	}

	virtual node<T>* operator->() const
	{
		return current_node;
	}

	virtual iterator& operator++ ()
	{
		this->current_node = this->current_node->next;
		return *this;
	}

	virtual iterator operator++ (int)
	{
		iterator old = *this;
		++(*this);
		return old;
	}

	virtual iterator& operator-- ()
	{
		this->current_node = this->current_node->previous;
		return *this;
	}

	virtual iterator operator-- (int)
	{
		iterator old = *this;
		--(*this);
		return old;
	}

	virtual void swap(iterator& left, iterator& right)
	{
		//Oder std::swap
		T temp = *left;
		*left = *right;
		*right = temp;
	}

protected:
	node<T>* current_node;
};

template<typename T>
class reverse_iterator : public iterator<T>
{
public:
	reverse_iterator() : iterator<T>() {}
	reverse_iterator(node<T>* start) : iterator<T>(start) {}
	reverse_iterator(reverse_iterator const& copy)
	{
		this->current_node = copy.current_node;
	}
	~reverse_iterator() {}
	iterator<T>& operator-- () override
	{
		this->current_node = this->current_node->next;
		return *this;
	}

	iterator<T> operator-- (int) override
	{
		reverse_iterator old = *this;
		++(*this);
		return old;
	}

	iterator<T>& operator++ () override
	{
		this->current_node = this->current_node->previous;
		return *this;
	}

	iterator<T> operator++ (int) override
	{
		reverse_iterator old = *this;
		--(*this);
		return old;
	}
};