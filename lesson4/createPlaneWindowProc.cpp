#include "window_class.h"
#include "button_class.h"
#include "field_class.h"
#include "text_class.h"

// The main window message handler.
LRESULT CALLBACK Window::CreatePlaneWindowProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    LRESULT result = 0;
    PAINTSTRUCT ps;

    static Button closeButton;
    static Button create;
    static Button apply;
    static Button close;

    static Field cubeWidth;
    static Field cubeHeight;
    static Field cubeDepth;
    static Field subdivCubeWidth;
    static Field subdivCubeHeight;
    static Field subdivCubeDepth;

    static Text polyCubeDataName;

    static std::unique_ptr<Text[]> pPolyCubeDataName(new Text[6]{});

    static int nonClientAreaSize{ 6 };
    static int mainMenuBarWidth{ 38 };
    static int buttonWidthHeight{ 32 };

    const wchar_t* txtCubeWidth = { L"Width" };
    const wchar_t* txtCubeHeight = { L"Height" };
    const wchar_t* txtCubeDepth = { L"Depth" };

    const wchar_t* txtSubdivCubeWidth = { L"Subdivision width" };
    const wchar_t* txtSubdivCubeHeight = { L"Subdivision height" };
    const wchar_t* txtSubdivCubeDepth = { L"Subdivision depth" };

    

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
                L"closeCreatePlaneWindowClass_0", L""
        };
        closeButton.Initialize(
            closeButton,
            closeButton.MinMaxResClosButtonWindowProc,
            NULL,
            hwnd
        );

        create = {
                CS_HREDRAW | CS_VREDRAW, NULL, WS_VISIBLE | WS_CHILD, hwnd,
                20,
                rc.bottom - 38,
                120,
                32,
                2000,
                L"createPlaneWindowClass_0", L"Create"
        };
        create.Initialize(
            create,
            create.RoundedRectButtonWindowProc,
            NULL,
            hwnd
        );

        apply = {
                CS_HREDRAW | CS_VREDRAW, NULL, WS_VISIBLE | WS_CHILD, hwnd,
                (rc.right / 2) - 60,
                rc.bottom - 38,
                120,
                32,
                3000,
                L"applyPlaneWindowClass_0", L"Apply"
        };
        apply.Initialize(
            apply,
            apply.RoundedRectButtonWindowProc,
            NULL,
            hwnd
        );

        close = {
                CS_HREDRAW | CS_VREDRAW, NULL, WS_VISIBLE | WS_CHILD, hwnd,
                rc.right - 140,
                rc.bottom - 38,
                120,
                32,
                4000,
                L"closePlaneWindowClass_0", L"Close"
        };
        close.Initialize(
            close,
            close.RoundedRectButtonWindowProc,
            NULL,
            hwnd
        );
        
        // cube dimensions
        cubeWidth = {
               CS_HREDRAW | CS_VREDRAW,
               NULL,
               WS_VISIBLE | WS_CHILD,
               hwnd,
               50,
               100,
               90,
               22,
               0,
               L"cubeWidthWindowClass_0", L""
        };
        cubeWidth.Initialize(
            cubeWidth,
            cubeWidth.FieldWindowProc,
            NULL,
            hwnd
        );

        cubeHeight = {
               CS_HREDRAW | CS_VREDRAW,
               NULL,
               WS_VISIBLE | WS_CHILD,
               hwnd,
               50,
               130,
               90,
               22,
               1,
               L"cubeHeightWindowClass_0", L""
        };
        cubeHeight.Initialize(
            cubeHeight,
            cubeHeight.FieldWindowProc,
            NULL,
            hwnd
        );

        cubeDepth = {
               CS_HREDRAW | CS_VREDRAW,
               NULL,
               WS_VISIBLE | WS_CHILD,
               hwnd,
               50,
               160,
               90,
               22,
               2,
               L"cubeDepthWindowClass_0", L""
        };
        cubeDepth.Initialize(
            cubeDepth,
            cubeDepth.FieldWindowProc,
            NULL,
            hwnd
        );

        // subdivision cube
        subdivCubeWidth = {
            CS_HREDRAW | CS_VREDRAW,
            NULL,
            WS_VISIBLE | WS_CHILD,
            hwnd,
            50,
            190,
            90,
            22,
            3,
            L"subdivCubeWidthWindowClass_0", L""
        };
        subdivCubeWidth.Initialize(
            subdivCubeWidth,
            subdivCubeWidth.FieldWindowProc,
            NULL,
            hwnd
        );

        subdivCubeHeight = {
               CS_HREDRAW | CS_VREDRAW,
               NULL,
               WS_VISIBLE | WS_CHILD,
               hwnd,
               50,
               220,
               90,
               22,
               4,
               L"subdivCubeHeightWindowClass_0", L""
        };
        subdivCubeHeight.Initialize(
            subdivCubeHeight,
            subdivCubeHeight.FieldWindowProc,
            NULL,
            hwnd
        );

        subdivCubeDepth = {
               CS_HREDRAW | CS_VREDRAW,
               NULL,
               WS_VISIBLE | WS_CHILD,
               hwnd,
               50,
               250,
               90,
               22,
               5,
               L"subdivCubeDepthWindowClass_0", L""
        };
        subdivCubeDepth.Initialize(
            subdivCubeDepth,
            subdivCubeDepth.FieldWindowProc,
            NULL,
            hwnd
        );

        // We write the names of the fields
        polyCubeDataName = {
            CS_HREDRAW | CS_VREDRAW,
            NULL,
            WS_VISIBLE | WS_CHILD,
            hwnd,
            220,
            96,
            80,
            30,
            0,
            L"polyCubeWidthWindowClass_0",
            txtCubeWidth,
            L"Verdana",
            14,
            0xDC8095,
            0,
            0,
            DWRITE_FONT_WEIGHT_EXTRA_LIGHT,
            DWRITE_FONT_STYLE_NORMAL,
            DWRITE_FONT_STRETCH_NORMAL
        };

        pPolyCubeDataName[0] = polyCubeDataName;

        polyCubeDataName = {
            CS_HREDRAW | CS_VREDRAW,
            NULL,
            WS_VISIBLE | WS_CHILD,
            hwnd,
            220,
            126,
            80,
            30,
            0,
            L"polyCubeHeightWindowClass_0",
            txtCubeHeight,
            L"Verdana",
            14,
            0xDC8095,
            0,
            0,
            DWRITE_FONT_WEIGHT_EXTRA_LIGHT,
            DWRITE_FONT_STYLE_NORMAL,
            DWRITE_FONT_STRETCH_NORMAL
        };

        pPolyCubeDataName[1] = polyCubeDataName;

        polyCubeDataName = {
            CS_HREDRAW | CS_VREDRAW,
            NULL,
            WS_VISIBLE | WS_CHILD,
            hwnd,
            220,
            156,
            80,
            30,
            0,
            L"polyCubeDepthWindowClass_0",
            txtCubeDepth,
            L"Verdana",
            14,
            0xDC8095,
            0,
            0,
            DWRITE_FONT_WEIGHT_EXTRA_LIGHT,
            DWRITE_FONT_STYLE_NORMAL,
            DWRITE_FONT_STRETCH_NORMAL
        };

        pPolyCubeDataName[2] = polyCubeDataName;


        polyCubeDataName = {
            CS_HREDRAW | CS_VREDRAW,
            NULL,
            WS_VISIBLE | WS_CHILD,
            hwnd,
            220,
            186,
            160,
            30,
            0,
            L"polyCubeSubdivWidthWindowClass_0",
            txtSubdivCubeWidth,
            L"Verdana",
            14,
            0xDC8095,
            0,
            0,
            DWRITE_FONT_WEIGHT_EXTRA_LIGHT,
            DWRITE_FONT_STYLE_NORMAL,
            DWRITE_FONT_STRETCH_NORMAL
        };

        pPolyCubeDataName[3] = polyCubeDataName;

        polyCubeDataName = {
            CS_HREDRAW | CS_VREDRAW,
            NULL,
            WS_VISIBLE | WS_CHILD,
            hwnd,
            220,
            216,
            160,
            30,
            0,
            L"polyCubeSubdivHeightWindowClass_0",
            txtSubdivCubeHeight,
            L"Verdana",
            14,
            0xDC8095,
            0,
            0,
            DWRITE_FONT_WEIGHT_EXTRA_LIGHT,
            DWRITE_FONT_STYLE_NORMAL,
            DWRITE_FONT_STRETCH_NORMAL
        };

        pPolyCubeDataName[4] = polyCubeDataName;

        polyCubeDataName = {
            CS_HREDRAW | CS_VREDRAW,
            NULL,
            WS_VISIBLE | WS_CHILD,
            hwnd,
            220,
            246,
            160,
            30,
            0,
            L"polyCubeSubdivDepthWindowClass_0",
            txtSubdivCubeDepth,
            L"Verdana",
            14,
            0xDC8095,
            0,
            0,
            DWRITE_FONT_WEIGHT_EXTRA_LIGHT,
            DWRITE_FONT_STYLE_NORMAL,
            DWRITE_FONT_STRETCH_NORMAL
        };

        pPolyCubeDataName[5] = polyCubeDataName;


        pPolyCubeDataName[0].Initialize(pPolyCubeDataName[0], pPolyCubeDataName[0].TextWindowProc, NULL, hwnd);
        pPolyCubeDataName[1].Initialize(pPolyCubeDataName[1], pPolyCubeDataName[1].TextWindowProc, NULL, hwnd);
        pPolyCubeDataName[2].Initialize(pPolyCubeDataName[2], pPolyCubeDataName[2].TextWindowProc, NULL, hwnd);
        pPolyCubeDataName[3].Initialize(pPolyCubeDataName[3], pPolyCubeDataName[3].TextWindowProc, NULL, hwnd);
        pPolyCubeDataName[4].Initialize(pPolyCubeDataName[4], pPolyCubeDataName[4].TextWindowProc, NULL, hwnd);
        pPolyCubeDataName[5].Initialize(pPolyCubeDataName[5], pPolyCubeDataName[5].TextWindowProc, NULL, hwnd);

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
                    //DestroyWindow(pAboutText[0].m_hwnd);
                    //DestroyWindow(pAboutText[1].m_hwnd);
                    DestroyWindow(closeButton.m_hwnd);
                    DestroyWindow(create.m_hwnd);
                    DestroyWindow(create.m_hwnd);
                    DestroyWindow(apply.m_hwnd);
                    DestroyWindow(close.m_hwnd);
                    DestroyWindow(hwnd);
                    return 0;
                    break;
                case 4000:
                    //DestroyWindow(pAboutText[0].m_hwnd);
                    //DestroyWindow(pAboutText[1].m_hwnd);
                    DestroyWindow(closeButton.m_hwnd);
                    DestroyWindow(create.m_hwnd);
                    DestroyWindow(create.m_hwnd);
                    DestroyWindow(apply.m_hwnd);
                    DestroyWindow(close.m_hwnd);
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
                pAbWindow->DrawingCreatePlaneWinContents(*pAbWindow, hwnd);
                EndPaint(hwnd, &ps);
            }
            result = 0;
            wasHandled = true;
            break;
            case WM_DESTROY:
            {
                //DestroyWindow(pAboutText[0].m_hwnd);
                //DestroyWindow(pAboutText[1].m_hwnd);
                DestroyWindow(closeButton.m_hwnd);
                DestroyWindow(create.m_hwnd);
                DestroyWindow(apply.m_hwnd);
                DestroyWindow(close.m_hwnd);
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