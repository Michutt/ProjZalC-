#include <iostream>
#include <cstdio>
#include <string>
#include <cstdlib>
#include <ctime>
#include <queue>

void wyswietlanie(int x, int y, char **tab) {
	std::string indeks = "123456789ABCDEFGHIJKLMNOPRSTUWZ";
	std::cout << "  " << indeks.substr(0, y) << std::endl << "  ";

	for (int i = 0; i < y; i++)
		std::cout << "-";

	std::cout << std::endl;
	for (int i = 0; i < x; i++, std::cout << std::endl) {
		std::cout << indeks[i] << "|";
		for (int j = 0; j < y; j++)
			std::cout << tab[i][j];
		std::cout << "|";
	}

	std::cout << "  ";
	for (int i = 0; i < y; i++)
		std::cout << "-";
}

void wypelnienie(int x, int y, char **tab, int zakres) {
	
	for (int i = 0; i < x; i++) {
		for (int j = 0; j < y; j++) {
			tab[i][j] = ' ';
			int zapelnienie = std::rand() % 4;
			if (zapelnienie == 0) {
				int wylosowana_liczba = std::rand() % zakres;
				switch (wylosowana_liczba)
				{
				case 0:
					tab[i][j] = 'a';
					break;

				case 1:
					tab[i][j] = 'b';
					break;

				case 2:
					tab[i][j] = 'c';
					break;

				case 3:
					tab[i][j] = 'd';
					break;

				case 4:
					tab[i][j] = 'e';
					break;
				}
			}
		}
	}
}

void dodanie_literki(int x, int y, int zakres, char** tab) {

	bool wylosowano = false;

	do {
		int k = std::rand() % x;
		int j = std::rand() % y;

		if (tab[k][j] == ' ') {
			int wylosowana_liczba = std::rand() % zakres;
			switch (wylosowana_liczba)
			{
			case 0:
				tab[k][j] = 'a';
				break;

			case 1:
				tab[k][j] = 'b';
				break;

			case 2:
				tab[k][j] = 'c';
				break;

			case 3:
				tab[k][j] = 'd';
				break;

			case 4:
				tab[k][j] = 'e';
				break;
			}
			wylosowano = true;
		}
	} while (wylosowano == false);
}

bool sprawdzanie_poprawnosci_ruchu(int x, int y, int wybor[4], char** tab)
{
	std::queue <int> kolejka;

	int** tab_pom = new int* [x + 2];
	for (int i = 0; i < x + 2; i++) {
		tab_pom[i] = new int[y + 2];
		for (int j = 0; j < y + 2; j++) {
			if (i == 0 || i == x + 1)
				tab_pom[i][j] = 1;
			else if (j == 0 || j == y + 1)
				tab_pom[i][j] = 1;
		}
	}

	for (int i = 0; i < x; i++)
		for (int j = 0; j < y; j++) {
			if (tab[i][j] == ' ')
				tab_pom[i + 1][j + 1] = 0;
			else
				tab_pom[i + 1][j + 1] = 1;
		}
	tab_pom[wybor[2] + 1][wybor[3] + 1] = 2;

	int i = wybor[0] + 1;
	int j = wybor[1] + 1;

	kolejka.push(i);
	kolejka.push(j);

	while (!kolejka.empty()) {
		i = kolejka.front(); kolejka.pop();
		j = kolejka.front(); kolejka.pop();

		if (tab_pom[i][j] == 2 || tab_pom[i+1][j] == 2 || tab_pom[i-1][j] == 2 || tab_pom[i][j+1] == 2 || tab_pom[i][j-1] == 2)
			return true;

		tab_pom[i][j] = 1;

		if (tab_pom[i + 1][j] == 0) {
			kolejka.push(i + 1);
			kolejka.push(j);
		}

		if (tab_pom[i][j + 1] == 0) {
			kolejka.push(i);
			kolejka.push(j + 1);
		}

		if (tab_pom[i - 1][j] == 0) {
			kolejka.push(i - 1);
			kolejka.push(j);
		}

		if (tab_pom[i][j - 1] == 0) {
			kolejka.push(i);
			kolejka.push(j - 1);
		}
	}
	return false;
}
	
bool zbicie(int f, int x, int y, char** tab) {
	for (int i = 0; i < x; i++) {
		for (int j = 0; j < y; j++) {
			if (tab[i][j] != ' ') {
				switch (f) {
				case 5:
					if (i <= x - 4 && tab[i + 4][j] == tab[i][j] && tab[i + 3][j] == tab[i][j] && tab[i + 2][j] == tab[i][j] && tab[i + 1][j] == tab[i][j]) {
						tab[i + 4][j] = ' ';
						tab[i + 3][j] = ' ';
						tab[i + 2][j] = ' ';
						tab[i + 1][j] = ' ';
						tab[i][j] = ' ';
						return true;
					}
					if (i >= 4 && tab[i - 4][j] == tab[i][j] && tab[i - 3][j] == tab[i][j] && tab[i - 2][j] == tab[i][j] && tab[i - 1][j] == tab[i][j]) {
						tab[i - 4][j] = ' ';
						tab[i - 3][j] = ' ';
						tab[i - 2][j] = ' ';
						tab[i - 1][j] = ' ';
						tab[i][j] = ' ';
						return true;
					}
					if (j <= y - 4 && tab[i][j + 4] == tab[i][j] && tab[i][j + 3] == tab[i][j] && tab[i][j + 2] == tab[i][j] && tab[i][j + 1] == tab[i][j]) {
						tab[i][j + 4] = ' ';
						tab[i][j + 3] = ' ';
						tab[i][j + 2] = ' ';
						tab[i][j + 1] = ' ';
						tab[i][j] = ' ';
						return true;
					}
					if (j >= 4 && tab[i][j - 4] == tab[i][j] && tab[i][j - 3] == tab[i][j] && tab[i][j - 2] == tab[i][j] && tab[i][j - 1] == tab[i][j]) {
						tab[i][j - 4] = ' ';
						tab[i][j - 3] = ' ';
						tab[i][j - 2] = ' ';
						tab[i][j - 1] = ' ';
						tab[i][j] = ' ';
						return true;
					}
					break;
				case 4:
					if (i <= x - 3 && tab[i + 3][j] == tab[i][j] && tab[i + 2][j] == tab[i][j] && tab[i + 1][j] == tab[i][j]) {
						tab[i + 3][j] = ' ';
						tab[i + 2][j] = ' ';
						tab[i + 1][j] = ' ';
						tab[i][j] = ' ';
						return true;
					}
					if (i >= 3 && tab[i - 3][j] == tab[i][j] && tab[i - 2][j] == tab[i][j] && tab[i - 1][j] == tab[i][j]) {
						tab[i - 3][j] = ' ';
						tab[i - 2][j] = ' ';
						tab[i - 1][j] = ' ';
						tab[i][j] = ' ';
						return true;
					}
					if (j <= y - 3 && tab[i][j + 3] == tab[i][j] && tab[i][j + 2] == tab[i][j] && tab[i][j + 1] == tab[i][j]) {
						tab[i][j + 3] = ' ';
						tab[i][j + 2] = ' ';
						tab[i][j + 1] = ' ';
						tab[i][j] = ' ';
						return true;
					}
					if (j >= 3 && tab[i][j - 3] == tab[i][j] && tab[i][j - 2] == tab[i][j] && tab[i][j - 1] == tab[i][j]) {
						tab[i][j - 3] = ' ';
						tab[i][j - 2] = ' ';
						tab[i][j - 1] = ' ';
						tab[i][j] = ' ';
						return true;
					}
					break;
				case 3:
					if (i < x - 2 && tab[i + 2][j] == tab[i][j] && tab[i + 1][j] == tab[i][j]) {
						tab[i + 2][j] = ' ';
						tab[i + 1][j] = ' ';
						tab[i][j] = ' ';
						return true;
					}
					if (i > 2 && tab[i - 2][j] == tab[i][j] && tab[i - 1][j] == tab[i][j]) {
						tab[i - 2][j] = ' ';
						tab[i - 1][j] = ' ';
						tab[i][j] = ' ';
						return true;
					}
					if (j < y - 2 && tab[i][j + 2] == tab[i][j] && tab[i][j + 1] == tab[i][j]) {
						tab[i][j + 2] = ' ';
						tab[i][j + 1] = ' ';
						tab[i][j] = ' ';
						return true;
					}
					if (j > 2 && tab[i][j - 2] == tab[i][j] && tab[i][j - 1] == tab[i][j]) {
						tab[i][j - 2] = ' ';
						tab[i][j - 1] = ' ';
						tab[i][j] = ' ';
						return true;
					}
					break;
				case 2:
					if (i <= x - 1 && tab[i + 1][j] == tab[i][j]) {
						tab[i + 1][j] = ' ';
						tab[i][j] = ' ';
						return true;
					}
					if (i >= 1 && tab[i - 1][j] == tab[i][j]) {
						tab[i - 1][j] = ' ';
						tab[i][j] = ' ';
						return true;
					}
					if (j <= y - 1 && tab[i][j + 1] == tab[i][j]) {
						tab[i][j + 1] = ' ';
						tab[i][j] = ' ';
						return true;
					}
					if (j >= 1 && tab[i][j - 1] == tab[i][j]) {
						tab[i][j - 1] = ' ';
						tab[i][j] = ' ';
						return true;
					}
					break;
				}
			}
		}
	}
	return false;
}

void ruch(int x, int y, int zakres, int zakres_zbic, char** tab) {
	std::string wybor1, wybor2;
	std::string zm = "123456789ABCDEFGHIJKLMNOPRSTUWZ";
	int wybor[4], pozycja[4];

	do {
		std::cout << "Ktora literka chcesz wykonac ruch?:  ";
		std::cin >> wybor1;

		for (int i = 0; i < zm.length(); i++) {
			if (wybor1[0] == zm[i])
				wybor[0] = i;
			if (wybor1[1] == zm[i])
				wybor[1] = i;
		}

	} while (tab[wybor[0]][wybor[1]] == ' ');
	
	do {
		std::cout << "Dokad chcesz sie ruszyc?:  ";
		std::cin >> wybor2;

		for (int i = 0; i < zm.length(); i++) {
			if (wybor2[0] == zm[i])
				wybor[2] = i;
			if (wybor2[1] == zm[i])
				wybor[3] = i;
		}

	} while (tab[wybor[2]][wybor[3]] != ' ');
	
	if (sprawdzanie_poprawnosci_ruchu(x, y, wybor, tab)) {
		tab[wybor[2]][wybor[3]] = tab[wybor[0]][wybor[1]];
		tab[wybor[0]][wybor[1]] = ' ';

		bool zmienna = zbicie(zakres_zbic, x, y, tab);
		if (zmienna == false)
			dodanie_literki(x, y, zakres, tab);
	}
	else {
		std::cout << "Taki ruch jest niewykonalny, sprobuj ponownie!" << std::endl;
		getchar();
	}
}

bool koniec(int x, int y, char** tab) {
	for (int i = 0; i < x; i++) {
		for (int j = 0; j < y; j++) {
			if (tab[i][j] != ' ')
				return true;
		}
	}
	return false;
}

int main()
{
	srand(time(NULL));
	int l_wierszy, l_kolumn, l_liter, l_rzad;
	int wynik = 0;

	do {
		std::cout << "Liczba wierszy:  ";
		std::cin >> l_wierszy;
	} while (l_wierszy < 1 && l_wierszy > 26);

	do {
		std::cout << "Liczba kolumn:  ";
		std::cin >> l_kolumn;
	} while (l_kolumn < 1 && l_kolumn > 26);

	do {
		std::cout << "Ile ma byc literek?(max 5):  ";
		std::cin >> l_liter;
	} while (l_liter < 0 && l_liter > 6);

	do {
		std::cout << "Wybierz poziom trudnosci(liczbe literek pod rzad, 2 - 5):  ";
		std::cin >> l_rzad;
	} while (l_rzad < 1 && l_rzad > 6);

	system("cls");
	char** tab = new char* [l_wierszy];
	for (int i = 0; i < l_wierszy; i++) 
		tab[i] = new char[l_kolumn];

	wypelnienie(l_wierszy, l_kolumn, tab, l_liter);

	do{
		wyswietlanie(l_wierszy, l_kolumn, tab);
		ruch(l_wierszy, l_kolumn, l_liter, l_rzad, tab);
		wynik++;
		system("cls");
	} while (koniec(l_wierszy, l_kolumn, tab));

	std::cout << "brawo, ukonczyles gre!!! Twoj wynik to: "<< wynik << " punktow!" << std::endl;
	system("pause");
	return 0;
}	

