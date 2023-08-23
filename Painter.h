#pragma once

#include <Windows.h>
#include <d2d1_3.h>
#include <d3d11.h>
#include <dcomp.h>

class Painter
{
public:
  Painter(const HWND &h_wnd);
  ~Painter();

  void on_resize(HWND h_wnd, UINT n_width, UINT n_height);
  void paint(const unsigned int &w, const unsigned int &h, const void *data, const unsigned int &stride);

private:
  HRESULT create_d_2d1_factory();
  HRESULT create_swap_chain(HWND h_wnd);
  HRESULT configure_swap_chain(HWND h_wnd);
  HRESULT create_d_3d_11device();
  HRESULT create_direct_composition(HWND h_wnd);

  ID2D1Factory1 *m_pD2DFactory1 = nullptr;
  ID3D11Device *m_pD3D11Device = nullptr;
  ID3D11DeviceContext *m_pD3D11DeviceContext = nullptr;
  IDXGIDevice1 *m_pDXGIDevice = nullptr;
  ID2D1Device *m_pD2DDevice = nullptr;
  ID2D1DeviceContext3 *m_pD2DDeviceContext3 = nullptr;
  IDXGISwapChain1 *m_pDXGISwapChain1 = nullptr;
  ID2D1Bitmap1 *m_pD2DTargetBitmap = nullptr;
  IDCompositionDevice *m_pDCompositionDevice = nullptr;
  IDCompositionTarget *m_pDCompositionTarget = nullptr;
  ID2D1Bitmap *d2DImage;
};