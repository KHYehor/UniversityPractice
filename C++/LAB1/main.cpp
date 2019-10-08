#include <iostream>
using namespace std;

template<typename T>                            // Это наш конструктор для каждого нового элемента списка,
struct Node                                     // в нём будут хранится сами данные в поле data, T - означает, что
{                                               // тип данных может быть любым, поле pNext ссылает наш на следующий узел
    T data;                                     // который и есть элементом наша списка, тоже самое и pPrev, идет ссылка на
    Node *pNext;                                // предыдщуий элемент.
    Node *pPrev;
};

template<typename T>                            // Это наш конструктор для самого списка, где будут хранится сами методы для него,
class List {                                    // в привате лежат ссылка на первый элемент нашего списка - head, и на последний элемент списка - tail,
private:                                        // и сам размер списка - Size;
    Node<T> *head;
    Node<T> *tail;
    int Size;
public:
    List();                                     // При объявлении нового списка, здесь будут задаваться поля Size, head, tail.
    void push(T el);                            // Метод push - для добавления элемента в конец списка.
    void unshift(T el);                         // Метод unshift - для добавления элемента в начало списка.
    void pop();                                 // Метод pop - для удаления элемента с конца списка.
    void shift();                               // Метод shift - для удаления элемента с начала списка.
    void insert(T el, int index);               // Метод для вставки элемента в место, выбранное нами (индексация идёт как и в массивах).
    void del(int index);                        // Метод для удалени элемента в том месте, которое нас интересует (индексация идет как и в массивах).
    void show();                                // Метод для вывода элементов списка в консоль.
    void copy(List<T> &copied);                 // Метод для коппирования списка в другой, пустой список что мы передаём в функцию.
};

template<typename T>                            // Конструктор для спика,
List<T>::List() {
    Size = 0;                                   // Так как он пуст при создании, то размер будет 0.
    head = tail = nullptr;                      // А первый и последний элементы у нас нулевые.
}

template<typename T>
void List<T>::push(T el)
{
    
    Node<T> *temp = new Node<T>;                // Создаём новый пустой узел, который будет позже элементом нашего списка.
    
    temp->pNext = nullptr;                      // Так как добавление идёт в конец, то ссылка на следующий элемент будет указывать на nullptr.
    temp->data = el;                            // В поле data положим сам элемент, который мы будем пушить.
    temp->pPrev = tail;                         // В ссылку на предыдущий элемент мы оставим наш последний текущий элемент - tail.
    
    if (Size != 0) tail->pNext = temp;          // Если наш список не пуст то теперь нужно с последнего текущего элемента оставить ссылку на тот
    // элемент который мы вставили,
    if (Size == 0) head = tail = temp;          // Если это наш первый элемент, то мы определим вставленный элмент как первый и последний
    else tail = temp;                           // в противном случае же теперь определим вставленный элмент как последний,
    Size++;                                     // и добавим размерность списка +1.
}

template<typename T>                            // Тоже самое что я и делал в push, но теперь сначала списка.
void List<T>::unshift(T el)
{
    Node<T> *temp = new Node<T>;
    temp->pPrev = nullptr;
    temp->data = el;
    temp->pNext = head;
    if (Size == 0) head = tail = temp;
    else head = temp;
    Size++;
}

template<typename T>
void List<T>::shift()
{
    if (Size == 0) {                            // Если в списке нет элементов, то мы ничего оттуда и не удалим.
        cout << "List is empty."<< endl;
    }
    else
    {
        Node<T> *temp = head->pNext;            // Положим в переменную temp второй элемент списка,
        head = temp;                            // в сам head уложим temp, но ссылку на предыдущий нам нужно удалить,
        head->pPrev = nullptr;                  // записав туда nullptr, ну и уменьшим нашу размерность на 1.
        delete temp;
        Size--;
    }
}

template<typename T>                            // Делаем тоже самое что и в shift, только с конца списка.
void List<T>::pop()
{
    Node<T> *temp = tail->pPrev;
    tail = temp;
    tail->pNext = nullptr;
    Size--;
}

template<typename T>
void List<T>::insert(T el, int index)
{
    if (index > Size + 1) {                     // Если индекс больше чем размер списка + 1, то произвести вставку по
        cout << "Impossible." << endl;          // этому индексу будет не возможно.
    }
    else                                        // В обратном же случае сделаем саму вставку, но для начала проверим как
    {                                           // добраться до элемента быстрее, с конца или с начала, что я и делаю в этом условии.
        if(index < Size - index)
        {                                       // Это условие когда добраться быстрее с начала,
            unshift(el);                        // вставляю один элемент в начало, с нашим вставляемым значением,
            Node<T> *temp = head;               // и делаю ссылку на этот первый элемент.
            T tmp;                              // переменная для хранения data.
            int i = 0;
            while (i < index)                   // после циклxино
            {
                temp = temp->pNext;             // двигаю мой промежуточный узел впреред
                tmp = temp->data;               // сохраняю в переменную data текущего элемента,
                temp->data = temp->pPrev->data; // двигаю свой вставленный элемент дальше,
                temp->pPrev->data = tmp;        // а в предыдущий присваиваю тот сохраненный,
                i++;                            // тем самым делаю swap, пока не доберусь до нужного индекса.
            }
        }
        else
        {
            push(el);                           // та же самая операция но с конца списка.
            Node<T> *temp = tail;
            T tmp;
            int i = Size;
            while (i > index)
            {
                temp = temp->pPrev;
                tmp = temp->data;
                temp->data = temp->pNext->data;
                temp->pNext->data = tmp;
                i--;
            }
        }
    }
}

template<typename T>
void List<T>::del(int index)
{
    if (Size == 0 && index >= Size) {           // Проверка на то, есть ли элементы в списке вообще,
        cout << "Are you kidding me?" << endl;  // ну и то, не удаляем ли элемент индекс которого больше,
    }                                           // чем размер списка.
    else
    {
        if (index < Size - index)               // Та же схема, ищем как добраться до элемента быстрее,
        {                                       // с конца или с начала.
            Node<T> *temp = head;               // Передвигаем все элементы впред, пока не затрём тот элемент,
            T tmp1 = temp->data;                // который необходимо удалить, после удалим крайний узел - первый,
            T tmp2 = temp->pNext->data;         // или последний.
            int i = 0;
            while (i < index)
            {
                temp = temp->pNext;
                temp->data = tmp1;
                temp->pNext->data = tmp2;
                tmp1 = temp->pNext->data;
                tmp2 = temp->pNext->pNext-> data;
                i++;
            }
            shift();
        }
        else                                    // тоже самое но с конца.
        {
            Node<T> *temp = tail;
            T tmp1 = temp->data;
            T tmp2 = temp->pPrev->data;
            int i = Size;
            while (i > index)
            {
                temp = temp->pPrev;
                temp->data = tmp1;
                temp->pPrev->data = tmp2;
                tmp1 = temp->pPrev->data;
                tmp2 = temp->pPrev->pPrev-> data;
                i--;
            }
            pop();
        }
    }
    
}

template<typename T>
void List<T>::show()
{
    if (Size != 0) {                            // проверка есть ли элементы в списке,
        Node<T> *temp = head;                   // устанавливаем указатель на первый элемент,
        while (temp->pNext != nullptr) {        // после циклично выводим data каждого элемента
            cout << temp->data << ", ";
            temp = temp->pNext;
        }
        cout << temp->data << ".\n" << endl;
    } else {
        cout << "List is empty." << endl;
    }
}

template<typename T>
void List<T>::copy(List<T> &copied)
{
    Node<T> *cur = head;                        // делаем указатель на первый элемент списка,
    copied.push(cur->data);                     // в наш пустой список добавляем элементы циклом,
    while (cur->pNext != nullptr)               // пока не дойдем до конца.
    {
        cur = cur->pNext;
        copied.push(cur->data);
    }
}

int main() {
    setlocale(LC_ALL, "ru");
    List<int> Numbers1;
    List<int> Numbers2;
    Numbers1.push(1);
    Numbers1.push(2);
    Numbers1.push(3);
    Numbers1.push(4);
    Numbers1.push(5);
    Numbers1.push(6);
    Numbers1.push(7);
    Numbers1.push(8);
    Numbers1.push(9);
    Numbers1.push(10);
    cout << "Added elements to List.\n" << endl;
    Numbers1.show();
    Numbers1.unshift(0);
    Numbers1.pop();
    Numbers1.insert(4, 5);
    Numbers1.del(8);
    cout << "After operations with List.\n" << endl;
    Numbers1.show();
    Numbers1.copy(Numbers2);
    Numbers2.push(10);
    Numbers2.push(11);
    cout << "Numbers1 - List:\n" << endl;
    Numbers1.show();
    cout << "Numbers2 - List:\n" << endl;
    Numbers2.show();
}
