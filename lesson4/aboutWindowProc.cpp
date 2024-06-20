#include "window_class.h"
#include "button_class.h"
#include "text_class.h"

// The main window message handler.
LRESULT CALLBACK Window::AboutWindowProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    LRESULT result = 0;
    PAINTSTRUCT ps;

    static Button closeButton;
    static Button okButton;
    static Text aboutText;

    static std::unique_ptr<Text[]> pAboutText(new Text[2]{});
    
    static int nonClientAreaSize{ 6 };
    static int mainMenuBarWidth{ 38 };
    static int buttonWidthHeight{ 32 };

    const wchar_t* sc_titleText =
    {
        L"2D Graphics Editor"
    };

    const wchar_t* sc_descriptionText =
    {
        L"Hi all! My name is Victor and I study C++. "
        "To make learning programming more interesting, "
        "I decided to learn C++ while creating this 2D editor."
    };

    if (message == WM_CREATE)
    {
        RECT rc;
        GetClientRect(hwnd, &rc);

        closeButton = {
                CS_HREDRAW | CS_VREDRAW, NULL, WS_VISIBLE | WS_CHILD, hwnd,
                rc.right - (buttonWidthHeight + (nonClientAreaSize * 2)),
                nonClientAreaSize,
                buttonWidthHeight,
                buttonWidthHeight,
                1000,
                L"closeAboutWindowClass_0", L""
        };
        closeButton.Initialize(
            closeButton,
            closeButton.MinMaxResClosButtonWindowProc,
            NULL,
            hwnd
        );

        okButton = {
                CS_HREDRAW | CS_VREDRAW, NULL, WS_VISIBLE | WS_CHILD, hwnd,
                (rc.right / 2) - 40,
                rc.bottom - 38,
                80,
                32,
                1000,
                L"okAboutWindowClass_0", L"OK"
        };
        okButton.Initialize(
            okButton,
            okButton.RoundedRectButtonWindowProc,
            NULL,
            hwnd
        );

        aboutText = {
        CS_HREDRAW | CS_VREDRAW,
        NULL,
        WS_VISIBLE | WS_CHILD,
        hwnd,
        (rc.right / 2) - 160,
        60,
        320,
        50,
        0,
        L"textAboutWindowClass_0",
        sc_titleText,
        L"Verdana",
        28,
        0xDC8095,
        0xFEE3EE,
        0xE1B4C6,
        DWRITE_FONT_WEIGHT_EXTRA_LIGHT,
        DWRITE_FONT_STYLE_NORMAL,
        DWRITE_FONT_STRETCH_NORMAL
        };

        pAboutText[0] = aboutText;

        aboutText = {
        CS_HREDRAW | CS_VREDRAW,
        NULL,
        WS_VISIBLE | WS_CHILD,
        hwnd,
        32,
        200,
        320,
        80,
        0,
        L"textAboutWindowClass_1",
        sc_descriptionText,
        L"Verdana",
        14,
        0xDC8095,
        0,
        0,
        DWRITE_FONT_WEIGHT_THIN,
        DWRITE_FONT_STYLE_NORMAL,
        DWRITE_FONT_STRETCH_NORMAL
        };

        pAboutText[1] = aboutText;

        pAboutText[0].Initialize(pAboutText[0], pAboutText[0].TextWindowProc, NULL, hwnd);
        pAboutText[1].Initialize(pAboutText[1], pAboutText[1].TextWindowProc, NULL, hwnd);

        LPCREATESTRUCT pcs = (LPCREATESTRUCT)lParam;
        Window* pAbWindow = (Window*)pcs->lpCreateParams;
        // The "SetWindowLongPtrW" function allows you to create several windows
        // using one "WindowProc" function for all.
        //
        ::SetWindowLongPtrW(
            hwnd,
            GWLP_USERDATA,
            reinterpret_cast<LONG_PTR>(pAbWindow)
        );

        HRESULT hr = RoInitialize(RO_INIT_MULTITHREADED);

        if (SUCCEEDED(hr))
        {
            hr = pAbWindow->CreateD2D1Factory(*pAbWindow);

            if (SUCCEEDED(hr))
            {
                hr = pAbWindow->CreateD3D11Device(*pAbWindow);

                hr = pAbWindow->CreateSwapChain(*pAbWindow, NULL);
                if (SUCCEEDED(hr))
                {
                    hr = pAbWindow->ConfigureSwapChain(*pAbWindow, hwnd);
                    hr = pAbWindow->CreateDirectComposition(*pAbWindow, hwnd);
                }
            }
        }
        // ??????
        RoUninitialize();

        result = 1;
    }
    else
    {
        Window* pAbWindow = reinterpret_cast<Window*>(
            ::GetWindowLongPtrW(
                hwnd,
                GWLP_USERDATA
            ));

        bool wasHandled = false;

        if (pAbWindow)
        {
            switch (message)
            {
            case WM_KEYDOWN:
                break;
            case WM_NCHITTEST:
            {
                RECT clientRc;
                GetClientRect(hwnd, &clientRc);

                POINT pt{};
                pt.x = LOWORD(lParam);
                pt.y = HIWORD(lParam);
                ScreenToClient(hwnd, &pt);
              
                // We define non-client areas -> menu bar.
                if (pt.y > nonClientAreaSize && pt.y < mainMenuBarWidth)
                {
                    return HTCAPTION;
                }
                // Define the client area.
                if (pt.y > mainMenuBarWidth && pt.y < (clientRc.bottom - nonClientAreaSize))
                {
                    if (pt.x > nonClientAreaSize && pt.x < (clientRc.right - nonClientAreaSize))
                    {
                        return HTCLIENT;
                    }
                }
                // Now, if you hover your mouse over the non-client area we have defined, 
                // you can stretch the window in different directions or move it.
                // The mouse pointer will change automatically.
            }
            return 0;
            break;
            case WM_LBUTTONDOWN:
            {              
            }
            return 0;
            break;
            case WM_LBUTTONUP:
            {
            }
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
                    SetCursor(LoadCursorW(0, IDC_ARROW));
                }
                return 0;
                break;
            case WM_MOUSELEAVE:
            {
            }
            case WM_COMMAND:
            {
                int wmId = LOWORD(wParam);

                switch (wmId)
                {
                case 1000:
                    DestroyWindow(closeButton.m_hwnd);
                    DestroyWindow(okButton.m_hwnd);
                    DestroyWindow(hwnd);
                    return 0;
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
                pAbWindow->OnResize(*pAbWindow, hwnd, nWidth, nHeight);
            }
            result = 0;
            wasHandled = true;
            break;
            case WM_PAINT:
            case WM_DISPLAYCHANGE:
            {
                BeginPaint(hwnd, &ps);
                pAbWindow->DrawingAboutWindowContents(*pAbWindow, hwnd);
                EndPaint(hwnd, &ps);
            }
            result = 0;
            wasHandled = true;
            break;
            case WM_DESTROY:
            {
                DestroyWindow(pAboutText[0].m_hwnd);
                DestroyWindow(pAboutText[1].m_hwnd);
                DestroyWindow(closeButton.m_hwnd);
                DestroyWindow(okButton.m_hwnd);
                DestroyWindow(hwnd);
                return 0;
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