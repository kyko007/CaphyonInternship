#include <iostream>
#include <fstream>
#include <cstring>
#include <string>

using namespace std;

inline string ltrim(string s)
{
	int position = 0;
	while (position < s.size() && s[position] == ' ')
	{
		position++;
	}

	return s.substr(position);
}

inline string rtrim(string s)
{
	int position = s.size() - 1;
	while (position >= 0 && s[position] == ' ')
	{
		position--;
	}

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