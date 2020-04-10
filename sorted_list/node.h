template<typename T>
struct node
{
	node(T value) : value{ value }, next{nullptr}, previous{nullptr}
	{
	}

	T value;
	node* next;
	node* previous;
};