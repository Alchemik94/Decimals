#ifndef __DECIMAL__
#define __DECIMAL__

#include <vector>

#define LET(a,b) (auto a = (b))
#define PB push_back

using namespace std;

typedef unsigned long long int ULLI;
typedef long long int LLI;

class Decimal
{
	vector<ULLI> v;
	short int sign; //short int to make it easier while multiplying or antyhing
	const ULLI base = 1000000000; //10^9 - gives us possibility to multiply without danger of getting out of range


	public:
		//constructors - different for signed and unsigned
		//we don't need any others - any value we can cast on this two
		//additionally we have no argument constructor setting our Decimal to 0
		Decimal(const ULLI& number)
		{
			sign = 1;
			while (number != 0)
			{
				v.PB(number%base);
				number /= base;
			}
		}
		Decimal(const LLI& number)
		{
			sign = ((number < 0) ? -1 : 1);
			while (number != 0)
			{
				v.PB(number%base);
				number /= base;
			}
		}
		Decimal()
		{
			sign = 1;
			v.PB(0);
		}
		Decimal(const Decimal& number)
		{
			this->sign = number.sign;
			this->v = number.v;
		}

		//three basic cases - any other can be represented as one of them
		Decimal& operator=(const Decimal& number)
		{
			this->sign = number.sign;
			this->v = number.v;
			return *this;
		}
		Decimal& operator=(const ULLI& number)
		{
			(*this) = Decimal(number);
		}
		Decimal& operator=(const LLI& number)
		{
			*this = Decimal(number);
			return *this;
		}
		

};

#endif