#include <iostream>
#include <iomanip>
#include <fstream>
#include "locale.h"
#include "math.h"
using namespace std;

const int coun1 = 33;
const int coun2 = 34;
double freq_with[2][coun2];
double freq_without[2][coun1];
double bi_without[coun1][coun1];
double bi_with[coun2][coun2];
double bip_without[coun1][coun1];
double bip_with[coun2][coun2];


double entropy_mono(int j)
{
    double a = 0;
    if (j == coun2)
    {
        for (int i = 0; i < j; i++)
        {
            if (freq_with[1][i] != 0)
                a += freq_with[1][i] * (log10(freq_with[1][i]) / log10(2));
        }
    }
    if (j == coun1)
    {
        for (int i = 0; i < j; i++)
        {
            if (freq_without[1][i] != 0)
                a += freq_without[1][i] * (log10(freq_without[1][i]) / log10(2));
        }
    }
    return -a;
}

double entropy_bi(int a)
{
    double h = 0;
    switch (a)
    {
    case 1:
        for (int i = 0; i < 33; i++)
        {
            for (int j = 0; j < 33; j++)
            {
                if (bi_without[i][j] != 0)
                    h += bi_without[i][j] * (log2(bi_without[i][j]));
            }
        }
        break;
    case 2:
        for (int i = 0; i < 34; i++)
        {
            for (int j = 0; j < 34; j++)
            {
                if (bi_with[i][j] != 0)
                    h += bi_with[i][j] * (log2(bi_with[i][j]));
            }
        }
        break;
    case 3:
        for (int i = 0; i < 33; i++)
        {
            for (int j = 0; j < 33; j++)
            {
                if (bip_without[i][j] != 0)
                    h += bip_without[i][j] * log2(bip_without[i][j]);
            }
        }
        break;
    case 4:
        for (int i = 0; i < 34; i++)
        {
            for (int j = 0; j < 34; j++)
            {
                if (bip_with[i][j] != 0)
                    h += bip_with[i][j] * log2(bip_with[i][j]);
            }
        }
        break;
    }
    return -h/2;
}



int main()
{
    setlocale(LC_ALL, "Russian");
    ifstream in("idiot.txt", ios::in);

    if (!in.is_open())
    {
        cout << "Файл не может быть открыт!\n";
        return -1;
    }

    char a;
    char b;
    char c;
    int small1 = -1;     // я
    int small2 = -32;    // а
    int Big1 = -33;      // Я
    int Big2 = -64;      // А
    int small_e = -72;   // ё
    int Big_e = -88;     // Ё
    int prob = 32;       // пробел
    long int count_without = 0;
    long int count_with = 0;
    int bic_with = 0;
    int bic_without = 0;
    int bicp_with = 0;
    int bicp_without = 0;
    double arr_without[2][coun1];
    double arr_with[2][coun2];


    for (int i = 0; i < coun1; i++)
    {
        arr_without[0][i] = i;
        arr_without[1][i] = 0;
        arr_with[0][i] = i;
        arr_with[1][i] = 0;
        freq_with[0][i] = i;
        freq_without[0][i] = i;
        freq_with[1][i] = 0;
        freq_without[1][i] = 0;
    }
    for (int i = 0; i < coun1; i++)
    {
        for (int j = 0; j < coun1; j++)
        {
            bi_without[i][j] = 0;
            bi_with[i][j] = 0;
            bip_without[i][j] = 0;
            bip_with[i][j] = 0;
        }
    }
    for (int i = 0; i < coun2; i++)
    {
        bi_with[i][coun2-1] = 0;
        bi_with[coun2-1][i] = 0;
        bip_with[i][coun2-1] = 0;
        bip_with[coun2-1][i] = 0;
    }
    bi_with[coun2-1][coun2-1] = 0;
    arr_with[0][coun2-1] = coun2-1;
    arr_with[1][coun2-1] = 0;
    freq_with[0][coun2-1] = coun2-1;
    freq_with[1][coun2-1] = 0;

    int co = 1;

    in.get(a);
    c = a;
    if ((int)a <= small1 && (int)a >= small2)
    {
        arr_with[1][(int)a - small2]++;
        arr_without[1][(int)a - small2]++;
        count_with++;
        count_without++;
    }
    if ((int)a <= Big1 && (int)a >= Big2)
    {
        arr_with[1][(int)a - Big2]++;
        arr_without[1][(int)a - Big2]++;
        count_with++;
        count_without++;
    }
    if ((int)a == prob)
    {
        arr_with[1][coun2 - 1]++;
        count_with++;
    }
    if ((int)a == Big_e || (int)a == small_e)
    {
        arr_with[1][coun2 - 2]++;
        arr_without[1][coun1 - 1]++;
        count_with++;
        count_without++;
    }

    while (!in.eof())
    {
        in.get(b);
        if ((int)b <= small1 && (int)b >= small2)
        {
            arr_with[1][(int)b - small2]++;
            arr_without[1][(int)b - small2]++;
            count_with++;
            count_without++;
            if (c == a)
            {
                if ((int)a <= small1 && (int)a >= small2)
                {
                    bi_with[(int)a - small2][(int)b - small2]++;
                    bic_with++;
                    bi_without[(int)a - small2][(int)b - small2]++;
                    bic_without++;
                }
                if ((int)a <= Big1 && (int)a >= Big2)
                {
                    bi_with[(int)a - Big2][(int)b - small2]++;
                    bic_with++;
                    bi_without[(int)a - Big2][(int)b - small2]++;
                    bic_without++;
                }
                if ((int)a == prob)
                {
                    bi_with[coun2 - 1][(int)b - small2]++;
                    bic_with++;
                }
                if ((int)a == Big_e || (int)a == small_e)
                {
                    bi_with[coun2 - 2][(int)b - small2]++;
                    bic_with++;
                    bi_without[coun1-1][(int)b - small2]++;
                    bic_without++;
                }
            }
            else
            {
                if ((int)a <= small1 && (int)a >= small2)
                {
                    bi_with[(int)a - small2][(int)b - small2]++;
                    bic_with++;
                }
                if ((int)a <= Big1 && (int)a >= Big2)
                {
                    bi_with[(int)a - Big2][(int)b - small2]++;
                    bic_with++;
                }
                if ((int)a == prob)
                {
                    bi_with[coun2 - 1][(int)b - small2]++;
                    bic_with++;
                }
                if ((int)a == Big_e || (int)a == small_e)
                {
                    bi_with[coun2 - 2][(int)b - small2]++;
                    bic_with++;
                }

                if ((int)c <= small1 && (int)c >= small2)
                {
                    bi_without[(int)c - small2][(int)b - small2]++;
                    bic_without++;
                }
                if ((int)c <= Big1 && (int)c >= Big2)
                {
                    bi_without[(int)c - Big2][(int)b - small2]++;
                    bic_without++;
                }
                if ((int)c == Big_e || (int)c == small_e)
                {
                    bi_without[coun1 - 1][(int)b - small2]++;
                    bic_without++;
                }
            }
            a = b;
            c = a;
        }
        if ((int)b <= Big1 && (int)b >= Big2)
        {
            arr_with[1][(int)b - Big2]++;
            arr_without[1][(int)b - Big2]++;
            count_with++;
            count_without++;
            if (c == a)
            {
                if ((int)a <= small1 && (int)a >= small2)
                {
                    bi_with[(int)a - small2][(int)b - Big2]++;
                    bic_with++;
                    bi_without[(int)a - small2][(int)b - Big2]++;
                    bic_without++;
                }
                if ((int)a <= Big1 && (int)a >= Big2)
                {
                    bi_with[(int)a - Big2][(int)b - Big2]++;
                    bic_with++;
                    bi_without[(int)a - Big2][(int)b - Big2]++;
                    bic_without++;
                }
                if ((int)a == prob)
                {
                    bi_with[coun2 - 1][(int)b - Big2]++;
                    bic_with++;
                }
                if ((int)a == Big_e || (int)a == small_e)
                {
                    bi_with[coun2 - 2][(int)b - Big2]++;
                    bic_with++;
                    bi_without[coun1-1][(int)b - Big2]++;
                    bic_without++;
                }
            }
            else
            {
                if ((int)a <= small1 && (int)a >= small2)
                {
                    bi_with[(int)a - small2][(int)b - Big2]++;
                    bic_with++;
                }
                if ((int)a <= Big1 && (int)a >= Big2)
                {
                    bi_with[(int)a - Big2][(int)b - Big2]++;
                    bic_with++;
                }
                if ((int)a == prob)
                {
                    bi_with[coun2 - 1][(int)b - Big2]++;
                    bic_with++;
                }
                if ((int)a == Big_e || (int)a == small_e)
                {
                    bi_with[coun2 - 2][(int)b - Big2]++;
                    bic_with++;
                }

                if ((int)c <= small1 && (int)c >= small2)
                {
                    bi_without[(int)c - small2][(int)b - Big2]++;
                    bic_without++;
                }
                if ((int)c <= Big1 && (int)c >= Big2)
                {
                    bi_without[(int)c - Big2][(int)b - Big2]++;
                    bic_without++;
                }
                if ((int)c == Big_e || (int)c == small_e)
                {
                    bi_without[coun1 - 1][(int)b - Big2]++;
                    bic_without++;
                }
            }
            a = b;
            c = a;
        }
        if ((int)b == prob)
        {
            if ((int)a != prob)
            {
                arr_with[1][coun2 - 1]++;
                count_with++;
            }
            if ((int)a <= small1 && (int)a >= small2)
            {
                bi_with[(int)a - small2][coun2 - 1]++;
                bic_with++;
            }
            if ((int)a <= Big1 && (int)a >= Big2)
            {
                bi_with[(int)a - Big2][coun2 - 1]++;
                bic_with++;
            }
            if ((int)a == Big_e || (int)a == small_e)
            {
                bi_with[coun2 - 2][coun2 - 1]++;
                bic_with++;
            }
            a = b;
        }
        if ((int)b == Big_e || (int)b == small_e)
        {
            arr_with[1][coun2 - 2]++;
            arr_without[1][coun1 - 1]++;
            count_with++;
            count_without++;
            if (c == a)
            {
                if ((int)a <= small1 && (int)a >= small2)
                {
                    bi_with[(int)a - small2][coun2-2]++;
                    bic_with++;
                    bi_without[(int)a - small2][coun1-1]++;
                    bic_without++;
                }
                if ((int)a <= Big1 && (int)a >= Big2)
                {
                    bi_with[(int)a - Big2][coun2-2]++;
                    bic_with++;
                    bi_without[(int)a - Big2][coun1-1]++;
                    bic_without++;
                }
                if ((int)a == prob)
                {
                    bi_with[coun2 - 1][coun2-2]++;
                    bic_with++;
                }
                if ((int)a == Big_e || (int)a == small_e)
                {
                    bi_with[coun2 - 2][coun2-2]++;
                    bic_with++;
                    bi_without[coun1 - 1][coun1-1]++;
                    bic_without++;
                }
            }
            else
            {
                if ((int)a <= small1 && (int)a >= small2)
                {
                    bi_with[(int)a - small2][coun2-2]++;
                    bic_with++;
                }
                if ((int)a <= Big1 && (int)a >= Big2)
                {
                    bi_with[(int)a - Big2][coun2-2]++;
                    bic_with++;
                }
                if ((int)a == prob)
                {
                    bi_with[coun2 - 1][coun2-2]++;
                    bic_with++;
                }
                if ((int)a == Big_e || (int)a == small_e)
                {
                    bi_with[coun2 - 2][coun2-2]++;
                    bic_with++;
                }

                if ((int)c <= small1 && (int)c >= small2)
                {
                    bi_without[(int)c - small2][coun1-1]++;
                    bic_without++;
                }
                if ((int)c <= Big1 && (int)c >= Big2)
                {
                    bi_without[(int)c - Big2][coun1-1]++;
                    bic_without++;
                }
                if ((int)c == Big_e || (int)c == small_e)
                {
                    bi_without[coun1 - 1][coun1-1]++;
                    bic_without++;
                }
            }
            a = b;
            c = a;
        }
        co--;
    }
    in.close();

    in.open("idiot.txt");
    if (!in.is_open())
    {
        cout << "Файл не может быть открыт!\n";
        return -1;
    }
    while (!in.eof())
    {
        in.get(a);
        while (!((int)a <= small1 && (int)a >= small2) && !((int)a <= Big1 && (int)a >= Big2) && !((int)a == Big_e || (int)a == small_e) && !in.eof())
        {
            in.get(a);
        }
        in.get(b);
        while (!((int)b <= small1 && (int)b >= small2) && !((int)b <= Big1 && (int)b >= Big2) && !((int)b == Big_e || (int)b == small_e) && !in.eof())
        {
            in.get(b);
        }
        if ((int)a <= small1 && (int)a >= small2)
        {
            if ((int)b <= small1 && (int)b >= small2)
            {
                bip_without[(int)a - small2][(int)b - small2]++;
                bicp_without++;
            }
            if ((int)b <= Big1 && (int)b >= Big2)
            {
                bip_without[(int)a - small2][(int)b - Big2]++;
                bicp_without++;
            }
            if ((int)b == Big_e || (int)b == small_e)
            {
                bip_without[(int)a - small2][coun1-1]++;
                bicp_without++;
            }
        }
        if ((int)a <= Big1 && (int)a >= Big2)
        {
            if ((int)b <= small1 && (int)b >= small2)
            {
                bip_without[(int)a - Big2][(int)b - small2]++;
                bicp_without++;
            }
            if ((int)b <= Big1 && (int)b >= Big2)
            {
                bip_without[(int)a - Big2][(int)b - Big2]++;
                bicp_without++;
            }
            if ((int)b == Big_e || (int)b == small_e)
            {
                bip_without[(int)a - Big2][coun1 - 1]++;
                bicp_without++;
            }
        }
        if ((int)a == Big_e || (int)a == small_e)
        {
            if ((int)b <= small1 && (int)b >= small2)
            {
                bip_without[coun1 - 1][(int)b - small2]++;
                bicp_without++;
            }
            if ((int)b <= Big1 && (int)b >= Big2)
            {
                bip_without[coun1 - 1][(int)b - Big2]++;
                bicp_without++;
            }
            if ((int)b == Big_e || (int)b == small_e)
            {
                bip_without[coun1 - 1][coun1 - 1]++;
                bicp_without++;
            }
        }
    }
    in.close();

    in.open("idiot.txt");
    if (!in.is_open())
    {
        cout << "Файл не может быть открыт!\n";
        return -1;
    }
    in.get(a);
    while (!((int)a <= small1 && (int)a >= small2) && !((int)a <= Big1 && (int)a >= Big2) && !((int)a == Big_e || (int)a == small_e) && !in.eof())
    {
        in.get(a);
    }
    in.get(b);
    if ((int)a == prob)
    {
        while (!((int)b <= small1 && (int)b >= small2) && !((int)b <= Big1 && (int)b >= Big2) && !((int)b == Big_e || (int)b == small_e) && !in.eof())
        {
            in.get(b);
        }
    }
    else
    {
        while (!((int)b == prob) && !((int)b <= small1 && (int)b >= small2) && !((int)b <= Big1 && (int)b >= Big2) && !((int)b == Big_e || (int)b == small_e) && !in.eof())
        {
            in.get(b);
        }
    }
    if ((int)a <= small1 && (int)a >= small2)
    {
        if ((int)b <= small1 && (int)b >= small2)
        {
            bip_with[(int)a - small2][(int)b - small2]++;
            bicp_with++;
        }
        if ((int)b <= Big1 && (int)b >= Big2)
        {
            bip_with[(int)a - small2][(int)b - Big2]++;
            bicp_with++;
        }
        if ((int)b == prob)
        {
            bip_with[(int)a - small2][coun2 - 1]++;
            bicp_with++;
        }
        if ((int)b == Big_e || (int)b == small_e)
        {
            bip_with[(int)a - small2][coun2 - 2]++;
            bicp_with++;
        }
    }
    if ((int)a <= Big1 && (int)a >= Big2)
    {
        if ((int)b <= small1 && (int)b >= small2)
        {
            bip_with[(int)a - Big2][(int)b - small2]++;
            bicp_with++;
        }
        if ((int)b <= Big1 && (int)b >= Big2)
        {
            bip_with[(int)a - Big2][(int)b - Big2]++;
            bicp_with++;
        }
        if ((int)b == prob)
        {
            bip_with[(int)a - Big2][coun2 - 1]++;
            bicp_with++;
        }
        if ((int)b == Big_e || (int)b == small_e)
        {
            bip_without[(int)a - Big2][coun2 - 2]++;
            bicp_with++;
        }
    }
    if ((int)a == prob)
    {
        if ((int)b <= small1 && (int)b >= small2)
        {
            bip_with[coun2 - 1][(int)b - small2]++;
            bicp_with++;
        }
        if ((int)b <= Big1 && (int)b >= Big2)
        {
            bip_with[coun2 - 1][(int)b - Big2]++;
            bicp_with++;
        }
        if ((int)b == Big_e || (int)b == small_e)
        {
            bip_with[coun2 - 1][coun2 - 2]++;
            bicp_with++;
        }
    }
    if ((int)a == Big_e || (int)a == small_e)
    {
        if ((int)b <= small1 && (int)b >= small2)
        {
            bip_with[coun2 - 2][(int)b - small2]++;
            bicp_with++;
        }
        if ((int)b <= Big1 && (int)b >= Big2)
        {
            bip_with[coun2 - 2][(int)b - Big2]++;
            bicp_with++;
        }
        if ((int)b == prob)
        {
            bip_with[coun2 - 2][coun2 - 1]++;
            bicp_with++;
        }
        if ((int)b == Big_e || (int)b == small_e)
        {
            bip_with[coun2 - 2][coun2 - 2]++;
            bicp_with++;
        }
    }
    while (!in.eof())
    {
        in.get(a);
        if ((int)b == prob)
        {
            while (!((int)a <= small1 && (int)a >= small2) && !((int)a <= Big1 && (int)a >= Big2) && !((int)a == Big_e || (int)a == small_e) && !in.eof())
            {
                in.get(a);
            }
        }
        else
        {
            while (!((int)a == prob) && !((int)a <= small1 && (int)a >= small2) && !((int)a <= Big1 && (int)a >= Big2) && !((int)a == Big_e || (int)a == small_e) && !in.eof())
            {
                in.get(a);
            }
        }
        while (!((int)a == prob) && !((int)a <= small1 && (int)a >= small2) && !((int)a <= Big1 && (int)a >= Big2) && !((int)a == Big_e || (int)a == small_e) && !in.eof())
        {
            in.get(a);
        }
        in.get(b);
        if ((int)a==prob)
        {
            while (!((int)b <= small1 && (int)b >= small2) && !((int)b <= Big1 && (int)b >= Big2) && !((int)b == Big_e || (int)b == small_e) && !in.eof())
            {
                in.get(b);
            }
        }
        else
        {
            while (!((int)b == prob) && !((int)b <= small1 && (int)b >= small2) && !((int)b <= Big1 && (int)b >= Big2) && !((int)b == Big_e || (int)b == small_e) && !in.eof())
            {
                in.get(b);
            }
        }
        //cout << a << "     " << b << endl;
        if ((int)a <= small1 && (int)a >= small2)
        {
            if ((int)b <= small1 && (int)b >= small2)
            {
                bip_with[(int)a - small2][(int)b - small2]++;
                bicp_with++;
            }
            if ((int)b <= Big1 && (int)b >= Big2)
            {
                bip_with[(int)a - small2][(int)b - Big2]++;
                bicp_with++;
            }
            if ((int)b == prob)
            {
                bip_with[(int)a - small2][coun2-1]++;
                bicp_with++;
            }
            if ((int)b == Big_e || (int)b == small_e)
            {
                bip_with[(int)a - small2][coun2 - 2]++;
                bicp_with++;
            }
        }
        if ((int)a <= Big1 && (int)a >= Big2)
        {
            if ((int)b <= small1 && (int)b >= small2)
            {
                bip_with[(int)a - Big2][(int)b - small2]++;
                bicp_with++;
            }
            if ((int)b <= Big1 && (int)b >= Big2)
            {
                bip_with[(int)a - Big2][(int)b - Big2]++;
                bicp_with++;
            }
            if ((int)b == prob)
            {
                bip_with[(int)a - Big2][coun2 - 1]++;
                bicp_with++;
            }
            if ((int)b == Big_e || (int)b == small_e)
            {
                bip_without[(int)a - Big2][coun2 - 2]++;
                bicp_with++;
            }
        }
        if ((int)a == prob)
        {
            if ((int)b <= small1 && (int)b >= small2)
            {
                bip_with[coun2 - 1][(int)b - small2]++;
                bicp_with++;
            }
            if ((int)b <= Big1 && (int)b >= Big2)
            {
                bip_with[coun2 - 1][(int)b - Big2]++;
                bicp_with++;
            }
            if ((int)b == Big_e || (int)b == small_e)
            {
                bip_with[coun2 - 1][coun2 - 2]++;
                bicp_with++;
            }
        }
        if ((int)a == Big_e || (int)a == small_e)
        {
            if ((int)b <= small1 && (int)b >= small2)
            {
                bip_with[coun2 - 2][(int)b - small2]++;
                bicp_with++;
            }
            if ((int)b <= Big1 && (int)b >= Big2)
            {
                bip_with[coun2 - 2][(int)b - Big2]++;
                bicp_with++;
            }
            if ((int)b == prob)
            {
                bip_with[coun2 - 2][coun2 - 1]++;
                bicp_with++;
            }
            if ((int)b == Big_e || (int)b == small_e)
            {
                bip_with[coun2 - 2][coun2 - 2]++;
                bicp_with++;
            }
        }
        
    }
    in.close();

    cout << "Количество символов в файле с пробелами   " << count_with << endl;
    cout << "Количество символов в файле без пробелов   " << count_without << endl;
    cout << "Количество пересекающихся биграмм с пробелами   " << bic_with << endl;
    cout << "Количество пересекающихся биграмм без пробелов   " << bic_without << endl;
    cout << "Количество непересекающихся биграмм с пробелами   " << bicp_with << endl;
    cout << "Количество непересекающихся биграмм без пробелов   " << bicp_without << endl << endl;

    //частоты монограмм
    for (int i = 0; i < coun1; i++)        // частоты
    {
        freq_without[1][i] = arr_without[1][i] / count_without;
    }
    for (int i = 0; i < coun2; i++)        // частоты
    {
        freq_with[1][i] = arr_with[1][i] / count_with;
    }

    for (int i = 0; i < coun1-1; i++)            // сортировка
    {
        for (int j = 0; j < coun1 - 1 - i; j++)
        {
            if (freq_without[1][j + 1] > freq_without[1][j])
            {
                double temp = 0;
                int temp2 = 0;
                temp = freq_without[1][j];
                freq_without[1][j] = freq_without[1][j + 1];
                freq_without[1][j + 1] = temp;
                temp = freq_without[0][j];
                freq_without[0][j] = freq_without[0][j + 1];
                freq_without[0][j + 1] = temp;

                temp = freq_with[1][j];
                freq_with[1][j] = freq_with[1][j + 1];
                freq_with[1][j + 1] = temp;
                temp = freq_with[0][j];
                freq_with[0][j] = freq_with[0][j + 1];
                freq_with[0][j + 1] = temp;
            }
        }
    }
    for (int i = 0; i < coun2-1; i++)          // вставляем на нужное место пробел
    {
        if (freq_with[1][coun2-1] > freq_with[1][i])
        {
            double temp = freq_with[1][coun2-1];
            double temp2 = freq_with[0][coun2-1];
            for (int j = coun2-1; j > i; j--)
            {
                freq_with[1][j] = freq_with[1][j - 1];
                freq_with[0][j] = freq_with[0][j - 1];
            }
            freq_with[1][i] = temp;
            freq_with[0][i] = temp2;
        }
    }

    //частоты биграмм
    for (int i = 0; i < coun1; i++)
    {
        for (int j = 0; j < coun1; j++)
        {
            bi_without[i][j] = bi_without[i][j] / bic_without;
        }
    }
    for (int i = 0; i < coun2; i++)
    {
        for (int j = 0; j < coun2; j++)
        {
            bi_with[i][j] = bi_with[i][j] / bic_with;
        }
    }
    for (int i = 0; i < coun1; i++)
    {
        for (int j = 0; j < coun1; j++)
        {
            bip_without[i][j] = bip_without[i][j] / bicp_without;
        }
    }
    for (int i = 0; i < coun2; i++)
    {
        for (int j = 0; j < coun2; j++)
        {
            bip_with[i][j] = bip_with[i][j] / bicp_with;
        }
    }
    
    ofstream freq_mono;
    freq_mono.open("monogram.csv");
    freq_mono << "Таблица частот для текста без пробелов;;;;;Таблица частот для текста с пробелами\n";
    for (int i = 0; i < coun1; i++)
    {
        if (freq_without[0][i] == coun1 - 1)
        {
            freq_mono << ";" << "ё;" << freq_without[1][i] << ";;;;";
            if (freq_with[0][i] == coun2 - 2)
                freq_mono << "ё;" << freq_with[1][i] << "\n";
            if (freq_with[0][i] == coun2 - 1)
                freq_mono << "_;" << freq_with[1][i] << "\n";
            if (freq_with[0][i] != coun2 - 1 && freq_with[0][i] != coun2 - 2)
                freq_mono << (char)(freq_with[0][i] + 224) << ";" << freq_with[1][i] << "\n";
        }
        else
        {
            freq_mono << ";" << (char)(freq_without[0][i] + 224) << ";" << freq_without[1][i] << ";;;;";
            if (freq_with[0][i] == coun2 - 2)
                freq_mono << "ё;" << freq_with[1][i] << "\n";
            if (freq_with[0][i] == coun2 - 1)
                freq_mono << "_;" << freq_with[1][i] << "\n";
            if (freq_with[0][i] != coun2 - 1 && freq_with[0][i] != coun2 - 2)
                freq_mono << (char)(freq_with[0][i] + 224) << ";" << freq_with[1][i] << "\n";
        }
    }
    freq_mono << ";;;;;;";
    if (freq_with[0][coun2 - 1] == coun2 - 2)
        freq_mono << "ё;" << freq_with[1][coun2 - 1] << "\n";
    if (freq_with[0][coun2 - 1] == coun2 - 1)
        freq_mono << "_;" << freq_with[1][coun2 - 1] << "\n";
    if (freq_with[0][coun2 - 1] != coun2 - 1 && freq_with[0][coun2 - 1] != coun2 - 2)
        freq_mono << (char)(freq_with[0][coun2 - 1] + 224) << ";" << freq_with[1][coun2 - 1] << "\n";
    freq_mono.close();
    cout << "Таблицы частот монограмм находятся в файле monogram.csv" << endl;

    ofstream freq_biw;
    freq_biw.open("bigram.csv");
    freq_biw << ";;;;;;;Таблица частот пересекающихся биграмм для текста с пробелами\n;";
    for (int i = 0; i < coun2; i++)
    {
        if (i!=coun2-1 && i!=coun2-2)
            freq_biw  << (char)(i + 224)<< ";";
        if(i==coun2-2)
            freq_biw << "ё;";
        if (i == coun2 - 1)
            freq_biw << "_;";
    }
    freq_biw << "\n";
    for (int i = 0; i < coun2; i++)
    {
        if (i != coun2 - 1 && i != coun2 - 2)
            freq_biw << (char)(i + 224)<< ";" ;
        if (i == coun2 - 2)
            freq_biw << "ё;";
        if (i == coun2 - 1)
            freq_biw << "_;";
        for (int j = 0; j < coun2; j++)
        {
            freq_biw << setprecision(3) <<  bi_with[i][j] << ";";
        }
        freq_biw << "\n";
    }

    freq_biw << "\n\n\n;;;;;;;Таблица частот пересекающихся биграмм для текста без пробелов\n;";
    for (int i = 0; i < coun1; i++)
    {
        if (i != coun1 - 1)
            freq_biw << (char)(i + 224) << ";";
        else
            freq_biw << "ё;";
    }
    freq_biw << "\n";
    for (int i = 0; i < coun1; i++)
    {
        if (i != coun1 - 1)
            freq_biw << (char)(i + 224) << ";";
        else
            freq_biw << "ё;";
        for (int j = 0; j < coun1; j++)
        {
            freq_biw << bi_without[i][j] << ";";
        }
        freq_biw << "\n";
    }

    freq_biw << "\n\n\n;;;;;;;Таблица частот непересекающихся биграмм для текста с пробелами\n;";
    for (int i = 0; i < coun2; i++)
    {
        if (i != coun2 - 1 && i != coun2 - 2)
            freq_biw << (char)(i + 224) << ";";
        if (i == coun2 - 2)
            freq_biw << "ё;";
        if (i == coun2 - 1)
            freq_biw << "_;";
    }
    freq_biw << "\n";
    for (int i = 0; i < coun2; i++)
    {
        if (i != coun2 - 1 && i != coun2 - 2)
            freq_biw << (char)(i + 224) << ";";
        if (i == coun2 - 2)
            freq_biw << "ё;";
        if (i == coun2 - 1)
            freq_biw << "_;";
        for (int j = 0; j < coun2; j++)
        {
            freq_biw << bip_with[i][j] << ";";
        }
        freq_biw << "\n";
    }

    freq_biw << "\n\n\n;;;;;;;Таблица частот непересекающихся биграмм для текста без пробелов\n;";
    for (int i = 0; i < coun1; i++)
    {
        if (i != coun1 - 1)
            freq_biw << (char)(i + 224) << ";";
        else
            freq_biw << "ё;";
    }
    freq_biw << "\n";
    for (int i = 0; i < coun1; i++)
    {
        if (i != coun1 - 1)
            freq_biw << (char)(i + 224) << ";";
        else
            freq_biw << "ё;";
        for (int j = 0; j < coun1; j++)
        {
            freq_biw << bip_without[i][j] << ";";
        }
        freq_biw << "\n";

    }
    freq_biw.close();
    cout << "Таблицы частот биграмм находятся в файле bigram.csv" << endl << endl;
    

    cout << "Энтропия монограмм для текста без пробелов:   " << entropy_mono(coun1) << endl;
    cout << "Энтропия монограмм для текста с пробелами:   " << entropy_mono(coun2) << endl << endl;

    cout << "Энтропия пересекающихся биграмм для текста без пробелов:   " << entropy_bi(1) << endl;
    cout << "Энтропия непересекающихся биграмм для текста без пробелов:   " << entropy_bi(3) << endl << endl;

    cout << "Энтропия пересекающихся биграмм для текста с пробелами:   " << entropy_bi(2) << endl;
    cout << "Энтропия непересекающихся биграмм для текста с пробелами:   " << entropy_bi(4) << endl;

    return 0;
}