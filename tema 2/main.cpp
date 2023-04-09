#include <iostream>
#include <fstream>
#include <cstring>

///Pasii de rezolvare
//1. Citesc afnl
//2. Adaug lambda
//3. Sterg lambda-urile si obtin AFN
//4. Transform AFN in AFD

using namespace std;
///Citire afn lambda
void citire(int afnl[100][10], int &init, int final[100], int &nr, int &cuv, int &finl)
{
    char aux[100], auxi[100], lit;
    int i, st, sti, auxf;
    ifstream  fin("C:\\Users\\Ciprian\\Documents\\GitHub\\lfa-lab\\tema 2\\ex2.txt");
    fin>>aux;
    init = aux[1] - '0' + 10;
    fin>>finl>>cuv;
    fin.get();

    for(int j=0; j<finl; j++)
    {
        fin>>aux;
        final[j] = 0;
        for(int k=1; k<strlen(aux); k++)
        {
            final[j] = final[j]*10 + aux[k] - '0';
        }
        final[j] = final[j] + 10;
    }

    for (i = 10; i<50; i++)
        for(int j = 0; j<=cuv; j++)
            afnl[i][j] = -1;

    nr = 0;
    while(fin>>aux>>lit>>auxi)
    {
        st = 0;
        for(int k=1; k<strlen(aux); k++)
        {
            st = st*10 + aux[k] - '0';
        }
        sti = 0;
        for(int k=1; k<strlen(auxi); k++)
        {
            sti = sti*10 + auxi[k] - '0';
        }

        if(lit >= '`')
        {
            if(afnl[st + 10][lit - '`'] != -1)
                afnl[st + 10][lit - '`'] = afnl[st + 10][lit - '`']*100 + sti + 10;
            else
                afnl[st + 10][lit - '`'] = sti + 10;
        }
        else
        {
            if(afnl[st + 10][lit - '/'] != -1)
                afnl[st + 10][lit - '/'] = afnl[st + 10][lit - '/']*100 + sti + 10;
            else
                afnl[st + 10][lit - '/'] = sti + 10;
        }

        if(st > nr)
            nr = st;
        if(sti > nr)
            nr = sti;
        if(afnl[st+10][0] != -1)
            auxf = afnl[st+10][0];
        else
            auxf = 0;
        for(int a=0; a<finl; a++)
            while(auxf != 0)
            {
                if(auxf%100 == final[a])
                {
                    finl++;
                    final[finl-1] = st+10;
                }
                auxf = auxf/100;
            }

    }
    fin.close();
}
///Adaug lambda
void addlambda(int afnl[100][10], int nr)
{
    int aux, auxi, auxj, k = 0;
    for(int i = 10; i<=nr+10; i++)
        if(afnl[i][0] != -1)
        {
            aux = afnl[i][0];
            while(aux != 0)
            {
                auxi = afnl[i][0];
                auxj = afnl[aux%100][0];
                if(afnl[aux%100][0] != -1)
                    while(auxj != 0)
                    {

                        while(auxi != 0)
                        {
                            if(auxi%100 != auxj%100)
                            {
                                k++;
                            }
                            auxi = auxi/100;
                        }
                        if(k == 2)
                        {
                            afnl[i][0] = afnl[i][0] * 100 + auxj%100;
                        }
                        auxi = afnl[i][0];
                        k = 0;
                        auxj = auxj/100;
                    }
                aux = aux/100;
            }
        }
}
///Sterg lambda urile si construiesc muchii obtinand un AFN
void removelambda(int afnl[100][10], int nr, int cuv)
{
    for(int i = 10; i<=nr + 10; i++)
    {
        if(afnl[i][0] != -1)
            while(afnl[i][0] != 0)
            {
                for(int j = 1; j<=cuv; j++)
                {
                    if(afnl[afnl[i][0]%100][j] != -1)
                    {
                        if(afnl[i][j] == -1)
                            afnl[i][j] = afnl[afnl[i][0]%100][j];
                        else
                            if(afnl[i][j]%100 != afnl[afnl[i][0]%100][j])
                                afnl[i][j] = afnl[i][j]*100 + afnl[afnl[i][0]%100][j];
                    }

                }
                afnl[i][0] = afnl[i][0]/100;
            }
        afnl[i][0] = -1;
    }

}
///Transform AFN in AFD
void dfa(int &nr, int afd[100][10], int cuv, int &n)
{

    nr++;
    n = 0;
    for(int i = 0; i<=30; i++)
        for(int j = 0; j<=cuv+1; j++)
            afd[i][j] = -1;
    for (int i = 0; i<=nr; i++)
    {
        afd[i][0] = i;
        afd[i][1] = i-1;
    }
}//initializare AFD
void completdfa(int afnl[100][10], int &nr, int afd[100][10], int cuv, int v[100], int n, int &ok)
{
    int k;
    for(int i = n; i<=nr; i++)
    {
        while(v[i] != 0)
        {
            for(int j = 1; j<=cuv+1; j++)
            {
                k = 0;
                if(afd[i][j+1] == -1 && afnl[v[i]%100][j] != -1)
                {
                    afd[i][j+1] = afnl[v[i]%100][j] - 9;
                    k = 1;
                }

                if(afd[i][j+1] != -1 && afnl[v[i]%100][j] != -1 && k != 1)
                {
                    if(afd[i][j + 1] != afnl[v[i]%100][j]-9)
                    {
                        afd[i][j + 1] = (afd[i][j + 1] + 10) * 100 + afnl[v[i]%100][j];
                        ok = 0;
                    }
                }
            }
            v[i] = v[i]/100;
        }
    }

}//Verificare AFD
void dubludfa(int afnl[100][10], int &nr, int afd[100][10], int cuv, int v[100], int &n) {
    int auxi, auxj, aux = nr + 1, k = nr + 1, ok1, ok2, valid, auxn;
    auxn = nr + 1;
    for (int i = n; i <= nr; i++)
        for (int j = 1; j <= cuv; j++)
            if (afnl[i + 10][j] > 9)
            {
                if (afnl[i + 10][j] < 99)
                    afd[i + 1][j + 1] = afnl[i + 10][j] - 9;
                else
                {
                    valid = 1;
                    while (v[k] != 0 && valid == 1)
                    {
                        ok1 = 0;
                        auxi = v[k];
                        auxj = afnl[i + 10][j];
                        while (auxj != 0) {
                            while (auxi != 0) {
                                ok1++;
                                if (auxi % 100 == auxj % 100)
                                {
                                    ok2++;
                                }
                                auxi = auxi / 100;
                            }
                            auxi = v[k];
                            auxj = auxj / 100;
                        }
                        if (ok2 == ok1 / 2)
                        {
                            valid = 0;
                        }
                        else
                        {
                            k++;
                        }

                        ok1 = 0;
                        ok2 = 0;
                    }
                    if (valid == 1) {
                        nr++;
                        afd[nr][0] = nr;
                        afd[nr][1] = afnl[i + 10][j];
                        v[k] = afnl[i + 10][j];
                    }
                    else
                        valid = 1;
                    afd[i+1][j+1] = k;
                }
                k = aux;
            }
                n = auxn;
}//Adaugare noduri

int main()
{
 int afnl[100][10], init, final[100], nr, afd[100][10], cuv, v[100], n, ok = 0, finl;

 citire(afnl, init, final, nr, cuv, finl);
 addlambda(afnl, nr);
 removelambda(afnl, nr, cuv);
 dfa(nr, afd, cuv, n);
 if(nr != n)
     while(ok == 0)
     {
         ok = 1;
         dubludfa(afnl, nr, afd, cuv, v, n);
         completdfa(afnl, nr, afd, cuv, v, n, ok);
     }

    for(int i = 0; i <= nr; i++)
    {
        for(int j = 0; j<=cuv+1; j++)
        {
            if(j == 0)
                cout<<"q";
            cout<<afd[i][j]<<" ";
        }

        cout<<endl;
    }
    cout<<"starea initiala :"<<"q"<<init-9<<endl<<"stari finale : ";
    for(int i = 0; i<finl; i++)
        cout<<"q"<<final[i]-9<<", ";
    cout<<endl;
    cout<<"unde prima coloana reprezinta nodurile, a 2-a starea/starile curente si restul alfabetul"<<endl;
    for(int i = 10; i <= nr+10; i++)
    {
        for(int j = 0; j<=cuv; j++)
        {
            cout<<afnl[i][j]<<" ";
        }

        cout<<endl;
    }
}