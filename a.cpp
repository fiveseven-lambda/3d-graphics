#include <algorithm>
#include <cmath>
#include <utility>
#include "bmp.h"

img test;

color fore = {.r = 0xFF, .g = 0xFF, .b = 0xFF};

class Pos{
	static double xa, xo, ya, yo;
	double x, y;
public:
	Pos(double x, double y): x(x), y(y) {
		if(x > xa || x < xo || y > ya || y < yo) fprintf(stderr, "out : (%lf, %lf)\n", x, y);
	}
	friend void plot(Pos), segment(Pos, Pos), line(Pos, Pos);
};

double Pos::xa = 85, Pos::xo = -60, Pos::ya = 60, Pos::yo = -85;

void plot(Pos p){
	test.data[p.y == p.ya ? test.height - 1 : (int)(test.height * (p.y - p.yo) / (p.ya - p.yo))][p.x == p.xa ? test.width - 1 : (int)(test.width * (p.x - p.xo) / (p.xa - p.xo))] = fore;
}

void segment(Pos a, Pos b){
	if(a.x > b.x) std::swap(a, b);
	for(int i = (int)(test.width * (a.x - a.xo) / (a.xa - a.xo)); i <= (int)(test.width * (b.x - b.xo) / (b.xa - b.xo)); ++i){
		double p = (i * (a.xa - a.xo) / test.width + a.xo - a.x) * (b.y - a.y) / (b.x - a.x) + a.y;
		double q = ((i + 1) * (a.xa - a.xo) / test.width + a.xo - a.x) * (b.y - a.y) / (b.x - a.x) + a.y;
		if(p > q) std::swap(p, q);
		if(p < a.y && p < b.y) p = std::min(a.y, b.y);
		if(q > a.y && q > b.y) q = std::max(a.y, b.y);
		for(int j = (int)(test.height * (p - a.yo) / (a.ya - a.yo)); j <= (int)(test.height * (q - a.yo) / (a.ya - a.yo)); ++j)
			test.data[j][i] = fore;
	}
}

void line(Pos a, Pos b){
	if(a.x > b.x) std::swap(a, b);
	for(int i = 0; i < test.width; ++i){
		double p = (i * (a.xa - a.xo) / test.width + a.xo - a.x) * (b.y - a.y) / (b.x - a.x) + a.y;
		double q = ((i + 1) * (a.xa - a.xo) / test.width + a.xo - a.x) * (b.y - a.y) / (b.x - a.x) + a.y;
		if(p > q) std::swap(p, q);
		if(p < a.yo) p = a.yo;
		if(q > a.ya) q = a.ya;
		for(int j = (p == a.ya ? test.height - 1 : (int)(test.height * (p - a.yo) / (a.ya - a.yo))); j <= (q == a.ya ? test.height - 1 : (int)(test.height * (q - a.yo) / (a.ya - a.yo))); ++j)
			test.data[j][i] = fore;
	}
}

double ex = 800, ey = 750, ez = 650, el = -150, em = -150, en = -150;

class Point{
public:
	double x, y, z;
	Point(){}
	Point(double x, double y, double z): x(x), y(y), z(z) {}
	operator Pos(){


		double t = (el * el + em * em + en * en) / ((x - ex) * el + (y - ey) * em + (z - ez) * en);

		//double t = sqrt((el * el + em * em + en * en) / ((x - ex) * (x - ex) + (y - ey) * (y - ey) + (z - ez) * (z - ez)));

		double tx = t * (x - ex) - el, ty = t * (y - ey) - em, tz = t * (z - ez) - en;


		double co = (tx * em - ty * el) / sqrt(em * em + el * el);
		double si = sqrt(tx * tx + ty * ty + tz * tz - co * co);

		if(tx * en * el + ty * en * em - tz * (el * el + em * em) < 0) si = -si;

		printf("%lf %lf\n", co, si);
		return Pos(co, si);
	}
};

int main(){
	test.height = 1000;
	test.width = 1000;

	Point a(-100, -100, -100), b(-100, 100, -100);
	Point c(100, -100, -100), d(100, 100, -100);
	Point e(-100, -100, 100), f(-100, 100, 100);
	Point g(100, -100, 100), h(100, 100, 100);

	segment(a, b);
	segment(c, d);
	segment(e, f);
	segment(g, h);
	segment(a, c);
	segment(b, d);
	segment(e, g);
	segment(f, h);
	segment(a, e);
	segment(b, f);
	segment(c, g);
	segment(d, h);

	
	char out[] = "out.bmp";
	WriteBmp(out, &test);
	PrintBmpInfo(out);
}
