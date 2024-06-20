#include "text_class.h"
#include "globalVariables.h"
#include "getParentWindow.h"

// Default constructor.
Text::Text() :
    m_fontName { nullptr },
    m_fontSize{},
    m_fontRGB{},
    m_backgroundRGB{},
    m_outlineRGB{},
    m_fontWeight{},
    m_fontStyle{},
    m_fontStretch{}
{
}

// Class constructor with parameters.
Text::Text(
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
    const wchar_t* windowTitle,
    const wchar_t* fontName,
    float fontSize,
    UINT32 fontRGB,
    UINT32 backgroundRGB,
    UINT32 outlineRGB,
    DWRITE_FONT_WEIGHT fontWeight,
    DWRITE_FONT_STYLE fontStyle,
    DWRITE_FONT_STRETCH fontStretch
) : Window(
    windowClassStyle,
    dwExStyle,
    dwStyle,
    parentHwnd,
    windowPositionX,
    windowPositionY,
    windowWidth,
    windowHeight,
    message,
    windowClass,
    windowTitle
),  m_fontName{ fontName }, 
    m_fontSize{ fontSize }, 
    m_fontRGB{ fontRGB },
    m_backgroundRGB{ backgroundRGB },
    m_outlineRGB{ outlineRGB },
    m_fontWeight{ fontWeight },
    m_fontStyle{ fontStyle },
    m_fontStretch{ fontStretch }
{
}

// Release resources. Class destructor.
Text::~Text()
{
}

// The text window message handler.
LRESULT CALLBACK Text::TextWindowProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    LRESULT result = 0;
    PAINTSTRUCT ps;

    if (message == WM_CREATE)
    {
        LPCREATESTRUCT pcs = (LPCREATESTRUCT)lParam;
        Text* txtPWindow = (Text*)pcs->lpCreateParams;
        // The "SetWindowLongPtrW" function allows you to create several windows
        // using one "WindowProc" function for all.
        //
        ::SetWindowLongPtrW(
            hwnd,
            GWLP_USERDATA,
            reinterpret_cast<LONG_PTR>(txtPWindow)
        );

        HRESULT hr = S_OK;

        if (SUCCEEDED(hr))
        {
            hr = txtPWindow->CreateD2D1Factory(*txtPWindow);

            if (SUCCEEDED(hr))
            {
                hr = txtPWindow->CreateD3D11Device(*txtPWindow);

                hr = txtPWindow->CreateSwapChain(*txtPWindow, NULL);
                if (SUCCEEDED(hr))
                {
                    hr = txtPWindow->ConfigureSwapChain(*txtPWindow, hwnd);
                    hr = txtPWindow->CreateDirectComposition(*txtPWindow, hwnd);
                }
            }
        }

        result = 1;
    }
    else
    {
        Text* txtPWindow = reinterpret_cast<Text*>(
            ::GetWindowLongPtrW(
                hwnd,
                GWLP_USERDATA
            ));

        bool wasHandled = false;

        if (txtPWindow)
        {
            switch (message)
            {
            case WM_LBUTTONDOWN:

                return 0;
                break;
            case WM_LBUTTONUP:

                return 0;
                break;
            case WM_RBUTTONDOWN:

                return 0;
                break;
            case WM_RBUTTONUP:

                return 0;
                break;
            case WM_MBUTTONDOWN:

                return 0;
                break;
            case WM_MBUTTONUP:

                return 0;
                break;
            case WM_MOUSEMOVE:

                if ((DWORD)wParam & MK_LBUTTON)
                {

                }
                if (HIBYTE(GetKeyState(VK_MENU)) & 0x80)
                {
                    // The following conditions only work while the Alt key is pressed.
                    if ((DWORD)wParam & MK_RBUTTON)
                    {

                    }
                    if ((DWORD)wParam & MK_MBUTTON)
                    {

                    }
                }
                else
                {

                }
                return 0;
                break;
            case WM_MOUSELEAVE:

                // TODO: Handle the mouse-leave message.

                return 0;
                break;
            case WM_MOUSEHOVER:

                // TODO: Handle the mouse-hover message.

                return 0;
                break;
            case WM_COMMAND:
            {
                int wmId = LOWORD(wParam);
                switch (wmId)
                {
                case 0:
                {                 
                }
                break;
                default:
                    return DefWindowProc(hwnd, message, wParam, lParam);
                }
            }

            break;
            case WM_SIZE:
            {
                UINT nWidth = GET_X_LPARAM(lParam);
                UINT nHeight = GET_Y_LPARAM(lParam);
                txtPWindow->OnResize(*txtPWindow, hwnd, nWidth, nHeight);
            }
            result = 0;
            wasHandled = true;
            break;
            case WM_PAINT:
            case WM_DISPLAYCHANGE:
            {
                BeginPaint(hwnd, &ps);
                txtPWindow->DrawingText(*txtPWindow, Global::inputUserText, hwnd);
                EndPaint(hwnd, &ps);
            }
            result = 0;
            wasHandled = true;
            break;
            case WM_DESTROY:
            {
                DestroyWindow(hwnd);
            }
            result = 1;
            wasHandled = true;
            break;
            }
        }

        if (!wasHandled)
        {
            result = DefWindowProc(hwnd, message, wParam, lParam);
        }
    }

    return result;
}

// This function draws plain text with a background and border (optional).
HRESULT Text::DrawingText(
    Text& object,
    const wchar_t* inputTitle,
    HWND hwnd
)
{
    HRESULT hr = S_OK;

    if (object.m_pD2DDeviceContext.Get() && object.m_pDXGISwapChain.Get())
    {
        D2D1_SIZE_F size = object.m_pD2DDeviceContext.Get()->GetSize();

        object.m_pD2DDeviceContext.Get()->BeginDraw();
        object.m_pD2DDeviceContext.Get()->Clear(D2D1::ColorF(D2D1::ColorF(0xFEE3EE)));

        //Drawing the background.
        Microsoft::WRL::ComPtr<ID2D1SolidColorBrush> pBackgroundBrush;
        Microsoft::WRL::ComPtr<ID2D1SolidColorBrush> pOutlinerBrush;

        D2D1_ROUNDED_RECT roundedRect{};

        // To make the rounded corners look neater, 
        // it was decided to reduce the area in which the rectangle is drawn by two pixels.
        roundedRect = D2D1::RoundedRect(
            D2D1::RectF(
                2.0f,
                2.0f,
                size.width - 2.0f,
                size.height - 2.0f
            ),
            8.0f,
            8.0f
        );

        if (object.m_backgroundRGB != 0)
        {
            hr = object.m_pD2DDeviceContext.Get()->CreateSolidColorBrush(
                D2D1::ColorF(D2D1::ColorF(object.m_backgroundRGB, 1.0f)),
                &pBackgroundBrush
            );

            if (SUCCEEDED(hr))
            {
                object.m_pD2DDeviceContext.Get()->FillRoundedRectangle(roundedRect, pBackgroundBrush.Get());
            }
        }
        if (object.m_outlineRGB != 0)
        {
            hr = object.m_pD2DDeviceContext.Get()->CreateSolidColorBrush(
                D2D1::ColorF(D2D1::ColorF(object.m_outlineRGB, 1.0f)),
                &pOutlinerBrush
            );

            if (SUCCEEDED(hr))
            {
                object.m_pD2DDeviceContext.Get()->DrawRoundedRectangle(roundedRect, pOutlinerBrush.Get(), 0.6f);
            }
        }

        // Creating text format.
        Microsoft::WRL::ComPtr<IDWriteTextFormat> pTextFormat;

        UINT textColor = 0;

        if (object.m_fontRGB != 0)
        {
            textColor = object.m_fontRGB;
        }
        else
        {
            textColor = 0x233567;
        }

        // Create a DirectWrite text format object.
        hr = object.m_pDWriteFactory->CreateTextFormat(
            object.m_fontName,
            NULL,
            object.m_fontWeight,
            object.m_fontStyle,
            object.m_fontStretch,
            object.m_fontSize,
            L"", //locale
            &pTextFormat
        );

        if (SUCCEEDED(hr))
        {
            if (SUCCEEDED(hr))
            {
                // Center the text horizontally and vertically.
                pTextFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
                // and vertically.
                pTextFormat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
            }

            // Drawing text.
            Microsoft::WRL::ComPtr<ID2D1SolidColorBrush> pTextBrush;

            hr = object.m_pD2DDeviceContext.Get()->CreateSolidColorBrush(
                D2D1::ColorF(D2D1::ColorF(textColor, 1.0f)),
                pTextBrush.ReleaseAndGetAddressOf()
            );

            if (SUCCEEDED(hr))
            {               
                if (wcslen(object.m_windowTitle) == 0)
                {
                    object.m_pD2DDeviceContext.Get()->DrawText(
                        inputTitle,
                        lstrlen(inputTitle),
                        pTextFormat.Get(),
                        D2D1::RectF(
                            4.0f,
                            4.0f,
                            size.width - 4.0f,
                            size.height - 4.0f
                        ),
                        pTextBrush.Get()
                    );
                }
                else
                {
                    object.m_pD2DDeviceContext.Get()->DrawText(
                        object.m_windowTitle,
                        lstrlen(object.m_windowTitle),
                        pTextFormat.Get(),
                        D2D1::RectF(
                            4.0f,
                            4.0f,
                            size.width - 4.0f,
                            size.height - 4.0f
                        ),
                        pTextBrush.Get()
                    );
                }              
            }
        }

        hr = object.m_pD2DDeviceContext.Get()->EndDraw();
        // Make the swap chain available to the composition engine.
        hr = object.m_pDXGISwapChain.Get()->Present(0, 0);
    }

    return hr;
}