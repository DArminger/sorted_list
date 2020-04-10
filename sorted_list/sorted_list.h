#pragma once
#include <functional>
#include <iostream>
#include "node.h"

namespace swe4
{
	template<typename T, typename C = std::less<T>>
	class sorted_list
	{
	public:
		sorted_list()
		{

		}

		~sorted_list()
		{
			clear();
		}

		template<typename T>
		class sorted_list_iterator
		{
		public:
			sorted_list_iterator() : current_node{ nullptr } {}
			sorted_list_iterator(node<T>* start) : current_node{ start } {}
			sorted_list_iterator(sorted_list_iterator const& copy)
			{
				this->current_node = copy.current_node;
			}
			~sorted_list_iterator(){}
			sorted_list_iterator& operator=(const sorted_list_iterator & other)
			{
				this->current_node = other.current_node;
				return *this;
			}

			bool operator==(const sorted_list_iterator & other) const
			{
				//Werte vergleichen fand ich hier keine Loesung, wegen dem one past end für den end iterator (nullptr deref).
				return current_node == other.current_node;
			}

			bool operator!=(const sorted_list_iterator& other) const
			{
				return !(*this == other);
			}

			T& operator*() const
			{
				return current_node->value;
			}

			node<T>* operator->() const
			{
				return current_node;
			}

			sorted_list_iterator& operator++ ()
			{
				this->current_node = this->current_node->next;
				return *this;
			}

			sorted_list_iterator operator++ (int)
			{
				sorted_list_iterator old = *this;
				++(*this);
				return old;
			}

			sorted_list_iterator operator-- ()
			{
				this->current_node = this->current_node->previous;
				return *this;
			}

			sorted_list_iterator operator-- (int)
			{
				sorted_list_iterator old = *this;
				--(*this);
				return old;
			}

			void swap(sorted_list_iterator& left, sorted_list_iterator& right)
			{
				//Oder std::swap
				T temp = *left;
				*left = *right;
				*right = temp;
			}

		private:
			node<T>* current_node;
		};

		sorted_list_iterator<T> begin()
		{
			return sorted_list_iterator<T>(m_head);
		}

		sorted_list_iterator<T> end()
		{
			return sorted_list_iterator<T>(m_tail->next);
		}

		sorted_list_iterator<T> rbegin()
		{
			return sorted_list_iterator<T>(m_head);
		}

		sorted_list_iterator<T> rend()
		{
			return sorted_list_iterator<T>(m_tail->next);
		}

		void insert(const T& value)
		{
			auto new_node = new node<T>(value);
			element_count++;

			if (m_head == nullptr) {
				m_head = new_node;
				m_tail = m_head;
				return;
			}


			//insert at the front
			if (comp(new_node->value, m_head->value))
			{
				new_node->next = m_head;
				m_head->previous = new_node;
				m_head = new_node;
				return;
			}

			//insert at the end
			if (!comp(new_node->value, m_tail->value))
			{
				new_node->previous = m_tail;
				m_tail->next = new_node;
				m_tail = new_node;
				return;
			}

			//insert to middle
			auto temp = m_head;
			while (temp && !comp(new_node->value, temp->value))
			{
				temp = temp->next;
			}
			if (temp)
			{
				new_node->next = temp;
				new_node->previous = temp->previous;
				temp->previous->next = new_node;
				temp->previous = new_node;
			}
		}

		T& back() const
		{
			if (m_tail->value > m_head->value)
				return m_tail->value;
			return m_head->value;
		}


		void clear()
		{
			if (element_count == 0) return;
			auto i = m_head;
			while (i != nullptr)
			{
				auto temp = i;
				i = i->next;
				delete temp;
				temp = nullptr;
			}
			m_head = nullptr;
			m_tail = nullptr;
			element_count = 0;
		}


		bool empty() const
		{
			return element_count == 0;
		}


		T& front() const
		{
			if (m_head->value < m_tail->value)
				return m_head->value;
			return m_tail->value;
		}


		void pop_back()
		{
			if (m_tail->value > m_head->value)
			{
				auto temp = m_tail;
				m_tail = m_tail->previous;
				m_tail->next = nullptr;
				delete temp;
				temp = nullptr;
				element_count--;
			}
			else {
				auto temp = m_head;
				m_head = m_head->next;
				m_head->previous = nullptr;
				delete temp;
				temp = nullptr;
				element_count--;
			}
		}


		void pop_front()
		{
			if (m_head->value < m_tail->value)
			{
				auto temp = m_head;
				m_head = m_head->next;
				m_head->previous = nullptr;
				delete temp;
				temp = nullptr;
				element_count--;
			}
			else {
				auto temp = m_tail;
				m_tail = m_tail->previous;
				m_tail->next = nullptr;
				delete temp;
				temp = nullptr;
				element_count--;
			}
		}


		size_t size() const
		{
			return element_count;
		}



		bool find(const T& value) const
		{
			for (auto temp = m_head; temp != nullptr; temp = temp->next)
			{
				if (temp->value == value)
				{
					return true;
				}
			}
			return false;
		}


		bool erase(const T& value)
		{
			for (auto temp = m_head; temp != nullptr; temp = temp->next)
			{
				if (temp->value == value)
				{
					temp->previous->next = temp->next;
					temp->next->previous = temp->previous;
					delete temp;
					temp = nullptr;

					element_count--;
					return true;
				}
			}
			return false;
		}

		friend std::ostream& operator<< (std::ostream& out, sorted_list<T, C>& lhs)
		{
			if (!lhs.empty())
				return lhs.print(out);
			return out << "List is empty!" << '\n';
		}

	private:
		std::ostream& print(std::ostream& out) const
		{
			for (node<T>* i = m_head; i != nullptr; i = i->next)
			{
				out << i->value;
			}
			out << '\n';
			return out;
		}

		node<T>* m_head{ nullptr };
		node<T>* m_tail{ nullptr };
		C comp;
		size_t element_count{ 0 };
	};
}


