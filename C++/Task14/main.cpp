#include <iostream>
#include <cmath>
using namespace std;

//14. Дан упорядоченный массив А - числа, расположенные в порядке возрастания, и число а, которое необходимо вставить в массив А, так,  чтобы упорядоченность массива сохранилась.

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

void insert(int *arr, const int SIZEARR, int el) // Передаем массив, его длину и вставочный элемент.
{
    int *arrayB = new int[SIZEARR + 1];          // Создаем новый массив на 1 элемент больший.
    int i = 0;
    int tmp;
    while (i < SIZEARR + 1) {
        arrayB[i] = arr[i];                      // Автозаполняем наш второй массив элементами первого,
        i++;
    }
    arrayB[SIZEARR] = el;
    i = SIZEARR;                                 // Последнему элементу мы присваиваем вставочный элемент,
    while (i > 0)                                // Теперь с конца массива двигаем вставочный элемент дальше в начало,
    {                                            // пока следующий элемент не будет меньше чем вставочный.
        if (arrayB[i] < arrayB[i - 1])
        {
            tmp = arrayB[i];
            arrayB[i] = arrayB[i - 1];
            arrayB[i - 1] = tmp;
        }
        i--;
    }
    printArray(arrayB, SIZEARR + 1);
    delete[] arrayB;
}


int main() {
    const int SIZE = 9;
    int *arrayA = new int[SIZE]{1, 2, 3, 4, 6, 7, 8, 9, 10};
    printArray(arrayA, SIZE);
    cout << "insert el - 7" << endl;
    insert(arrayA, SIZE, 7);
}
