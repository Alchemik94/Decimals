#include "Decimal.h"
#include <iostream>

using namespace std;

int main()
{
	long long int a = 12345678900987, b = 908649503, c = -2;

	Decimal ad(a), bd(b), cd(c);

	cout << ad;
	cout << " " << bd << " " << cd << "\n";

	Decimal sum = ad + bd;
	Decimal subtraction = ad - bd;
	Decimal product = ad*bd;
	Decimal division = ad / cd;
	Decimal modulo = ad%cd;

	cout << "sum = " << sum << "\n";
	cout << "subtraction = " << subtraction << "\n";
	cout << "product = " << product << "\n";
	cout << "division = " << division << "\n";
	cout << "modulo = " << modulo << "\n";

	return 0;
}