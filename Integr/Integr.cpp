// Integr.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main()
{
	ofstream a("C:\\Temp\\integr\\out.txt");
	a.clear();
	int maxdefpow = 4, defn = 15;
	int x1 = 0, x2 = 15, l = x2 - x1;
	int maxdef = 1; for (int i = 0; i < maxdefpow; i++) maxdef *= 2;
	int rsize = maxdef * defn + 1;
	double *graph = new double[rsize];

	for (int def = 1; def <= maxdef; def *= 2)
	{
		int n = defn * def;

		double dx = l / (double)n, t = 2 / dx;

		double Bf[2]{ 1,1 }, Bdf[2]{ -1 * t ,1 * t }, Aff[2][2]{ { 2 / 3.0, 1 / 3.0 }, { 1 / 3.0, 2 / 3.0 } }, Adfdf[2][2]{ { 0.5 * t * t ,-0.5 * t * t  } , { -0.5 * t * t , 0.5 * t * t  } }, Adff[2][2]{ { -0.5 * t , 0.5 * t } , { -0.5 * t , 0.5 * t } };

		double f = 0, df = 12, ff = 6, dfdf = 10, dff = 0;

		double B[2], A[2][2];

		for (int i = 0; i < 2; i++)
			B[i] = Bf[i] * f + Bdf[i] * df;
		for (int i = 0; i < 2; i++) for (int j = 0; j < 2; j++)
			A[i][j] = Aff[i][j] * ff + Adfdf[i][j] * dfdf + Adff[i][j] * dff;

		double d1 = 1, dn = 20;

		int ms = n - 1;

		double **mat = new double*[ms];

		for (int i = 0; i < ms; i++) mat[i] = new double[4];

		mat[0][0] = 0;				mat[0][1] = A[0][0] + A[1][1];			mat[0][2] = A[0][1];		mat[0][3] = -B[0] - B[1] - d1 * A[1][0];
		mat[ms - 1][0] = A[1][0];	mat[ms - 1][1] = A[0][0] + A[1][1];		mat[ms - 1][2] = 0;			mat[ms - 1][3] = -B[0] - B[1] - dn * A[0][1];

		for (int i = 1; i < ms - 1; i++) { mat[i][0] = +A[1][0]; mat[i][1] = A[0][0] + A[1][1]; ; mat[i][2] = A[0][1]; mat[i][3] = -B[0] - B[1]; }

		std::cout << 0
			<< " " << 1
			<< " " << 0
			<< " " << d1
			<< std::endl;

		for (int i = 0; i < ms; i++)
		{
			std::cout << ((abs(mat[i][0]) < 1e-5) ? 0 : mat[i][0])
				<< " " << ((abs(mat[i][1]) < 1e-5) ? 0 : mat[i][1])
				<< " " << ((abs(mat[i][2]) < 1e-5) ? 0 : mat[i][2])
				<< " " << ((abs(mat[i][3]) < 1e-5) ? 0 : mat[i][3])
				<< std::endl;
		}

		std::cout << 0
			<< " " << 1
			<< " " << 0
			<< " " << dn
			<< std::endl << std::endl;

		for (int i = 1; i < ms; i++) { t = mat[i][0] / mat[i - 1][1]; mat[i][0] = mat[i][0] - mat[i - 1][1] * t; mat[i][1] = mat[i][1] - mat[i - 1][2] * t; mat[i][3] = mat[i][3] - mat[i - 1][3] * t; }

		for (int i = ms - 2; i >= 0; i--) { t = mat[i][2] / mat[i + 1][1]; mat[i][2] = mat[i][2] - mat[i + 1][1] * t; mat[i][3] = mat[i][3] - mat[i + 1][3] * t; }

		for (int i = 0; i < ms; i++) { t = 1 / mat[i][1]; mat[i][0] = mat[i][0] * t; mat[i][1] = mat[i][1] * t; mat[i][2] = mat[i][2] * t; mat[i][3] = mat[i][3] * t; }

		std::cout << 0
			<< " " << 1
			<< " " << 0
			<< " " << d1
			<< std::endl;

		for (int i = 0; i < ms; i++)
		{
			std::cout << ((abs(mat[i][0]) < 1e-5) ? 0 : mat[i][0])
				<< " " << ((abs(mat[i][1]) < 1e-5) ? 0 : mat[i][1])
				<< " " << ((abs(mat[i][2]) < 1e-5) ? 0 : mat[i][2])
				<< " " << ((abs(mat[i][3]) < 1e-5) ? 0 : mat[i][3])
				<< std::endl;
		}

		std::cout << 0
			<< " " << 1
			<< " " << 0
			<< " " << dn
			<< std::endl;

		graph[0] = d1; graph[rsize - 1] = dn;

		int r = (maxdef / def), _i; t = r;

		for (int i = 1; i < rsize - 1; i++)
		{
			_i = i / r;
			dx = i % r / (double)r;

			if (_i == 0)
			{
				graph[i] = d1 + dx * (mat[0][3] - d1);
			}
			else if (_i == ms)
			{
				graph[i] = mat[ms - 1][3] + dx * (dn - mat[ms - 1][3]);
			}
			else
			{
				graph[i] = mat[_i - 1][3] + dx * (mat[_i][3] - mat[_i - 1][3]);
			}

		}

		std::string str = "", razd = ";";

		for (int i = 0; i < rsize; i++)
		{
			str += to_string((abs(graph[i]) < 1e-5) ? 0 : graph[i]) + razd;
		}

		str += '\n';
		if (def == maxdef)
		{
			str += to_string(x1) + razd;

			for (int i = 0; i < ms; i++)
				str += to_string(x1 + l / (double)n * (i + 1)) + razd;

			str += to_string(x2) + '\n';
		}
		for (int i = 0; i < str.size(); i++)
		{
			if (str[i] == '.') str[i] = ',';
		}

		a << str;
	}
	a.close();
	//system("pause");

}