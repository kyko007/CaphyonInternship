#include<iostream>
#include<map>
#include<string>
#include<vector>
#include<array>
#include<algorithm>
#include<unordered_map>

using namespace std;

template <typename T, int N>
typename std::enable_if< !(N<4 * 1024), vector<T> >::type
	create_temp_buffer()
{
	return vector<T>(N);
}

template <typename T, int N>
typename std::enable_if< N<4 * 1024, array<T, N> >::type
	create_temp_buffer()
{
	return array<T, N>{};
}

int main()
{
	auto lbi = create_temp_buffer<int, 1000>();
	auto lbd = create_temp_buffer<double, 1000>();

	fill(begin(lbi), end(lbi), -1);
	fill(begin(lbd), end(lbd), 3.14159);

	for (auto it : lbi)
	{
		cout << it << ' ';
	}
	cout << '\n';
	for (auto it : lbd)
	{
		cout << it << ' ';
	}
	cout << '\n';


	char ch;
	cin >> ch;
	return 0;
}
