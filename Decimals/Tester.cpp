#include "Decimal.h"
#include <iostream>
#include <string>

using namespace std;

int main()
{
	long long int a = 13066099060603, b = 4, c = -3;

	string str = "444444444444444444444444444444444444444444444444444444444444444444";

	Decimal ad(a), bd(b), cd(c);

	ad = Decimal(str);
	cout << ad;
	cout << " " << bd << " " << cd << "\n\n\n";

	cout << "\nPodaj ad = ";
	cin >> ad;
	cout << "ad = " << ad << "\n";

	Decimal sum = ad + bd;
	Decimal subtraction = ad - bd;
	Decimal product = ad*bd;
	Decimal division = ad / bd;
	Decimal modulo = ad%cd;

	cout << "sum = " << sum << "\n\n\n";
	cout << "subtraction = " << subtraction << "\n\n\n";
	cout << "product = " << product << "\n\n\n";
	cout << "division = " << division << "\n\n\n";
	cout << "modulo = " << modulo << "\n\n\n";

	cout << "\n\n\n\n\n\n\n\n\n" << Decimal(-2) - Decimal(4) << "\n\n\n\n\n";

	cout << (((ad / cd)*cd + ad%cd) == ad);
	return 0;
}