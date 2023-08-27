#include <iostream>
#include <fstream>
#include "locale.h"

using namespace std;

const int quantity = 33;
int coun = 0;
char alphabet[34] = "абвгдеёжзийклмнопрстуфхцчшщъыьэюя";
char valphabet[33] = "абвгдежзийклмнопрстуфхцчшщъыьэюя";
char alphabet_big[34] = "АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ";


int findKeyLength() 
{
	char a;
	int congruents[25];
	double variantCipher[quantity];
	for (int i = 0; i < quantity; i++)
	{
		variantCipher[i] = 0;
	}

	for (int i = 6; i <= 30; i++)
	{
		congruents[i - 6] = 0;
		ifstream in("variant.txt");
		if (!in.is_open())
		{
			cout << "Файл не может быть открыт!\n";
			return -1;
		}
		int coun = 0;
		char* arr = new char[i];
		for (int j = 0; j < i; j++)
		{
			in.get(a);
			arr[j] = a;
		}
		while (in.get(a))
		{
			for (int j = 0; j < quantity; j++)
			{
				if (a == alphabet[j])
				{
					if (a == arr[coun % i])
					{
						congruents[i - 6]++;
					}
					coun++;
					if (i == 6)
						variantCipher[j]++;
				}
			}
		}
		in.close();
		delete[] arr;
	}
	int keyLength = 0;
	int temp = 0;
	cout << "Последовательность D_{r}" << endl;
	for (int i = 0; i < 25; i++)
	{
		cout << "r = " << i + 6 << "       D_{r} = " << congruents[i] << endl;
		if (congruents[i] > temp)
		{
			keyLength = i + 6;
			temp = congruents[i];
		}
	}
	cout << "Длина ключа по статистике совпадений:   " << keyLength << endl << endl;
	return keyLength;
}

int varLength()
{
	char a;
	int variantLength = 0;
	ifstream in("variant.txt");
	while (in.get(a))
	{
		for (int i = 0; i < quantity-1; i++)
		{
			if (a == valphabet[i])
			{
				variantLength++;
				i = quantity;
			}
		}
		
	}
	in.close();
	return variantLength;
}

char** divisionText(int keyLength)
{
	coun = varLength() / keyLength + 1;
	char** division = new char* [coun];
	for (int i = 0; i < coun; i++)
	{
		division[i] = new char[keyLength];
	}
	for (int i = 0; i < coun; i++)
	{
		for (int j = 0; j < keyLength; j++)
		{
			division[i][j] = '_';
		}
	}
	ifstream in("variant.txt");
	char a;
	int k = 0;
	int j = 0;
	while (in.get(a))
	{
		for (int i = 0; i < quantity-1; i++)
		{
			if (a == valphabet[i])
			{
				division[k][j % keyLength] = a;
				i = quantity;
				j++;
				if (j >= keyLength && j % keyLength == 0)
					k++;
			}
		}
	}
	in.close();
	return division;
}


int main()
{
	setlocale(LC_ALL, "Russian");

	char a;
	int key2[2] = { 19, 23 };      //тц
	int key3[3] = { 15, 7, 16 };     //ожп
	int key4[4] = { 13, 17, 0, 11 };   //мрак
	int key5[5] = { 2, 0, 12, 5, 19 };   //валет
	int key16[16] = { 2, 14, 0, 24, 0, 12, 5, 1, 28, 12, 15, 18, 12, 15, 2, 15 };   //вначалебылослово
	double length =0;
	double openText[quantity];
	double cipher1[quantity];
	double cipher2[quantity];
	double cipher3[quantity];
	double cipher4[quantity];
	double cipher5[quantity];
	for (int i = 0; i < quantity; i++)
	{
		openText[i] = 0;
		cipher1[i] = 0;
		cipher2[i] = 0;
		cipher3[i] = 0;
		cipher4[i] = 0;
		cipher5[i] = 0;
	}

	
	ofstream out("cipher.txt");
	if (!out.is_open())
	{
		cout << "Файл не может быть открыт!\n";
		return -1;
	}
	for (int t = 2; t <= 6; t++)
	{
		int coun = 0;
		ifstream in("text.txt");
		if (!in.is_open())
		{
			cout << "Файл не может быть открыт!\n";
			return -1;
		}
		switch (t)
		{
		case 2: out << "Шифр с ключем длины 2 (ключ: тц)\n\n"; break;
		case 3: out << "Шифр с ключем длины 3 (ключ: ожп)\n\n"; break;
		case 4: out << "Шифр с ключем длины 4 (ключ: мрак)\n\n"; break;
		case 5: out << "Шифр с ключем длины 5 (ключ: валет)\n\n"; break;
		case 6: out << "Шифр с ключем длины 16 (ключ: вначалебылослово)\n\n"; break;
		}
		
		while (in.get(a))
		{
			char c;
			for (int i = 0; i < quantity; i++)
			{
				if (a == alphabet[i] || a == alphabet_big[i])
				{
					switch (t)
					{
					case 2: out << alphabet[(i + key2[coun % 2]) % quantity]; 
						c = alphabet[(i + key2[coun % 2]) % quantity];
						for (int j = 0; j < quantity; j++)
						{
							if (c == alphabet[j] || c == alphabet_big[j])
								cipher1[j]++;
							if (a == alphabet[j] || a == alphabet_big[j])
								openText[j]++;
						}
						length++;
						break;
					case 3: out << alphabet[(i + key3[coun % 3]) % quantity];
						c = alphabet[(i + key3[coun % 3]) % quantity];
						for (int j = 0; j < quantity; j++)
						{
							if (c == alphabet[j] || c == alphabet_big[j])
								cipher2[j]++;
						}
						break;
					case 4: out << alphabet[(i + key4[coun % 4]) % quantity];
						c = alphabet[(i + key4[coun % 4]) % quantity];
						for (int j = 0; j < quantity; j++)
						{
							if (c == alphabet[j] || c == alphabet_big[j])
								cipher3[j]++;
						}
						break;
					case 5: out << alphabet[(i + key5[coun % 5]) % quantity]; 
						c = alphabet[(i + key5[coun % 5]) % quantity];
						for (int j = 0; j < quantity; j++)
						{
							if (c == alphabet[j] || c == alphabet_big[j])
								cipher4[j]++;
						}
						break;
					case 6: out << alphabet[(i + key16[coun % 16]) % quantity]; 
						c = alphabet[(i + key16[coun % 16]) % quantity];
						for (int j = 0; j < quantity; j++)
						{
							if (c == alphabet[j] || c == alphabet_big[j])
								cipher5[j]++;
						}
						break;
					}
					coun++;
					if (coun % 100 == 0)
					{
						out << "\n";
					}
				}
			}
		}
		in.close();
		if(t!=6)
			out << "\n\n\n-----------------------------------------------\n\n\n\n";
	}
	out.close();
	cout << "Зашифрованый текст находится в файле cipher.txt" << endl << endl;
	//cout << "Длина текста: " << length << endl << endl;
	
	double index[6];
	for (int i = 0; i < 6; i++)
	{
		index[i] = 0;
		for (int j = 0; j < quantity; j++)
		{
			switch (i)
			{
			case 0: index[i] += openText[j] * (openText[j] - 1) / (length * (length - 1)); break;
			case 1: index[i] += cipher1[j] * (cipher1[j] - 1) / (length * (length - 1)); break;
			case 2: index[i] += cipher2[j] * (cipher2[j] - 1) / (length * (length - 1)); break;
			case 3: index[i] += cipher3[j] * (cipher3[j] - 1) / (length * (length - 1)); break;
			case 4: index[i] += cipher4[j] * (cipher4[j] - 1) / (length * (length - 1)); break;
			case 5: index[i] += cipher5[j] * (cipher5[j] - 1) / (length * (length - 1)); break;
			}
		}
	}

	cout << "Индекс для открытого текста :   " << index[0] << endl;
	cout << "Индекс для зашифрованого текста (ключ длины 2):   " << index[1] << endl;
	cout << "Индекс для зашифрованого текста (ключ длины 3):   " << index[2] << endl;
	cout << "Индекс для зашифрованого текста (ключ длины 4):   " << index[3] << endl;
	cout << "Индекс для зашифрованого текста (ключ длины 5):   " << index[4] << endl;
	cout << "Индекс для зашифрованого текста (ключ длины 16):  " << index[5] << endl << endl;

	
	int keyLength = findKeyLength();
	

	char* arr = new char[keyLength];
	double freqOpen[2][quantity];

	ifstream inn("freq.csv");
	if (!inn.is_open())
	{
		cout << "Файл не может быть открыт!\n";
		return -1;
	}
	int j = 0;
	while (inn.get(a))
	{
		for (int i = 0; i < quantity; i++)
		{
			if (a==alphabet[i])
			{
				freqOpen[1][j] = 0;
				freqOpen[0][j]=i;
				inn.get(a);
				inn >> freqOpen[1][j];
				i = quantity;
				j++;
			}
		}
	}
	inn.close();
	
	char** division = new char*[coun];
	for (int i = 0; i < coun; i++)
	{
		division[i] = new char[keyLength];
	}
	double** variantFreq = new double*[keyLength];
	for (int i = 0; i < keyLength; i++)
	{
		variantFreq[i] = new double[quantity-1];
		for (int j = 0; j < quantity -1; j++)
		{
			variantFreq[i][j] = 0;
		}
	}
	division = divisionText(keyLength);
	for (int j = 0; j < keyLength; j++)
	{
		int k = 0;
		for (int i = 0; i < coun; i++)
		{
			for (int t = 0; t < quantity - 1; t++)
			{
				if (division[i][j] == valphabet[t])
				{
					variantFreq[j][t]++;
					t = quantity;
					k++;
				}
			}
		}
		for (int i = 0; i < quantity - 1; i++)
		{
			variantFreq[j][i] /= k;
		}
	}
	int* key = new int[keyLength];
	cout << "Ключ, найденый с помощью приравнивания самых частых букв блока:   ";
	for (int i = 0; i < keyLength; i++)
	{
		int max = 0;
		double temp = 0;
		for (int j = 0; j < quantity - 1; j++)
		{
			if (variantFreq[i][j] > temp)
			{
				max = j;
				temp = variantFreq[i][j];
			}
		}
		if (max - freqOpen[0][0] + 1< 0)
			key[i] = max - freqOpen[0][0] + quantity;
		if (max - freqOpen[0][0] + 1 >= 0)
			key[i] = (max - freqOpen[0][0] + 1);
		key[i] %= (quantity - 1);
		cout << valphabet[key[i]];
	}
	cout << endl;

	ifstream in("variant.txt");
	if (!in.is_open())
	{
		cout << "Файл не может быть открыт!!!\n";
		return -1;
	}
	ofstream outv("decipher1.txt");

	int k = 0;
	while (in.get(a))
	{
		int num = 0;
		for (int i = 0; i < quantity - 1; i++)
		{
			if (a == valphabet[i])
			{
				num = i - key[k % keyLength];
				if (num < 0)
					num += (quantity - 1);
				num %= (quantity - 1);
				outv << valphabet[num];
				k++;
				i = quantity;
			}
		}
		if (k % 100 == 0)
		{
			outv << "\n";
		}
	}

	outv.close();
	in.close();
	cout << "Расшифрованый этим ключем текст находится в файле decipher1.txt" << endl << endl;

	for (int  i = 0; i < keyLength; i++)
	{
		for (int j = 0; j < quantity - 1; j++)
		{
			if (division[i][coun - 1] != '_')
				variantFreq[i][j] *= (coun - 1);
			else
				variantFreq[i][j] *= (coun - 2);
			variantFreq[i][j] = round(variantFreq[i][j]);
		}
	}

	double** funkM = new double* [keyLength];
	for (int i = 0; i < keyLength; i++)
	{
		funkM[i] = new double[quantity - 1];
		for (int j = 0; j < quantity - 1; j++)
		{
			funkM[i][j] = 0;
		}
	}

	//сортировка по алфавиту и убийство ё
	for (int i = 0; i < quantity; i++)
	{
		for (int j = 0; j < quantity - 1 - i; j++)
		{
			if (freqOpen[0][j + 1] < freqOpen[0][j])
			{
				double temp = 0;
				int temp2 = 0;
				temp = freqOpen[1][j + 1];
				temp2 = freqOpen[0][j + 1];
				freqOpen[1][j + 1] = freqOpen[1][j];
				freqOpen[0][j + 1] = freqOpen[0][j];
				freqOpen[1][j] = temp;
				freqOpen[0][j] = temp2;
			}
		}
	}
	for (int i = 6; i < quantity - 1; i++)
	{
		freqOpen[0][i] = freqOpen[0][i + 1];
		freqOpen[1][i] = freqOpen[1][i + 1];
	}
	
	//подсчет значений функции M(g)
	for (int i = 0; i < keyLength; i++)
	{
		for (int j = 0; j < quantity - 1; j++)
		{
			for (int t = 0; t < quantity - 1; t++)
			{
				funkM[i][j] += freqOpen[1][t] * variantFreq[i][(t + j) % (quantity - 1)];
			}
		}
	}
	cout << "Ключ, найденый с помощью функции M(g):   ";
	for (int i = 0; i < keyLength; i++)
	{
		int max = 0;
		double temp = 0;
		for (int j = 0; j < quantity - 1; j++)
		{
			if (funkM[i][j] > temp)
			{
				max = j;
				temp = funkM[i][j];
			}
		}
		key[i] = max;
		cout << valphabet[key[i]];
	}

	ifstream in2("variant.txt");
	if (!in2.is_open())
	{
		cout << "Файл не может быть открыт!!!\n";
		return -1;
	}
	ofstream outv2("decipher2.txt");

	k = 0;
	while (in2.get(a))
	{
		int num = 0;
		for (int i = 0; i < quantity - 1; i++)
		{
			if (a == valphabet[i])
			{
				num = i - key[k % keyLength];
				if (num < 0)
					num += (quantity - 1);
				num %= (quantity - 1);
				outv2 << valphabet[num];
				k++;
				i = quantity;
			}
		}
		if (k % 100 == 0)
		{
			outv2 << "\n";
		}
	}

	outv2.close();
	in2.close();
	cout << endl << "Расшифрованый этим ключем текст находится в файле decipher2.txt" << endl << endl;

	for (int i = 0; i < keyLength; i++)
	{
		delete[] variantFreq[i];
	}
	delete[] variantFreq;
	for (int i = 0; i < coun; i++)
	{
		delete[] division[i];
	}
	delete[] division;
	return 0;
}