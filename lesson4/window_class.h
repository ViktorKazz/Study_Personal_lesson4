#ifndef WINDOW_CLASS_H
#define WINDOW_CLASS_H

#include "framework.h"

// This function frees the ppT pointer and assigns it the value NULL.
//
// Another option is to use a smart pointer class such as ComPtr, 
// which is defined in the Windows Runtime C++ Template Library (WRL).

template <class T>

void SafeRelease(T** ppT)
{
	if (*ppT)
	{
		(*ppT)->Release();
		*ppT = nullptr;
	}
}

class Window
{
public:
	// Default constructor.
    Window();

    // Constructor with parameters.
    Window(
        UINT windowClassStyle,
        DWORD dwExStyle,
        DWORD dwStyle,
        HWND parentHwnd,
        int windowPositionX,
        int windowPositionY,
        int windowWidth,
        int windowHeight,
        int message,
        const wchar_t* windowClass,
        const wchar_t* windowTitle
    );
    
	~Window();

	BOOL Initialize(
		Window& object,
		WNDPROC wndProc,
		HINSTANCE hInstance,
		HWND parentHwnd
	);

    void RunMessageLoop();

    HRESULT CreateD2D1Factory(Window& object);
    HRESULT CreateD3D11Device(Window& object);
    HRESULT CreateSwapChain(Window& object, HWND hwnd);
    HRESULT ConfigureSwapChain(Window& object, HWND hwnd);
    HRESULT CreateDirectComposition(Window& object, HWND hWnd);

    void OnResize(Window& object, HWND hwnd, UINT nWidth, UINT nHeight);

    HRESULT LoadBitmapFromFile(
        Window& object,
        PCWSTR uri,
        UINT destinationWidth,
        UINT destinationHeight
    );

    static LRESULT CALLBACK MainWindowProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
    //
    HRESULT DrawingMainWindowContents(Window& object, HWND hwnd);

    static LRESULT CALLBACK AboutWindowProc(
        HWND hwnd, 
        UINT message, 
        WPARAM wParam, 
        LPARAM lParam
    );
    //
    HRESULT DrawingAboutWindowContents(Window& object, HWND hwnd);

    static LRESULT CALLBACK CreatePlaneWindowProc(
        HWND hwnd,
        UINT message,
        WPARAM wParam,
        LPARAM lParam
    );

    HRESULT DrawingCreatePlaneWinContents(Window& object, HWND hwnd);
    
    

protected:
    int m_windowPositionX{};
    int m_windowPositionY{};
    int m_windowWidth{};
    int m_windowHeight{};
    int m_message{};

protected:
    const wchar_t* m_windowClass{ nullptr };
    const wchar_t* m_windowTitle{ nullptr };

protected:
    UINT m_windowClassStyle{};
    DWORD m_dwExStyle{};
    DWORD m_dwStyle{};

protected:
    const wchar_t* m_fontName{ nullptr };
    float m_fontSize{};
    UINT32 m_fontRGB{};
    UINT32 m_backgroundRGB{};
    UINT32 m_outlineRGB{};
    DWRITE_FONT_WEIGHT m_fontWeight{};
    DWRITE_FONT_STYLE m_fontStyle{};
    DWRITE_FONT_STRETCH m_fontStretch{};

protected:
    HWND m_hwnd{ nullptr };
    HWND m_parentHwnd{ nullptr };
    HINSTANCE m_hInstance{ nullptr };
    IWICImagingFactory2* m_pWICFactory{ nullptr };
    ID2D1Bitmap* m_pBitmap{ nullptr };

protected:
    Microsoft::WRL::ComPtr<ID2D1Factory7> m_pD2DFactory;
    Microsoft::WRL::ComPtr<IDWriteFactory7> m_pDWriteFactory;
    Microsoft::WRL::ComPtr<ID3D11Device> m_pD3D11Device;
    Microsoft::WRL::ComPtr<ID3D11DeviceContext> m_pD3D11DeviceContext;
    Microsoft::WRL::ComPtr<IDXGIDevice4> m_pDXGIDevice;
    Microsoft::WRL::ComPtr<ID2D1Device6> m_pD2DDevice;
    Microsoft::WRL::ComPtr<ID2D1DeviceContext6> m_pD2DDeviceContext;
    Microsoft::WRL::ComPtr<IDXGISwapChain1> m_pDXGISwapChain;
    Microsoft::WRL::ComPtr<ID2D1Bitmap1> m_pD2DTargetBitmap;
    Microsoft::WRL::ComPtr<IDCompositionDevice> m_pDCompositionDevice;
    Microsoft::WRL::ComPtr<IDCompositionTarget> m_pDCompositionTarget;
    Microsoft::WRL::ComPtr<ID3D12Device> m_pD3D12Device;
    Microsoft::WRL::ComPtr<IDXGIFactory4> m_DXGIFactory;
};

#endif // !WINDOW_CLASS_H