void merge(ifstream *f1, ifstream *f2, ofstream *f, int n1, int n2, int step)
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
        *f2 >>b;
        j++;
    }
    
}
