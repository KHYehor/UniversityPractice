#include <iostream>
#include <cmath>
using namespace std;

//20. Имеется n слов различной  длины, все они занесены в массив А.  Составить программу упорядочения слов по возрастанию их длин.


void printStringArray (string *arr, const int SIZEARR)
{
    int i = 0;
    while(i < SIZEARR)
    {
        cout << arr[i] << " ";              // Для вывода чисел через пробел.
        i++;
    }
    cout << "" << endl;                     // Перевод на новую строчку.
}

void lengthSort(string *arr, const int SIZEARR)
{
    int i = 0;
    int j;
    string tmp;
    while(i < SIZEARR)
    {
        j = i;
        while (j > 0)
        {
            if(arr[j].length() < arr[j - 1].length())
            {
                tmp = arr[j];
                arr[j] = arr[j - 1];
                arr[j - 1] = tmp;
            }
            j--;
        }
        i++;
    }
    printStringArray(arr, SIZEARR);
}

int main()
{
    const int SIZE = 9;
    string *arrayA = new string[SIZE]{"one", "difficult", "functor", "function", "hi", "adidas", "more", "impossible", "lol"};
    cout << "Before sorting" << endl;
    printStringArray(arrayA, SIZE);
    cout << "after sorting" << endl;
    lengthSort(arrayA, SIZE);
}
