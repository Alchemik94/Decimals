#include "Decimal.h"
#include <iostream>
#include <string>

using namespace std;

int main()
{
	long long int a = 13066099060603, b = 908649503, c = -3;

	string str = "183495834275845820934890268438985910853476892535890428592043768178954758234768903248695723895710854127584237589042376817485014895023740856740923859023468904328590428593427689532758438250984237684328509124858904237089584319057238678890432850934275089342";

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
	Decimal division = ad / cd;
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