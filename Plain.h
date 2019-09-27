#include <vector>
#include <string>

class Plain {
private:
	std::vector<std::string> field;
	unsigned int w, h;
	unsigned int absc, ord;
	unsigned char axisFiller;

	void _drawLine(unsigned char c, int sx, int ex, int ny);

public:
	Plain(unsigned int width, unsigned int height, unsigned char axesFiller = '#');

	void show();
	void clear();
	bool noBoundariesError(int x, int y);

	void putPoint(unsigned char ch, int x, int y);
	void putLine(unsigned char ch, int x1, int y1, int x2, int y2);
	void putTriangle(unsigned char c, int x1, int y1, int x2, int y2, int x3, int y3);
};