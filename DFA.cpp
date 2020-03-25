#include <bits/stdc++.h>

using namespace std;
ifstream fin("DFA.in");
ofstream fout("DFA.out");
int nrStari,nrAlfabet,stareInitiala,nrStariFinale,stariFinale[100],nrMiscari,nrCuvinte;
int Miscari[100][30];
char alfabet[30];
void Init()
{
       for(int i=0;i<100;i++)
        for(int j=0;j<30;j++)
            Miscari[i][j]=-1;
}
void Afis()
{
    for(int i=0;i<nrStari;i++)
    {
      for(int j=1;j<=nrAlfabet;j++)
            cout<<i<<" "<<alfabet[j]<<" "<<Miscari[i][alfabet[j]-'a']<<"\n";
    }
}
bool Finala(int x)
{
    int ok=0;
    for(int i=1;i<=nrStariFinale;i++)
        if(stariFinale[i]==x)
            return 1;
    return 0;
}
int main()
{
    Init();
    fin>>nrStari;
    fin>>nrAlfabet;
    for(int i=1;i<=nrAlfabet;i++)
        fin>>alfabet[i];
    fin>>stareInitiala;
    fin>>nrStariFinale;
    for(int i=1;i<=nrStariFinale;i++)
        fin>>stariFinale[i];
    fin>>nrMiscari;
    for(int i=1;i<=nrMiscari;i++)
    {
        int st1,st2;
        char caracter;
        fin>>st1>>caracter>>st2;
        Miscari[st1][caracter-'a']=st2;
    }
    Afis();
    fin>>nrCuvinte;
    for(int i=1;i<=nrCuvinte;i++)
    {
        char cuvant[50];
        fin>>cuvant;
        fout<<cuvant<<"\n";
        int ok=1;
        int j=Miscari[0][cuvant[0]-'a'];
        int poz=1;
        while(ok==1 && cuvant[poz])
        {
            if(j==-1)
                ok=0;
            else
            {
                j=Miscari[j][cuvant[poz]-'a'];
                poz++;
            }
        }
        if(Finala(j))
            fout<<"DA";
        else
            fout<<"NU";
        fout<<"\n";
    }
    return 0;
}
