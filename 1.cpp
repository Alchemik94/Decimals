#include <iostream>
#include <string>
#include <algorithm> 
using namespace std;

char* reverse( char* s )
  {
  char  c;
  char* s0 = s - 1;
  char* s1 = s;

  /* Find the end of the string */
  while (*s1) ++s1;

  /* Reverse it */
  while (s1-- > ++s0)
    {
    c   = *s0;
    *s0 = *s1;
    *s1 =  c;
    }

  return s;
  } // function reversing the array.;

char* addition( char str1[], char str2[], int len1, int len2 )
{
	int i=0;
	char* ptr;
	char result[10000];
	ptr = result;
	int lenght = max(len1,len2);
	result[lenght+1]=0;
	for (i=0; i<lenght; i++)
	{
		result[i] = max((int)str1[i],48) + max((int)str2[i],48) - 48;
	}
	for (i=0; i<lenght; i++);
	{
		if (result[i]>57)
			{
				result[i]=result[i]-10;
				result[i+1]=result[i+1]+1;
			}

	}
	if (result[lenght]<48 || result[lenght]>48) result[lenght]=0;
	return ptr;
}

char* subtraction( char str1[], char str2[], int len1, int len2 )
{
	int i=0;
	char* ptr;
	char result[10000];
	ptr = result;
	int lenght = max(len1,len2);
	result[lenght+1]=0;
	for (i=0; i<lenght; i++)
	{
		result[i] = max((int)str1[i],48) - max((int)str2[i],48) + 48;
	}
	for (int j=0; j<lenght; j++)
	{
	for (i=0; i<lenght; i++);
	{
		if (result[i]<48)
			{
				result[i]=result[i]+10;
				result[i+1]=result[i+1]-1;
			}

	}
	}

	if (result[lenght]<48 || result[lenght]>48) result[lenght]=0;


	if (result[lenght-1]<48) // if the result is negative...
	{
		result[lenght-1]=48+(48-result[lenght-1]);
		result[lenght]='-';
		result[lenght+1]='\0';
	}
		return ptr;
}

int main()
{
  
int i=0;

  char number1[10000];
  char number2[10000];
  char* result;

  cout << "Please, enter first number: \n";
  cin.getline(number1, 10000);
  cout << "Please, enter second number: \n";
  cin.getline(number2, 10000);

  int len1 = strlen(number1);
  int len2 = strlen(number2);

  reverse(number1);
  reverse(number2);






  cout << "1: " << number1 << endl;
  cout << "2: " << number2 << endl;

  cout << "3: " << len1 << endl;
  cout << "4: " << len2 << endl;

  cout << addition(number1, number2, len1, len2) << endl;
  cout << subtraction(number1, number2, len1, len2) << endl;

  getchar();
  return 0;
}



