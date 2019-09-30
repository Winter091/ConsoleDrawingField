#include <vector>
#include <string>

#include <Windows.h>

#define COLOR_DARKBLUE    1
#define COLOR_DARKGREEN   2
#define COLOR_DARKMAGENTA 3
#define COLOR_DARKRED     4
#define COLOR_DARKPINK    5
#define COLOR_DARKYELLOW  6
#define COLOR_DARKWHITE   7
#define COLOR_GRAY        8
#define COLOR_BLUE		  9
#define COLOR_GREEN		  10
#define COLOR_MAGENTA	  11
#define COLOR_RED		  12
#define COLOR_PINK		  13
#define COLOR_YELLOW	  14
#define COLOR_WHITE		  15

class Plain {
private:
	std::vector<std::string> field;
	unsigned int w, h;
	unsigned int absc, ord;
	unsigned char axisFiller;

	HANDLE hConsole;

	void _drawLine(unsigned char c, int sx, int ex, int ny);

public:
	Plain(unsigned int width, unsigned int height, unsigned char axesFiller = '#');

	void show();
	void showBuffered();
	void showBufferedColored();
	void clear();
	void setColor(unsigned int color);
	bool noBoundariesError(int x, int y);

	void putPoint(unsigned char ch, int x, int y);
	void putLine(unsigned char ch, int x1, int y1, int x2, int y2);
	void putTriangle(unsigned char c, int x1, int y1, int x2, int y2, int x3, int y3);
	void putCircle(unsigned char c, int x1, int y1, int r);
	void putCircleFilled(unsigned char c, int x1, int y1, int r);
};