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


	double o[N] = {500, 400, 300}, p[N] = {-1, -1, -1}, q[N] = {1, -1, 0};

	normalize(p);
	normalize(q);

	double r[N] = {p[1] * q[2] - p[2] * q[1], p[2] * q[0] - p[0] * q[2], p[0] * q[1] - p[1] * q[0]};

	double a[N];
	for(int i = 0; i < 1 << N; ++i){
		for(int j = 0; j < N; ++j){
			a[j] = ((i >> j) & 1 ? -100 : 100);
		}
		for(int j = 0; j < N; ++j){
			printf("%f ", a[j]);
		}
		putchar('\n');
		
		for(int j = 0; j < N; ++j) a[j] -= o[j];
		double x, y;
		x = inner_product(a, q) / inner_product(a, p);
		y = inner_product(a, r) / inner_product(a, p);

		printf("%f %f\n", x, y);
		printf("%d %d\n", (int)(x * 1000), (int)(y * 1000));
		for(int j = x * 1000 + 495; j < x * 1000 + 505; ++j)
			for(int k = y * 1000 + 495; k < y * 1000 + 505; ++k)
				test.data[j][k] = fore;
	}

	
	char out[] = "out.bmp";
	WriteBmp(out, &test);
	PrintBmpInfo(out);
}
