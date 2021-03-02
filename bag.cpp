#include <fstream>
#include <iostream>

using namespace std;

struct size_
{
    int n = 0;
    int m = 0;
};

int merge(ifstream *f1, ifstream *f2, ofstream *f, int n1, int n2, int step);
size_ merger(ifstream *f1, ifstream *f2, ofstream *f3, ofstream *f4, int n1, int n2, int step);
size_ split(ifstream *file, ofstream *f1, ofstream *f2);

void sort_machine()
{
    int  n1 = 5, n2 = 5;
    int step = 1;
    int i = 0;
    size_ n = {n1, n2};
    while (step < n.n  || step < n.m || (n.n && n.m))
    {
        string rfname1;
        string rfname2;
        string wfname1;
        string wfname2;

        if (i % 2 == 0)
        {
            rfname1 = "f1";
            rfname2 = "f2";

            wfname1 = "f3";
            wfname2 = "f4";
        }
        else
        {
            rfname1 = "f3";
            rfname2 = "f4";

            wfname1 = "f1";
            wfname2 = "f2";

        }

        ifstream rf1, rf2;
        ofstream wf1, wf2;

        rf1.open(rfname1);
        rf2.open(rfname2);

        wf1.open(wfname1, ios::app);
        wf2.open(wfname2, ios::app);

        n = merger(&rf1, &rf2, &wf1, &wf2, n.n, n.m, step);
        rf1.close(); rf2.close(); wf1.close(); wf2.close();

        ofstream clr1, clr2;
        clr1.open(rfname1, std::ofstream::out | std::ofstream::trunc);
        clr2.open(rfname2, std::ofstream::out | std::ofstream::trunc);
        clr1.close(); clr2.close();

        step *= 2; i++;

    }

    cout << n.n << " " << n.m;

}

int main() {
    sort_machine();
    return 0;
}


size_ split(ifstream *file, ofstream *f1, ofstream *f2, int n)
{
    int num; size_ count = {0, 0};
    for (int i = 0; i < n; i++)
    {
        *file >> num;

        if (i % 2 == 0)
        {
            *f1 << num;
            count.n ++;
        }
        else
        {
            *f2 << num;
            count.m ++;
        }
    }
    return count;
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
        n += merge(f1, f2, f3, n1, n2, step);
        n1 -= step;
        n2 -= step;
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



