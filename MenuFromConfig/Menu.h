#pragma once
#include "framework.h"
#include "stdio.h"
typedef struct {
	int x;
	int y;
	int x1;
	int y1;
}Size;
typedef struct {
	int r;
	int g;
	int b;
}Color;
typedef struct {
	Size size;
	Color color;
}Window;
typedef struct {
	Size size;
	Color color;
	char* name;
}Button;
typedef struct {
	Window window;
	Button* buttons;
	int index;
}Config;
Config* SystemInitialise(const char* configName);
char* SystemUpdate(Config* config, HDC hdc, HWND hWnd, int curBut, int enterPressed);
void SystemRelease(Config* config);
