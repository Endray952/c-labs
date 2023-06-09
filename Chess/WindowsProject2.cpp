// WindowsProject2.cpp : Определяет точку входа для приложения.
//
#include <stdio.h>
#include <string.h>
#include "stdafx.h"
#include "WindowsProject2.h"
int click_counter = 0;
int prevX, prevY;
int width;
int height;
int sx;							
int sy;
int cell_width;		
int cell_height;
#define MAX_LOADSTRING 100

// Глобальные переменные:
HINSTANCE hInst;                                // текущий экземпляр
WCHAR szTitle[MAX_LOADSTRING];                  // Текст строки заголовка
WCHAR szWindowClass[MAX_LOADSTRING];            // имя класса главного окна

// Отправить объявления функций, включенных в этот модуль кода:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

void CalculateBoardParams(HDC hdc, const RECT& rc) {
	// Вычисление координат отрисовки доски такими, что
	// доска всегда квадратная и в центре окна
	 width = rc.right - rc.left + 1;
	 height = rc.bottom - rc.top + 1;
	 sx = 0;							
     sy = 0;							
	if (width > height) {				
		sx = (width - height) / 2;
		width = height;
	}
	else {
		sy = (height - width) / 2;
		height = width;
	}
	 cell_width = width / 10;		
	 cell_height = height / 10;     
}
void DrawSolution(HDC hdc, WORD xPos, WORD yPos, const RECT& rc)
{
	HBRUSH White = CreateSolidBrush(RGB(255, 145, 192));
	HPEN Pen = CreatePen(PS_SOLID, 3, RGB(0, 255, 0));
	HBRUSH Green = CreateSolidBrush(RGB(0, 255, 0));
	HPEN ExtraPen = CreatePen(PS_SOLID, 3, RGB(255, 0, 0));
	CalculateBoardParams(hdc, rc);
	for (int i = 0; i < 8; ++i) {
		for (int j = 0; j < 8; ++j) {
			int x = sx + (i + 1) * cell_width;
			int y = sy + (j + 1) * cell_height;
			if (click_counter == 0) {
				prevX = x;
				prevY = y;
			}
			if ((xPos > x && xPos < x + cell_width) && (yPos > y && yPos < y + cell_width)) { // Определяем нажатую клетку
				SelectObject(hdc, White);
				Ellipse(hdc, x, y, x + cell_width, y + cell_height);
				if (click_counter == 1) {
					if (x == prevX && y == prevY) {
						click_counter--;
					}
					else if (x == prevX) {
						MoveToEx(hdc, prevX + cell_width / 2, prevY + cell_height / 2, NULL);
						SelectObject(hdc, Pen);
						LineTo(hdc, x + cell_width / 2, y + cell_height / 2);
						LineTo(hdc, x + cell_width / 2 - 5, (prevY - y > 0) ? y + cell_height / 2 + 10 : y + cell_height / 2 - 10);
						//LineTo(hdc, x + cell_width / 2, y + cell_height / 2);
						MoveToEx(hdc, x + cell_width / 2, y + cell_height / 2, NULL);
						LineTo(hdc, x + cell_width / 2 + 5, (prevY - y > 0) ? y + cell_height / 2 + 10 : y + cell_height / 2 - 10);
					}
					else if (y == prevY) {
						MoveToEx(hdc, prevX + cell_width / 2, prevY + cell_height / 2, NULL);
						SelectObject(hdc, Pen);
						LineTo(hdc, x + cell_width / 2, y + cell_height / 2);
						MoveToEx(hdc, x + cell_width / 2, y + cell_height / 2, NULL); 
						LineTo(hdc, (prevX - x > 0) ? x + cell_width / 2 + 10 : x + cell_width / 2 - 10, y + cell_height / 2 - 5);
						MoveToEx(hdc, x + cell_width / 2, y + cell_height / 2, NULL);
						LineTo(hdc, (prevX - x > 0) ? x + cell_width / 2 + 10 : x + cell_width / 2 - 10, y + cell_height / 2 + 5);
					}
					else {
						MoveToEx(hdc, prevX + cell_width / 2, prevY + cell_height / 2, NULL);
						SelectObject(hdc, Pen);
						LineTo(hdc, x + cell_width / 2, prevY + cell_height / 2);

						Ellipse(hdc, x + cell_width / 2-10, prevY + cell_height / 2-10, x + cell_width / 2+10, prevY + cell_height / 2+10);
						LineTo(hdc, x + cell_width / 2, y + cell_height / 2);

						MoveToEx(hdc, x + cell_width / 2, y + cell_height / 2, NULL); // рисую зеленую стрелку
						LineTo(hdc, x + cell_width / 2 - 5,(prevY-y >0) ? y + cell_height / 2 + 10 : y + cell_height / 2 - 10);
						MoveToEx(hdc, x + cell_width / 2, y + cell_height / 2, NULL);
						LineTo(hdc, x + cell_width / 2 + 5, (prevY - y > 0) ? y + cell_height / 2 + 10 : y + cell_height / 2 - 10);

						MoveToEx(hdc, prevX + cell_width / 2, prevY + cell_height / 2, NULL);
						SelectObject(hdc, ExtraPen);
						LineTo(hdc, prevX + cell_width / 2, y + cell_height / 2);

						Ellipse(hdc, prevX + cell_width / 2 - 10, y + cell_height / 2 - 10, prevX + cell_width / 2 + 10, y + cell_height / 2 + 10);
						LineTo(hdc, x + cell_width / 2, y + cell_height / 2);

						MoveToEx(hdc, x + cell_width / 2, y + cell_height / 2, NULL); // рисую Красную стрелку
						LineTo(hdc,(prevX-x > 0)? x + cell_width / 2 + 10 : x + cell_width / 2 - 10,  y + cell_height / 2 - 5);
						MoveToEx(hdc, x + cell_width / 2, y + cell_height / 2, NULL);
						LineTo(hdc, (prevX - x > 0) ? x + cell_width / 2 + 10 : x + cell_width / 2 - 10, y + cell_height / 2 + 5);
					}
				}
				DeleteObject(White);
				DeleteObject(Pen);
				DeleteObject(ExtraPen);
				DeleteObject(Green);
				return;
			}


		}
	}
	click_counter--;
	DeleteObject(White);
}
void DrawBoard(HDC hdc, const RECT& rc)
{

	HBRUSH board = CreateSolidBrush(RGB(240, 240, 240));	
	HBRUSH white = CreateSolidBrush(RGB(255, 255, 192));	
	HBRUSH black = CreateSolidBrush(RGB(0, 0, 0));			

	CalculateBoardParams(hdc, rc);
	
	// Отрисовка фона доски
	SelectObject(hdc, board);
	Rectangle(hdc, sx + 1, sy + 1, sx + width - 2, sy + height - 2);
	// Отрисовка всех клеток доски
	for (int i = 0; i < 8; ++i) {
		for (int j = 0; j < 8; ++j) {

			// Выбор цвета клеточки
			SelectObject(hdc, ((i ^ j) & 1) ? black : white); // черный цвет, если строка и столбец разной четности

			// Отрисовка одной клеточки
			int x = sx + (i + 1) * cell_width;
			int y = sy + (j + 1) * cell_height;
			Rectangle(hdc, x, y, x + cell_width, y + cell_height);
		}
	}

	// Установка прозрачного фона у текста
	SetBkMode(hdc, TRANSPARENT);

	// Отрисовка обозначений по краям доски
	RECT rcLetter;
	char letter;
	for (int i = 0; i < 8; ++i) {
		// Горизонтальные A-H
		letter = i + 'A';
		rcLetter.left = sx + (i + 1) * cell_width;
		rcLetter.right = rcLetter.left + cell_width;
		rcLetter.top = sy;
		rcLetter.bottom = rcLetter.top + cell_height;
		DrawText(hdc, &letter, 1, &rcLetter, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		rcLetter.top = sy + 9 * cell_height;
		rcLetter.bottom = rcLetter.top + cell_height;
		DrawText(hdc, &letter, 1, &rcLetter, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

		// Вертикальные 1-8
		letter = i + '1';
		rcLetter.left = sx;
		rcLetter.right = rcLetter.left + cell_width;
		rcLetter.top = sy + (8 - i) * cell_height;
		rcLetter.bottom = rcLetter.top + cell_height;
		DrawText(hdc, &letter, 1, &rcLetter, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		rcLetter.left = sx + 9 * cell_width;
		rcLetter.right = rcLetter.left + cell_width;
		DrawText(hdc, &letter, 1, &rcLetter, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	}
	HBRUSH red = CreateSolidBrush(RGB(0, 240, 0));
	SelectObject(hdc, red);
	//SelectObject(hdc, old_brush);
	DeleteObject(board);
	DeleteObject(white);
	DeleteObject(black);
	
}
int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Разместите код здесь.

    // Инициализация глобальных строк
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_WINDOWSPROJECT2, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Выполнить инициализацию приложения:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WINDOWSPROJECT2));

    MSG msg;

    // Цикл основного сообщения:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  ФУНКЦИЯ: MyRegisterClass()
//
//  ЦЕЛЬ: Регистрирует класс окна.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WINDOWSPROJECT2));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_WINDOWSPROJECT2);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   ФУНКЦИЯ: InitInstance(HINSTANCE, int)
//
//   ЦЕЛЬ: Сохраняет маркер экземпляра и создает главное окно
//
//   КОММЕНТАРИИ:
//
//        В этой функции маркер экземпляра сохраняется в глобальной переменной, а также
//        создается и выводится главное окно программы.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Сохранить маркер экземпляра в глобальной переменной

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, 700, 700, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  ФУНКЦИЯ: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  ЦЕЛЬ: Обрабатывает сообщения в главном окне.
//
//  WM_COMMAND  - обработать меню приложения
//  WM_PAINT    - Отрисовка главного окна
//  WM_DESTROY  - отправить сообщение о выходе и вернуться
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Разобрать выбор в меню:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);           
			RECT rcClient; 
			GetClientRect(hWnd, &rcClient); //  размеры окна
			DrawBoard(hdc, rcClient);		
            EndPaint(hWnd, &ps);
        }
        break;
	case WM_LBUTTONDOWN:
	{
		WORD xPos, yPos;
		xPos = LOWORD(lParam);
		yPos = HIWORD(lParam);
	    hdc = GetDC(hWnd);
		RECT rcClient; 
		GetClientRect(hWnd, &rcClient); // размеры окна
		DrawSolution(hdc, xPos, yPos, rcClient);
		if (click_counter == 2) {			
			DrawBoard(hdc, rcClient);
			click_counter = 0;
			DrawSolution(hdc, xPos, yPos, rcClient);
		}
		click_counter++;
		ReleaseDC(hWnd, hdc);
		break;
	}
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Обработчик сообщений для окна "О программе".
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
