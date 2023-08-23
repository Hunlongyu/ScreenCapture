#include "MainWin.h"
#include "Utils/Util.h"

void MainWin::drawMaskBox()
{
  paintCtx->setFillStyle(BLRgba32(0, 0, 0, 180));
  paintCtx->fillBoxArray(maskBoxes, 8);
  paintCtx->setStrokeStyle(BLRgba32(22, 119, 255));
  paintCtx->setStrokeWidth(cutBoxBorderWidth);
  paintCtx->strokeBox(cutBox);
}

void MainWin::setCutBox(const int &x1, const int &y1, const int &x2, const int &y2)
{
  SetBoxByPos(cutBox, x1, y1, x2, y2);
  maskBoxes[0].x0 = 0;
  maskBoxes[0].x1 = cutBox.x0;
  maskBoxes[1].x0 = cutBox.x0;
  maskBoxes[1].x1 = cutBox.x1;
  maskBoxes[2].x0 = cutBox.x1;
  maskBoxes[2].x1 = w;
  maskBoxes[3].x0 = cutBox.x1;
  maskBoxes[3].x1 = w;
  maskBoxes[4].x0 = cutBox.x1;
  maskBoxes[4].x1 = w;
  maskBoxes[5].x0 = cutBox.x0;
  maskBoxes[5].x1 = cutBox.x1;
  maskBoxes[6].x0 = 0;
  maskBoxes[6].x1 = cutBox.x0;
  maskBoxes[7].x0 = 0;
  maskBoxes[7].x1 = cutBox.x0;

  maskBoxes[0].y0 = 0;
  maskBoxes[0].y1 = cutBox.y0;
  maskBoxes[1].y0 = 0;
  maskBoxes[1].y1 = cutBox.y0;
  maskBoxes[2].y0 = 0;
  maskBoxes[2].y1 = cutBox.y0;
  maskBoxes[3].y0 = cutBox.y0;
  maskBoxes[3].y1 = cutBox.y1;
  maskBoxes[4].y0 = cutBox.y1;
  maskBoxes[4].y1 = h;
  maskBoxes[5].y0 = cutBox.y1;
  maskBoxes[5].y1 = h;
  maskBoxes[6].y0 = cutBox.y1;
  maskBoxes[6].y1 = h;
  maskBoxes[7].y0 = cutBox.y0;
  maskBoxes[7].y1 = cutBox.y1;

  refresh();
}
