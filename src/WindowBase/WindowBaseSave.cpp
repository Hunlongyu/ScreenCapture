#include "../Utils/Util.h"
#include "WindowBase.h"
#include <Commctrl.h>
#include <Shobjidl.h>
#include <atlbase.h>
#include <format>
#include <string>

char *ConvertWStringToCharPtr(const std::wstring &wstr)
{
  const int bufferSize = WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(), -1, nullptr, 0, nullptr, nullptr);
  const auto char_ptr = new char[bufferSize];
  WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(), -1, char_ptr, bufferSize, nullptr, nullptr);
  return char_ptr;
}

void WindowBase::saveFile() const
{
  const auto w = cutBox.x1 - cutBox.x0;
  const auto h = cutBox.y1 - cutBox.y0;
  BLImage imgSave(w, h, BL_FORMAT_PRGB32);
  paintCtx->begin(imgSave);
  paintCtx->blitImage(BLPoint(0, 0), *originalImg, BLRectI(static_cast<int>(cutBox.x0), static_cast<int>(cutBox.y0), static_cast<int>(w), static_cast<int>(h)));
  paintCtx->end();
  const auto path = ConvertWStringToCharPtr(filename);
  const auto res = imgSave.writeToFile(path);
  delete[] path;
  if (res != BL_SUCCESS) {
    quitApp(0);
  }
  quitApp(2);
}

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
