#include <graphics.h>
#include <math.h>
#define vertex 5
#define PI acos(-1.0)

double* get_average(double coords[vertex][2]) {
	float x = 0, y = 0;
	for (size_t i = 0; i < vertex; i++)
		x += coords[i][0], y += coords[i][1];
	return new double[2]{x /= vertex, y /= vertex};
}

void rotate_shape(double coords[vertex][2], double alpha, double ax, double ay) {
	for (size_t i = 0; i < vertex; i++)
	{
		coords[(i+1) % vertex][0] = ax + (coords[(i+1) % vertex][0] - ax) * cos(alpha * PI / 180) - (coords[(i+1) % vertex][1] - ay) * sin(alpha * PI / 180);
		coords[(i+1) % vertex][1] = ay + (coords[(i+1) % vertex][0] - ax) * sin(alpha * PI / 180) + (coords[(i+1) % vertex][1] - ay) * cos(alpha * PI / 180);
		coords[i][0] = ax + (coords[i][0] - ax) * cos(alpha * PI / 180) - (coords[i][1] - ay) * sin(alpha * PI / 180);
		coords[i][1] = ay + (coords[i][0] - ax) * sin(alpha * PI / 180) + (coords[i][1] - ay) * cos(alpha * PI / 180);
	}
}

void move_shape(double coords[vertex][2], double dx, double dy) {
	for (size_t i = 0; i < vertex; i++)
	{
		coords[(i+1) % vertex][0] += dx;///????
		coords[(i+1) % vertex][1] += dy;///????
		coords[i][0] += dx;
		coords[i][1] += dy;
	}
}

void scale_shape(double coords[vertex][2], double coef, double ax, double ay) {
	coef = coef > 0 ? coef : -1 / coef;
	for (size_t i = 0; i < vertex; i++)
	{
		coords[(i+1) % vertex][0] = (coords[(i+1) % vertex][0] - ax) * coef + ax;
		coords[(i+1) % vertex][1] = (coords[(i+1) % vertex][1] - ay) * coef + ay;
		coords[i][0] = (coords[i][0] - ax) * coef + ax;
		coords[i][1] = (coords[i][1] - ay) * coef + ay;
	}
}

main() {
	int window = initwindow(640, 480), KeyStroke;
	double coords[vertex][2] = {{100, 100}, {100, 200}, {150, 190}, {200, 200}, {200, 100}};
	do {
		double ax = get_average(coords)[0], ay = get_average(coords)[1];
		for (size_t i = 0; i < vertex; i++)
			line(coords[i][0], coords[i][1], coords[(i + 1) % vertex][0], coords[(i + 1) % vertex][1]);
		
		KeyStroke = getch();
		if (KeyStroke == 119) rotate_shape(coords, 1, ax, ay);
		else if (KeyStroke == 115) rotate_shape(coords, -1, ax, ay);
		else if (KeyStroke == 72) move_shape(coords, 0, -10);
		else if (KeyStroke == 80) move_shape(coords, 0, 10);
		else if (KeyStroke == 75) move_shape(coords, -10, 0);
		else if (KeyStroke == 77) move_shape(coords, 10, 0);
		else if (KeyStroke == 61) scale_shape(coords, 1.1, ax, ay);
		else if (KeyStroke == 45) scale_shape(coords, -1.1, ax, ay);
		cleardevice();
	} while (KeyStroke != 27);
	return 0;
}