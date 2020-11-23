﻿// Integr.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

int main()
{
	int n = 10;

	double l = 10, dx = l / (double)n, t = 2 / dx;


	double Bf[2]{ 2,2 }, Bdf[2]{ 2 * t ,2 * t }, Aff[2][2]{ { 2 + 2 / 3.0,2 - 2 / 3.0 }, { 2 - 2 / 3.0,2 + 2 / 3.0 } }, Adfdf[2][2]{ { 2 * t * t ,-2 * t * t  } , { 2 * t * t ,2 * t * t  } }, Adff[2][2]{ { 2 * t ,-2 * t } , { 2 * t ,2 * t } };

	double f = 1, df = 0, ff = 1, dfdf = 0, dff = 0;

	double B[2], A[2][2];

	for (int i = 0; i < 2; i++)
		B[i] = Bf[i] * f + Bdf[i] * df; 
	for (int i = 0; i < 2; i++) for (int j = 0; j < 2; j++)
		A[i][j] = Aff[i][j] * ff + Adfdf[i][j] * dfdf + Adff[i][j] * dff;

	double d1 = 1, dn = 0, t;

	int ms = n - 2;

	double **mat = new double*[ms];

	for (int i = 0; i < ms; i++) mat[i] = new double[4];

	mat[0][0] = 0; mat[0][1] = A[0][0] + A[1][1]; ; mat[0][2] = A[0][1]; mat[0][3] = -B[0] - B[1] - d1 * A[1][0];
	mat[ms - 1][2] = 0; mat[ms - 1][1] = A[0][0] + A[1][1]; ; mat[ms - 1][0] = A[1][0]; mat[ms - 1][3] = -B[0] - B[1] - dn * A[0][1];

	for (int i = 1; i < ms - 1; i++) { mat[i][0] = A[1][0]; mat[i][1] = A[0][0] + A[1][1]; ; mat[i][2] = A[0][1]; mat[i][3] = -B[0] - B[1]; }

	for (int i = 1; i < ms; i++) { t = mat[i][0] / mat[i - 1][1]; mat[i][0] = mat[i][0] - mat[i - 1][1] * t; mat[i][1] = mat[i][1] - mat[i - 1][2] * t; mat[i][3] = mat[i][3] - mat[i - 1][3] * t; }

	for (int i = ms - 2; i >= 0; i--) { t = mat[i][2] / mat[i + 1][1]; mat[i][2] = mat[i][2] - mat[i + 1][1] * t; mat[i][3] = mat[i][3] - mat[i - 1][3] * t; }



}