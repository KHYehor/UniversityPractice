#include <iostream>
#include <cmath>
using namespace std;

//17. Составить программу, которая будет из массива А брать одно число за другим и формировать из них массив В, располагая числа в порядке возрастания.

void FillArray(int *arr, const int SIZEARR)   // Передаем массив и его размер.
{
    int i = 0;
    while (i < SIZEARR)                       // Циклом задаем ему числа в диапозоне
    {                                         // от -99 до 99.
        arr[i] = (rand() % 198) - 99;
        i++;
    }
}

void quicksort(int *arr, int left, int right)
{
    int i = left;                           // указатель на то число откуда мы начинаем сортировать
    int j = right;                          // указатель на то число до куда мы начинаем сортировать
    int tmp;                                // временнная переменная для изменения местами двух чисел
    int pivot = arr[(left + right) / 2];    // опорный эллемент для сравнения, который берется по середине массива (типо продвинутый метод)
    while (i <= j)                          // до тех пор пока левое меньше/равно правому
    {
        while(arr[i] < pivot) { i++; }      // сравнение с опорным, если меньше, то всё окей, проверяем и ищем то число, которое больше опороного
        while(arr[j] > pivot) { j--; }      // сравнение с опорным, если большн, то всё окей, проверяме и ищем то число, которое меньше опороного
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

void specialsort(int *arr, const int SIZEARR)
{
    int *newarr = new int[SIZEARR];
    int i = 0;
    while (i < SIZEARR)
    {
        newarr[i] = arr[i];
        quicksort(newarr, 0, i);
        i++;
    }
    printArray(newarr, SIZEARR);
}

//void specialsort(int *arr, const int SIZEARR)
//{
//    int *newarr = new int[SIZEARR];
//    int i = 0;
//    int j = 0;
//    int tmp;
//    while (i < SIZEARR)
//    {
//        newarr[i] = arr[i];                     // Вставляем элементы в массив циклом
//        while (j > 0)
//        {                                       // Тут делаем сравнение элмента с предыдущеми
//            if (newarr[j] < newarr[j - 1])      // и переставляем их местами, если последний больше предыдущего
//            {
//                tmp = newarr[j];
//                newarr[j] = newarr[j - 1];
//                newarr[j - 1] = tmp;
//            } else break;
//            j--;
//        }
//        i++;
//        j = i;
//
//    }
//    printArray(newarr, SIZEARR);
//}

int main() {
    const int SIZE = 9;
    int *arrayA = new int[SIZE];
    FillArray(arrayA, SIZE);
    cout << "array before sorting" << endl;
    printArray(arrayA, SIZE);
    cout << "array after sorting" << endl;
    specialsort(arrayA, SIZE);
}

