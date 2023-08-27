#include <iostream>
#include <iomanip>
#include <fstream>
#include "locale.h"

using namespace std;
int alph_length = 31;
char alphabet[32] = "абвгдежзийклмнопрстуфхцчшщьыэюя";
int gcd = 0;


int euclid(int num,int n=alph_length)
{
	gcd = 0;
	if (num==1)
	{
		return 1;
	}
	int inverse = 0;
	int temp = 0;
	int temp2 = 1;
	int c = -1;
	int b = 0;
	int r0 = n;
	int r1 = num;
	// r0=b*r1+c
	while (c!=0)
	{
		b = r0 / r1;
		c = r0 - b * r1;
		if (c != 0)
		{
			int temp3 = -b * temp2 + temp;
			temp = temp2;
			temp2 = temp3;
			r0 = r1;
			r1 = c;
		}
		else
			gcd = r1;
	}
	if (temp2 < 0)
		inverse = temp2 + n;
	else
		inverse = temp2 % n;
	inverse %= n;
	if (gcd!=1)
	{
		return -1;
	}
	return inverse;
}

int* congruence_solution(int a, int b, int mod)
{
	gcd = 0;
	int k = euclid(a, mod);
	int* arr = new int[gcd];
	for (int i = 0; i < gcd; i++)
	{
		arr[i] = 0;
	}
	if (gcd==1)
	{
		arr[0] = (k * b) % mod;
	}
	if (gcd>1)
	{
		if (b%gcd!=0)
		{
			//cout << "Решения не существует" << endl;
			arr[0] = -1;
		}
		else
		{
			a /= gcd;
			b /= gcd;
			mod /= gcd;
			int temp = gcd;
			k = euclid(a, mod);
			arr[0] = (k * b) % mod;
			for (int i = 1; i < temp; i++)
			{
				arr[i] = arr[0] + i * mod;
			}
			gcd = temp;
		}
	}
	return arr;
}

int deciphering(int a, int b)
{
	int c = 0;
	char first;
	char second;
	ofstream out("decipher.txt");
	ifstream inn("test2.txt");
	if (!inn.is_open())
	{
		cout << "Файл не может быть открыт!\n";
		return -1;
	}
	int inverse = 0;
	inverse = euclid(a, alph_length * alph_length);
	while (inn.get(first) && inn.get(second) && inverse != -1)
	{
		int temp = 0;
		for (int j = 0; j < alph_length; j++)
		{
			if (first == alphabet[j])
			{
				for (int t = 0; t < alph_length; t++)
				{
					if (second == alphabet[t])
					{
						temp = alph_length * j + t;
						t = alph_length;
					}
				}
				j = alph_length;
			}
		}
		temp -= b;
		temp *= inverse;
		while (temp < 0)
		{
			temp += alph_length * alph_length;
		}
		temp %= alph_length * alph_length;
		out << alphabet[temp / alph_length] << alphabet[temp % alph_length];
		c += 2;
		if (c%100==0)
		{
			out << "\n";
		}
	}
	inn.close();
	out.close();
	return 1;
}

bool choosing(int a, int b, int inverse)
{
	double *choose_text = new double[alph_length];
	for (int i = 0; i < alph_length; i++)
	{
		choose_text[i] = 0;
	}
	char first;
	char second;
	ifstream inn("test2.txt");
	if (!inn.is_open())
	{
		cout << "Файл не может быть открыт!\n";
		return -1;
	}
	int file_length = 0;
	while (inn.get(first) && inn.get(second))
	{
		int temp = 0;
		for (int j = 0; j < alph_length; j++)
		{
			if (first == alphabet[j])
			{
				for (int t = 0; t < alph_length; t++)
				{
					if (second == alphabet[t])
					{
						temp = alph_length * j + t;
						t = alph_length;
					}
				}
				j = alph_length;
			}
		}
		temp -= b;
		temp *= inverse;
		while (temp < 0)
		{
			temp += alph_length * alph_length;
		}
		temp %= alph_length * alph_length;
		choose_text[temp / alph_length]++;
		choose_text[temp % alph_length]++;
		file_length += 2;
	}
	inn.close();
	for (int i = 0; i < alph_length; i++)
	{
		choose_text[i] /= file_length;
	}
	if (choose_text[0] + choose_text[5] + choose_text[14] > 0.25)
	{
		if (choose_text[20] + choose_text[25] + choose_text[28] < 0.008)
		{
			delete[] choose_text;
			return true;
		}
	}
	delete[] choose_text;
	return false;
}


int main()
{
	setlocale(LC_ALL,"Russian");
	int** freq = new int*[alph_length];
	for (int i = 0; i < alph_length; i++)
	{
		freq[i] = new int [alph_length];
		for (int j = 0; j < alph_length; j++)
		{
			freq[i][j] = 0;
		}
	}
	ifstream in("test2.txt");
	if (!in.is_open())
	{
		cout << "Файл не может быть открыт!\n";
		return -1;
	}
	char first;
	char second;
	int file_length = 0;
	while (in.get(first) && in.get(second))
	{
		for (int i = 0; i < alph_length; i++)
		{
			if (first==alphabet[i])
			{
				for (int j = 0; j < alph_length; j++)
				{
					if (second==alphabet[j])
					{
						freq[i][j]++;
						file_length+=2;
						j = alph_length;
					}
					
				}
				i = alph_length;
			}
			
		}
	}
	in.close();
	int max_freq = 0;
	int maximum_bigrams[5];
	for (int i = 0; i < 5; i++)
	{
		maximum_bigrams[i] = 0;
	}
	for (int t = 0; t < 5; t++)
	{
		max_freq = 0;
		for (int i = 0; i < alph_length; i++)
		{
			for (int j = 0; j < alph_length; j++)
			{
				if (freq[i][j] > max_freq)
				{
					max_freq = freq[i][j];
					maximum_bigrams[t] = i * alph_length + j;
				}
			}
		}
		freq[maximum_bigrams[t] / alph_length][maximum_bigrams[t] % alph_length] = -1;
	}
	cout << "Биграммы с максимальной частотой в тестовом файле: " << endl;
	for (int i = 0; i < 5; i++)
	{
		cout << "(" << alphabet[maximum_bigrams[i] / alph_length] << ", " << alphabet[maximum_bigrams[i] % alph_length] << ")     ";
	}
	cout << endl << endl;

	int maximum_open[5];
	cout << "Биграммы с максимальной частотой в русском языке: " << endl;
	maximum_open[0] = 17 * alph_length + 18;       //ст
	maximum_open[1] = 13 * alph_length + 14;       //но
	maximum_open[2] = 18 * alph_length + 14;       //то
	maximum_open[3] = 13 * alph_length;            //на
	maximum_open[4] = 5 * alph_length + 13;        //ен
	for (int i = 0; i < 5; i++)
	{
		cout << "(" << alphabet[maximum_open[i] / alph_length] << ", " << alphabet[maximum_open[i] % alph_length] << ")     ";
	}
	cout << endl << endl;


	int coun = 0;
	
	for (int t = 0; t < 5; t++)
	{
		for (int i = 0; i < 5; i++)
		{
			for (int g = 0; g < 5; g++)
			{
				if (i != t && g!=t)
				{
					int y = 0;
					y = maximum_bigrams[t] - maximum_bigrams[i];
					int x = 0;
					x = maximum_open[t] - maximum_open[g];

					if (y < 0)
					{
						y += alph_length * alph_length;
					}
					if (x < 0)
					{
						x += alph_length * alph_length;
					}
					euclid(x, alph_length * alph_length);
					int* key;
					key = congruence_solution(x, y, alph_length * alph_length);
					if (key[0] != -1 && key[0]!=0)
					{
						int temp_gcd = gcd;
						for (int j = 0; j < temp_gcd; j++)
						{
							int inv = euclid(key[j], alph_length * alph_length);
							if (inv!=-1)
							{
								int b = (maximum_bigrams[t] - key[j] * maximum_open[t]);
								while (b < 0)
								{
									b += alph_length * alph_length;
								}
								b %= alph_length * alph_length;
								if (choosing(key[j], b, inv))
								{
									cout << "Подходит ключ:   (" << key[j] << ", " << b << ")" << endl;
									deciphering(key[j],b);
									j = temp_gcd;
									g = 5;
									t = 5;
									i = 5;
								}
							}
						}
					}
					delete[] key;
				}	
			}
		}
	}
	cout << endl << "Расшифрованый текст находиться в файле decipher.txt" << endl;
	return 0;
}