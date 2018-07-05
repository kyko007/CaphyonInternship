#include<iostream>
#include<string>
#include<stdexcept>
#include<optional>

using namespace std;


pair<int, bool> integral_div(int num, int denom)
{
	if(denom != 0)
		return { num / denom, true };

	return {-1, false};
}

/*std::optional<int> integral_div(int num, int denom)
{
	if (denom != 0)
		return num / denom;

	return {};
}*/

int main() {

	
	//integral_div(3, 1).has_value() ? cout << integral_div(3,1).value() << '\n' : cout << "Division by 0";
	//integral_div(3, 0).has_value() ? cout << integral_div(3, 0).value() << '\n' : cout << "Division by 0";
	
	/*cout << integral_div(0, 3).value() << '\n';
	cout << integral_div(1, 1).value() << '\n';
	cout << integral_div(2, 2).value() << '\n';
	cout << integral_div(5372547, 613463).value() << '\n';
	cout << integral_div(10, 4).value() << '\n';
	cout << integral_div(4, 0).value() << '\n';
	cout << integral_div(10, 0).value() << '\n';
	cout << integral_div(0, 0).value() << '\n';*/

	if (int num, denom; cin >> num >> denom)
	{
		if ( auto [x, y] = integral_div(num, denom) ; y)
			cout << x << endl;
		else
			cerr << "Division by zero\n";
	}


	char ch;
	cin >> ch;

	pair<int, bool> p = pair<int, bool>(2, true);
	pair<int, bool> p2 = make_pair(2, true);
	auto p3 = make_pair(2, true);
	auto p4 = pair(2, true); // C++17
	pair<int,bool> p5 = {2, true};

	struct A
	{
		int mI;
		bool mB;
		const char * const mBuf;
	};

	auto a = A{2, true, "fds"};

	return 0;
}
