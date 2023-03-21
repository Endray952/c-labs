// WindowsProject4.cpp : Определяет точку входа для приложения.
//
#define _CRT_SECURE_NO_WARNINGS
#include "framework.h"
#include "WindowsProject4.h"
#include "Menu.h"
#define MAX_LOADSTRING 100

// Глобальные переменные:
Config* config;// = SystemInitialise("Config.txt");
int curBut = 0;
HMENU hMenubar;
int isStopped = 1;
int enterPressed = 0;
HINSTANCE myHin;
int myNCmdShow;
HINSTANCE hInst;                                // текущий экземпляр
WCHAR szTitle[MAX_LOADSTRING];                  // Текст строки заголовка
WCHAR szWindowClass[MAX_LOADSTRING];            // имя класса главного окна

// Отправить объявления функций, включенных в этот модуль кода:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    myHin = hInstance;
    myNCmdShow = nCmdShow;

    // TODO: Разместите код здесь.
    //
    
    // Инициализация глобальных строк
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_WINDOWSPROJECT4, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Выполнить инициализацию приложения:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WINDOWSPROJECT4));

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
    //HBRUSH backGrColor = CreateSolidBrush(RGB(config->window.color.r, config->window.color.g, config->window.color.b));
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WINDOWSPROJECT4));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_WINDOWSPROJECT4);
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

   HWND hWnd = CreateWindowW(szWindowClass, _T("Menu"), WS_SYSMENU,
       0,0,500,500, nullptr, nullptr, hInstance, nullptr);

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
    switch (message)
    {

    case WM_CREATE: 
    {
        hMenubar = CreateMenu();
        AppendMenu(hMenubar, MF_STRING,  1, L"SystemRelease");
        AppendMenu(hMenubar, MF_STRING, 2, L"SystemInitialise");
        AppendMenu(hMenubar, MF_STRING, 3, L"SystemClose");
        SetMenu(hWnd, hMenubar);
        
    }
    break;
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Разобрать выбор в меню:
            switch (wmId)
            {
            case 1:
                 //MessageBoxA(hWnd, "The menu was unloaded", "", MB_OK);
                 if (isStopped != 1) {
                     MessageBoxA(hWnd, "The menu was unloaded", "", MB_OK);
                     SystemRelease(config);
                     isStopped = 1;
                     curBut = 0;
                 }
                 else {
                     MessageBoxA(hWnd, "Nothing to unload", "", MB_OK);
                 }
                 InvalidateRect(hWnd, NULL, TRUE);
                break;
            case 2:              
                config = SystemInitialise("Config.txt");
                isStopped = 0;
                MoveWindow(hWnd, config->window.size.x, config->window.size.y, config->window.size.x1, config->window.size.y1, TRUE);
                InvalidateRect(hWnd, NULL, TRUE);
                break;
            case 3:
                DestroyWindow(hWnd);
                break;
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
            // TODO: Добавьте сюда любой код прорисовки, использующий HDC...

            if (isStopped != 1) {
                char* res = SystemUpdate(config, hdc, hWnd, curBut, enterPressed);
                if (res != NULL) {
                    MessageBoxA(hWnd, res, "", MB_OK);
                    enterPressed = 0;
                }
            }
            else {
                RECT rc;
                GetClientRect(hWnd, &rc);
                HBRUSH brush = CreateSolidBrush(RGB(255,255,255));
                SelectObject(hdc, brush);
                Rectangle(hdc, rc.left, rc.top, rc.right, rc.bottom);
            }
            EndPaint(hWnd, &ps);

        }
        break;
    case WM_KEYDOWN:
    {
        switch (wParam) {
        case VK_UP:
            if (isStopped != 1) {
                curBut--;
                if (curBut < 0) {
                    curBut = 0;
                }
                InvalidateRect(hWnd, NULL, TRUE);
            }
            break;

        case VK_DOWN:  
            if (isStopped != 1) {
                curBut++;
                if (curBut > config->index) {
                    curBut = config->index;
                }

                InvalidateRect(hWnd, NULL, TRUE);
            }
            break;
        case VK_RETURN:
            if (isStopped != 1) {
               // MessageBoxA(hWnd, conf1->buttons[curBut].name, "", MB_OK);
                enterPressed = 1;
                InvalidateRect(hWnd, NULL, TRUE);
            }
            break;       
        }
    }
    break;
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
