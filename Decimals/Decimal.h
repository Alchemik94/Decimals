#ifndef __DECIMAL__
#define __DECIMAL__

#include <vector>

#define LET(a,b) (auto a = (b))
#define PB push_back
#define MAX(a,b) ((a)<(b) ? (b) : (a))
#define MIN(a,b) ((a)<(b) ? (a) : (b))

using namespace std;

typedef unsigned long long int ULLI;
typedef long long int LLI;

class Decimal
{
	vector<ULLI> v;
	short int sign; //short int to make it easier while multiplying or antyhing
	const ULLI base = 1000000000; //10^9 - gives us possibility to multiply without danger of getting out of range
	
	//if any cell has bigger value than expected, we have to repair our structure and move rest to the next cell
	void Repair()
	{
		for (int i = 0; i < this->v.size(); ++i)
		if (this->v[i]>base)
		{
			if (i + 1 < this->v.size())
			{
				this->v[i + 1] += this->v[i] / base;
				this->v[i] %= base;
			}
			else
			{
				this->v.PB(this->v[i] / base);
				this->v[i] %= base;
			}
		}
	}

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
		
		//TODO - another signs of decimals
		Decimal operator+(Decimal number)
		{
			Decimal tmp(*this);
			int i = MIN(number.v.size(),tmp.v.size());
			if (number.v.size() > tmp.v.size())
			{
				for (; i >= 0; --i)
					number.v[i] += tmp.v[i];
				number.Repair();
				return number;
			}
			else
			{
				for (; i >= 0; --i)
					tmp.v[i] += number.v[i];
				tmp.Repair();
				return tmp;			
			}

		}

};

#undef LET(a,b)
#undef PB
#undef MAX
#undef MIN

#endif