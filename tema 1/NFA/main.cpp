#include <iostream>
#include <fstream>
#include <iostream>
#include <cstring>
using namespace std;
int self[100];
void citire(int m[100][100], int f[100], int self[100])
{
    ifstream fin("D:\\clionpr\\nfa\\nr.txt");
    int j, i, n;
    char k[100], l[100];
    fin>>n;
    for(i = 0; i<100; i++)
        for(j = 0; j<100; j++)
        {
            m[i][j] = -1;
            f[i] = -1;
        }

    for(i = 0; i<n; i++)
    {
        fin>>k>>j>>l;

        if(m[k[1]-'0'][j] != -1)
            if(m[k[1]-'0'][j] == 0)
            {
                m[k[1]-'0'][j] = (l[1]-'0')*10 + m[k[1]-'0'][j];
            }
            else
                m[k[1]-'0'][j] = l[1]-'0' + (m[k[1]-'0'][j])*10;
        else
            m[k[1]-'0'][j] = l[1]-'0';

        if(m[k[1]-'0'][j] == k[1]-'0')
            self[k[1]-'0'] = 1;
    }

    i = 0;
    while(fin>>k)
    {
        f[i] = k[1] - '0';
        i++;
    }
    fin.close();
}
int ok, aux, count1, count2;
bool verificare(int m[100][100], int f[100], char cuv[100], int j, int poz, int v1[100], int v2[100])
{
    int i;
    if(j<strlen(cuv))
    {
        if(m[poz][cuv[j]-'0'] != -1 && cuv[j]-'0'<=9 && cuv[j]-'0'>=0 && m[poz][cuv[j]-'0'] <= 9)
        {

            verificare(m, f, cuv, j+1, m[poz][cuv[j]-'0'], v1, v2);
            if(v1[j] == 0)
            {
                v1[j] = poz;
                count1++;

            }
            else
            {
                v2[j] = poz;
                count2++;
            }

        }

        else
            if(cuv[j]-'0'<=9 && cuv[j]-'0'>=0 && m[poz][cuv[j]-'0'] >= 10)
            {

                verificare(m, f, cuv, j+1, (m[poz][cuv[j]-'0'])%10, v1, v2);
                verificare(m, f, cuv, j+1, (m[poz][cuv[j]-'0'])/10, v1, v2);
                    v1[j] = poz;
                    v2[j] = poz;
                    count1++;
                    count2++;

            }
    }

    if(j == strlen(cuv))
    {
        if(m[poz][cuv[j]-'0'] < 10)
        {
            i = 0;
            while(f[i] != -1)
            {
                if(f[i] == poz)
                {
                    if(v2[j-1] != poz)
                            v2[j] = poz;
                        else
                            count2 = 0;

                    if(v1[j-1] != poz)
                    {
                        v1[j] = poz;
                    }

                    else
                        count1 = 0;

                    ok = 1;
                }

                i++;
            }
        }
        else {
            aux = m[poz][cuv[j] - '0'];
            i = 0;
            while (f[i] != -1) {
                if (f[i] == aux % 10)
                {
                    ok = 1;
                    if(v2[j-1] != poz)
                        v2[j] = poz;
                    else
                        count2 = 0;

                    if(v1[j-1] != poz)
                    {
                        v1[j] = poz;
                    }

                    else
                        count1 = 0;
                }

                i++;
            aux = aux / 10;
            }
        }
    }
    return ok;
}
int verificare2v(int v1[100], int v2[100], char cuv[100])
{

    if(count1 != 0 && count1 >= count2)
    {
        ok = 0;
        for(int i = 1; i<strlen(cuv)-1; i++)
            if(v1[i] == v1[i+1] && self[v1[i]] == 0 && self[v1[i+1]] == 0)
            {
                cout<<v1[i]<<" "<<v1[i+1];
                ok = 1;
                break;
            }
        if(ok == 0)
        {
            for(int i = 0; i<=strlen(cuv); i++)
                cout<<" -> "<<v1[i];
            ok = 2;
        }
    }


    if(count2 != 0 && count2 >= count1)
    {
        if(ok != 2)
        {
            ok = 1;
            if(v2[strlen(cuv)+1] == v1[strlen(cuv)+1])
            {
                ok = 0;
                for(int i = 1; i<strlen(cuv)-1; i++)
                {
                    if(v2[i] == v2[i+1] && self[v2[i]] == 0 && self[v2[i+1]] == 0)
                    {
                        ok = 1;
                        break;
                    }
                }

            }
            if(ok == 0)
                for(int i = 0; i<=strlen(cuv); i++)
                    cout<<" -> "<<v2[i];
    }

    }
}
int main() {
    int m[100][100], f[100], v1[100], v2[100], ok=0;
    char cuv[100];

    citire(m, f, self);
    cin>>cuv;
    if(verificare(m, f, cuv, 0, 0, v1, v2) == 1)
    {
        cout<<"Your word was accepted!"<<"\n";
        cout<<"This is the path : ";
    }
    else
        cout<<"Your word was rejected :("<<"\n";
    if(verificare(m, f, cuv, 0, 0, v1, v2) == 1)
        verificare2v(v1, v2, cuv);

    return 0;
}
