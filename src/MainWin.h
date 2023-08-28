#pragma once

#include "WindowBase/WindowBase.h"
#include <blend2d.h>
#include <vector>

class MainWin : public WindowBase
{
public:
  ~MainWin();

  static void init();
  static MainWin *get();
  static void dispose();

  void set_filename(const std::wstring &filename);

private:
  MainWin();
  void initWindowSize();
  void shotScreen();

  void enumDesktopWindow();
  void highLightWindowBox(const int &x, const int &y) override;
  std::vector<BLBox> desktopWindowBoxes;

  void setCutBox(const int &x1, const int &y1, const int &x2, const int &y2) override;
  void drawMaskBox() override;
  BLBox maskBoxes[8];
  BLPoint dragStartCutBoxStartPos;
  BLPoint dragStartCutBoxEndPos;
};
