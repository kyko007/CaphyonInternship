#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <regex>
using namespace std;

string restrictions = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ01234567890_`!@#$%^&*()_+-=[]{};':,./<>?\|";

inline string ltrim(string s)
{
	size_t position = s.find_first_of(restrictions);
	if (position == string::npos)
		return "";

	return s.substr(position);
}

inline string rtrim(string s)
{
	size_t position = s.find_last_of(restrictions);
	if (position == string::npos)
		return "";

	return s.substr(0, position + 1);
}

inline string trim(string s)
{
	return ltrim(rtrim(s));
}

int correctness_test_ltrim() {
	int failures = 0;
	if (!("I love my instructor" == ltrim("I love my instructor"))) ++failures;
	if (!("I love my instructor" == ltrim("   I love my instructor"))) ++failures;
	if (!("I love my instructor  " == ltrim("I love my instructor  "))) ++failures;
	if (!("I love my instructor  " == ltrim(" I love my instructor  "))) ++failures;
	if (!("" == ltrim(""))) ++failures;
	if (!("" == ltrim("  "))) ++failures;
	return failures;
}

int correctness_test_rtrim() {
	int failures = 0;
	if (!("I love my instructor" == rtrim("I love my instructor"))) ++failures;
	if (!("   I love my instructor" == rtrim("   I love my instructor"))) ++failures;
	if (!("I love my instructor" == rtrim("I love my instructor  "))) ++failures;
	if (!(" I love my instructor" == rtrim(" I love my instructor  "))) ++failures;
	if (!("" == rtrim(""))) ++failures;
	if (!("" == rtrim("  "))) ++failures;
	return failures;
}

int correctness_test_trim() {
	int failures = 0;
	if (!("I love my instructor" == trim("I love my instructor"))) ++failures;
	if (!("I love my instructor" == trim("   I love my instructor"))) ++failures;
	if (!("I love my instructor" == trim("I love my instructor  "))) ++failures;
	if (!("I love my instructor" == trim(" I love my instructor  "))) ++failures;
	if (!("" == trim(""))) ++failures;
	if (!("" == trim("  "))) ++failures;
	return failures;
}

int main()
{
	cout << correctness_test_ltrim() << '\n';
	cout << correctness_test_rtrim() << '\n';
	cout << correctness_test_trim() << '\n';
	char ch;
	cin >> ch;
}
