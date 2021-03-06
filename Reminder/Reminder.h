#pragma once

#include "resource.h"
#include <queue>
#include "stdafx.h"

using namespace std;

queue<SYSTEMTIME> date_times;

void start(HWND hWnd) {
	int times[4][2] = { {9, 0}, {11, 59}, {13, 0}, {17, 59} };

	SYSTEMTIME now;
	GetLocalTime(&now);

	for (int i = 0; i < 4; i++) {
		int* time = times[i];
		int hour = time[0];
		int minute = time[1];

		if (hour >= now.wHour && minute >= now.wMinute) {
			SYSTEMTIME time;
			time.wHour = times[i][0];
			time.wMinute = times[i][1];
			date_times.push(time);
		}
	}

	SetTimer(hWnd, 0, 10000, (TIMERPROC)NULL);
}

void tick(HWND hWnd) {
	if (!date_times.empty())
	{
		SYSTEMTIME now;
		GetLocalTime(&now);
		SYSTEMTIME next = date_times.front();

		if (now.wHour >= next.wHour && now.wMinute >= next.wMinute) {
			ShowWindow(hWnd, SHOW_OPENWINDOW);
			date_times.pop();
		}
	}
}

void draw(HDC hdc) {
	HFONT hFont = CreateFont(30, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS,
		CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, VARIABLE_PITCH, TEXT("Segoe UI"));
	SelectObject(hdc, hFont);
	SetTextColor(hdc, RGB(255, 255, 255));
	SetBkColor(hdc, RGB(0x8B, 0xC3, 0x4A));
	RECT rect{ 0, 0, 300, 100 };
	DrawText(hdc, TEXT("Clock"), -1, &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
}
