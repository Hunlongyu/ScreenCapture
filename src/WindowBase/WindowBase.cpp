#include "WindowBase.h"
#include "../Utils/Util.h"
#include <dwmapi.h>
#include <windowsx.h>

static int mainWinQuitCode = 0;

LRESULT CALLBACK WindowBase::routeWindowMessage(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
  if (msg == WM_NCCREATE) {
    const CREATESTRUCT *pCS = reinterpret_cast<CREATESTRUCT *>(lParam);
    LPVOID pThis = pCS->lpCreateParams;
    SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pThis));
  }
  const auto obj = reinterpret_cast<WindowBase *>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
  if (obj) {
    if (msg == WM_CLOSE) {
      delete obj;
    }
    else {
      return obj->windowProc(hWnd, msg, wParam, lParam);
    }
  }
  return DefWindowProc(hWnd, msg, wParam, lParam);
}

WindowBase::WindowBase() {}

WindowBase::~WindowBase()
{
  delete paintCtx;
  delete originalImg;
  delete prepareImg;
  delete bottomImg;
  delete painter;
}

void WindowBase::quitApp(const int &exitCode) const
{
  mainWinQuitCode = exitCode;
  CloseWindow(hwnd);
  PostQuitMessage(0);
}

int WindowBase::getQuitCode() { return mainWinQuitCode; }

void WindowBase::initWindow()
{
  static int num = 0;
  const std::wstring class_name = std::format(L"ScreenCapture{}", num++);
  const auto h_instance = GetModuleHandle(nullptr);
  WNDCLASSEX wcx{};
  wcx.cbSize = sizeof(wcx);
  wcx.style = CS_HREDRAW | CS_VREDRAW;
  wcx.lpfnWndProc = &WindowBase::routeWindowMessage;
  wcx.cbWndExtra = sizeof(WindowBase *);
  wcx.hInstance = h_instance;
  wcx.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
  wcx.hCursor = LoadCursor(nullptr, IDC_ARROW);
  wcx.hbrBackground = reinterpret_cast<HBRUSH>((COLOR_WINDOW + 1));
  wcx.lpszClassName = class_name.c_str();
  if (!RegisterClassEx(&wcx)) {
    MessageBox(nullptr, L"注册窗口类失败", L"系统提示", NULL);
    return;
  }
  this->hwnd = CreateWindowEx(WS_EX_NOREDIRECTIONBITMAP, wcx.lpszClassName, wcx.lpszClassName, WS_OVERLAPPEDWINDOW, x, y, w, h, nullptr, nullptr, h_instance, static_cast<LPVOID>(this));
  constexpr BOOL attr = TRUE;
  DwmSetWindowAttribute(hwnd, DWMWA_TRANSITIONS_FORCEDISABLED, &attr, sizeof(attr)); // 移除窗口打开与关闭时的动画效果
  SetWindowPos(hwnd, nullptr, 0, 0, 0, 0, SWP_NOZORDER | SWP_NOOWNERZORDER | SWP_NOMOVE | SWP_NOSIZE | SWP_FRAMECHANGED);
  painter = new Painter(hwnd);
}

void WindowBase::show() const
{
  ShowWindow(hwnd, SW_SHOW);
  UpdateWindow(hwnd);
  ChangeCursor(IDC_ARROW);
}

void WindowBase::close() const { CloseWindow(hwnd); }

LRESULT CALLBACK WindowBase::windowProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
  switch (msg) {
  case WM_NCCALCSIZE: {
    if (wParam == TRUE) {
      return false;
    }
    break;
  }
  case WM_NCHITTEST: {
    return onHitTest();
  }
  case WM_SETCURSOR: {
    return true;
  }
  case WM_ERASEBKGND: {
    return true;
  }
  case WM_LBUTTONDOWN: {
    return onLeftBtnDown(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
  }
  case WM_LBUTTONUP: {
    return onLeftBtnUp(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
  }
  case WM_MOUSEMOVE: {
    return onMouseMove(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
  }
  case WM_SIZE: {
    if (painter) {
      painter->on_resize(hWnd, LOWORD(lParam), HIWORD(lParam));
      refresh();
    }
    return false;
  }
  }
  return DefWindowProcW(hWnd, msg, wParam, lParam);
}