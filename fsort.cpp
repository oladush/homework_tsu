#include <iostream>
#include <fstream>

using namespace std;

struct size_
{
    int n = 0;
    int m = 0;
};

int merge(ifstream *f1, ifstream *f2, ofstream *f, int n1, int n2, int step);
size_ merger(ifstream *f1, ifstream *f2, ofstream *f3, ofstream *f4, int n1, int n2, int step);
void machine();

int main() {
//    size_ a = {5, 5};
//    ifstream rf1;
//    ifstream rf2;
//    ifstream rf3;
//    ifstream rf4;
//
//    ofstream wf1;
//    ofstream wf2;
//    ofstream wf3;
//    ofstream wf4;
////
////
//    rf1.open("f1");
//    rf2.open("f2");
//
//
//    wf3.open("f3");
//    wf4.open("f4");
////
////
////
//    int a = merge(&rf1, &rf2, &wf3, 5, 5, 1);
//    int b = merge(&rf1, &rf2, &wf4, 5, 5, 1);
//
//    cout << a;
//    cout << b;
////    cout << a;
//
//    merger(&rf1, &rf2, &wf3, &wf4, 4, 4, 4);
////
////    rf1.close(); rf2.close(); wf3.close(); wf4.close();
//
////    rf3.open("f3");
////    rf4.open("f4");
////
////    wf1.open("f1");
////    wf2.open("f2");
//
//    // merger(&rf3, &rf4, &wf1, &wf2, 4, 4, 2);
//
//
////    int a = merge(&rf1, &rf2, &wf3, 4, 4, 1);
////
////    rf1.seekg(-1, ios::cur);

    machine();


    return 0;
}

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

    (*f1).seekg(-2, ios::cur);
    (*f2).seekg(-2, ios::cur);

    return n1 + n2;

}

size_ merger(ifstream *f1, ifstream *f2, ofstream *f3, ofstream *f4, int n1, int n2, int step)
{
    int n = 0, m = 0;
    int i = 0;
    while (n1 > 0 || n2 > 0)
    {
        cout << "to_one" << endl;
        n += merge(f1, f2, f3, n1, n2, step);
        n1 -= step;
        n2 -= step;
        if (n1 < 0) n1 = 0;
        if (n2 < 0) n2 = 0;
        cout << "to_two" << endl;
        m += merge(f1, f2, f4, n1, n2, step);
        n1 -= step;
        n2 -= step;
        if (n1 < 0) n1 = 0;
        if (n2 < 0) n2 = 0;

        cout << "n= " << n << endl;
        cout << "m= " << m << endl;
        i++;

    }

    cout << "it" << i << endl;

    return size_{n, m};
}

void machine()
{
    int  n1 = 5, n2 = 5;
    int step = 1;
    int i = 0;
    size_ n = {n1, n2};
    while (step < n.n  || step < n.m || (n.n && n.m))
    {
        if (i % 2 == 0)
        {
            ifstream rf1, rf2;
            ofstream wf3, wf4;

            rf1.open("f1");
            rf2.open("f2");

            wf3.open("f3", ios::app);
            wf4.open("f4", ios::app);

            n = merger(&rf1, &rf2, &wf3, &wf4, n.n, n.m, step);
            rf1.close(); rf2.close(); wf3.close(); wf4.close();

            ofstream clr1, clr2;
            clr1.open("f1", std::ofstream::out | std::ofstream::trunc);
            clr2.open("f2", std::ofstream::out | std::ofstream::trunc);
            clr1.close();
            clr2.close();

            step*=2; i++;
        }
        else
        {
            ifstream rf3, rf4;
            ofstream wf1, wf2;

            rf3.open("f3");
            rf4.open("f4");

            wf1.open("f1", ios::app);
            wf2.open("f2", ios::app);

            n = merger(&rf3, &rf4, &wf1, &wf2, n.n, n.m, step);
            rf3.close(); rf4.close(); wf1.close(); wf2.close();

            ofstream clr1, clr2;
            clr1.open("f3", std::ofstream::out | std::ofstream::trunc);
            clr2.open("f4", std::ofstream::out | std::ofstream::trunc);
            clr1.close();
            clr2.close();

            step*=2; i++;

        }


    }

    cout << n.n << " " << n.m;

}
