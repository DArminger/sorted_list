#include "sorted_list.h"
#include <algorithm>

template <typename T>
struct comparator
{
	bool operator()(T const & left, T const & right) const
	{
		return left > right;
	}
};

void test_list_less()
{
	swe4::sorted_list<int, std::less<int>> list;
	std::cout << "Is Empty: " << list.empty() << '\n';
	list.insert(5);
	list.insert(8);
	list.insert(2);
	list.insert(6);

	std::cout << list;

	std::cout << "Find 6: " << list.find(6) << '\n';
	std::cout << "Erase 6: " << list.erase(6) << '\n';

	std::cout << "Greatest element: " << list.back() << '\n';
	std::cout << "Smallest element: " << list.front() << '\n';

	std::cout << list;

	list.pop_front();
	std::cout << "Pop front: " << list;

	list.pop_back();
	std::cout << "Pop back: " << list;

	list.insert(9);
	list.insert(8);
	list.insert(2);
	list.insert(6);

	std::cout << list;
	list.clear();

	list.insert(10);
	list.insert(2);
	list.insert(5);
	list.insert(1);
	list.insert(25);
	list.insert(16);
	list.insert(13);
	list.insert(11);
	list.insert(30);

	std::cout << "-----------------------Normal iterator----------------------\n";
	for (auto it = list.begin(); it != list.end(); it++)
	{
		std::cout << *it << "\t";
	}
	std::cout << '\n';
	std::cout << "-----------------------Reverse iterator----------------------\n";
	for (auto it = list.rbegin(); it != list.rend(); it++)
	{
		std::cout << *it << "\t";
	}
	std::cout << '\n';
	std::cout << "-----------------------Deleting in range with erase----------------------\n";
	list.erase(list.begin(), list.end());
	std::cout << list;

	list.insert(10);
	list.insert(2);
	list.insert(5);
	list.insert(1);
	list.insert(25);
	list.insert(16);
	list.insert(13);
	list.insert(11);
	list.insert(30);
	std::cout << list;

	std::cout << "-----------------------Std::Transform----------------------\n";
	std::transform(list.begin(), list.end(), list.begin(), [](int i)->int
	{
			return i + 1;
	});
	std::cout << list;
	/*std::cout << "-----------------------Std::Copy----------------------\n";
	swe4::sorted_list<int, std::less<int>> copy;
	copy.insert(2);
	std::copy(list.begin(), list.end(), copy.begin());
	std::cout << copy;*/
}

void test_list_custom_comp()
{
	swe4::sorted_list<int, comparator<int>> list;
	std::cout << "Is Empty: " << list.empty() << '\n';
	list.insert(5);
	list.insert(8);
	list.insert(2);
	list.insert(6);

	std::cout << list;

	std::cout << "Find 6: " << list.find(6) << '\n';
	std::cout << "Erase 6: " << list.erase(6) << '\n';

	std::cout << "Greatest element: " << list.back() << '\n';
	std::cout << "Smallest element: " << list.front() << '\n';

	std::cout << list;

	list.pop_front();
	std::cout << "Pop front: " << list;

	list.pop_back();
	std::cout << "Pop back: " << list;

	list.insert(9);
	list.insert(8);
	list.insert(2);
	list.insert(6);

	std::cout << list;
	list.clear();

	list.insert(10);
	list.insert(2);
	list.insert(5);
	list.insert(1);
	list.insert(25);
	list.insert(16);
	list.insert(13);
	list.insert(11);
	list.insert(30);

	std::cout << "-----------------------Normal iterator----------------------\n";
	for (auto it = list.begin(); it != list.end(); it++)
	{
		std::cout << *it << "\t";
	}
	std::cout << '\n';
	std::cout << "-----------------------Reverse iterator----------------------\n";
	for (auto it = list.rbegin(); it != list.rend(); it++)
	{
		std::cout << *it << "\t";
	}
	std::cout << '\n';
	std::cout << "-----------------------Deleting in range with erase----------------------\n";
	list.erase(list.begin(), list.end());
	std::cout << list;
}

void test_list_greater()
{
	swe4::sorted_list<int, std::greater<int>> list;
	std::cout << "Is Empty: " << list.empty() << '\n';
	list.insert(5);
	list.insert(8);
	list.insert(2);
	list.insert(6);

	std::cout << list;

	std::cout << "Find 6: " << list.find(6) << '\n';
	std::cout << "Erase 6: " << list.erase(6) << '\n';

	std::cout << "Greatest element: " << list.back() << '\n';
	std::cout << "Smallest element: " << list.front() << '\n';

	std::cout << list;

	list.pop_front();
	std::cout << "Pop front: " << list;

	list.pop_back();
	std::cout << "Pop back: " << list;

	list.insert(9);
	list.insert(8);
	list.insert(2);
	list.insert(6);

	std::cout << list;
	list.clear();
	
	std::cout << "-----------------------Inserting new values----------------------\n";
	list.insert(10);
	list.insert(2);
	list.insert(5);
	list.insert(1);
	list.insert(25);
	list.insert(16);
	list.insert(16);
	list.insert(13);
	list.insert(11);
	list.insert(30);

	std::cout << "-----------------------Normal iterator----------------------\n";
	for (auto it = list.begin(); it != list.end(); it++)
	{
		std::cout << *it << "\t";
	}
	std::cout << '\n';
	std::cout << "-----------------------Reverse iterator----------------------\n";
	for (auto it = list.rbegin(); it != list.rend(); it++)
	{
		std::cout << *it << "\t";
	}
	std::cout << '\n';
	std::cout << "-----------------------Deleting with predicate----------------------\n";
	list.erase_if([](int i) -> bool
		{
			return i == 16;
		});
	std::cout << list;
	std::cout << "-----------------------Deleting with std::remove_if----------------------\n";
	std::remove_if(list.begin(), list.end(), [](int i) -> bool
		{
			return i == 25;
		});
	std::cout << list;
}

int main()
{
	std::cout << "------------------------------------TESTING STD::LESS-----------------------------------\n";
	test_list_less();
	std::cout << "------------------------------------TESTING STD::GREATER-----------------------------------\n";
	test_list_greater();
	std::cout << "------------------------------------TESTING CUSTOM COMPARATOR-----------------------------------\n";
	test_list_custom_comp();
	return 0;
}