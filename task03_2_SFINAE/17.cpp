#include<iostream>
#include<type_traits>
#include<typeinfo>

using namespace std;

template <class T>
constexpr auto threshold = static_cast<T>(0.0000010);

template <class T>
constexpr T absolute(T val)
{
	return val < T{ 0 } ? -val : val;
} 

template <class T>
constexpr T close_enough(T a, T b)
{
	if constexpr (! (is_floating_point_v<T>) )
		return a == b;
	else
		return absolute(a - b) <= threshold<T>;
}

int main()
{
	static_assert(close_enough(3, 3), "");
	static_assert(!close_enough(3, 4), "");
	static_assert(close_enough(3.0f, 10.0f - 7), "");
	static_assert(close_enough(3.0, 1.0 + 2.0), "");

	cout << "abcd";
	system("pause");

	return 0;
}
