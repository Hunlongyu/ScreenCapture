﻿#include "MainWin.h"

void MainWin::enumDesktopWindow()
{
  EnumWindows(
      [](HWND hwnd, LPARAM lparam) {
        if (!hwnd)
          return TRUE;
        if (!IsWindowVisible(hwnd))
          return TRUE;
        if (IsIconic(hwnd))
          return TRUE;
        if (GetWindowTextLength(hwnd) < 1)
          return TRUE;
        auto self = (MainWin *)lparam;
        RECT rect;
        GetWindowRect(hwnd, &rect);
        if (rect.right - rect.left <= 6 || rect.bottom - rect.top <= 6) {
          return TRUE;
        }
        BLBox item(rect.left - self->x, rect.top - self->y, rect.right - self->x, rect.bottom - self->y);
        self->desktopWindowBoxes.push_back(std::move(item));
        return TRUE;
      },
      (LPARAM)this);
}

void MainWin::highLightWindowBox(const int &x, const int &y)
{
  for (size_t i = 0; i < desktopWindowBoxes.size(); i++) {
    if (desktopWindowBoxes[i].contains(x, y)) {
      setCutBox(desktopWindowBoxes[i].x0, desktopWindowBoxes[i].y0, desktopWindowBoxes[i].x1, desktopWindowBoxes[i].y1);
      break;
    }
  }
}