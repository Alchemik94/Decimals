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
		//constructors
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
		Decimal(const float& number)
		{
			*this = Decimal((LLI)number);
		}
		Decimal(const double& number)
		{
			*this = Decimal((LLI)number);
		}
		Decimal(const int& number)
		{
			*this = Decimal((LLI)number);
		}
		Decimal(const unsigned int& number)
		{
			*this = Decimal((ULLI)number);
		}
		Decimal(const long int& number)
		{
			*this = Decimal((LLI)number);
		}
		Decimal(const unsigned long int& number)
		{
			*this = Decimal((ULLI)number);
		}
		Decimal(const short int& number)
		{
			*this = Decimal((LLI)number);
		}
		Decimal(const unsigned short int& number)
		{
			*this = Decimal((ULLI)number);
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
		Decimal& operator=(const float& number)
		{
			return *this = Decimal(number);
		}
		Decimal& operator=(const double& number)
		{
			return *this = Decimal(number);
		}
		Decimal& operator=(const int& number)
		{
			return *this = Decimal(number);
		}
		Decimal& operator=(const unsigned int& number)
		{
			return *this = Decimal(number);
		}
		Decimal& operator=(const long int& number)
		{
			return *this = Decimal(number);
		}
		Decimal& operator=(const unsigned long int& number)
		{
			return *this = Decimal(number);
		}
		Decimal& operator=(const short int& number)
		{
			return *this = Decimal(number);
		}
		Decimal& operator=(const unsigned short int& number)
		{
			return *this = Decimal(number);
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
					number.Repair();
					return number;
				}
				else if (number.Abs() < tmp.Abs())
				{
					for (; i >= 0; --i)
						tmp.v[i] -= number.v[i];
					tmp.Repair();
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

		//bit operations - not optimalized at all
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