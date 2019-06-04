#include <iostream>
#include <cmath>
using namespace std;

//22. В отсортированный массив А. между каждой соседней парой элементов вставить число больше левого и меньше правого элемента в массиве и вывести полученный массив на экран.


void FillArray(int *arr, const int SIZEARR)   // Передаем массив и его размер.
{
    int i = 0;
    while (i < SIZEARR)                       // Циклом задаем ему числа в диапозоне
    {                                         // от -99 до 99.
        arr[i] = (rand() % 198) - 99;
        i++;
    }
}

void shellsort(int *arr, const int SIZEARR)
{
    int step, j, k, tmp;                        // Объявляем наши переменные шаг, одну для свапа и два для циклов
    for(step = SIZEARR / 2; step > 0; step /= 2) // здесь сначала наш шаг равен Массив / 2, после он будет равен массив / 2 / 2
    {
        for(j = step; j < SIZEARR; j++)          // теперь присваимваем в j наш шаг
        {
            for(k = j - step; k >= 0; k -= step) // а здесь мы выссчитываеи сколько будет элементов в одной связке с таким-то шагом
            {                                    // сначала 2, потом больше и больше
                if(arr[k + step] <= arr[k])
                {
                    tmp = arr[k];
                    arr[k] = arr[k + step];
                    arr[k + step] = tmp;
                }
                else { break; }
            }
        }
    }
}

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

void doubleinsert (int *arr, const int SIZEARR)
{
    int *arrayB = new int[SIZEARR * 2 - 1];
    int i = 0;
    int j = 0;
    while (i < SIZEARR)
    {
        arrayB[j] = arr[i];
        arrayB[j + 2] = arr[i + 1];
        arrayB[j + 1] = (arr[i] + arr[i + 1]) / 2;
        i++;
        j += 2;
    }
    printArray(arrayB, SIZEARR * 2 - 1);
}

int main() {
    const int SIZE = 8;
    int *arrayA = new int[SIZE];
    FillArray(arrayA, SIZE);
    shellsort(arrayA, SIZE);
    cout << "array before insert" << endl;
    printArray(arrayA, SIZE);
    cout << "array after insert" << endl;
    doubleinsert(arrayA, SIZE);
}
