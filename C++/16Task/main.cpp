#include <iostream>
#include <cmath>
using namespace std;

//16. Дан массив А, содержащий как отрицательные, так и положительные числа. Составить программу исключения из него всех отрицательных чисел, а оставшиеся положительные расположить в порядке их возрастания.

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

void shellsort(int *arr, const int SIZEARR)
{
    int step, j, k, tmp;                         // Объявляем наши переменные шаг, одну для свапа и два для циклов
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
                else break;
            }
        }
    }
}

void filter(int *arr, const int SIZEARR)        // функция фильтр
{
    int i = 0;
    int j = 0;
    int size = 0;
    while(i < SIZEARR)                          // этот цикл для того, чтобы насчитать то число элемнтов которое пройдет проверку
    {
        if(arr[i] >= 0)                         // сама проверка элементов
        {
            size++;
        }
        i++;
    }
    i = 0;                                      // скидываем до нуля
    int *ArrayC = new int[size];                // создаём снова массив для элементов которые прошли проверку
    while(i < SIZEARR)
    {
        if(arr[i] >= 0)
        {
            ArrayC[j] = arr[i];
            j++;
        }
        i++;
    }
    shellsort(ArrayC, size);                   // после уже отсортируем этот массив по возрастанию
    printArray(ArrayC, size);
}

int main()
{
    const int SIZE = 9;
    int *arrayA = new int[SIZE];
    cout << "array before sort" << endl;
    FillArray(arrayA, SIZE);
    printArray(arrayA, SIZE);
    cout << "array after filtrening + sorting" << endl;
    filter(arrayA, SIZE);
}
