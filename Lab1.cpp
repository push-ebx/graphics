#include <graphics.h>
#include <math.h>

struct segment {
	double x1, y1, x2, y2, cx, cy;
	segment(double x1, double y1, double x2, double y2) {
		this->x1 = x1, this->y1 = y1, this->x2 = x2, this->y2 = y2;
		this->cx = (x1 + x2) / 2, this->cy = (y1 + y2) / 2;
	}
};

void rotate_seg(segment &seg, double alpha) {
	double x1_tmp = cos(alpha) * (seg.x1 - seg.cx) - sin(alpha) * (seg.y1 - seg.cy) + seg.cx;
	double y1_tmp = sin(alpha) * (seg.x1 - seg.cx) + cos(alpha) * (seg.y1 - seg.cy) + seg.cy;
	seg.x1 = x1_tmp, seg.y1 = y1_tmp;
	seg.x2 = 2 * seg.cx - x1_tmp, seg.y2 = 2 * seg.cy - y1_tmp;
}

void move_seg(segment &seg, double dx, double dy) {
	seg.x1 += dx, seg.y1 += dy, seg.x2 += dx, seg.y2 += dy, seg.cx += dx, seg.cy += dy;
}

void scale_seg(segment &seg, double coef) {
	coef = coef > 0 ? coef : -1 / coef;
	seg.x2 = (seg.x2 - seg.cx) * coef + seg.cx;
	seg.y2 = (seg.y2 - seg.cy) * coef + seg.cy;
	seg.x1 = (seg.x1 - seg.cx) * coef + seg.cx;
	seg.y1 = (seg.y1 - seg.cy) * coef + seg.cy;
}

void line_bresenham(int x1, int y1, int x2, int y2) {
	int dx = abs(x2 - x1), sx = x1 < x2 ? 1 : -1;
	int dy = abs(y2 - y1), sy = y1 < y2 ? 1 : -1;
	int err = (dx > dy ? dx : -dy) / 2, e2;
	while (true) {
		putpixel(x1, y1, YELLOW);
		if (x1 == x2 && y1 == y2) break;
		e2 = err;
		if (e2 > -dx) err -= dy, x1 += sx;
		if (e2 < dy) err += dx, y1 += sy;
	}
}

main() {
	int window = initwindow(640, 480), KeyStroke, index = 0;
	segment palks[] = {segment(100, 200, 300, 400), segment(200, 400, 100, 300)};
	do {
		line(palks[0].x1, palks[0].y1,palks[0].x2,palks[0].y2);	
		line_bresenham(palks[1].x1, palks[1].y1,palks[1].x2,palks[1].y2);
		KeyStroke = getch();
		if (KeyStroke == 119) rotate_seg(palks[index], 0.1);
		else if (KeyStroke == 115) rotate_seg(palks[index], -0.1);
		else if (KeyStroke == 72) move_seg(palks[index], 0, -10);
		else if (KeyStroke == 80) move_seg(palks[index], 0, 10);
		else if (KeyStroke == 75) move_seg(palks[index], -10, 0);
		else if (KeyStroke == 77) move_seg(palks[index], 10, 0);
		else if (KeyStroke == 61) scale_seg(palks[index], 1.1);
		else if (KeyStroke == 45) scale_seg(palks[index], -1.1);
		else if (KeyStroke == 49) index = 0;
		else if (KeyStroke == 50) index = 1;
		cleardevice();
	} while (KeyStroke != 27);
	return 0;
}