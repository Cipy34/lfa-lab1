#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;
int citire(int m[100][100], int n, int f[100])
{
    ifstream fin("C:\\Users\\Ciprian\\lfa\\ex5.txt");
    int j, i;
    char k[10], l[10], h;
    fin>>n;
    for(i = 0; i<n; i++)
        for(j = 0; j<n; j++)
        {
            m[i][j] = -1;
            f[i] = -1;
        }

    for(i = 0; i<n; i++)
    {
        fin>>k>>h>>l;
        if(h >= 'a')
            m[k[1]-'0'][h - 'a'] = l[1]-'0';
        else
            m[k[1]-'0'][h - '0'] = l[1]-'0';
    }

    i = 0;
    while(fin>>k)
    {
        f[i] = k[1] - '0';
        i++;
    }

    fin.close();
    return 0;
}
int verificare(int m[100][100], int n, int f[100], int v[100], char cuv[100])
{
    int i=0, j, ok = 1;
    if(cuv[j]-'0'<=9 && cuv[j]-'0'>=0)
        for(j = 0; j<strlen(cuv); j++)
        {
            if(m[i][cuv[j]-'0'] != -1 && cuv[j]-'0'<=9 && cuv[j]-'0'>=0)
            {
                v[j+1] = m[i][cuv[j]-'0'];
                i = m[i][cuv[j]-'0'];
            }
            else
            {
                ok = 0;
                break;
            }
        }
    else
        for(j = 0; j<strlen(cuv); j++)
        {
            if(m[i][cuv[j]-'a'] != -1 && cuv[j] >= 'a' && cuv[j] <= 'z')
            {
                v[j+1] = m[i][cuv[j]-'a'];
                i = m[i][cuv[j]-'a'];
            }
            else
            {
                ok = 0;
                break;
            }
        }

    i = 0;
    if(ok == 1)
        while(f[i] != -1)
        {
            if(f[i] == v[j])
                ok = 2;

            i++;
        }
    return ok;
}
int v[100];
int main()
{
    int n, m[100][100], f[100], i, a;
    char cuv[100];
    citire(m, n, f);
    start:
    cout<<"Try a word!"<<"\n";
    cin.get(cuv, 100);

    if(verificare(m, n, f, v, cuv) == 2)
    {
        cout<<"Your word was accepted!"<<"\n";
        cout<<"This is the path:";
        for(i = 0; i<strlen(cuv)+1; i++)
            cout<<"->q"<<v[i];
        cout<<"\n"<<"\n";
    }
    else
        cout<<"Your word was rejected :("<<"\n";

    cout<<"Do you want to try again?"<<"\n";
    cout<<"1 - Yes      0 - No"<<"\n";
    cin>>a;
    cin.get();
    if(a == 1)
        goto start;
    return 0;
}




//    for(i = 0; i<n; i++)
//    {
//        for(j = 0; j<3; j++)
//            cout<<m[i][j]<<" ";
//        cout<<endl;
//    }