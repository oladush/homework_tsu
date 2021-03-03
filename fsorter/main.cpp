#include <fstream>
#include <iostream>

using namespace std;

// структура для удобной передачи размерности файлов,
// понимаю, что не обязательно было создавать  новый тип данных для двух переменных одинакового типа,
// но на мой взгляд, так получается лаконичнее
struct size_
{
    int n = 0;
    int m = 0;
};

int len(int num);
size_ split(ifstream *f1, ofstream *f2, ofstream *f3, int size);
int merge(ifstream *f1, ifstream *f2, ofstream *f, int n1, int n2, int step);
size_ merger(ifstream *f1, ifstream *f2, ofstream *f3, ofstream *f4, int n1, int n2, int step);
void sort_machine(string *filename, string *f1, string *f2, string *f3, string *f4, int size);


int main() {
    // выделяем память под имена файлов, я решил использовать
    // тип данных string потому что это удобно, и с++ позволяет.

    string *file = new string;

    string *fn1 = new string;
    string *fn2 = new string;
    string *fn3 = new string;
    string *fn4 = new string;

    // имена файлов с которыми будем работать
    *file = "file.txt";
    *fn1 = "f1.txt";
    *fn2 = "f2.txt";
    *fn3 = "f3.txt";
    *fn4 = "f4.txt";

    //основная функция
    sort_machine(file, fn1, fn2, fn3, fn4, 13);

    //очищаем память
    delete file, fn1, fn2, fn3, fn4;

    return 0;
}

// функция делит исходный файл(сортируемый) на две части(файла)
// и возвращает их размер
size_ split(ifstream *f1, ofstream *f2, ofstream *f3, int size)
{
    int num, n = 0, m = 0;
    for (int i = 0; i < size; i++)
    {
        *f1 >> num;

        if (i % 2 == 0)
        {
            *f2 << num << " ";
            n++;
        }
        else
        {
            *f3 << num << " ";
            m++;
        }
    }

    return size_ {n, m};

}

// функция выполняет слияние двух файлов беря у каждого step чисел,
// записывая их в третий файл. Возвращает длину полученного слияния.
int merge(ifstream *f1, ifstream *f2, ofstream *f, int n1, int n2, int step)
{
    n1 = n1 > step ? n1 = step : n1;
    n2 = n2 > step ? n2 = step : n2;

    int i = 0, j = 0;
    int a, b;

    *f1 >> a; *f2 >> b;

    while (i < n1 && j < n2)
    {
        if (a < b)
        {
            *f << a << " ";
            *f1 >> a;
            i++;
        }
        else
        {
            *f << b << " ";
            *f2 >> b;
            j++;

        }

    }
    while (i < n1)
    {
        *f << a << " ";
        *f1 >> a;
        i++;
    }
    while (j < n2)
    {
        *f << b << " ";
        *f2 >> b;
        j++;
    }

    // здесь я сдвигаю положение потоков чтения
    // т.к. чтение потока происходит до проверки
    // условий и действий с ними.
    // откатываюсь назад до длины прочтенного числа
    // + пробел
    (*f1).seekg(-len(a)-1, ios::cur);
    (*f2).seekg(-len(b)-1, ios::cur);

    cout << "len = "<<len(a) << endl;

    return n1 + n2;

}

// контроллирует функцию merge и разбивает согласно алгоритму сбалансированной сортировки
// два входных файла, на два выходных
size_ merger(ifstream *f1, ifstream *f2, ofstream *f3, ofstream *f4, int n1, int n2, int step)
{
    int n = 0, m = 0;
    while (n1 > 0 || n2 > 0)
    {
        n += merge(f1, f2, f3, n1, n2, step);
        n1 -= step;
        n2 -= step;

        // чтобы колличество не становилось отрицательным
        if (n1 < 0) n1 = 0;
        if (n2 < 0) n2 = 0;

        m += merge(f1, f2, f4, n1, n2, step);
        n1 -= step;
        n2 -= step;

        if (n1 < 0) n1 = 0;
        if (n2 < 0) n2 = 0;

    }

    return size_{n, m};
}

// форматирование файла
void clear(string *filename)
{
    ofstream clr;
    clr.open(*filename, ofstream::out | ofstream::trunc);
    clr.close();
}

// реализует алгоритм сбалансированной сортировки
void sort_machine(string *filename, string *f1, string *f2, string *f3, string *f4, int size)
{
    int step = 1; // устанавливаем шаг с которого начинаем

    clear(f1); clear(f2); clear(f3); clear(f4); // очищаем вспомогательные файлы

    ifstream fr;
    fr.open(*filename); // файл с исходнымми данными

    ofstream fw1, fw2;
    fw1.open(*f1);
    fw2.open(*f2);

    size_ n = split(&fr, &fw1, &fw2, size);
    fr.close(); fw1.close(); fw2.close();

    //разбили исходный файл на два, сохранили их размеры.


    int i = 0; // счетчик для проверки на четность

    string rfname1, rfname2; //переменные в которых будут храниться имена читаемых и записываемых файлов
    string wfname1, wfname2;

    while (n.n && n.m) // пока один из пары файлов не опустеет, будет выполняться слияние
    {
        if (i % 2 == 0)
        {
            rfname1 = *f1;
            rfname2 = *f2;

            wfname1 = *f3;
            wfname2 = *f4;
        }
        else
        {
            rfname1 = *f3;
            rfname2 = *f4;

            wfname1 = *f1;
            wfname2 = *f2;

        }
        // если проход четный читаем f1, f2. Пишем в f2, f3. Иначе. наоборот.

        ifstream rf1, rf2;
        ofstream wf1, wf2;

        rf1.open(rfname1); // открываем на чтение
        rf2.open(rfname2);

        wf1.open(wfname1, ios::app); // открываем на дозапись
        wf2.open(wfname2, ios::app);

        n = merger(&rf1, &rf2, &wf1, &wf2, n.n, n.m, step); // делаем "слияние"
        rf1.close(); rf2.close(); wf1.close(); wf2.close(); // закрываем потоки

//        ofstream clr1, clr2;
//        clr1.open(rfname1, std::ofstream::out | std::ofstream::trunc);
//        clr2.open(rfname2, std::ofstream::out | std::ofstream::trunc);
//        clr1.close(); clr2.close();

        clear(&rfname1); // очищаем файлы, которые прочитали
        clear(&rfname2);

        step *= 2; i++; // шаг для следуещего слияния увеличивается вдвое, сменяется четность(или нечетность)

    }
}

// просто нахождение длины числа(колличества разрядов в десятичной записи)
int len(int num)
{
    int length = 0;
    while (num > 0)
    {
        num /= 10;
        length++;
    }
    return length;
}
