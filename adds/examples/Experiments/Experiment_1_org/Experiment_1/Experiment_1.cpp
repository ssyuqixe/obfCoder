#include <iostream>
#include <random>
#include <fstream>
#include <string>
#include <vector>
#include <stdlib.h>



void magic(int& a, int& b)
{
	if (a != b)
	{
		a ^= b;
		b ^= a;
		a ^= b;
	}
}

void func(int** tab, int size)
{
	int* arr = new int[size * size];
	int k = 0;
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			arr[k++] = tab[i][j];
		}
	}

	bool swapped = false;
	do
	{
		swapped = false;

		for (int i = 0; i < size * size - 2; i++)
		{
			if (arr[i] > arr[i + 1])
			{
				magic(arr[i], arr[i + 1]);
				swapped = true;
			}

		}

		if (!swapped)
			break;

		for (int i = size * size - 2; i >= 0; i--)
		{
			if (arr[i] > arr[i + 1]) {
				magic(arr[i], arr[i + 1]);
				swapped = true;
			}
		}

	} while (swapped);


	k = 0;
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			tab[i][j] = arr[k++];
		}
	}

	delete[] arr;

}

int main() {
	system("Color 02");
	unsigned char eleArr[] = { 3, 4, 5 };
	unsigned char eleArrLastIndex = 3;
	unsigned char elements = eleArr[rand() % (eleArrLastIndex + 1)];
	srand(time(NULL));

	std::ifstream input("input.txt");
	std::vector<int> v_elements;
	if (input)
	{
		std::string _string;
		while (std::getline(input, _string, ' '))
		{
			v_elements.push_back(atoi(_string.c_str()));

		}

		for (int i = 0; i <= eleArrLastIndex; i++)
		{
			if (v_elements.size() <= (int)(eleArr[i] * eleArr[i]))
			{
				elements = eleArr[i];
				break;
			}
		}

		if (v_elements.size() >= (int)(eleArr[eleArrLastIndex] * eleArr[eleArrLastIndex]))
		{
			elements = eleArr[eleArrLastIndex];
		}


	}

	int** arr = new int* [elements];
	int k = 0;
	for (int i = 0; i < elements; i++)
	{
		arr[i] = new int[elements];
		for (int j = 0; j < elements; j++)
		{
			if (k < v_elements.size())
			{
				arr[i][j] = v_elements[k++];
			}
			else
			{
				arr[i][j] = rand();
			}
		}
		//std::cout << std::endl;
	}

	func(arr, elements);

	int sum = 0;

	for (int i = 0; i < elements; i++)
	{
		for (int j = 0; j < elements; j++)
		{
			std::cout << arr[i][j] << "\t ";
		}
	}

	for (int i = 0; i < elements; i++)
	{
		sum += arr[i][i];
	}


	std::cout << "\n\n" << (sum / elements) << std::endl;

	for (int i = 0; i < elements; i++)
	{
		delete[] arr[i];
	}
	delete[] arr;

	system("pause");
	return 0;

}
