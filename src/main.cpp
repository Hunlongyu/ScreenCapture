#include "MainWin.h"
#include <Shlwapi.h>

int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPTSTR lpCmdLine, _In_ int nCmdShow)
{
  MainWin::init();

  try {
    LPWSTR args = PathGetArgs(GetCommandLineW());

    PathRemoveBlanks(args);
    std::wstring path(args);
    MainWin::get()->set_filename(path);
  }
  catch (...) {
  }

  MSG msg;
  while (GetMessage(&msg, nullptr, 0, 0)) {
    TranslateMessage(&msg);
    DispatchMessage(&msg);
  }
  MainWin::dispose();
  const auto code = MainWin::getQuitCode();
  return code;
}
