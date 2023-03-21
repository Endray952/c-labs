#define _CRT_SECURE_NO_WARNINGS
#include "Menu.h"


Config* SystemInitialise(const char* configName) {
	FILE* openConf = fopen(configName, "r");
	char* str = (char*)malloc(50 * sizeof(char));
	Window window;
	Button* buttons = (Button*)malloc(sizeof(Button));
	Button* p;
	int butNum = 0;
	int butIndex;
	//Обработка тела конфига
	while (fscanf(openConf, "%s", str) >= 1) {
		if (str[0] == '#') continue;
		if (strcmp(str, "WindowBegin") == 0) {
			do {
				if ((fscanf(openConf, "%s", str) >= 1) && (strcmp(str, "Size") == 0)) {
					fscanf(openConf, "%s", str);
					sscanf(str, "(%i,%i,%i,%i)", &(window.size.x), &(window.size.y), &(window.size.x1), &(window.size.y1));
				}
				else if (strcmp(str, "Color") == 0) {
					fscanf(openConf, "%s", str);
					sscanf(str, "(%i,%i,%i)", &(window.color.r), &(window.color.g), &(window.color.b));
				}
			} while (strcmp(str, "WindowEnd") != 0);

		}
		else if (strcmp(str, "ButtonBegin") == 0) {
			butNum++;
			butIndex = butNum - 1;
			p = (Button*)realloc(buttons, butNum * sizeof(Button));
			if (p == NULL) {
				puts("realloc error");
				return NULL;
			}
			else {
				buttons = p;
			}
			do {
				if ((fscanf(openConf, "%s", str) >= 1) && (strcmp(str, "Size") == 0)) {
					fscanf(openConf, "%s", str);
					sscanf(str, "(%i,%i,%i,%i)", &(buttons[butIndex].size.x), &(buttons[butIndex].size.y), &(buttons[butIndex].size.x1), &(buttons[butIndex].size.y1));
				}
				else if (strcmp(str, "Color") == 0) {
					fscanf(openConf, "%s", str);
					sscanf(str, "(%i,%i,%i)", &(buttons[butIndex].color.r), &(buttons[butIndex].color.g), &(buttons[butIndex].color.b));
				}
				else if (strcmp(str, "Name") == 0) {
					fscanf(openConf, "%s", str);
					buttons[butIndex].name = (char*)malloc(strlen(str) - 4);
					for (int i = 2; i < strlen(str) - 2; i++) {
						buttons[butIndex].name[i - 2] = str[i];
					}
					buttons[butIndex].name[strlen(str) - 4] = '\0';
				}
			} while (strcmp(str, "ButtonEnd") != 0);

		}
	}

		
	Config* config = (Config*)malloc(sizeof(Config));
	config->window = window;
	config->buttons = buttons;
	config->index = butIndex;
	free(str);
	fclose(openConf);
	return config;
}
char* SystemUpdate(Config* config, HDC hdc, HWND hWnd, int curBut, int enterPressed) {
	RECT rcWindow;
	RECT rcLine;
	HBRUSH backGrColor = CreateSolidBrush(RGB(config->window.color.r, config->window.color.g, config->window.color.b));
	GetClientRect(hWnd, &rcWindow);
	SelectObject(hdc, backGrColor);
	Rectangle(hdc, config->window.size.x, config->window.size.y, config->window.size.x1, config->window.size.y1);
	for (int i = 0; i <= config->index; i++) {
		HBRUSH brush = CreateSolidBrush(RGB(config->buttons[i].color.r, config->buttons[i].color.g, config->buttons[i].color.b));
		SelectObject(hdc, brush);
		Rectangle(hdc, config->buttons[i].size.x, config->buttons[i].size.y, config->buttons[i].size.x1, config->buttons[i].size.y1);
		rcLine.left = config->buttons[i].size.x;
		rcLine.top = config->buttons[i].size.y;
		rcLine.right = config->buttons[i].size.x1;
		rcLine.bottom = config->buttons[i].size.y1;
		SetBkMode(hdc, TRANSPARENT);
		if (i == curBut) {
			SetTextColor(hdc, RGB(255, 0, 0));
			DrawTextA(hdc, config->buttons[i].name, -1, &rcLine, DT_CENTER | DT_SINGLELINE | DT_VCENTER);
		}
		else {
			SetTextColor(hdc, RGB(255, 255, 255));
			DrawTextA(hdc, config->buttons[i].name, -1, &rcLine, DT_CENTER | DT_SINGLELINE | DT_VCENTER);
		}


	}
	if (enterPressed == 1) {
		return config->buttons[curBut].name;
	}
	else {
		return NULL;
	}
}
void SystemRelease(Config* config) {
	free(config->buttons);
	free(config);
	config = NULL;

}
