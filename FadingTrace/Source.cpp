#include "Header.h"
RECT rcClient;
int delta = 0;
TObject player;
TPoint trackMas[TRACK_MAS_SIZE];
int isMoving = 0;
enum KeyState { KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT };
TPoint point(float x, float y) {
	TPoint pt;
	pt.x = x;
	pt.y = y;
	return pt;
}
void WinInit() {
	ObjectInit(&player, INITIAL_POS_X, INITIAL_POS_Y, OBJ_SIZE, OBJ_SIZE);
	MasInit();
}
void MasInit() {
	for (int i = 0; i < TRACK_MAS_SIZE; i++) {
		trackMas[i].x = INITIAL_POS_X;
		trackMas[i].y = INITIAL_POS_Y;
	}
}
void ObjectInit(TObject* obj, float xPos, float yPos, float width, float height) {
	obj->pos = point(xPos, yPos);
	obj->size = point(width, height);
	obj->brush = RGB(R, G, B);
	obj->speed = point(0, 0);
}
void PlayerControl(enum KeyState key) {
	switch (key)
	{
	case KEY_UP:
		player.speed.y = -PLAYER_SPEED;
		break;
	case KEY_DOWN:
		player.speed.y = PLAYER_SPEED;
		break;
	case KEY_LEFT:
		player.speed.x = -PLAYER_SPEED;
		break;
	case KEY_RIGHT:
		player.speed.x = PLAYER_SPEED;
		break;
	}
	if ((player.speed.x != 0) && (player.speed.y != 0))
		player.speed = point(player.speed.x * 0.7, player.speed.y * 0.7);

}
void StartMove(HWND hWnd) {

	if (GetKeyState(VK_UP) < 0) PlayerControl(KEY_UP);
	if (GetKeyState(VK_DOWN) < 0) PlayerControl(KEY_DOWN);
	if (GetKeyState(VK_LEFT) < 0)PlayerControl(KEY_LEFT);
	if (GetKeyState(VK_RIGHT) < 0) PlayerControl(KEY_RIGHT);
	ObjectMove(&player, hWnd);
}

void ObjectMove(TObject* obj, HWND hWnd) {
	TrackInit(obj->pos.x, obj->pos.y);
	GetClientRect(hWnd, &rcClient);
	obj->pos.x += obj->speed.x;
	obj->pos.y += obj->speed.y;
	if (obj->pos.x < rcClient.left || obj->pos.x > rcClient.right - OBJ_SIZE) {
		obj->pos.x -= obj->speed.x;
	}
	if (obj->pos.y < rcClient.top || obj->pos.y > rcClient.bottom - OBJ_SIZE) {
		obj->pos.y -= obj->speed.y;
	}
}
void WinShow(HDC hdc, HWND hWnd) {
	HDC memDC = CreateCompatibleDC(hdc);
	HBITMAP memBM = CreateCompatibleBitmap(hdc, rcClient.right - rcClient.left, rcClient.bottom - rcClient.top);
	SelectObject(memDC, memBM);

	SelectObject(memDC, GetStockObject(DC_BRUSH));
	SetDCBrushColor(memDC, RGB(255, 255, 255));

	GetClientRect(hWnd, &rcClient);
	Rectangle(memDC, rcClient.left, rcClient.top, rcClient.right, rcClient.bottom);
	ObjectShow(player, memDC);
	TrackDraw(memDC, player);
	BitBlt(hdc, 0, 0, rcClient.right - rcClient.left, rcClient.bottom - rcClient.top, memDC, 0, 0, SRCCOPY);
	DeleteDC(memDC);
	DeleteObject(memBM);
}
void ObjectShow(TObject obj, HDC hdc) {
	SelectObject(hdc, GetStockObject(DC_BRUSH));
	SetDCBrushColor(hdc, obj.brush);
	SelectObject(hdc, GetStockObject(DC_PEN));
	SetDCPenColor(hdc, obj.brush);
	Ellipse(hdc, (int)(obj.pos.x), (int)(obj.pos.y), (int)(obj.pos.x + obj.size.x), (int)(obj.pos.y + obj.size.y));
	player.speed.x = 0;
	player.speed.y = 0;
}
void TrackInit(float x, float y) {
	if ((player.speed.x == 0) && (player.speed.y == 0)) {
		if (delta < TRACK_MAS_SIZE - 1) {
			delta++;
		}
		isMoving = 0;
	}
	else {
		if (delta > 0) {
			delta--;
		}
		isMoving = 1;
	}
	if (isMoving == 1) {
		trackMas[TRACK_MAS_SIZE - 1].x = x;
		trackMas[TRACK_MAS_SIZE - 1].y = y;
		for (int i = 0; i < TRACK_MAS_SIZE - 1; i++) {
			trackMas[i].x = trackMas[i + 1].x;
			trackMas[i].y = trackMas[i + 1].y;
		}
	}

}
void TrackDraw(HDC hdc, TObject obj) {
	SelectObject(hdc, GetStockObject(DC_BRUSH));
	SetDCBrushColor(hdc, obj.brush);
	SelectObject(hdc, GetStockObject(DC_PEN));
	SetDCPenColor(hdc, obj.brush);
	for (int i = delta; i < TRACK_MAS_SIZE - 1; i++) {
		Ellipse(hdc, trackMas[i].x + (TRACK_MAS_SIZE - 1 - i) / 2, trackMas[i].y + (TRACK_MAS_SIZE - 1 - i) / 2, trackMas[i].x + obj.size.x - (TRACK_MAS_SIZE - 1 - i) / 2, trackMas[i].y + obj.size.y - (TRACK_MAS_SIZE - 1 - i) / 2);

	}

}









