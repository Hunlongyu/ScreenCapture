#include "MainWin.h"

static MainWin *mainWin;

MainWin::MainWin()
{
  initWindowSize();
  shotScreen();
  enumDesktopWindow();
  initLayerImg();
  initWindow();
  show();
}

MainWin::~MainWin() {}

void MainWin::init() { mainWin = new MainWin(); }
MainWin *MainWin::get() { return mainWin; }
void MainWin::dispose() { delete mainWin; }

void MainWin::initWindowSize()
{
  x = GetSystemMetrics(SM_XVIRTUALSCREEN);
  y = GetSystemMetrics(SM_YVIRTUALSCREEN);
  w = GetSystemMetrics(SM_CXVIRTUALSCREEN);
  h = GetSystemMetrics(SM_CYVIRTUALSCREEN);
}

void MainWin::shotScreen()
{
  const HDC h_screen = GetDC(nullptr);
  const HDC h_dc = CreateCompatibleDC(h_screen);
  const HBITMAP hBitmap = CreateCompatibleBitmap(h_screen, w, h);
  DeleteObject(SelectObject(h_dc, hBitmap));
  BOOL bRet = BitBlt(h_dc, 0, 0, w, h, h_screen, x, y, SRCCOPY);
  const unsigned int stride = w * 4;
  const unsigned int dataSize = stride * h;
  const auto desktopPixelData = new unsigned char[dataSize];
  BITMAPINFO info = {sizeof(BITMAPINFOHEADER), static_cast<long>(w), 0 - static_cast<long>(h), 1, 32, BI_RGB, dataSize, 0, 0, 0, 0};
  GetDIBits(h_dc, hBitmap, 0, h, desktopPixelData, &info, DIB_RGB_COLORS);
  DeleteDC(h_dc);
  DeleteObject(hBitmap);

  originalImg = new BLImage();
  originalImg->createFromData(w, h, BL_FORMAT_PRGB32, desktopPixelData, stride, BL_DATA_ACCESS_RW, [](void *impl, void *externalData, void *userData) { delete[] externalData; });
}
