#include <iostream>
#include <fstream>
#include <ctime>
#include <string>
#include <chrono>
#include <thread>
#include <sstream>
#include <windows.h>
using namespace std;

#include "Plain.h"

void setConsoleCursorVisibility(bool state)
{
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO info;
	GetConsoleCursorInfo(hOut, &info);
	info.bVisible = state;
	SetConsoleCursorInfo(hOut, &info);
}

void setConsoleFontSize()
{
	CONSOLE_FONT_INFOEX cfi;
	cfi.cbSize = sizeof(cfi);
	cfi.nFont = 0;
	cfi.dwFontSize.X = 2;                   // Width of each character in the font
	cfi.dwFontSize.Y = 2;                  // Height
	cfi.FontFamily = FF_DONTCARE;
	cfi.FontWeight = FW_NORMAL;
	std::wcscpy(cfi.FaceName, L"Consolas"); // Choose your font
	SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);
}

struct vec3 {
	float x, y, z;
};

vector<vec3>* readVerticies() {
	vector<vec3>* verticies = new vector<vec3>;
	verticies->reserve(200000);

	ifstream in("rooster.obj");

	vec3 temp;
	string line, type;
	while (!in.eof())
	{
		getline(in, line);
		istringstream iss(line);
		iss >> type;
		if (type == "v")
		{
			iss >> temp.x >> temp.y >> temp.z;
			temp.x *= 10;
			temp.y *= 10;
			verticies->push_back(temp);
		}
	}

	while (verticies->size() % 3) verticies->pop_back();
	return verticies;
}

void getTm(int& hour, int& mins, int& secs)
{
	time_t tt;
	time(&tt);
	tm TM = *localtime(&tt);

	hour = TM.tm_hour;
	mins = TM.tm_min;
	secs = TM.tm_sec;
}

int main()
{
	Plain p1(451, 451, ' ');
	setConsoleCursorVisibility(false);
	setConsoleFontSize();

	int len = 180;
	int hour, mins, secs;

	while (true)
	{
		getTm(hour, mins, secs);
		p1.clear();

		p1.putLine(219, 0, 0, sin(secs * 2 * 3.1415926 / 60.0f) * len, cos(secs * 2 * 3.1415926 / 60.0f) * len);
		p1.putLine(219, 0, 0, sin(mins * 2 * 3.1415926 / 60.0f + secs * 2 * 3.1415926 / 60.0f / 60.0f) * len * 0.85, cos(mins * 2 * 3.1415926 / 60.0f + secs * 2 * 3.1415926 / 60.0f / 60.0f) * len * 0.85);
		p1.putLine(219, 0, 0, sin(hour * 2 * 3.1415926 / 12.0f + mins * 2 * 3.1415926 / 60.0f / 12.0f) * len * 0.5, cos(hour * 2 * 3.1415926 / 12.0f + mins * 2 * 3.1415926 / 60.0f / 12.0f) * len * 0.5);

		p1.putCircle(219, 0, 0, 200);
		for (float i = 0; i <= 2 * 3.1415926; i += 2 * 3.1415926 / 60.0f) {
			p1.putCircleFilled(219, sin(i) * 198, cos(i) * 198, 5);
		}

		p1.putCircleFilled(219, 0, 0, 5);

		p1.showBuffered();
	}

}
