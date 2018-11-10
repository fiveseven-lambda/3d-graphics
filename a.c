#include <math.h>
#include "bmp.h"

#define N 3

img test;

color fore = {.r = 0xFF, .g = 0xFF, .b = 0xFF};

void normalize(double x[]){
	double abs = 0;
	for(int i = 0; i < N; ++i) abs += x[i] * x[i];
	abs = sqrt(abs);
	for(int i = 0; i < N; ++i) x[i] /= abs;
}

double inner_product(double x[], double y[]){
	double rtn = 0;
	for(int i = 0; i < N; ++i) rtn += x[i] * y[i];
	return rtn;
}

int main(){
	test.height = 1000;
	test.width = 1000;


	double o[N] = {500, 430, 300}, p[N] = {-500, -430, -300}, q[N] = {4.3, -5, 0};

	normalize(p);
	normalize(q);

	double r[N] = {p[1] * q[2] - p[2] * q[1], p[2] * q[0] - p[0] * q[2], p[0] * q[1] - p[1] * q[0]};

	double a[N];

	for(int i = -2; i < 2; ++i) for(int j = -2; j < 2; ++j) for(int k = -2; k < 2; ++k){
		a[0] = i * 100;
		a[1] = j * 100;
		a[2] = k * 100;
		for(int l = 0; l < 3; ++l) a[l] -= o[l];
		double x, y;
		x = - inner_product(a, r) / inner_product(a, p);
		y = inner_product(a, q) / inner_product(a, p);
		printf("%f %f\n", x, y);
		for(int l = x * 500 + 498; l < x * 500 + 502; ++l)
			for(int m = y * 500 + 498; m < y * 500 + 502; ++m)
				test.data[l][m - 200] = fore;
	}

	o[0] = 480;
	o[1] = 460;
	o[2] = 300;
	p[0] = -480;
	p[1] = -460;
	p[2] = -300;
	q[0] = 4.6;
	q[1] = -4.8;
	q[2] = 0;
	normalize(p);
	normalize(q);

	double r2[N] = {p[1] * q[2] - p[2] * q[1], p[2] * q[0] - p[0] * q[2], p[0] * q[1] - p[1] * q[0]};

	for(int i = -2; i < 2; ++i) for(int j = -2; j < 2; ++j) for(int k = -2; k < 2; ++k){
		a[0] = i * 100;
		a[1] = j * 100;
		a[2] = k * 100;
		for(int l = 0; l < 3; ++l) a[l] -= o[l];
		double x, y;
		x = - inner_product(a, r2) / inner_product(a, p);
		y = inner_product(a, q) / inner_product(a, p);
		printf("%f %f\n", x, y);
		for(int l = x * 500 + 498; l < x * 500 + 502; ++l)
			for(int m = y * 500 + 498; m < y * 500 + 502; ++m)
				test.data[l][m + 200] = fore;
	}
	
	char out[] = "out.bmp";
	WriteBmp(out, &test);
	PrintBmpInfo(out);
}
