#include <iostream>
#include <cmath>
using namespace std;

//21. Составить программу для сортировки массива А по возрастанию и убыванию модулей его элементов.


void printArray(int arr[], const int SIZEARR) // Передаем массив и его размер.
{
    int i = 0;
    while(i < SIZEARR)
    {
        cout << arr[i] << " ";                // Для вывода чисел через пробел.
        i++;
    }
    cout << "" << endl;                       // Перевод на новую строчку.
}

void modulesort(int *arr, const int SIZEARR)
{
    int i = 0;
    int j = 0;
    int num1;
    int num2;
    int tmp;
    while (i < SIZEARR)
    {
        while (j > 0)
        {
            if (arr[j] < 0) num1 = arr[j] * -1;
            else num1 = arr[j];
            if (arr[j - 1] < 0) num2 = arr[j - 1] * -1;
            else num2 = arr[j - 1];
            if (num1 < num2)
            {
                tmp = arr[j];
                arr[j] = arr[j - 1];
                arr[j - 1] = tmp;
            } else break;
            j--;
        }
        i++;
        j = i;
    }
    printArray(arr, SIZEARR);
}

int main() {
    const int SIZE = 9;
    int *arrayA = new int[SIZE]{-45, 23, -56, 1, 0, -87, 4, 2, -9};
    cout << "before module sort" << endl;
    printArray(arrayA, SIZE);
    cout << "after module sort" << endl;
    modulesort(arrayA, SIZE);
}
