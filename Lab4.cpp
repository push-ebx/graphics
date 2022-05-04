#include "headers.h"

int ribs[rib_count][2] = {
	{0, 1}, {1, 2}, {2, 3}, {3, 0}, {4, 5}, {5, 6},
	{6, 7}, {7, 4}, {0, 4}, {1, 5}, {2, 6}, {3, 7}};

double coords[vertex][3] = {
		{-0.324249, 0.381751, -0.054578}, {-0.333815 , -0.099276, -0.190674},
		{0.124415, -0.053299, -0.385383}, {0.133980, 0.427727, -0.249287},
		{-0.124415, 0.253299, 0.385383}, {-0.133980, -0.227727, 0.249287},
		{0.324249, -0.181751, 0.054578}, {0.333815 , 0.299276, 0.190674}};

double *get_average() {
	float x = 0, y = 0, z = 0;
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

void show() {
	for (size_t i = 0; i < rib_count; i++) {
		double x[2] = {coords[ribs[i][0]][0], coords[ribs[i][1]][0]};
		double y[2] = {coords[ribs[i][0]][1], coords[ribs[i][1]][1]};
		setcolor(i + 1);
		line(X(x[0]), Y(y[0]), X(x[1]), Y(y[1]));
	}
}

void rotate(double angles[3]) {
	double s[3] = {sin(angles[0]), sin(angles[1]), sin(angles[2])};
	double c[3] = {cos(angles[0]), cos(angles[1]), cos(angles[2])};
	for (int i = 0; i < vertex + 1; i++) {
		double x = coords[i][0], y = coords[i][1], z = coords[i][2];
		coords[i][0] = c[1] * (s[2] * y + c[2] * x) - s[1] * z;
		coords[i][1] = s[0] * (c[1] * z + s[1] * (s[2] * y + c[2] * x)) + c[0]*(c[2] * y - s[2] * x);
		coords[i][2] = c[0] * (c[1] * z + s[1] * (s[2] * y + c[2] * x)) - s[0]*(c[2] * y - s[2] * x);
	}
}

void move(double* avg, double dx, double dy, double dz) {
	for (size_t i = 0; i < vertex; i++)
		coords[i][0] += dx, coords[i][1] += dy;
}

main() {
	int window = initwindow(width, height), KeyStroke;
	do {
		double *avg = get_average();
		show();
		KeyStroke = getch();
		if (KeyStroke == W_KEY) rotate(new double[3]{0.1, 0.0, 0.0});
		else if (KeyStroke == S_KEY) rotate(new double[3]{-0.1, 0.0, 0.0});
		else if (KeyStroke == D_KEY) rotate(new double[3]{0.0, -0.1, 0.0});
		else if (KeyStroke == A_KEY) rotate(new double[3]{0.0, 0.1, 0.0});
		else if (KeyStroke == Z_KEY) rotate(new double[3]{0.0, 0.0, -0.1});
		else if (KeyStroke == X_KEY) rotate(new double[3]{0.0, 0.0, 0.1});
		else if (KeyStroke == UP_KEY) move(avg, 0, 0.1, 0);
		else if (KeyStroke == DOWN_KEY) move(avg, 0, -0.1, 0);
		else if (KeyStroke == LEFT_KEY) move(avg, -0.1, 0, 0);
		else if (KeyStroke == RIGHT_KEY) move(avg, 0.1, 0, 0);
		else if (KeyStroke == PLUS_KEY) scale(1.1, avg);
		else if (KeyStroke == MINUS_KEY) scale(-1.1, avg);
		cleardevice();
	} while (KeyStroke != 27);
}