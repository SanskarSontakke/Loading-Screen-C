#include <stdio.h>
#include <time.h>
#include <windows.h>

#ifndef ENABLE_VIRTUAL_TERMINAL_PROCESSING
#define ENABLE_VIRTUAL_TERMINAL_PROCESSING 0x0004
#endif

static HANDLE stdoutHandle;
static DWORD outModeInit;

void loading_screen(int no_of_sections, int delay_per_section, int type, int x, int y, int colour, int arrow)
{
	void setupConsole(void)
	{
		DWORD outMode = 0;
		stdoutHandle = GetStdHandle(STD_OUTPUT_HANDLE);

		if (stdoutHandle == INVALID_HANDLE_VALUE)
		{
			exit(GetLastError());
		}

		if (!GetConsoleMode(stdoutHandle, &outMode))
		{
			exit(GetLastError());
		}

		outModeInit = outMode;

		// Enable ANSI escape codes
		outMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;

		if (!SetConsoleMode(stdoutHandle, outMode))
		{
			exit(GetLastError());
		}
	}

	void restoreConsole(void)
	{
		// Reset colors
		printf("\x1b[0m");

		// Reset console mode
		if (!SetConsoleMode(stdoutHandle, outModeInit))
		{
			exit(GetLastError());
		}
	}
	setupConsole();

	printf("\033[0;3%dm", colour);
	printf("\033[?25l");

	COORD c = { 0, 0 };

	void setxy(int x, int y)
	{
		c.X = x;
		c.Y = y;
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
	}

	setxy(x, y);

	int _x = x;
	int _y = y;

	void delay(float number_of_milli_seconds)
	{
		clock_t start_time = clock();
		while (clock() < start_time + number_of_milli_seconds)
			;
	}

	if (type == 1)
	{
		printf("|");
		for (int i = 1; i <= no_of_sections; i++)
		{
			x = x + 1;
			setxy(x, y);
			printf("#");
			delay(delay_per_section);
			setxy(_x + no_of_sections + 2, _y);
			printf("   %d", (i * 100) / no_of_sections);
		}
		setxy(x + 1, y);
		printf("|");
		printf("  100 ");
	}
	else if (type == 2)
	{
		printf("|");
		for (int i = 1; i <= (no_of_sections - 1); i++)
		{
			x = x + 1;
			setxy(x, y);
			printf("=");
			if (arrow == 1)
			{
				setxy((x + 1), y);
				printf(">");
			}
			delay(delay_per_section);
			setxy(_x + no_of_sections + 2, _y);
			printf("   %d", (i * 100) / no_of_sections);
		}
		setxy((x + 1), y);
		printf("=");
		printf("|");
		printf("  100 ");
	}
	else if (type == 3)
	{
		printf("|");
		for (int i = 1; i <= no_of_sections; i++)
		{
			x = x + 1;
			setxy(x, y);
			printf(">");
			delay(delay_per_section);
			setxy(_x + no_of_sections + 2, _y);
			printf("   %d", (i * 100) / no_of_sections);
		}
		setxy(x + 1, y);
		printf("|");
		printf("  100 ");
	}
	else if (type == 4)
	{
		printf("|");
		for (int i = 1; i <= no_of_sections; i++)
		{
			x = x + 1;
			setxy(x, y);
			printf("*");
			delay(delay_per_section);
			setxy(_x + no_of_sections + 2, _y);
			printf("   %d", (i * 100) / no_of_sections);
		}
		setxy(x + 1, y);
		printf("|");
		printf("  100 ");
	}
	else if (type == 5)
	{
		printf("|");
		for (int i = 1; i <= (no_of_sections - 1); i++)
		{
			x = x + 1;
			setxy(x, y);
			printf("-");
			if (arrow == 1)
			{
				setxy((x + 1), y);
				printf(">");
			}
			delay(delay_per_section);
			setxy(_x + no_of_sections + 2, _y);
			printf("   %d", (i * 100) / no_of_sections);
		}
		setxy((x + 1), y);
		printf("-");
		printf("|");
		printf("  100 ");
	}

	printf("\033[0;37m");
	restoreConsole();
}
