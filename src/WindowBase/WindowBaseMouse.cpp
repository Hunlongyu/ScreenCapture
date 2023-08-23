#include "Util.h"
#include "WindowBase.h"
#include <chrono>

bool WindowBase::onLeftBtnDown(const int &x, const int &y)
{
  mouseDownPos.x = static_cast<LONG>(x);
  mouseDownPos.y = static_cast<LONG>(y);
  isLeftBtnDown = true;
  return false;
}

bool WindowBase::onMouseMove(const int &x, const int &y)
{
  if (isLeftBtnDown) {
    setCutBox(x, y, mouseDownPos.x, mouseDownPos.y);
  }
  else {
    ChangeCursor(IDC_CROSS);
    highLightWindowBox(x, y);
  }
  return false;
}

bool WindowBase::onLeftBtnUp(const int &x, const int &y)
{

  isLeftBtnDown = false;
  saveClipboard();
  return false;
}
