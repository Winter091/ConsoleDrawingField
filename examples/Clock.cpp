#include <ctime>
#include "Plain.h"
#include "Windows.h"

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
		p1.putCircle((unsigned char)219, 0, 0, 200);
		p1.putLine(219, 0, 0, sin(secs * 2 * 3.1415926 / 60.0f) * len, cos(secs * 2 * 3.1415926 / 60.0f) * len);
		p1.putLine(219, 0, 0, sin(mins * 2 * 3.1415926 / 60.0f + secs * 2 * 3.1415926 / 60.0f / 60.0f) * len * 0.85, cos(mins * 2 * 3.1415926 / 60.0f + secs * 2 * 3.1415926 / 60.0f / 60.0f) * len * 0.85);
		p1.putLine(219, 0, 0, sin(hour * 2 * 3.1415926 / 12.0f + mins * 2 * 3.1415926 / 60.0f / 12.0f) * len * 0.5, cos(hour * 2 * 3.1415926 / 12.0f + mins * 2 * 3.1415926 / 60.0f / 12.0f) * len * 0.5);
		p1.showBuffered();
	}

}
