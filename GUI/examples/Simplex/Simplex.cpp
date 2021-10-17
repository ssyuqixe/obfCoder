#include <iostream>
#include <fstream>
#include <string>
#include <vector> 
#include <cmath>  
#include <algorithm> 

//Test comment


bool checkWW(double tab[], int size) {
	for (int i = 0; i < size; i++)
	{
		if (tab[i] > 0) {
			return true;
		}
	}
	return false;
}



int findMaxElementIndex(double tab[], int size) {
	int temp = tab[0];
	int index = 0;
	for (int i = 0; i < size; i++)
	{
		if (temp < tab[i]) {
			temp = tab[i];
			index = i;
		}
	}
	return index;
}

int findMinElementIndex(double tab[], int size) {
	int temp = tab[0];
	int index = 0;
	for (int i = 0; i < size; i++)
	{
		if (temp > tab[i] && tab[i] > 0) {
			temp = tab[i];
			index = i;
		}
	}

	return index;
}

int main(){
	int m = 0;
	int n = 0;
	double** A = nullptr;
	double* B = nullptr;

	double* Cj = nullptr;
	double* Cb = nullptr;

	double* ww = nullptr;;

	std::ifstream inFile("simplex.txt");
	if (inFile.is_open()) {
		//Pobranie wymiarow macierzy
		inFile >> m >> n;

		//Stworzenie tablicy A
		A = new double* [m];
		for (int i = 0; i < m; i++)
		{
			A[i] = new double[n];
		}

		//Przepisanie zmiennych
		for (int i = 0; i < m; i++)
		{
			for (int j = 0; j < n; j++)
			{
				inFile >> A[i][j];
			}
		}

		B = new double[m];
		for (int i = 0; i < m; i++)
		{
			inFile >> B[i];
		}

		Cj = new double[n];
		for (int i = 0; i < n; i++)
		{
			inFile >> Cj[i];
		}

		Cb = new double[m];
		for (int i = 0; i < m; i++)
		{
			inFile >> Cb[i];
		}

		ww = new double[n];
		for (int i = 0; i < n; i++)
		{
			inFile >> ww[i];
		}


		inFile.close();
	}
	else {
		std::cout << "Nie mozna otworzyc pliku" << std::endl;
		return 0;
	}


	for (int i = 0; i < n; i++) 
	{
		ww[i] = Cj[i]; // Cb' * A(:,i) otrzymamy 0
	}

	double F = 0;

	bool zakoncz = false;

	while (checkWW(ww, n)) {
		int KK = findMaxElementIndex(ww, n);

		double* iloraz = new double[m];

		for (int i = 0; i < m; i++) 
		{
			iloraz[i] = B[i] / A[i][KK];
		}

		int WK = findMinElementIndex(iloraz, m);
		delete[] iloraz;

		Cb[WK] = Cj[KK];

		double ER = A[WK][KK];

		for (int i = 0; i < n; i++) 
		{
			A[WK][i] = A[WK][i] / ER;
		}
		B[WK] = B[WK] / ER;

		double temp = 0;

		for (int i = 0; i < m; i++) 
		{
			if (i != WK) {
				temp = A[i][KK] / A[WK][KK];
				for (int j = 0; j < n; j++) 
				{
					A[i][j] = A[i][j] - temp * A[WK][j];
				}
				B[i] = B[i] - temp * B[WK];
			}
		}

		for (int i = 0; i < m; i++) 
		{
			F += Cb[i] * B[i];
		}

		double* iloczyn = new double[n];
		for (int i = 0; i < n; i++) 
		{
			iloczyn[i] = 0;
			for (int j = 0; j < m; j++) 
			{
				iloczyn[i] += Cb[j] * A[j][i];
			}
		}

		for (int i = 0; i < n; i++) 
		{
			ww[i] = Cj[i] - iloczyn[i];
		}

		/*		
		double iloczyn = 0;
		for (int i = 0; i < 5; i++) 
		{
			for (int j = 0; j < 3; j++) 
			{
				iloczyn += Cb[j] * A[j][i];
			}
			ww[i] = Cj[i] - iloczyn;
			iloczyn = 0;
		}*/

	}

	double x1 = 0;
	double x2 = 0;

	for (int i = 0; i < n; i++) 
	{
		if (Cb[i] == Cj[0]) {
			x1 = B[i];
		}
		if (Cb[i] == Cj[1]) {
			x2 = B[i];
		}
	}

	std::cout << "Wynik: x1 = " << x1 << " x2 = " << x2 << std::endl;
	
	for (int i = 0; i < m; i++)
	{
		delete[] A[i];
	}
	delete[] A; 
	delete[] B;
	delete[] Cj;
	delete[] Cb;
	delete[] ww;



	return 0;
}
