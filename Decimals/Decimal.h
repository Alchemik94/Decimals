#ifndef __DECIMAL__
#define __DECIMAL__

#ifdef __DEBUG__
#define dbg printf
#else
#define dbg
#endif


#include <vector>
#include <string>


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
	static const ULLI base = 1000000000; //10^9 - gives us possibility to multiply without danger of getting out of range
	static const ULLI powOfTen(int i)
	{
		static const ULLI pow[10] = { 1, 10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000, 1000000000 };
		return pow[i];
	}

	//if any cell has bigger value than expected, we have to repair our structure and move rest to the next cell
	//we also have to delete leading zeroes
	void Repair()
	{
		//borrowing bits
		for (int i = 0; i < this->v.size()-1; ++i)
		while (this->v[i]<0)
		{
			this->v[i + 1] -= 1;
			this->v[i] += base;
		}
		if (this->v[this->v.size() - 1] < 0)
		{
			this->v[this->v.size() - 1] *= -1;
			this->sign *= -1;
		}

		//moving our over-results
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
		while (this->v[this->v.size() - 1] == 0 && this->v.size()>1) this->v.pop_back();

		if (this->v.size() == 0) this->v.PB(0);
	}

	string Reverse(string str) const
	{
		string res = "";
		for (int i = str.length() - 1; i >= 0; --i)
			res += str[i];
		return res;
	}
	string Zeroes(int i) const
	{
		if (i == this->v.size() - 1)
			return "";
		string res = "";
		ULLI tmp = base / 10;
		while (tmp > this->v[i])
		{
			res += "0";
			tmp /= 10;
		}
		return res;
	}
	string Rest(int i) const
	{
		string res = "";
		ULLI tmp = this->v[i];
		while (tmp != 0)
		{
			res = res + (char)((char)(tmp % 10) + '0');
			tmp /= 10;
		}
		res = Reverse(res);
		return res;
	}

public:
	//constructors
	Decimal(ULLI number)
	{
		sign = 1;
		if (number == 0) v.PB(0);
		while (number != 0)
		{
			v.PB(number%base);
			number /= base;
		}
		Repair();
	}
	Decimal(LLI number)
	{
		if (number == 0) this->v.PB(0);
		sign = ((number < 0) ? -1 : 1);
		if (number < 0)
			number = -number;
		while (number != 0)
		{
			v.PB(number%base);
			number /= base;
		}
		Repair();
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
		this->sign = 1;
		this->v.PB(0);
	}
	Decimal(const Decimal& number)
	{
		this->sign = number.sign;
		this->v = number.v;
		Repair();
	}
	Decimal(string str)
	{
		*this = Decimal();
		int i = 0;
		if (str[0] == '-')
		{
			sign = -1;
			++i;
		}
		else sign = 1;
		for (; i < str.length(); ++i)
		{
			*this *= (ULLI)(10);
			*this += Decimal((int)(str[i] - '0'));
		}
		Repair();
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
	Decimal Abs() const
	{
		Decimal tmp(*this);
		tmp.sign = 1;
		return tmp;
	}

	//conversion to string
	string ToStr() const
	{
		if (*this == 0) return "0";
		string res = "";
		if (sign < 0) res += "-";
		for (int i = this->v.size() - 1; i >= 0; --i)
		{
			res += Zeroes(i) + Rest(i);
		}
		return res;
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
				for (int i = this->v.size() - 1; i >= 0; --i)
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
	int operator()(const ULLI number) const
	{
		return this->operator()(Decimal(number));
	}
	int operator()(const LLI number) const
	{
		return this->operator()(Decimal(number));
	}
	int operator()(const float number) const
	{
		return this->operator()(Decimal(number));
	}
	int operator()(const double number) const
	{
		return this->operator()(Decimal(number));
	}
	int operator()(const int number) const
	{
		return this->operator()(Decimal(number));
	}
	int operator()(const unsigned int number) const
	{
		return this->operator()(Decimal(number));
	}
	int operator()(const long int number) const
	{
		return this->operator()(Decimal(number));
	}
	int operator()(const unsigned long int number) const
	{
		return this->operator()(Decimal(number));
	}
	int operator()(const short int number) const
	{
		return this->operator()(Decimal(number));
	}
	int operator()(const unsigned short int number) const
	{
		return this->operator()(Decimal(number));
	}

	bool operator<(const Decimal& number) const
	{
		return (this->operator()(number) == -1);
	}
	bool operator<(const ULLI number) const
	{
		return this->operator<(Decimal(number));
	}
	bool operator<(const LLI number) const
	{
		return this->operator<(Decimal(number));
	}
	bool operator<(const float number) const
	{
		return this->operator<(Decimal(number));
	}
	bool operator<(const double number) const
	{
		return this->operator<(Decimal(number));
	}
	bool operator<(const int number) const
	{
		return this->operator<(Decimal(number));
	}
	bool operator<(const unsigned int number) const
	{
		return this->operator<(Decimal(number));
	}
	bool operator<(const long int number) const
	{
		return this->operator<(Decimal(number));
	}
	bool operator<(const unsigned long int number) const
	{
		return this->operator<(Decimal(number));
	}
	bool operator<(const short int number) const
	{
		return this->operator<(Decimal(number));
	}
	bool operator<(const unsigned short int number) const
	{
		return this->operator<(Decimal(number));
	}

	bool operator>(const Decimal& number) const
	{
		return this->operator()(number) == 1;
	}
	bool operator>(const ULLI number) const
	{
		return this->operator>(Decimal(number));
	}
	bool operator>(const LLI number) const
	{
		return this->operator>(Decimal(number));
	}
	bool operator>(const float number) const
	{
		return this->operator>(Decimal(number));
	}
	bool operator>(const double number) const
	{
		return this->operator>(Decimal(number));
	}
	bool operator>(const int number) const
	{
		return this->operator>(Decimal(number));
	}
	bool operator>(const unsigned int number) const
	{
		return this->operator>(Decimal(number));
	}
	bool operator>(const long int number) const
	{
		return this->operator>(Decimal(number));
	}
	bool operator>(const unsigned long int number) const
	{
		return this->operator>(Decimal(number));
	}
	bool operator>(const short int number) const
	{
		return this->operator>(Decimal(number));
	}
	bool operator>(const unsigned short int number) const
	{
		return this->operator>(Decimal(number));
	}

	bool operator==(const Decimal& number) const
	{
		return this->operator()(number) == 0;
	}
	bool operator==(const ULLI number) const
	{
		return this->operator==(Decimal(number));
	}
	bool operator==(const LLI number) const
	{
		return this->operator==(Decimal(number));
	}
	bool operator==(const float number) const
	{
		return this->operator==(Decimal(number));
	}
	bool operator==(const double number) const
	{
		return this->operator==(Decimal(number));
	}
	bool operator==(const int number) const
	{
		return this->operator==(Decimal(number));
	}
	bool operator==(const unsigned int number) const
	{
		return this->operator==(Decimal(number));
	}
	bool operator==(const long int number) const
	{
		return this->operator==(Decimal(number));
	}
	bool operator==(const unsigned long int number) const
	{
		return this->operator==(Decimal(number));
	}
	bool operator==(const short int number) const
	{
		return this->operator==(Decimal(number));
	}
	bool operator==(const unsigned short int number) const
	{
		return this->operator==(Decimal(number));
	}

	bool operator>=(const Decimal& number) const
	{
		return (*this < number) == 0;
	}
	bool operator>=(const ULLI number) const
	{
		return this->operator>=(Decimal(number));
	}
	bool operator>=(const LLI number) const
	{
		return this->operator>=(Decimal(number));
	}
	bool operator>=(const float number) const
	{
		return this->operator>=(Decimal(number));
	}
	bool operator>=(const double number) const
	{
		return this->operator>=(Decimal(number));
	}
	bool operator>=(const int number) const
	{
		return this->operator>=(Decimal(number));
	}
	bool operator>=(const unsigned int number) const
	{
		return this->operator>=(Decimal(number));
	}
	bool operator>=(const long int number) const
	{
		return this->operator>=(Decimal(number));
	}
	bool operator>=(const unsigned long int number) const
	{
		return this->operator>=(Decimal(number));
	}
	bool operator>=(const short int number) const
	{
		return this->operator>=(Decimal(number));
	}
	bool operator>=(const unsigned short int number) const
	{
		return this->operator>=(Decimal(number));
	}

	bool operator<=(const Decimal& number) const
	{
		return (*this>number) == 0;
	}
	bool operator<=(const ULLI number) const
	{
		return this->operator<=(Decimal(number));
	}
	bool operator<=(const LLI number) const
	{
		return this->operator<=(Decimal(number));
	}
	bool operator<=(const float number) const
	{
		return this->operator<=(Decimal(number));
	}
	bool operator<=(const double number) const
	{
		return this->operator<=(Decimal(number));
	}
	bool operator<=(const int number) const
	{
		return this->operator<=(Decimal(number));
	}
	bool operator<=(const unsigned int number) const
	{
		return this->operator<=(Decimal(number));
	}
	bool operator<=(const long int number) const
	{
		return this->operator<=(Decimal(number));
	}
	bool operator<=(const unsigned long int number) const
	{
		return this->operator<=(Decimal(number));
	}
	bool operator<=(const short int number) const
	{
		return this->operator<=(Decimal(number));
	}
	bool operator<=(const unsigned short int number) const
	{
		return this->operator<=(Decimal(number));
	}

	Decimal operator+(Decimal number) const
	{
		Decimal tmp(*this);
		int i = MIN(number.v.size()-1, tmp.v.size()-1);
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
	Decimal& operator+=(const Decimal& number)
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
	Decimal operator+(const ULLI& number) const
	{
		return *this + Decimal(number);
	}
	Decimal operator+(const LLI& number) const
	{
		return *this + Decimal(number);
	}
	Decimal operator+(const float& number) const
	{
		return *this + Decimal(number);
	}
	Decimal operator+(const double& number) const
	{
		return *this + Decimal(number);
	}
	Decimal operator+(const int& number) const
	{
		return *this + Decimal(number);
	}
	Decimal operator+(const unsigned int& number) const
	{
		return *this + Decimal(number);
	}
	Decimal operator+(const long int& number) const
	{
		return *this + Decimal(number);
	}
	Decimal operator+(const unsigned long int& number) const
	{
		return *this + Decimal(number);
	}
	Decimal operator+(const short int& number) const
	{
		return *this + Decimal(number);
	}
	Decimal operator+(const unsigned short int& number) const
	{
		return *this + Decimal(number);
	}
	Decimal& operator+=(const ULLI& number)
	{
		return *this += Decimal(number);
	}
	Decimal& operator+=(const LLI& number)
	{
		return *this += Decimal(number);
	}
	Decimal& operator+=(const float& number)
	{
		return *this += Decimal(number);
	}
	Decimal& operator+=(const double& number)
	{
		return *this += Decimal(number);
	}
	Decimal& operator+=(const int& number)
	{
		return *this += Decimal(number);
	}
	Decimal& operator+=(const unsigned int& number)
	{
		return *this += Decimal(number);
	}
	Decimal& operator+=(const long int& number)
	{
		return *this += Decimal(number);
	}
	Decimal& operator+=(const unsigned long int& number)
	{
		return *this += Decimal(number);
	}
	Decimal& operator+=(const short int& number)
	{
		return *this += Decimal(number);
	}
	Decimal& operator+=(const unsigned short int& number)
	{
		return *this += Decimal(number);
	}

	Decimal operator-(Decimal number) const
	{
		if (this->Abs() == number.Abs() && this->sign*number.sign == 1)
			return Decimal();
		number.sign *= -1;
		return *this + number;
	}
	Decimal& operator-=(const Decimal& number)
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
	Decimal operator-(const ULLI& number) const
	{
		return *this - Decimal(number);
	}
	Decimal operator-(const LLI& number) const
	{
		return *this - Decimal(number);
	}
	Decimal operator-(const float& number) const
	{
		return *this - Decimal(number);
	}
	Decimal operator-(const double& number) const
	{
		return *this - Decimal(number);
	}
	Decimal operator-(const int& number) const
	{
		return *this - Decimal(number);
	}
	Decimal operator-(const unsigned int& number) const
	{
		return *this - Decimal(number);
	}
	Decimal operator-(const long int& number) const
	{
		return *this - Decimal(number);
	}
	Decimal operator-(const unsigned long int& number) const
	{
		return *this - Decimal(number);
	}
	Decimal operator-(const short int& number) const
	{
		return *this - Decimal(number);
	}
	Decimal operator-(const unsigned short int& number) const
	{
		return *this - Decimal(number);
	}
	Decimal& operator-=(const ULLI& number)
	{
		return *this -= Decimal(number);
	}
	Decimal& operator-=(const LLI& number)
	{
		return *this -= Decimal(number);
	}
	Decimal& operator-=(const float& number)
	{
		return *this -= Decimal(number);
	}
	Decimal& operator-=(const double& number)
	{
		return *this -= Decimal(number);
	}
	Decimal& operator-=(const int& number)
	{
		return *this -= Decimal(number);
	}
	Decimal& operator-=(const unsigned int& number)
	{
		return *this -= Decimal(number);
	}
	Decimal& operator-=(const long int& number)
	{
		return *this -= Decimal(number);
	}
	Decimal& operator-=(const unsigned long int& number)
	{
		return *this -= Decimal(number);
	}
	Decimal& operator-=(const short int& number)
	{
		return *this -= Decimal(number);
	}
	Decimal& operator-=(const unsigned short int& number)
	{
		return *this -= Decimal(number);
	}

	Decimal operator*(ULLI number) const
	{
		Decimal tmp(*this);
		if (number <= base)
		{
			for (int i = 0; i < tmp.v.size(); ++i)
				tmp.v[i] *= number;
			tmp.Repair();
			return tmp;
		}
		else
			return *this * Decimal(number);
	}
	Decimal operator*(const Decimal& number) const
	{
		Decimal tmp, res;
		for (int i = 0; i < number.v.size(); ++i)
		{
			tmp = *this;
			for (int j = 0; j < i; ++j)
			{
				tmp *= (ULLI)base;
			}
			tmp *= (ULLI)number.v[i];
			res += tmp;
		}
		res.sign = this->sign * number.sign;
		return res;
	}
	Decimal& operator*=(Decimal& number)
	{
		*this = *this * number;
		return *this;
	}
	Decimal& operator*=(ULLI number)
	{
		if (number <= base)
		{
			for (int i = 0; i < this->v.size(); ++i)
				this->v[i] *= number;
			this->Repair();
			return *this;
		}
		else
			return *this *= Decimal(number);
	}
	Decimal operator*(const LLI& number) const
	{
		return *this * Decimal(number);
	}
	Decimal operator*(const float& number) const
	{
		return *this * Decimal(number);
	}
	Decimal operator*(const double& number) const
	{
		return *this * Decimal(number);
	}
	Decimal operator*(const int& number) const
	{
		return *this * Decimal(number);
	}
	Decimal operator*(const unsigned int& number) const
	{
		return *this * Decimal(number);
	}
	Decimal operator*(const long int& number) const
	{
		return *this * Decimal(number);
	}
	Decimal operator*(const unsigned long int& number) const
	{
		return *this * Decimal(number);
	}
	Decimal operator*(const short int& number) const
	{
		return *this * Decimal(number);
	}
	Decimal operator*(const unsigned short int& number) const
	{
		return *this * Decimal(number);
	}
	Decimal& operator*=(const LLI& number)
	{
		return *this *= Decimal(number);
	}
	Decimal& operator*=(const float& number)
	{
		return *this *= Decimal(number);
	}
	Decimal& operator*=(const double& number)
	{
		return *this *= Decimal(number);
	}
	Decimal& operator*=(const int& number)
	{
		return *this *= Decimal(number);
	}
	Decimal& operator*=(const unsigned int& number)
	{
		return *this *= Decimal(number);
	}
	Decimal& operator*=(const long int& number)
	{
		return *this *= Decimal(number);
	}
	Decimal& operator*=(const unsigned long int& number)
	{
		return *this *= Decimal(number);
	}
	Decimal& operator*=(const short int& number)
	{
		return *this *= Decimal(number);
	}
	Decimal& operator*=(const unsigned short int& number)
	{
		return *this *= Decimal(number);
	}

	Decimal operator/(Decimal number) const
	{
		if (number.Abs() > this->Abs()) return 0;
		if (number == *this) return 1;
		if (number == Decimal()-(*this)) return -1;

		Decimal tmp, rest(this->Abs()), result, partial;
		int i,j;
		while (rest >= number.Abs())
		{
			tmp = number.Abs();
			partial = 0;
			for (i = 0; (tmp << (i+1)) <= rest; ++i)
				tmp <<= 1;
			for (j = 0; tmp*powOfTen(j+1) <= rest; ++j);
			tmp *= powOfTen(j);
			while ((rest - (tmp*partial)) >= tmp)
			{
				++partial;
			}
			rest -= tmp*(partial);
			result += (partial << i) * powOfTen(j);
		}
		
		result.sign = this->sign * number.sign;
		result.Repair();
		return result;
	}
	Decimal& operator/=(Decimal& number)
	{
		*this = *this / number;
		return *this;
	}
	Decimal operator/(const ULLI& number) const
	{
		return *this / Decimal(number);
	}
	Decimal operator/(const LLI& number) const
	{
		return *this / Decimal(number);
	}
	Decimal operator/(const float& number) const
	{
		return *this / Decimal(number);
	}
	Decimal operator/(const double& number) const
	{
		return *this / Decimal(number);
	}
	Decimal operator/(const int& number) const
	{
		return *this / Decimal(number);
	}
	Decimal operator/(const unsigned int& number) const
	{
		return *this / Decimal(number);
	}
	Decimal operator/(const long int& number) const
	{
		return *this / Decimal(number);
	}
	Decimal operator/(const unsigned long int& number) const
	{
		return *this / Decimal(number);
	}
	Decimal operator/(const short int& number) const
	{
		return *this / Decimal(number);
	}
	Decimal operator/(const unsigned short int& number) const
	{
		return *this / Decimal(number);
	}
	Decimal& operator/=(const ULLI& number)
	{
		return *this /= Decimal(number);
	}
	Decimal& operator/=(const LLI& number)
	{
		return *this /= Decimal(number);
	}
	Decimal& operator/=(const float& number)
	{
		return *this /= Decimal(number);
	}
	Decimal& operator/=(const double& number)
	{
		return *this /= Decimal(number);
	}
	Decimal& operator/=(const int& number)
	{
		return *this /= Decimal(number);
	}
	Decimal& operator/=(const unsigned int& number)
	{
		return *this /= Decimal(number);
	}
	Decimal& operator/=(const long int& number)
	{
		return *this /= Decimal(number);
	}
	Decimal& operator/=(const unsigned long int& number)
	{
		return *this /= Decimal(number);
	}
	Decimal& operator/=(const short int& number)
	{
		return *this /= Decimal(number);
	}
	Decimal& operator/=(const unsigned short int& number)
	{
		return *this /= Decimal(number);
	}

	Decimal operator%(Decimal number) const
	{
		if (number.Abs() > this->Abs()) return (this->sign*number.sign > 0 ? *this : number - *this);
		if (number == *this) return 0;
		if (number == Decimal() - (*this)) return 0;

		Decimal tmp, rest(this->Abs()), result, partial;
		int i, j;
		while (rest >= number.Abs())
		{
			tmp = number.Abs();
			partial = 0;
			for (i = 0; (tmp << (i + 1)) <= rest; ++i)
				tmp <<= 1;
			for (j = 0; tmp*powOfTen(j + 1) <= rest; ++j);
			tmp *= powOfTen(j);
			while ((rest - (tmp*partial)) >= tmp)
			{
				++partial;
			}
			rest -= tmp*(partial);
			result += (partial << i) * powOfTen(j);
		}

		result.sign = this->sign * number.sign;
		result.Repair();
		return rest >= 0 ? rest : number + rest;
	}
	Decimal& operator%=(Decimal& number)
	{
		*this = *this % number;
		return *this;
	}
	Decimal operator%(const ULLI& number) const
	{
		return *this % Decimal(number);
	}
	Decimal operator%(const LLI& number) const
	{
		return *this % Decimal(number);
	}
	Decimal operator%(const float& number) const
	{
		return *this % Decimal(number);
	}
	Decimal operator%(const double& number) const
	{
		return *this % Decimal(number);
	}
	Decimal operator%(const int& number) const
	{
		return *this % Decimal(number);
	}
	Decimal operator%(const unsigned int& number) const
	{
		return *this % Decimal(number);
	}
	Decimal operator%(const long int& number) const
	{
		return *this % Decimal(number);
	}
	Decimal operator%(const unsigned long int& number) const
	{
		return *this % Decimal(number);
	}
	Decimal operator%(const short int& number) const
	{
		return *this % Decimal(number);
	}
	Decimal operator%(const unsigned short int& number) const
	{
		return *this % Decimal(number);
	}
	Decimal& operator%=(const ULLI& number)
	{
		return *this %= Decimal(number);
	}
	Decimal& operator%=(const LLI& number)
	{
		return *this %= Decimal(number);
	}
	Decimal& operator%=(const float& number)
	{
		return *this %= Decimal(number);
	}
	Decimal& operator%=(const double& number)
	{
		return *this %= Decimal(number);
	}
	Decimal& operator%=(const int& number)
	{
		return *this %= Decimal(number);
	}
	Decimal& operator%=(const unsigned int& number)
	{
		return *this %= Decimal(number);
	}
	Decimal& operator%=(const long int& number)
	{
		return *this %= Decimal(number);
	}
	Decimal& operator%=(const unsigned long int& number)
	{
		return *this %= Decimal(number);
	}
	Decimal& operator%=(const short int& number)
	{
		return *this %= Decimal(number);
	}
	Decimal& operator%=(const unsigned short int& number)
	{
		return *this %= Decimal(number);
	}

	//moving operators
	Decimal operator<<(const Decimal& number)
	{
		Decimal tmp(*this);
		for (Decimal i((ULLI)(0)); i < number; ++i)
		{
			tmp.v.PB(tmp.v[tmp.v.size() - 1]);
			for (int i = tmp.v.size() - 1; i > 0; --i)
				tmp.v[i] = tmp.v[i - 1];
			tmp.v[0] = 0;
		}
		return tmp;
	}
	Decimal& operator<<=(const Decimal& number)
	{
		return (*this = (*this << number));
	}
	Decimal operator>>(const Decimal& number)
	{
		Decimal tmp(*this);
		for (Decimal i((ULLI)(0)); i < number; ++i)
		{
			for (int i = 0; i < tmp.v.size() - 1; ++i)
				tmp.v[i] = tmp.v[i + 1];
			tmp.v.pop_back();
		}
		return tmp;
	}
	Decimal& operator>>=(const Decimal& number)
	{
		return (*this = (*this >> number));
	}

	//input and output
	friend ostream& operator<<(ostream& output, Decimal& number)
		{
			return output << number.ToStr();
		}
	friend istream& operator>>(istream& input, Decimal& number)
		{
			string str;
			input >> str;
			number = Decimal(str);
			return input;
		}
	

};

#undef LET(a,b)
#undef PB
#undef MAX
#undef MIN

#endif