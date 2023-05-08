#include <iostream>
#include <cstring>
#include <fstream>
using namespace std;
class Exp{
private:
    char start, lit, stop;
public:
    Exp(){
        start = ' ';
        lit = ' ';
        stop = ' ';
    }
    Exp(const char start_, const char lit_, const char stop_){
        start = start_;
        lit = lit_;
        stop = stop_;
    }

    void setStart(const char start_){
        start = start_;
    }
    void setLit(const char lit_){
        lit = lit_;
    }
    void setStop(const char stop_){
        stop = stop_;
    }

    const char getStart() {
        return start;
    }
    const char getLit(){
        return lit;
    }
    const char getStop(){
        return stop;
    }
};
ifstream fin("C:\\Users\\Ciprian\\Documents\\GitHub\\lfa-lab\\tema 3\\date.txt");
bool ok = false;
void citire(Exp *&e, int &nr){
    string s, aux;
    int i = 0;
    fin>>s;
    while(s != "Stop"){
        e[i].setStart(s[0]);
        aux = s;
        fin >> s >> s;
        e[i].setLit(s[0]);
        e[i].setStop(s[1]);
        fin >> s;
        while(s == "|"){
            i++;
            e[i].setStart(aux[0]);
            fin>>s;
            e[i].setLit(s[0]);
            e[i].setStop(s[1]);
            fin>>s;
        }
        i++;
    }
    nr = i-1;
    fin.close();
}
void verific(char cuv[100], char curr, int poz, int nr, Exp *&e) {
    if (poz == strlen(cuv) - 1) {
        for (int i = 0; i <= nr; i++) {
            if (e[i].getLit() == cuv[poz] && e[i].getStop() == NULL) {
                ok = true;
                return;
            }
        }
    }
    if (poz == strlen(cuv))
        for (int i = 0; i <= nr; i++)
            if (e[i].getLit() == '~' && e[i].getStart() == curr) {
                ok = true; return;
            }
    for (int i = 0; i <= nr; i++) {
        if (e[i].getLit() == cuv[poz] && e[i].getStop() != NULL && e[i].getStart() == curr)
            verific(cuv, e[i].getStop(), poz + 1, nr, e);
    }
}
int main(){
    Exp *e = new Exp[10];
    int nr, choose;
    char curr, cuv[100];
    citire(e, nr);
    cout<<"0 - Exit \n1 - Try a word! \n";
    cin>>choose;
    if(choose == 0)
        return 0;
    start:
    ok = false;
    cout<<"word : ";
    cin>>cuv;
    verific(cuv, 'S', 0, nr, e);
    if(ok == 1)
        cout<<"Your word was accepted\n";
    else
        cout<<"Your word was rejected\n";
    cout<<"Do you want to try again?\n0 - No\n1 - Yes\n";
    cin>>choose;
    if(choose == 0)
        return 0;
    goto start;
}