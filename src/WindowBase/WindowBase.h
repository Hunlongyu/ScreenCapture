#pragma once

#include "../State.h"
#include "../Utils/Painter.h"
#include <Windows.h>
#include <blend2d.h>
#include <format>

class WindowBase
{
public:
  WindowBase();
  virtual ~WindowBase();

  void show() const;
  void close() const;
  static int getQuitCode();

  int x, y;
  unsigned int w, h;
  HWND hwnd;
  State state = State::start;

  BLContext *paintCtx;
  BLImage *prepareImg;
  BLImage *originalImg;
  bool isDrawing = false;
  unsigned int stride;

  // mouse
  POINT mouseDownPos;
  bool isLeftBtnDown{false};

protected:
  void refresh();
  void initWindow();
  void initLayerImg();

  virtual int onHitTest() { return HTCLIENT; }
  virtual void setCutBox(const int &x1, const int &y1, const int &x2, const int &y2){};
  virtual void drawMaskBox(){};
  virtual void highLightWindowBox(const int &x, const int &y){};

  BLBox cutBox;
  int cutBoxBorderWidth{3};
  int mouseInMaskBoxIndex{-1};

private:
  static LRESULT CALLBACK routeWindowMessage(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
  LRESULT CALLBACK windowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);
  void quitApp(const int &exitCode) const;

  // paint
  bool onPaint();
  BLImage *bottomImg;
  unsigned char *pixelData;
  Painter *painter;

  // mouse
  bool onLeftBtnDown(const int &x, const int &y);
  bool onMouseMove(const int &x, const int &y);
  bool onLeftBtnUp(const int &x, const int &y);

  // save
  void saveClipboard() const;
};