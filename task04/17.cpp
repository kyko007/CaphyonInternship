#include<iostream>
#include<vector>

using namespace std;


template<typename T, typename... Types>
constexpr T average(Types... args)
{
	return (... + args) / sizeof...(args);
}


int main()
{

	static_assert(average<float>(2, 3, 5, 2.4, 11, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10) > 8, "");
	cout << average<float>(2, 3, 5, 2.4, 11, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10 ) << '\n';
	
	system("pause");

	return 0;
}
