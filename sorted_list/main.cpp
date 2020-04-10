#include "sorted_list.h"

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

	for (auto it = list.begin(); it != list.end(); it++)
	{
		std::cout << *it << "\t";
	}
	std::cout << '\n';
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

	list.insert(10);
	list.insert(2);
	list.insert(5);
	list.insert(1);
	list.insert(25);
	list.insert(16);
	list.insert(13);
	list.insert(11);
	list.insert(30);

	for (auto it = list.begin(); it != list.end(); it++)
	{
		std::cout << *it << "\t";
	}
	std::cout << '\n';
}

int main()
{
	std::cout << "-----------------------TESTING STD::LESS----------------------\n";
	test_list_less();
	std::cout << "-----------------------TESTING STD::GREATER----------------------\n";
	test_list_greater();
	return 0;
}