#include <iostream>
#include <cmath>
using namespace std;

//19. Имеется n абонентов телефонной станции. Составить программу, в которой формируется  список по форме: номер телефона, фамилия (номера идут в порядке возрастания).


void printdata(int *arr1, string *arr2, const int SIZEARR) // Передаем массив и его размер.
{
    int i = 0;
    while (i < SIZEARR)
    {
        cout << arr2[i] << " - " << arr1[i] << endl;
        i++;
    }
}

void sort(int *arr1, string *arr2, const int SIZEARR)
{
    int i = 1;
    int j = 0;
    int tmp;
    string temp;
    while (i < SIZEARR)
    {
        j = i;
        while (j > 0)
        {
            if (arr1[j] < arr1[j - 1])
            {
                tmp = arr1[j];
                arr1[j] = arr1[j - 1];
                arr1[j - 1] = tmp;
                temp = arr2[j];
                arr2[j] = arr2[j - 1];
                arr2[j - 1] = temp;
            }
            j--;
        }
        i++;
    }
}

int main() {
    const int SIZE = 10;
    int *arratA = new int[SIZE]{1242, 5765, 2421, 9967, 2113, 1121, 9489, 7467, 8823, 2222};
    string *arrayB = new string[SIZE]{"Artur", "Gerold", "Zwain", "Shwein", "Spin", "Porto", "Utin", "Mopsy", "Zun", "Alfred"};
    cout << "before sort" << endl;
    cout << "" << endl;
    printdata(arratA, arrayB, SIZE);
    sort(arratA, arrayB, SIZE);
    cout << "" << endl;
    cout << "after sort" << endl;
    cout << "" << endl;
    printdata(arratA, arrayB, SIZE);
}
