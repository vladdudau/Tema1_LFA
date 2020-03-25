#include <bits/stdc++.h>
using namespace std;

ifstream fin("LNFA.in");
ofstream fout("LNFA.out");

vector <int> CareAuLambda[100];
unsigned int nrStari, nrAlfabet, stareInitiala;
unsigned int nrStariFinale, stariFinale[100], nrMiscari, nrCuvinte;
char alfabet[30];
unsigned int i, j;

///Am implementat o clasa pentru a gestiona mai usor automatul
///Clasa cuprinde o matrice[i][j] i reprezentand starea i si j reprezentand litera din alfabet
///Daca din starea i pot ajunge in alta stare atunci matrice[i][j] va avea lista de stari in care putem ajunge

class LNFA
{
private:
	vector <int> stariInCarePotAjunge;
public:
	void pushStare(int x);
	unsigned int nrStariInCarePotAjunge();
	int element(int pozitie);
} Miscari[100][30];

///Adauga o noua stare in care ne putem deplasa din starea i

void LNFA::pushStare(int nou)
{
	int ok = 1;

	for (unsigned int i = 0; i < stariInCarePotAjunge.size(); i++)
		if (nou == stariInCarePotAjunge[i])
			ok = 0;

	if (ok == 1)
		stariInCarePotAjunge.push_back(nou);
}

///Returneaza numarul de stari in care pot ajunge din starea i

unsigned int LNFA::nrStariInCarePotAjunge()
{
	return stariInCarePotAjunge.size();
}

///Returneaza elementul din lista de pe pozitia ceruta

int LNFA::element(int pozitie)
{
	return stariInCarePotAjunge[pozitie];
}

///Verifica daca este stare finala

bool stareFinala(unsigned int x)
{
	for (unsigned int i = 1; i <= nrStariFinale; i++)
		if (x == stariFinale[i])
			return 1;
	return 0;
}

///Verifica recursiv,un fel de backtracking deoarece cauta toate combinatiile, daca inputul nostru poate fi acceptat de LNFA

bool verificareCuvant(int stare, char cuvant[])
{
	unsigned int i;

	if (strlen(cuvant) == 1)
	{
		for (i = 0; i < Miscari[stare][cuvant[0] - 'a'].nrStariInCarePotAjunge(); i++)
			if (stareFinala(Miscari[stare][cuvant[0] - 'a'].element(i)))
				return 1;
		return 0;
	}
	else
	{
		for (i = 0; i < Miscari[stare][cuvant[0] - 'a'].nrStariInCarePotAjunge(); i++)
			if (verificareCuvant(Miscari[stare][cuvant[0] - 'a'].element(i), cuvant + 1))
				return 1;
		return 0;
	}
}

int main()
{
	fin >> nrStari;

    ///Adaug in CareAuLambda toate starile de la 0 la nrStari-1

	for (i = 0; i < nrStari; i++)
	{
		CareAuLambda[i].push_back(i);
	}

	fin >> nrAlfabet;
	for (i = 1; i <= nrAlfabet; i++)
		fin >> alfabet[i];

	fin >> stareInitiala;
	fin >> nrStariFinale;

	for (i = 1; i <= nrStariFinale; i++)
		fin >> stariFinale[i];

	fin >> nrMiscari;

	for (i = 1; i <= nrMiscari; i++)
	{
		int st1, st2;
		char caracter;
		fin >> st1 >> caracter >> st2;

        ///Daca variabila caracter este lambda, atunci adaug in CareAuLambda ca pot ajunge din starea st1 in st2
		if (caracter == '$')
		{
			CareAuLambda[st1].push_back(st2);
		}
		///Daca variabila caracter nu este lambda, atunci adaug in Miscari[st1][caracter-'a'] starea in care ma pot duce cu litera caracter
		else
		{
			Miscari[st1][caracter - 'a'].pushStare(st2);
		}
	}

	unsigned int stare1, stare2, litera, lambda;

	for (stare1 = 0; stare1 < nrStari; stare1++)
		for (litera = 1; litera <= nrAlfabet; litera++)
			for (stare2 = 0; stare2 < Miscari[stare1][alfabet[litera] - 'a'].nrStariInCarePotAjunge(); stare2++)
			{
				int element = Miscari[stare1][alfabet[litera] - 'a'].element(stare2);

				for (lambda = 1; lambda < CareAuLambda[element].size(); lambda++)
                    ///pornesc de la 1 pt ca pe pozitia 0 am starile de la 0 la nrStari-1
                ///Caut orice element din Miscari[i][j]{el1,el2,....} daca din el1...ma pot deplasa cu lambda intr-o stare care nu este deja in matrice
					Miscari[stare1][alfabet[litera] - 'a'].pushStare(CareAuLambda[element][lambda]);
			}
	fin >> nrCuvinte;
	for (i = 1; i <= nrCuvinte; i++)
	{
		char cuvant[50];
		fin >> cuvant;
		fout<<cuvant<<"\n";
		///Verific daca nu cumva din starea initiala ma pot duce cu lambda in alta stare, asadar
		///verific cuvantul ori din starea intiala, ori din starea in care pot ajunge cu lambda
		for (j = 0; j < CareAuLambda[stareInitiala].size(); j++)
			if (verificareCuvant(CareAuLambda[stareInitiala][j], cuvant))
				fout << "DA" << "\n";
			else
				fout << "NU" << "\n";
	}
	return 0;
}
