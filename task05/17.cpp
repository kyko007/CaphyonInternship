#include<iostream>
#include<vector>

using namespace std;

template<class T>
class ValueIterator {

	T it;
public:

	
	// Default constructible.
	ValueIterator() = default;
	ValueIterator(T iter) : it(iter) {}

	// Dereferencable.
	T operator*() const { return it; }

	// Pre- and post-incrementable.
	ValueIterator& operator++() { ++it; return *this; }
	ValueIterator operator++(int) { auto aux = ValueIterator(it); it++; return aux; }

	// Pre- and post-decrementable.
	ValueIterator& operator--() { --it; return *this; }
	ValueIterator operator--(int) { auto aux = ValueIterator(it); it--; return aux; }

	// Equality / inequality.
	bool operator==(const ValueIterator<T> value) { return this->it == value.it; }
	bool operator!=(const ValueIterator<T> value) { return this->it != value.it; }

};

template<class T>
class value_range
{
	T a, b;
public:
	value_range() : a(0), b(0) {};
	value_range(T a, T b) { this -> a = a, this -> b = b; }
	ValueIterator<T> begin() const { return ValueIterator<T>(a); }
	ValueIterator<T> end() const { return ValueIterator<T>(b); }

};

template<class T, class... Types>
constexpr T average(Types... args)
{
	//(..., (cout << args << " "));

	return (... + args) / sizeof...(args);
}

template<class T>
auto value_range_from(T& value)
{
	//cout << begin(value);
	return value_range(begin(value), end(value));
}

//template <class C>
//constexpr auto size(C && cont) noexcept
//{
//	return cont.size();
//}
//
//template <class T, std::size_t N>
//constexpr auto size(const T(&arr)[N]) noexcept
//{
//	return N;
//}
//
//template <class C>
//auto value_range_from(C && cont) -> value_range<decltype(size(cont))>
//{
//	return { 0, size(cont) };
//}


int main()
{

	//static_assert(average<float>(2, 3, 5, 2.4, 11, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10) > 8, "");
	cout << average<float>(2, 3, 5, 2.4, 11, 10) << '\n';
	
	value_range<int> vals{ 0, 10 };
	for (auto n : vals)
	{
		cout << n << ' ';
	}
	cout << '\n';
	
	int arr[]{ 2, 3, 5, 7, 11 };

	for (const auto &val : value_range_from(arr))
	{
		cout << *val << ' ';
	}
	cout << '\n';
	
	system("pause");

	return 0;
}
