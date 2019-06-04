#include <iostream>
#include <cmath>
using namespace std;

//  13. В массиве А находятся элементы. Составить программу, которая сформирует массив В, в котором расположить элементы массива А в порядке убывания.

void FillArray(int *arr, const int SIZEARR)   // Передаем массив и его размер.
{
    int i = 0;
    while (i < SIZEARR)                       // Циклом задаем ему числа в диапозоне
    {                                         // от -99 до 99.
        arr[i] = (rand() % 198) - 99;
        i++;
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

void quicksort(int *arr, int left, int right)
{
    int i = left;                           // указатель на то число откуда мы начинаем сортировать
    int j = right;                          // указатель на то число до куда мы начинаем сортировать
    int tmp;                                // временнная переменная для изменения местами двух чисел
    int pivot = arr[(left + right) / 2];    // опорный эллемент для сравнения, который берется по середине массива (типо продвинутый метод)
    while (i <= j)                          // до тех пор пока левое меньше/равно правому
    {
        while(arr[i] > pivot) { i++; }      // сравнение с опорным, если меньше, то всё окей, проверяем и ищем то число, которое больше опороного
        while(arr[j] < pivot) { j--; }      // сравнение с опорным, если большн, то всё окей, проверяме и ищем то число, которое меньше опороного
        if (i <= j) {                       // если же левый указатель залез за правый, то сортировка относительно опорного элемента закончена
            tmp = arr[i];                   // замена двух чисел ну и подвигаем наши указатели
            arr[i] = arr[j];
            arr[j] = tmp;
            i++;
            j--;
        }
    }
    if (left < j) quicksort(arr, left, j);      // повторяем тоже самое от начала массива до того числа, которое стояло перед опорным если
    if (i < right) quicksort(arr, i, right);    // массив не отсортирован, то начальный элемент не будет равен j
}

void copyArray(int * arr, const int SIZEARR)
{
    int *arrB = new int[SIZEARR];
    for(int i = 0; i < SIZEARR; i++)
    {
        arrB[i] = arr[i];
    }
    quicksort(arrB, 0, SIZEARR);
    printArray(arrB, SIZEARR);
}

int main() {
    const int SIZE = 9;
    int *arrayA = new int[SIZE];
    FillArray(arrayA, SIZE);
    cout << "array filled" << endl;
    printArray(arrayA, SIZE);
    cout << "new array reverse sorted" << endl;
    copyArray(arrayA, SIZE);
}
