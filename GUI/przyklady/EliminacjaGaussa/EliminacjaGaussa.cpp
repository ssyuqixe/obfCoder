// Przyklady.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>


int main()
{
	int m = 0; 
	int n = 0;
	double** macierz;
	double* wyniki;
	bool isEqual = true;

	std::ifstream in("macierz.txt");
	if (in.is_open()) {
		bool firstLine = true;
		std::string item;
		int i = 0;
		int j = 0;

		in >> m >> n;

		macierz = new double* [m];
		for (int i = 0; i < n; i++)
		{
			macierz[i] = new double[n];
		}

		for (int i = 0; i < m; i++)
		{
			for (int j = 0; j < n; j++)
			{
				in >> macierz[i][j];
			}
		}
		wyniki = new double[m];

		for (int i = 0; i < m; i++)
		{
			in >> wyniki[i];
		}



		in.close();
	}
	else {
		std::cout << "Nie mozna otworzyc pliku" << std::endl;
		return 0;
	}

	
	for (int k = 0; k < m; k++) 
	{
		for (int l = k + 1; l < m; l++) 
		{
			if (std::abs(macierz[k][k]) < std::abs(macierz[l][k])) {
				for (int i = 0; i < n; i++) 
				{
					std::swap(macierz[k][i], macierz[l][i]);
				}
				std::swap(wyniki[k], wyniki[l]);

			}

		}

	}

	for (int i = 0; i < m - 1; i++)
	{
		for (int j = 0; j < n - 1; j++)
		{
			if (!((macierz[i][j] / macierz[i + 1][j]) == (wyniki[i] / wyniki[i + 1]))) 
			{                                                                                
				isEqual = false;
				break;

			}
		}
	}


	//Uzywanie eliminacji Gaussa Jordana
	double b = 0;
	if (!isEqual) 
	{
		for (int i = 0; i < m; i++)
		{
			for (int j = i + 1; j < m; j++)
			{
				b = macierz[j][i] / macierz[i][i];
				for (int k = 0; k < n; k++){
					macierz[j][k] = macierz[j][k] - b * macierz[i][k];
				}
				wyniki[j] -= b * wyniki[i];
			}
		}


		for (int i = 0; i < m - 1; i++)
		{
			for (int j = i + 1; j < m; j++)
			{
				macierz[j][i] = 0;
			}
		}


		//Podstawianie wsteczne

		for (int i = (m > n) ? n - 1 : m - 1; i >= 0; i--) //Zabezpieczenie kiedy jest wiecej wierszy niz zmiennych
		{
			for (int j = i + 1; j < n; j++)
			{
				if (j != i)
				{
					wyniki[i] = wyniki[i] - macierz[i][j] * wyniki[((m >= n) ? j : j - (m - m))];
				}

			}

			if (macierz[i][i] == 0)
			{
				return 1;
			}
			else
			{
				wyniki[i] = wyniki[i] / macierz[i][i];
			}

		}
	}

	std::cout << "Wynik: ";
	for (int i = 0; i < m; i++)
	{
		std::cout << wyniki[i] << " ";
	}
	std::cout << std::endl;


	for (int i = 0; i < n; i++)
	{
		delete[] macierz[i];
	}
	delete[] macierz;

	delete[] wyniki;


	return 0;
}


/*

	for (int i = 0; i < m; i++){
		for (int j = 0; j < n; j++){
			std::cout << macierz[i][j] << " ";
			}
		std::cout << std::endl;
	}

*/