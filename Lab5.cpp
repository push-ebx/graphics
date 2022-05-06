#include "headers.h"

int sides[side_count][4] = {
	{1, 5, 4, 0}, {7, 4, 5, 6}, {2, 6, 5, 1},
	{0, 4, 7, 3}, {0, 1, 2, 3}, {3, 7, 6, 2}};
int colors[] = {CYAN, RED, YELLOW, BLUE, BROWN, GREEN};
double coords[vertex][3] = {
		{50, 50, 50}, {200, 50, 50}, {200, 200, 50}, {50, 200, 50}, 
		{50, 50, 200}, {200, 50, 200}, {200, 200, 200}, {50, 200, 200}};

void sort_sides() {
	double min_z[side_count];
	for (size_t i = 0; i < side_count; i++) {
		min_z[i] = numeric_limits<double>::max();
		for (size_t j = 0; j < 4; j++) {
			double z = coords[sides[i][j]][2];
			min_z[i] = z < min_z[i] ? z : min_z[i];
		}
	}
	
	for (size_t i = 0; i < side_count; i++)
		for(size_t j = side_count - 1; j > i; j--)
			if (min_z[j - 1] > min_z[j]) {
				swap(min_z[j - 1], min_z[j]);
				swap(sides[j - 1], sides[j]);
				swap(colors[j - 1], colors[j]);
			}
}

double *get_average() {
	double x = 0, y = 0, z = 0;
	for (size_t i = 0; i < vertex; i++)
		x += coords[i][0], y += coords[i][1], z += coords[i][2];
	return new double[3]{x /= vertex, y /= vertex, z /= vertex};
}

void scale(double coef, double* avg) {
	coef = coef > 0 ? coef : -1 / coef;
	for (size_t i = 0; i < vertex; i++) {
		coords[(i + 1) % vertex][0] = (coords[(i + 1) % vertex][0] - avg[0]) * coef + avg[0];
		coords[(i + 1) % vertex][1] = (coords[(i + 1) % vertex][1] - avg[1]) * coef + avg[1];
		coords[(i + 1) % vertex][2] = (coords[(i + 1) % vertex][2] - avg[2]) * coef + avg[2];
		coords[i][0] = (coords[i][0] - avg[0]) * coef + avg[0];
		coords[i][1] = (coords[i][1] - avg[1]) * coef + avg[1];
		coords[i][2] = (coords[i][2] - avg[2]) * coef + avg[2];
	}
}

void rotate(double angles[3], double *avg) {
	double s[3] = {sin(angles[0]), sin(angles[1]), sin(angles[2])};
	double c[3] = {cos(angles[0]), cos(angles[1]), cos(angles[2])};
	for (int i = 0; i < vertex + 1; i++) {
		double x = coords[i][0], y = coords[i][1], z = coords[i][2];
		coords[i][0] = avg[0] + c[1] * (s[2] * (y-avg[1]) + c[2] * (x-avg[0])) - s[1] * (z-avg[2]);
		coords[i][1] = avg[1] + s[0] * (c[1] * (z-avg[2]) + s[1] * (s[2] * (y-avg[1]) + c[2] * (x-avg[0]))) + c[0] * (c[2] * (y-avg[1]) - s[2] * (x-avg[0]));
		coords[i][2] = avg[2] + c[0] * (c[1] * (z-avg[2]) + s[1] * (s[2] * (y-avg[1]) + c[2] * (x-avg[0]))) - s[0] * (c[2] * (y-avg[1]) - s[2] * (x-avg[0]));
	}
}

void translate(double dx, double dy, double dz) {
	for (size_t i = 0; i < vertex; i++)
		coords[i][0] += dx, coords[i][1] += dy, coords[i][2] += dz;
}

void show() {
	sort_sides();
	for (size_t i = 0; i < side_count; i++) {
		int poly[(4+1) * 2] = {
			(int)round(coords[sides[i][0]][0]), (int)round(coords[sides[i][0]][1]),
			(int)round(coords[sides[i][1]][0]), (int)round(coords[sides[i][1]][1]),
			(int)round(coords[sides[i][2]][0]), (int)round(coords[sides[i][2]][1]),
			(int)round(coords[sides[i][3]][0]), (int)round(coords[sides[i][3]][1]),
			(int)round(coords[sides[i][0]][0]), (int)round(coords[sides[i][0]][1])
		};
		setfillstyle(SOLID_FILL, colors[i]);
		fillpoly(4 + 1, poly);
	}
}

main() {
	int window = initwindow(width, height), KeyStroke;
	show();
	do {
		double *avg = get_average();
		KeyStroke = getch();
		if (KeyStroke == W_KEY) rotate(new double[3]{-0.1, 0.0, 0.0}, avg);
		else if (KeyStroke == S_KEY) rotate(new double[3]{0.1, 0.0, 0.0}, avg);
		else if (KeyStroke == D_KEY) rotate(new double[3]{0.0, -0.1, 0.0}, avg);
		else if (KeyStroke == A_KEY) rotate(new double[3]{0.0, 0.1, 0.0}, avg);
		else if (KeyStroke == Z_KEY) rotate(new double[3]{0.0, 0.0, 0.1}, avg);
		else if (KeyStroke == X_KEY) rotate(new double[3]{0.0, 0.0, -0.1}, avg);
		else if (KeyStroke == UP_KEY) translate(0, -10, 0);
		else if (KeyStroke == DOWN_KEY) translate(0, 10, 0);
		else if (KeyStroke == LEFT_KEY) translate(-10, 0, 0);
		else if (KeyStroke == RIGHT_KEY) translate(10, 0, 0);
		else if (KeyStroke == PLUS_KEY) scale(1.1, avg);
		else if (KeyStroke == MINUS_KEY) scale(-1.1, avg);
		show();
		swapbuffers();
		cleardevice();
	} while (KeyStroke != 27);
}