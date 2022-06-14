// This file contains the 'main' function. Program execution begins and ends there.
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
	double** matrix;
	double* wyniki;
	bool isEqual = true;

	std::ifstream in("matrix.txt");
	if (in.is_open()) {
		bool firstLine = true;
		std::string item;
		int i = 0;
		int j = 0;

		in >> m >> n;

		matrix = new double* [m];
		for (int i = 0; i < n; i++)
		{
			matrix[i] = new double[n];
		}

		for (int i = 0; i < m; i++)
		{
			for (int j = 0; j < n; j++)
			{
				in >> matrix[i][j];
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
		std::cout << "Cant open the file!" << std::endl;
		return 0;
	}

	
	for (int k = 0; k < m; k++) 
	{
		for (int l = k + 1; l < m; l++) 
		{
			if (std::abs(matrix[k][k]) < std::abs(matrix[l][k])) {
				for (int i = 0; i < n; i++) 
				{
					std::swap(matrix[k][i], matrix[l][i]);
				}
				std::swap(wyniki[k], wyniki[l]);

			}

		}

	}

	for (int i = 0; i < m - 1; i++)
	{
		for (int j = 0; j < n - 1; j++)
		{
			if (!((matrix[i][j] / matrix[i + 1][j]) == (wyniki[i] / wyniki[i + 1]))) 
			{                                                                                
				isEqual = false;
				break;

			}
		}
	}


	//Using Gauss Elimination
	double b = 0;
	if (!isEqual) 
	{
		for (int i = 0; i < m; i++)
		{
			for (int j = i + 1; j < m; j++)
			{
				b = matrix[j][i] / matrix[i][i];
				for (int k = 0; k < n; k++){
					matrix[j][k] = matrix[j][k] - b * matrix[i][k];
				}
				wyniki[j] -= b * wyniki[i];
			}
		}


		for (int i = 0; i < m - 1; i++)
		{
			for (int j = i + 1; j < m; j++)
			{
				matrix[j][i] = 0;
			}
		}


		//backtrack?

		for (int i = (m > n) ? n - 1 : m - 1; i >= 0; i--) //
		{
			for (int j = i + 1; j < n; j++)
			{
				if (j != i)
				{
					wyniki[i] = wyniki[i] - matrix[i][j] * wyniki[((m >= n) ? j : j - (m - m))];
				}

			}

			if (matrix[i][i] == 0)
			{
				return 1;
			}
			else
			{
				wyniki[i] = wyniki[i] / matrix[i][i];
			}

		}
	}

	std::cout << "Result: ";
	for (int i = 0; i < m; i++)
	{
		std::cout << wyniki[i] << " ";
	}
	std::cout << std::endl;


	for (int i = 0; i < n; i++)
	{
		delete[] matrix[i];
	}
	delete[] matrix;

	delete[] wyniki;


	return 0;
}


/*

	for (int i = 0; i < m; i++){
		for (int j = 0; j < n; j++){
			std::cout << matrix[i][j] << " ";
			}
		std::cout << std::endl;
	}

*/