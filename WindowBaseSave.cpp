#include "Util.h"
#include "WindowBase.h"
#include <Commctrl.h>
#include <Shobjidl.h>
#include <atlbase.h>
#include <format>

void WindowBase::saveClipboard() const
{
  const int x = this->x + static_cast<int>(cutBox.x0) + cutBoxBorderWidth / 2;
  const int y = this->y + static_cast<int>(cutBox.y0) + cutBoxBorderWidth / 2;
  const int w = static_cast<int>(cutBox.x1) - static_cast<int>(cutBox.x0) - cutBoxBorderWidth;
  const int h = static_cast<int>(cutBox.y1) - static_cast<int>(cutBox.y0) - cutBoxBorderWidth;
  const HDC ScreenDC = ::GetDC(nullptr);
  const HDC hMemDC = CreateCompatibleDC(ScreenDC);
  HBITMAP hBitmap = CreateCompatibleBitmap(ScreenDC, w, h);
  const HBITMAP hOldBitmap = static_cast<HBITMAP>(SelectObject(hMemDC, hBitmap));
  StretchBlt(hMemDC, 0, 0, w, h, ScreenDC, x, y, w, h, SRCCOPY);
  hBitmap = static_cast<HBITMAP>(SelectObject(hMemDC, hOldBitmap));
  DeleteDC(hMemDC);
  DeleteObject(hOldBitmap);
  OpenClipboard(hwnd);
  EmptyClipboard();
  SetClipboardData(CF_BITMAP, hBitmap);
  CloseClipboard();
  ReleaseDC(nullptr, ScreenDC);
  quitApp(1);
}
