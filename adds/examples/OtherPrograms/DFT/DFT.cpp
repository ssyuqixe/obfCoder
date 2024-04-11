#include <iostream>
#include <fstream>


long double const pi = 3.141592653589793238462643383279502884L;


double functionIn(double k, double n, int N) {
	return  (-2.0f * pi * k * n) / N;
}

double* DFT(double* ptrValuesArray, int N) {
	double X_Re = 0; 
	double X_Im = 0;
	double* M = new double[N];

	for (int k = 0; k < N; k++) 
	{
		for (int n = 0; n < N; n++) 
		{
			X_Re += ptrValuesArray[n] * std::cos(functionIn(k, n, N));
			X_Im += ptrValuesArray[n] * std::sin(functionIn(k, n, N));
		}
		M[k] = std::sqrt(std::ceil(X_Re * X_Re) * std::ceil(X_Im * X_Im));
		M[k] = M[k] * (2.0f / N);
		X_Re = 0;
		X_Im = 0;
	}

	return M;
}

double sinusF(double a, double f, double t, double fi) {
	return a * std::sin(2 * pi * f * t + fi);
}



int main() {

	double fs = 0;
	double Tc = 0;
	double phi = 0;
	double A1 = 0;
	double f1 = 0;
	double A2 = 0;
	double f2 = 0;


	std::ifstream inFile("dft.txt");
	if (inFile.is_open()) {
		inFile >> fs >> Tc >> phi >> A1 >> f1 >> A2 >> f2;
	}
	else {
		std::cout << "Can't open the file!" << std::endl;
		return 0;
	}

	double Ts = 1 / fs;

	int N = std::ceil(Tc / Ts);

	double* s_1 = new double[N];
	double* s_2 = new double[N];
	double* tk = new double[N];




	for (int n = 0; n < N; n++)
	{
		tk[n] = n / fs;
	}

	for (int n = 0; n < N; n++)
	{
		s_1[n] = sinusF(A1, f1, tk[n], phi); //A * std::sin(2 * pi * f * tk[n] + phi);
	}


	for (int n = 0; n < N; n++)
	{
		s_2[n] = sinusF(A2, f2, tk[n], phi);//A * std::sin(2 * pi * f * tk[n] + phi);
	}


	double* x = new double[N];
	for (int i = 0; i < N; i++)
	{
		x[i] = s_1[i] + s_2[i];
	}

	double* M = DFT(x, N);
	for (int n = 0; n < N; n++)
	{
		tk[n] = n * (fs / N);
	}


	for (int i = 0; i < N; i++)
	{
		std::cout << tk[i] << "," << M[i] << ";" << std::endl;
	}

	delete[] s_1, delete[] s_2, delete[] tk, delete[] x, delete[] M;


	return 0;
}