#include "WindowBase.h"
#include <blend2d.h>

void WindowBase::initLayerImg()
{
  prepareImg = new BLImage(w, h, BL_FORMAT_PRGB32);
  paintCtx = new BLContext();
  paintCtx->begin(*prepareImg);
  paintCtx->clearAll();
  paintCtx->end();

  bottomImg = new BLImage(w, h, BL_FORMAT_PRGB32);
  BLImageData imgData;
  bottomImg->getData(&imgData);
  pixelData = static_cast<unsigned char *>(imgData.pixelData);
  stride = imgData.stride;
}

bool WindowBase::onPaint()
{
  paintCtx->begin(*bottomImg);
  paintCtx->blitImage(BLRect(0, 0, w, h), *originalImg);
  if (isDrawing) {
    paintCtx->blitImage(BLRect(0, 0, w, h), *prepareImg);
  }
  drawMaskBox();
  paintCtx->end();
  return true;
}

void WindowBase::refresh()
{
  auto result = onPaint();
  painter->paint(w, h, pixelData, stride);
}