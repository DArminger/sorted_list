#pragma once
#include <functional>
#include <iostream>
#include "node.h"
#include "iterator.h"

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

		iterator<T> begin()
		{
			return iterator<T>(m_head);
		}

		iterator<T> end()
		{
			return iterator<T>(m_tail->next);
		}

		reverse_iterator<T> rbegin()
		{
			return reverse_iterator<T>(m_tail);
		}

		reverse_iterator<T> rend()
		{
			return reverse_iterator<T>(m_head->previous);
		}

		std::pair<iterator<T>, bool> insertPair(const T& value)
		{
			auto new_node = new node<T>(value);
			element_count++;

			if (m_head == nullptr) {
				m_head = new_node;
				m_tail = m_head;
				return std::make_pair(iterator<T>(m_head), true);
			}


			if (comp(new_node->value, m_head->value))
			{
				new_node->next = m_head;
				m_head->previous = new_node;
				m_head = new_node;
				return std::make_pair(iterator<T>(m_head), true);
			}

			if (!comp(new_node->value, m_tail->value))
			{
				new_node->previous = m_tail;
				m_tail->next = new_node;
				m_tail = new_node;
				return std::make_pair(iterator<T>(m_tail), true);;
			}

			auto temp = m_head;
			while (temp && !comp(new_node->value, temp->value))
			{
				temp = temp->next;
			}
			if (temp != nullptr)
			{
				new_node->next = temp;
				new_node->previous = temp->previous;
				temp->previous->next = new_node;
				temp->previous = new_node;
				std::make_pair(iterator<T>(new_node), true);
			}

			element_count--;
			return std::make_pair(iterator<T>(nullptr), false);
		}

		iterator<T> insert(iterator<T> hint, const T& value)
		{
			auto new_node = new node<T>(value);

			auto temp = hint.current_node;
			while (temp && !comp(new_node->value, temp->value))
			{
				temp = temp->next;
			}
			if (temp != nullptr)
			{
				new_node->next = temp;
				new_node->previous = temp->previous;
				temp->previous->next = new_node;
				temp->previous = new_node;
				element_count++;
				return iterator<T>(temp);
			}
			return iterator<T>(nullptr);
		}

		void erase(iterator<T> first, iterator<T> last)
		{
			auto it = first;
			node<T>* temp_first_before{ nullptr };
			node<T>* temp_last_after{ nullptr };
			bool before{ false };
			bool after{ false };
			
			if (first != m_head && first != nullptr) {
				temp_first_before = first.current_node->previous;
				before = true;
			}
			if (last != m_tail && last != nullptr) {
				temp_last_after = last.current_node;
				after = false;
			}			
			
			while (it != last)	//If none of the upper cases apply, then first and last are begin and end
			{
				auto temp = it;
				it = it.current_node->next;
				iterator<T>::delete_node(temp);
				temp = nullptr;
				element_count--;
			}
			if (before) {
				temp_first_before->next = temp_last_after;
			}
			if (after) {
				temp_last_after->previous = temp_first_before;
			}
			if(!before && !after)
			{
				m_head = nullptr;
				m_tail = nullptr;
			}
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

		template<class UnaryPredicate>
		void erase_if(UnaryPredicate p)
		{
			node<T>* before {nullptr};
			node<T>* after {nullptr};
			bool relink_before{ false };
			bool relink_after{ false };
			auto i = m_head;
			while(i != nullptr)
			{
				if (p(i->value))
				{
					if (i->previous != nullptr)
					{
						before = i->previous;
						relink_before = true;
					}
					if (i->next != nullptr)
					{
						after = i->next;
						relink_after = after;
					}
					if (relink_before)
					{
						before->next = after;
					}
					if (relink_after)
					{
						after->previous = before;
					}
					delete i;
					i = after;

					element_count--;
				}
				else i = i->next;
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
				out << i->value << '\t';
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


