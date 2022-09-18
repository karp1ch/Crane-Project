#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "Resource.h"

// ============================================
RECT rct;
HWND hwndButton;


struct cords
{
	int x1, y1, x2, y2;
} chain;

struct object : cords {
	bool isSpawned;
	bool isTaken;
	int fallSpeed;
	bool isAuto;
}triangle, square, circle;


void ChainInit() {
	chain.x2 = chain.x1 = 350;
	chain.y1 = 161;
	chain.y2 =	chain.y1 + 200;

}



void ObjInit() {
	circle.isSpawned = square.isSpawned = triangle.isSpawned = 0;
	circle.isTaken = square.isTaken = triangle.isTaken = 0;

													// places where objects spawn
	square.x1 = RECTANGLE_LEFT + 5;
	square.x2 = square.x1 + 20;
	square.y1 = RECTANGLE_TOP - 100;
	square.y2 = square.y1 + 20;
	square.fallSpeed = 1;


	circle.x1 = RECTANGLE_RIGHT + 10 + 5 - 20;
	circle.x2 = circle.x1 + 20;
	circle.y1 = RECTANGLE_TOP - 100;
	circle.y2 = circle.y1 + 20;
	circle.fallSpeed = 1;

	triangle.x1 = RECTANGLE_RIGHT + 60 + 10 + 25 - 50;
	triangle.x2 = RECTANGLE_RIGHT + 60 + 10 + 25 - 10 - 50;
	triangle.y1 = RECTANGLE_TOP - 100;
	triangle.y2 = triangle.y1 + 20;
	triangle.fallSpeed = 1;
}

void ObjectGravitation() {
	if (square.isSpawned && square.y2 <= EARTH_LEVEL && !square.isTaken && !((square.y2 + square.fallSpeed == triangle.y1 && ((triangle.x1 >= square.x1 && triangle.x1 <= square.x2) || (triangle.x2 >= square.x1 && triangle.x2 <= square.x2)) ) || square.y2 + square.fallSpeed == circle.y1 && ((circle.x1 >= square.x1 && circle.x1 <= square.x2) || (circle.x2 >= square.x1 && circle.x2 <= square.x2))  )) {
		square.y1 += square.fallSpeed;
		square.y2 += square.fallSpeed;
	}
	if (circle.isSpawned && circle.y2 <= EARTH_LEVEL && !circle.isTaken && !((circle.y2 + circle.fallSpeed == square.y1 && ((square.x1 >= circle.x1 && square.x1 <= circle.x2) || (square.x2 >= circle.x1 && square.x2 <= circle.x2)) ) || circle.y2 + circle.fallSpeed == triangle.y1 && ((triangle.x1 >= circle.x1 && triangle.x1 <= circle.x2) || (triangle.x2 >= circle.x1 && triangle.x2 <= circle.x2)))) {
		circle.y1 += circle.fallSpeed;
		circle.y2 += circle.fallSpeed;
	}
	if (triangle.isSpawned && triangle.y2 <= EARTH_LEVEL && !triangle.isTaken && !( (triangle.y2 + triangle.fallSpeed == square.y1 && ((square.x1 >= triangle.x2 && square.x1 <= triangle.x1 + 10) || (square.x2 >= triangle.x2 && square.x2 <= triangle.x1 + 10)))|| triangle.y2 + triangle.fallSpeed == circle.y1 && ((circle.x1 >=triangle.x2 && circle.x1 <= triangle.x1 +10) || (circle.x2 >= triangle.x2 && circle.x2 <= triangle.x1 + 10))  )) {
		triangle.y1 += triangle.fallSpeed;
		triangle.y2 += triangle.fallSpeed;
	}



	if (square.isTaken) {
		square.x1 = chain.x1 - 7;
		square.x2 = square.x1 + 20;
		square.y1 = chain.y2 + 7;
		square.y2 = square.y1 + 20;
	}
	if (circle.isTaken) {
		circle.x1 = chain.x1 - 7;
		circle.x2 = circle.x1 + 20;
		circle.y1 = chain.y2 + 7;
		circle.y2 = circle.y1 + 20;
	}
	if (triangle.isTaken) {
		triangle.x1 = chain.x1 + 3;
		triangle.x2 = triangle.x1 - 10;
		triangle.y1 = chain.y2 + 7;
		triangle.y2 = triangle.y1 + 20;
	}

	
}

bool Taking() {
	// crain take the object or loose the object
	for (int i = -2; i < 4; i++) {
		if (chain.y2 + 7 + i == square.y1 && chain.x2 - 10 <= square.x1 && chain.x2 + 10 >= square.x1 && !square.isTaken) {
			square.isTaken++;
			return 0;
		}
		else if (square.isTaken) {
			square.isTaken = 0;
			return 0;
		}
		if (chain.y2 + 7 + i == circle.y1 && chain.x2 - 10 <= circle.x1 && chain.x2 + 10 >= circle.x1 && !circle.isTaken) {
			circle.isTaken++;
			return 0;
		}
		else if (circle.isTaken) {
			circle.isTaken = 0;
			return 0;
		}
		if (chain.y2 + 7 + i == triangle.y1 && chain.x2 - 10 <= triangle.x1 && chain.x2 + 10 >= triangle.x1 && !triangle.isTaken) {
			triangle.isTaken++;
			return 0;
		}
		else if (triangle.isTaken) {
			triangle.isTaken = 0;
			return 0;
		}

	}
}



void Paint(HDC hdc) {
	ObjectGravitation();

	HDC memDC = CreateCompatibleDC(hdc);																		// creating buffer for animation
	HBITMAP memBM = CreateCompatibleBitmap(hdc, rct.right - rct.left, rct.bottom - rct.top);
	SelectObject(memDC, memBM);
	
	
	

	SelectObject(memDC, GetStockObject(DC_BRUSH));																// clear background
	SetDCBrushColor(memDC, RGB(255, 255, 255));
	Rectangle(memDC, -1, -1, 650, 500);


	SelectObject(memDC, GetStockObject(DC_PEN));
	SetDCPenColor(memDC, RGB(0, 0, 0));
	SelectObject(memDC, GetStockObject(DC_BRUSH));
	SetDCBrushColor(memDC, RGB(47, 54, 64));



	HBITMAP hBmp = (HBITMAP)LoadImage(NULL, L"D:\\ownprojects\\cplusplus\\crane\\data\\crane.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);		// bitmap
	HDC bmpDC = CreateCompatibleDC(memDC);
	SelectObject(bmpDC, hBmp);
	BitBlt(memDC, 25, 82, crane_width, crane_height, bmpDC, 0, 0, SRCCOPY);
	DeleteDC(bmpDC);
	DeleteObject(hBmp);



	MoveToEx(memDC, chain.x1, chain.y1, NULL);					// left vertical line
	LineTo(memDC, chain.x2, chain.y2);

	MoveToEx(memDC, chain.x1 + 5, chain.y1, NULL);				// right vertical line
	LineTo(memDC, chain.x2 + 5, chain.y2);
	
	MoveToEx(memDC, chain.x1, chain.y2, NULL);				// magnet
	LineTo(memDC, chain.x2 + 6, chain.y2);
	MoveToEx(memDC, chain.x1, chain.y2, NULL);				// magnet
	LineTo(memDC, chain.x2 - 10, chain.y2 + 7);
	MoveToEx(memDC, chain.x1 + 5, chain.y2, NULL);				// magnet
	LineTo(memDC, chain.x2 + 15, chain.y2 + 7);
	MoveToEx(memDC, chain.x2 - 10, chain.y2 + 7, NULL);				// magnet
	LineTo(memDC, chain.x2 + 15, chain.y2 + 7);

	Rectangle(memDC, RECTANGLE_LEFT, RECTANGLE_TOP, RECTANGLE_RIGHT, RECTANGLE_BOTTOM);						// square
	Arc(memDC, RECTANGLE_RIGHT + 10, RECTANGLE_TOP, RECTANGLE_RIGHT + 60, RECTANGLE_BOTTOM, 0, 0, 0, 0);	// circle
	
	// triangle
	MoveToEx(memDC, RECTANGLE_RIGHT + 60 + 10 + 25, RECTANGLE_TOP, NULL);				
	LineTo(memDC, RECTANGLE_RIGHT + 60 + 10, RECTANGLE_BOTTOM);
	MoveToEx(memDC, RECTANGLE_RIGHT + 60 + 10 + 25, RECTANGLE_TOP, NULL);
	LineTo(memDC, RECTANGLE_RIGHT + 60 + 10 + 25 + 25, RECTANGLE_BOTTOM);
	MoveToEx(memDC, RECTANGLE_RIGHT + 60 + 10, RECTANGLE_BOTTOM, NULL);
	LineTo(memDC, RECTANGLE_RIGHT + 60 + 10 + 25 + 25, RECTANGLE_BOTTOM);


	if (square.isSpawned)
		Rectangle(memDC, square.x1, square.y1, square.x2, square.y2); // square
	if (circle.isSpawned)
		Arc(memDC, circle.x1, circle.y1, circle.x2, circle.y2, 0, 0, 0, 0); // circle
	if (triangle.isSpawned) {
		MoveToEx(memDC, triangle.x1, triangle.y1, NULL);	// triangle
		LineTo(memDC, triangle.x2, triangle.y2);
		MoveToEx(memDC, triangle.x1, triangle.y1, NULL);
		LineTo(memDC, triangle.x1 + 10, triangle.y2);
		MoveToEx(memDC, triangle.x2, triangle.y2, NULL);
		LineTo(memDC, triangle.x1 + 10, triangle.y2);
	}

	BitBlt(hdc, 0, 0, rct.right - rct.left, rct.bottom - rct.top, memDC, 0, 0, SRCCOPY);
	DeleteDC(memDC);
	DeleteObject(memBM);
}



LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam) {
	if (message == WM_DESTROY)
		PostQuitMessage(0);
	else if (message == WM_SIZE)
		GetClientRect(hwnd, &rct);
	else if (message == WM_KEYDOWN && wparam == 65 && chain.x1 > 180) {
		--chain.x2;
		--chain.x1;
	}
	else if (message == WM_KEYDOWN && wparam == 68 && chain.x2 < 476) {
		++chain.x2;
		++chain.x1;
	}
	else if (message == WM_KEYDOWN && wparam == 87 && chain.y2 > 180) {
		--chain.y2;
	}
	else if (message == WM_KEYDOWN && wparam == 83 && chain.y2 < EARTH_LEVEL - 26) {
		++chain.y2;
	}
	else if (message == WM_LBUTTONDOWN && LOWORD(lparam) >= RECTANGLE_LEFT && LOWORD(lparam) <= RECTANGLE_RIGHT && HIWORD(lparam) >= RECTANGLE_TOP && HIWORD(lparam) <= RECTANGLE_BOTTOM) {
		if (!square.isSpawned) {

			++square.isSpawned;
		}
	}
	else if (message == WM_LBUTTONDOWN && LOWORD(lparam) >= RECTANGLE_RIGHT + 10 && LOWORD(lparam) <= RECTANGLE_RIGHT + 60 && HIWORD(lparam) >= RECTANGLE_TOP && HIWORD(lparam) <= RECTANGLE_BOTTOM) {
		if (!circle.isSpawned) {
			++circle.isSpawned;
		}
	}
	else if (message == WM_LBUTTONDOWN && LOWORD(lparam) >= RECTANGLE_RIGHT + 60 + 10 && LOWORD(lparam) <= RECTANGLE_RIGHT + 60 + 10 + 50 && HIWORD(lparam) >= RECTANGLE_TOP && HIWORD(lparam) <= RECTANGLE_BOTTOM) {
		if (!triangle.isSpawned) {
			++triangle.isSpawned;
		}
	}
	else if (message == WM_KEYDOWN && wparam == 27) {
		square.isSpawned = circle.isSpawned = triangle.isSpawned = 0;
		ObjInit();
	}
	else if (message == WM_KEYDOWN && wparam == 32) {
		Taking();
	}
	return DefWindowProcA(hwnd, message, wparam, lparam);
}


int main(HINSTANCE hInstance, HINSTANCE, PSTR, INT iCmdShow)
{
	WNDCLASSA wcl;	
	memset(&wcl, 0, sizeof(WNDCLASSA));
		wcl.lpszClassName = "my Window"; 
		wcl.lpfnWndProc = WndProc; 
		wcl.hCursor = LoadCursor(NULL, IDC_ARROW);
		wcl.hInstance = hInstance;
		RegisterClassA(&wcl); 


	HWND hwnd; 
	HINSTANCE hInst = hInstance;
	hwnd = CreateWindowA("my Window", "Crane Project", WS_OVERLAPPEDWINDOW, 10, 10, Xsize, Ysize, NULL, NULL, hInstance, NULL); 
	
	
	ShowWindow(hwnd, SW_SHOWNORMAL); 
	UpdateWindow(hwnd);


	// ===================================================== animation

	HDC hdc = GetDC(hwnd);

	// =====================================================
	ChainInit();
	ObjInit();


	MSG msg;
	
	

	while (true) {
		if (PeekMessageA(&msg, NULL, 0, 0, PM_REMOVE)) {
			if (msg.message == WM_QUIT)
				break;
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else {
			ObjectGravitation();
			Paint(hdc);
		}

	}

}

