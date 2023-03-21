#pragma once
#include "framework.h"
#include "Task_5_1.h"
#define INITIAL_POS_X 100
#define INITIAL_POS_Y 100
#define OBJ_SIZE 30
#define TRACK_MAS_SIZE OBJ_SIZE
#define PLAYER_SPEED 4
#define R 0
#define G 255
#define B 0
typedef struct SPoint {
    float x, y;
}TPoint;
typedef struct SObject {
    TPoint pos;
    TPoint size;
    COLORREF brush;
    TPoint speed;
}TObject;

void TrackDraw(HDC hdc, TObject obj);
void ObjectInit(TObject* obj, float xPos, float yPos, float width, float height);
void ObjectShow(TObject obj, HDC hdc);
void WinInit();
void ObjectMove(TObject* obj, HWND hWnd);
void PlayerControl(enum KeyState key);
void WinShow(HDC hdc, HWND hWnd);
void StartMove(HWND hWnd);
void TrackInit(float x, float y);
void MasInit();