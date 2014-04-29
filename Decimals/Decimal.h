#ifndef __DECIMAL__
#define __DECIMAL__

#include <vector>
#include <string>

#include <iostream>

#define LET(a,b) (auto a = (b))
#define PB push_back
#define MAX(a,b) ((a)<(b) ? (b) : (a))
#define MIN(a,b) ((a)<(b) ? (a) : (b))

using namespace std;

typedef unsigned long long int ULLI;
typedef long long int LLI;

class Decimal
{
	vector<LLI> v;
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
		
		//deleting leading zeroes
		while (this->v[this->v.size() - 1] == 0) this->v.pop_back();
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
		//TODO:
		Decimal(string str)
		{
		
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
		
		//absolute value
		Decimal Abs()
		{
			Decimal tmp(*this);
			tmp.sign = 1;
			return tmp;
		}

		//conversion to string
		string ToStr()
		{

		}

		//comparators
		int operator()(const Decimal& number) const
		{
			if (this->sign < number.sign)
				return -1;
			else if (this->sign > number.sign)
				return 1;
			else
			{
				if (this->v.size() > number.v.size())
				{
					if (this->sign < 0)
						return -1;
					else return 1;
				}
				else if (this->v.size() < number.v.size())
				{
					if (this->sign < 0)
						return 1;
					else return -1;
				}
				else
				{
					for (int i = this->v.size()-1; i>=0; --i)
					{
						if (this->v[i]>number.v[i])
						{
							if (this->sign < 0)
								return -1;
							else return 1;
						}
						else if (this->v[i] < number.v[i])
						{
							if (this->sign < 0)
								return 1;
							else return -1;
						}
					}
					return 0;
				}
			}
		}
		bool operator<(const Decimal& number) const
		{
			return (this->operator()(number) == -1);
		}
		bool operator>(const Decimal& number) const
		{
			return this->operator()(number) == 1;
		}
		bool operator==(const Decimal& number) const
		{
			return this->operator()(number) == 0;
		}
		bool operator>=(const Decimal& number) const
		{
			return (*this < number) == 0;
		}
		bool operator<=(const Decimal& number) const
		{
			return (*this>number) == 0;
		}

		Decimal operator+(Decimal number)
		{
			Decimal tmp(*this);
			int i = MIN(number.v.size(),tmp.v.size());
			//the same sign
			if (number.sign == tmp.sign)
			{
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
			//another signs
			else
			{
				if (number.Abs() > tmp.Abs())
				{
					for (; i >= 0; --i)
						number.v[i] -= tmp.v[i];
					return number;
				}
				else if (number.Abs() < tmp.Abs())
				{
					for (; i >= 0; --i)
						tmp.v[i] -= number.v[i];
					return tmp;
				}
			}
		}
		Decimal& operator+=(Decimal& number)
		{
			*this = *this + number;
			return *this;
		}
		Decimal& operator++()
		{
			*this += Decimal((ULLI)1);
			return *this;
		}
		Decimal operator++(int)
		{
			Decimal tmp(*this);
			++*this;
			return tmp;
		}

		Decimal operator-(Decimal number)
		{
			number.sign *= -1;
			return *this + number;
		}
		Decimal& operator-=(Decimal& number)
		{
			*this = *this - number;
			return *this;
		}
		Decimal& operator--()
		{
			*this -= Decimal((ULLI)1);
			return *this;
		}
		Decimal operator--(int)
		{
			Decimal tmp(*this);
			--*this;
			return tmp;
		}

		//TODO:
		Decimal operator*(Decimal number)
		{
			
		}
		Decimal& operator*=(Decimal& number)
		{
			*this = *this * number;
			return *this;
		}

		//TODO:
		Decimal operator/(Decimal number)
		{

		}
		Decimal& operator/=(Decimal& number)
		{
			*this = *this / number;
			return *this;
		}

		//TODO:
		Decimal operator%(Decimal number)
		{
			
		}
		Decimal& operator%=(Decimal& number)
		{
			*this = *this % number;
			return *this;
		}

		Decimal operator<<(Decimal number)
		{
			Decimal tmp(*this);
			for (Decimal i((ULLI)(0)); i < number; ++i)
			{
				tmp *= Decimal((ULLI)2);
			}
			return tmp;
		}
		Decimal operator>>(Decimal number)
		{
			Decimal tmp(*this);
			for (Decimal i((ULLI)(0)); i < number; ++i)
			{
				tmp /= Decimal((ULLI)2);
			}
			return tmp;
		}

		//input and output
		friend ostream& operator<<(ostream& output, const Decimal& number)
		{
			return output << number.ToStr();
		}
		friend istream& operator>>(istream& input, Decimal& number)
		{
			string str;
			cin >> str;
			*this = Decimal(str);
			return cin;
		}
		

};

#undef LET(a,b)
#undef PB
#undef MAX
#undef MIN

#endif