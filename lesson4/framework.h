// These "#pragma comment" lines only work in Visual Studio; 
// otherwise include these libraries with the linker.
//
#pragma comment(lib, "runtimeobject.lib")  // For using with roapi.h
#pragma comment(lib, "dwrite.lib")         // For using with dwrite_3.h
#pragma comment(lib, "D3D11")              // For using with d3d11_4.h

#pragma comment(lib, "d3d12.lib")              // 
//#pragma comment(lib,"d3dcompiler.lib")

#pragma comment(lib, "D2d1")               // For using with d2d1.h
#pragma comment(lib, "d2d1") 
#pragma comment(lib, "dcomp")              // For using with dcomp.h
#pragma comment(lib, "windowscodecs.lib")
#pragma comment(lib, "shell32.lib")
#pragma comment(lib, "comctl32.lib")


//#pragma comment(lib, "d2d1.lib")
#pragma comment(lib, "dxguid.lib")



// Windows Header Files:
//
#include <windows.h>
#include <windowsx.h>


// ComPtr Class, optional: using namespace Microsoft::WRL;
//
#include <wrl.h> 

// RoInitialize
//
#include <roapi.h> 

// C RunTime Header Files:
//
#include <stdlib.h>
//#include <malloc.h>
//#include <memory.h>
#include <wchar.h>
#include <tchar.h>
#include <math.h>
//#include <vector>
#include <memory>
//#include <array>

// Read and write file:
#include <iostream>
#include <fstream>

// Text
//
#include <dwrite_3.h>
//Diretx 3D
//
#include <d3d11_4.h>

#include <d3d12.h>
#include <d3d12sdklayers.h>

//Diretx 2D
//
#include <d2d1.h>
#include <d2d1_1.h>
#include <d2d1_3.h>

#include <d2d1effects.h>

#include <dxgi1_5.h>
#include <dcomp.h>

#include <wincodec.h>
#include <shlobj.h>
#include <strsafe.h>

#pragma comment(linker,"\"/manifestdependency:type='win32' \
name='Microsoft.Windows.Common-Controls' version='6.0.0.0' \
processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

//#include "DPIScale_class.h"

