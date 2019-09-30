#include "Plain.h"

#include <iostream>

void Plain::_drawLine(unsigned char c, int sx, int ex, int ny)
{
	for (int i = sx; i <= ex; i++) putPoint(c, i, ny);
}

Plain::Plain(unsigned int width, unsigned int height, unsigned char axisFiller)
{
	this->hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	
	this->w = width;
	this->h = height;

	this->absc = height / 2;
	this->ord = width / 2;
	
	this->axisFiller = axisFiller;
	this->clear();
}

void Plain::show()
{
	std::system("cls");
	for (int i = 0; i < this->h; i++)
	{
		std::cout << this->field[i] << std::endl;
	}
}

void Plain::showBuffered()
{
	std::cout.flush();
	SetConsoleCursorPosition(this->hConsole, { (short)0, (short)0 });
	for (int i = 0; i < this->h; i++)
	{
		std::cout << this->field[i] << '\n';
	}
}

void Plain::showBufferedColored()
{
	std::cout.flush();
	SetConsoleCursorPosition(this->hConsole, { (short)0, (short)0 });

	for (register int i = 0; i < this->h; i++)
	{
		//std::cout << this->field[i] << '\n';
		for (register int j = 0; j < this->w; j++)
		{
			if (this->field[i][j] != ' ')
			{
				this->setColor(this->field[i][j]);
				std::cout << (unsigned char)219;
			}
			else std::cout << ' ';
		}
		std::cout << '\n';
	}
}

void Plain::clear()
{
	this->field.clear();
	for (int i = 0; i < h; i++)
	{
		std::string tempStr = "";
		for (int j = 0; j < w; j++)
		{
			char symbol = (i == absc || j == ord ? this->axisFiller : ' ');
			tempStr += symbol;
		}
		this->field.push_back(tempStr);
	}
}

void Plain::setColor(unsigned int color)
{
	SetConsoleTextAttribute(this->hConsole, color);
}

bool Plain::noBoundariesError(int x, int y)
{
	int posX = ord + x;
	int posY = absc - y;

	if (posX < 0 || posX > w - 1) {
		return false;
	}
	else if (posY < 0 || posY > h - 1) {
		return false;
	}
	return true;
}

void Plain::putPoint(unsigned char ch, int x, int y)
{
	if (noBoundariesError(x, y)) {
		this->field[absc - y][ord + x] = ch;
	}
}

void Plain::putLine(unsigned char ch, int x1, int y1, int x2, int y2)
{
	int dx = x2 - x1, dy = y2 - y1;
	float totalLength = sqrt(dx * dx + dy * dy);

	if (totalLength == 0) return;

	float xStep = dx / totalLength;
	float yStep = dy / totalLength;

	float currentX = x1, currentY = y1;

	while (noBoundariesError(currentX, currentY) && (abs(currentX - x2) > 1 || abs(currentY - y2) > 1))
	{
		this->putPoint(ch, (int)currentX, (int)currentY);
		currentX += xStep;
		currentY += yStep;
	}
}

void Plain::putTriangle(unsigned char c, int x1, int y1, int x2, int y2, int x3, int y3)
{
	int t1x, t2x, y, minx, maxx, t1xp, t2xp;
	bool changed1 = false;
	bool changed2 = false;
	int signx1, signx2, dx1, dy1, dx2, dy2;
	int e1, e2;
	// Sort vertices
	if (y1 > y2) { std::swap(y1, y2); std::swap(x1, x2); }
	if (y1 > y3) { std::swap(y1, y3); std::swap(x1, x3); }
	if (y2 > y3) { std::swap(y2, y3); std::swap(x2, x3); }

	t1x = t2x = x1; y = y1;   // Starting points
	dx1 = (int)(x2 - x1); if (dx1 < 0) { dx1 = -dx1; signx1 = -1; }
	else signx1 = 1;
	dy1 = (int)(y2 - y1);

	dx2 = (int)(x3 - x1); if (dx2 < 0) { dx2 = -dx2; signx2 = -1; }
	else signx2 = 1;
	dy2 = (int)(y3 - y1);

	if (dy1 > dx1) {   // swap values
		std::swap(dx1, dy1);
		changed1 = true;
	}
	if (dy2 > dx2) {   // swap values
		std::swap(dy2, dx2);
		changed2 = true;
	}

	e2 = (int)(dx2 >> 1);
	// Flat top, just process the second half
	if (y1 == y2) goto next;
	e1 = (int)(dx1 >> 1);

	for (int i = 0; i < dx1;) {
		t1xp = 0; t2xp = 0;
		if (t1x < t2x) { minx = t1x; maxx = t2x; }
		else { minx = t2x; maxx = t1x; }
		// process first line until y value is about to change
		while (i < dx1) {
			i++;
			e1 += dy1;
			while (e1 >= dx1) {
				e1 -= dx1;
				if (changed1) t1xp = signx1;//t1x += signx1;
				else          goto next1;
			}
			if (changed1) break;
			else t1x += signx1;
		}
		// Move line
	next1:
		// process second line until y value is about to change
		while (1) {
			e2 += dy2;
			while (e2 >= dx2) {
				e2 -= dx2;
				if (changed2) t2xp = signx2;//t2x += signx2;
				else          goto next2;
			}
			if (changed2)     break;
			else              t2x += signx2;
		}
	next2:
		if (minx > t1x) minx = t1x; if (minx > t2x) minx = t2x;
		if (maxx < t1x) maxx = t1x; if (maxx < t2x) maxx = t2x;
		this->_drawLine(c, minx, maxx, y);    // Draw line from min to max points found on the y
									 // Now increase y
		if (!changed1) t1x += signx1;
		t1x += t1xp;
		if (!changed2) t2x += signx2;
		t2x += t2xp;
		y += 1;
		if (y == y2) break;

	}
next:
	// Second half
	dx1 = (int)(x3 - x2); if (dx1 < 0) { dx1 = -dx1; signx1 = -1; }
	else signx1 = 1;
	dy1 = (int)(y3 - y2);
	t1x = x2;

	if (dy1 > dx1) {   // swap values
		std::swap(dy1, dx1);
		changed1 = true;
	}
	else changed1 = false;

	e1 = (int)(dx1 >> 1);

	for (int i = 0; i <= dx1; i++) {
		t1xp = 0; t2xp = 0;
		if (t1x < t2x) { minx = t1x; maxx = t2x; }
		else { minx = t2x; maxx = t1x; }
		// process first line until y value is about to change
		while (i < dx1) {
			e1 += dy1;
			while (e1 >= dx1) {
				e1 -= dx1;
				if (changed1) { t1xp = signx1; break; }//t1x += signx1;
				else          goto next3;
			}
			if (changed1) break;
			else   	   	  t1x += signx1;
			if (i < dx1) i++;
		}
	next3:
		// process second line until y value is about to change
		while (t2x != x3) {
			e2 += dy2;
			while (e2 >= dx2) {
				e2 -= dx2;
				if (changed2) t2xp = signx2;
				else          goto next4;
			}
			if (changed2)     break;
			else              t2x += signx2;
		}
	next4:

		if (minx > t1x) minx = t1x; if (minx > t2x) minx = t2x;
		if (maxx < t1x) maxx = t1x; if (maxx < t2x) maxx = t2x;
		this->_drawLine(c, minx, maxx, y);
		if (!changed1) t1x += signx1;
		t1x += t1xp;
		if (!changed2) t2x += signx2;
		t2x += t2xp;
		y += 1;
		if (y > y3) return;
	}
}

void Plain::putCircle(unsigned char c, int x, int y, int r)
{
	float a = 0.0f;
	while (a <= 2 * 3.1415926) {
		putPoint(c, x + cos(a) * r, y + sin(a) * r);
		a += 0.001f;
	}
}

void Plain::putCircleFilled(unsigned char c, int x, int y, int r)
{	
	float a = 0.0f;
	while (a <= 2 * 3.1415926) {
		putLine(c, x, y, x + cos(a) * r, y + sin(a) * r);
		a += 0.05f;
	}
}
