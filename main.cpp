#include <iostream>
#include<conio.h>
#include<windows.h>
#include<ctime>

using namespace std;



int apasare,distanta,pozitieActuala[2],scor,scorMaxim,joc;
bool sfarsit;
char mat[50][50], verificare[50][50];



void meniu()
{
	system("color B0");
	cout << endl;
	cout << "        MENIU" << endl;
	cout << "   1. Joaca"<<endl;
	cout << "   2. Instructiuni"<<endl;
	cout << "   3. Scor maxim" << endl;
}

void afisareScorMaxim()
{
	int inapoi;
	cout << endl;
	cout << "     Scorul maxim este: " << scorMaxim << endl;
	cout << "1. Inapoi" << endl;
    cin >> inapoi;
	system("cls");
	if (inapoi == 1)
	{
		cout << endl;
		meniu();
	}

}

void instructiuni()
{
	int inapoi;
	cout << endl;
	cout << "       Instructiuni:"                               << endl;
	cout << "   Prin apasarea oricarei taste, pasarea va zbura." << endl;
	cout << "   Scopul jocului este sa conduci pasarea printre obstacole, fara a le atinge, pentru a acumula un punctaj cat mai mare." << endl;
	cout << "   Jocul se incheie cand pasarea atinge un obstacol."<<endl;
	cout << "1. Inapoi"<<endl;
	cin  >> inapoi;
	system("cls");
	if (inapoi == 1)
	{
		cout << endl;
		meniu();
	}
}

void ecran()
{
	int lungime, latime;
	for (latime = 0; latime < 30; latime++)
	{
		for (lungime = 0; lungime < 21; lungime++)
		{
			cout << mat[latime][lungime];
		}
		cout << endl;
	}
}

void obstacole(int distanta)
{
	int latime, lungime, liber=0;
	system("color B0");
		if (distanta%2==0)
		{
			liber = (rand() % 11) + 5;
			for (latime = 0; latime < 30; latime++)
			{
				mat[latime][20]        = 'x';
				verificare[latime][20] = 2;
			}

			mat[liber - 1][20]        = ' ';
			mat[liber][20]            = ' ';
			mat[liber + 1][20]        = ' ';
			verificare[liber - 1][20] = 0;
			verificare[liber][20]     = 0;
			verificare[liber + 1][20] = 0;
		}
		else
		{
			for (latime = 0; latime < 30; latime++)
			{
				for (lungime = 0; lungime < 21; lungime++)
				{
					mat[latime][lungime]            = ' ';
					verificare[latime - 1][lungime] = 2;
					verificare[latime][lungime]     = 0;
				}
			}
	}
}

void zbor()
{
	int lungime,latime;
	if (apasare > 0)
	{
		for(latime=0;latime<30;latime++)
			for (lungime = 0; lungime < 20; lungime++)
			{
				if (mat[latime][lungime] == '*'&&lungime > 0)
				{
					mat[latime-1][lungime + 1] = '*';
					pozitieActuala[0]          = latime - 1;
					pozitieActuala[1]          = lungime + 1;
					mat[latime][lungime]       = ' ';
					return;
				}

			}

	}
	else
	{
		for(latime=0;latime<30;latime++)
			for (lungime = 0; lungime < 21; lungime++)
			{
				if (mat[latime][lungime] == '*')
				{
					mat[latime+1][lungime+1] = '*';
					pozitieActuala[0]        = latime + 1;
					pozitieActuala[1]        = lungime + 1;
					mat[latime][lungime]     = ' ';
					return;
				}
			}
	}

}

bool sfarsitJoc(int pozitieActuala[2])
{
	int latime, lungime;
	if (pozitieActuala[0] == 1 || pozitieActuala[0] == 21)
		return true;
	for(latime=0;latime<30;latime++)
		for (lungime = 0; lungime < 21; lungime++)
		{
			if (verificare[pozitieActuala[0]][pozitieActuala[1]] == 2)
				return true;
		}
	return false;
}

void joaca()
{
	scor     = -1;
	distanta = 0;
	while (!sfarsit)
	{
		scor++;
		mat[10][2] = '*';
		obstacole(distanta);
		ecran();
		for (int i = 0; i < 18; i++)
		{
			apasare = 0;
			Sleep((DWORD) (0.4 * 1000));
			if (_kbhit())
			{
				apasare = _getch();
			}
			zbor();
			ecran();
			distanta++;
		}
		sfarsit = sfarsitJoc(pozitieActuala);
	}
	cout << endl;
	cout << "Scor final: " << scor << endl;
	if (scor > scorMaxim)
	{
		scorMaxim = scor;
	}
}

void resetare()
{
	int latime, lungime;
	for(latime=0;latime<30;latime++)
		for (lungime = 0; lungime < 21; lungime++)
		{
			mat[latime][lungime] = ' ';
		}
	pozitieActuala[0] = 10;
	pozitieActuala[1] = 2;
	sfarsit           = false;
}


int main()
{
	cout << "        FLAPPY BIRDS"<<endl;
	joc = 1;
	srand((unsigned int) time(NULL));
	while (joc==1)
	{
	start:
		meniu();
		char optiune;
		cin >> optiune;
		if (optiune != '1' && optiune != '2' && optiune != '3')
			cout << "Optiune invalida"<<endl;
		else
		while (optiune != '1')
		{
			if (optiune == '2')
			{
				instructiuni();
				cin >> optiune;
			}
			if (optiune == '3')
			{
				afisareScorMaxim();
				cin >> optiune;
			}

		}
		if (optiune == '1')
		{
			joaca();
		}
		resetare();
		cout << "Apasa litera m pentru a reveni la meniu" << endl;;
        char joacaDinNou;
		cin >> joacaDinNou;
		system("cls");
		if (joacaDinNou =='m')
		{
			goto start;
		}
		else
			joc = 0;
	}
	cin.get();
}