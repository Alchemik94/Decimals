#include "Decimal.h"
#include <iostream>

#define __DEBUG__

using namespace std;

int main()
{
	long long int a = 12345678900987, b = 908649503, c = -2;

	Decimal ad(a), bd(b), cd(c);

	cout << ad;
	cout << " " << bd << " " << cd << "\n";



	return 0;
}