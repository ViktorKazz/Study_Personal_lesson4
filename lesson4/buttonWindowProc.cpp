#include "button_class.h"
#include "mouseTrackEvents_class.h"
#include "getParentWindow.h"

// The button window message handler.
// 
// The function is responsible for creating the following buttons:
// Minimize or maximize the window, restore or close.
LRESULT CALLBACK Button::MinMaxResClosButtonWindowProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    LRESULT result = 0;
    PAINTSTRUCT ps;
    HRESULT hr;

    MouseTrackEvents mouseEvents;

    static RECT rc;
    static int selectButton{};
    static int pressingButton{};

    if (message == WM_CREATE)
    {
        LPCREATESTRUCT pcs = (LPCREATESTRUCT)lParam;
        Button* pMMRCBt = (Button*)pcs->lpCreateParams;

        // The "SetWindowLongPtrW" function allows you to create several windows
        // using one "WindowProc" function for all.
        ::SetWindowLongPtrW(
            hwnd,
            GWLP_USERDATA,
            reinterpret_cast<LONG_PTR>(pMMRCBt)
        );

        hr = pMMRCBt->CreateD2D1Factory(*pMMRCBt);

        if (SUCCEEDED(hr))
        {
            hr = pMMRCBt->CreateD3D11Device(*pMMRCBt);

            hr = pMMRCBt->CreateSwapChain(*pMMRCBt, NULL);
            if (SUCCEEDED(hr))
            {
                hr = pMMRCBt->ConfigureSwapChain(*pMMRCBt, hwnd);
                hr = pMMRCBt->CreateDirectComposition(*pMMRCBt, hwnd);
            }
        }
        // So that the variables "select Button" and "pressing Button" are equal to zero 
        // each time the window is created, it was decided to place them here.
        selectButton = 0;
        pressingButton = 0;

        // Since the mouse cursor tracking area is the entire window, 
        // the width and height parameters are zero.
        rc = mouseEvents.controlElementArea(hwnd, 0, 0, 0, 0);
        result = 1;
    }
    else
    {
        Button* pMMRCBt = reinterpret_cast<Button*>(
            ::GetWindowLongPtrW(
                hwnd,
                GWLP_USERDATA
            ));

        bool wasHandled = false;

        if (pMMRCBt)
        {
            switch (message)
            {
            case WM_LBUTTONDOWN:
                pressingButton = mouseEvents.OnButtonDown(hwnd, rc);

                return 0;
                break;
            case WM_LBUTTONUP:
                pressingButton = mouseEvents.OnButtonUp(hwnd, rc);
                
                if (selectButton)
                {                  
                    // Finding the parent window.
                    HWND parent = GetParentWindow(hwnd);

                    // We send a message to the parent window.
                    // Instead of WM_COMMAND there may be something else, 
                    // for example WM_LBUTTONDOWN, etc.
                    if(pMMRCBt->m_message == 1000)
                        SendMessageW(parent, WM_DESTROY, pMMRCBt->m_message, lParam);
                    else
                        SendMessageW(parent, WM_COMMAND, pMMRCBt->m_message, lParam);
                }
                return 0;
                break;
            case WM_RBUTTONDOWN:
            {
            }
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
                    selectButton = mouseEvents.OnMouseMove(
                        mouseEvents,
                        hwnd,
                        rc,
                        GET_X_LPARAM(lParam),
                        GET_Y_LPARAM(lParam)
                    );
                }
                return 0;
                break;
            case WM_MOUSELEAVE:

                // TODO: Handle the mouse-leave message.
                selectButton = mouseEvents.Reset(mouseEvents, hwnd);
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
                    break;
                case 1:
                    break;           
                default:
                    return DefWindowProc(hwnd, message, wParam, lParam);
                }
            }
            return 0;
            break;
            case WM_SIZE:
            {
                UINT nWidth = GET_X_LPARAM(lParam);
                UINT nHeight = GET_Y_LPARAM(lParam);
                pMMRCBt->OnResize(*pMMRCBt, hwnd, nWidth, nHeight);
            }
            result = 0;
            wasHandled = true;
            break;
            case WM_PAINT:
            case WM_DISPLAYCHANGE:
            {
                BeginPaint(hwnd, &ps);

                if (pMMRCBt->m_message == 1000)
                    pMMRCBt->DrawingCloseButton(*pMMRCBt, selectButton, pressingButton);

                if (pMMRCBt->m_message == 2000)
                {
                    RECT workAreaSize{};
                    SystemParametersInfoW(SPI_GETWORKAREA, 0, &workAreaSize, 0);
                    RECT clientRc;
                    GetClientRect(GetParentWindow(hwnd), &clientRc);

                    int changeIcon{};

                    if (clientRc.right == workAreaSize.right && clientRc.bottom == workAreaSize.bottom)
                    {
                        changeIcon = 1;
                    }
                    else
                    {
                        changeIcon = 0;
                    }

                    pMMRCBt->DrawingMaximizeRestoreButton(*pMMRCBt, selectButton, pressingButton, changeIcon);
                }
                    
                if (pMMRCBt->m_message == 3000)
                    pMMRCBt->DrawingMinimizeButton(*pMMRCBt, selectButton, pressingButton);

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

// Function for buttons on the top panel of the main window.
LRESULT CALLBACK Button::MainPanelButtonWindowProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    LRESULT result = 0;
    PAINTSTRUCT ps;
    HRESULT hr;

    MouseTrackEvents mouseEvents;

    static RECT rc;
    static int selectButton{};
    static int pressingButton{};

    if (message == WM_CREATE)
    {
        LPCREATESTRUCT pcs = (LPCREATESTRUCT)lParam;
        Button* pMPBt = (Button*)pcs->lpCreateParams;

        // The "SetWindowLongPtrW" function allows you to create several windows
        // using one "WindowProc" function for all.
        ::SetWindowLongPtrW(
            hwnd,
            GWLP_USERDATA,
            reinterpret_cast<LONG_PTR>(pMPBt)
        );

        hr = pMPBt->CreateD2D1Factory(*pMPBt);

        if (SUCCEEDED(hr))
        {
            hr = pMPBt->CreateD3D11Device(*pMPBt);

            hr = pMPBt->CreateSwapChain(*pMPBt, NULL);
            if (SUCCEEDED(hr))
            {
                hr = pMPBt->ConfigureSwapChain(*pMPBt, hwnd);
                hr = pMPBt->CreateDirectComposition(*pMPBt, hwnd);
            }
        }
        // So that the variables "select Button" and "pressing Button" are equal to zero 
        // each time the window is created, it was decided to place them here.
        selectButton = 0;
        pressingButton = 0;

        // Since the mouse cursor tracking area is the entire window, 
        // the width and height parameters are zero.
        rc = mouseEvents.controlElementArea(hwnd, 0, 0, 0, 0);
        result = 1;
    }
    else
    {
        Button* pMPBt = reinterpret_cast<Button*>(
            ::GetWindowLongPtrW(
                hwnd,
                GWLP_USERDATA
            ));

        bool wasHandled = false;

        if (pMPBt)
        {
            switch (message)
            {
            case WM_LBUTTONDOWN:
                pressingButton = mouseEvents.OnButtonDown(hwnd, rc);

                return 0;
                break;
            case WM_LBUTTONUP:
                pressingButton = mouseEvents.OnButtonUp(hwnd, rc);

                if (selectButton)
                {
                    // Finding the parent window.
                    HWND parent = GetParentWindow(hwnd);

                    // We send a message to the parent window.
                    // Instead of WM_COMMAND there may be something else, 
                    // for example WM_LBUTTONDOWN, etc.
                    SendMessageW(parent, WM_COMMAND, pMPBt->m_message, lParam);
                }
                return 0;
                break;
            case WM_RBUTTONDOWN:
            {
            }
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
                    selectButton = mouseEvents.OnMouseMove(
                        mouseEvents,
                        hwnd,
                        rc,
                        GET_X_LPARAM(lParam),
                        GET_Y_LPARAM(lParam)
                    );
                }
                return 0;
                break;
            case WM_MOUSELEAVE:

                // TODO: Handle the mouse-leave message.
                selectButton = mouseEvents.Reset(mouseEvents, hwnd);
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
                    break;
                case 1:
                    break;
                default:
                    return DefWindowProc(hwnd, message, wParam, lParam);
                }
            }
            return 0;
            break;
            case WM_SIZE:
            {
                UINT nWidth = GET_X_LPARAM(lParam);
                UINT nHeight = GET_Y_LPARAM(lParam);
                pMPBt->OnResize(*pMPBt, hwnd, nWidth, nHeight);
            }
            result = 0;
            wasHandled = true;
            break;
            case WM_PAINT:
            case WM_DISPLAYCHANGE:
            {
                BeginPaint(hwnd, &ps);
                pMPBt->DrawingMainPanelButton(*pMPBt, selectButton, pressingButton);
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

//
// Window message handler for a regular button with rounded corners
LRESULT CALLBACK Button::RoundedRectButtonWindowProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    LRESULT result = 0;
    PAINTSTRUCT ps;
    HRESULT hr;

    MouseTrackEvents mouseEvents;

    static RECT rc;
    static int selectButton{};
    static int pressingButton{};

    if (message == WM_CREATE)
    {
        LPCREATESTRUCT pcs = (LPCREATESTRUCT)lParam;
        Button* pMPBt = (Button*)pcs->lpCreateParams;

        // The "SetWindowLongPtrW" function allows you to create several windows
        // using one "WindowProc" function for all.
        ::SetWindowLongPtrW(
            hwnd,
            GWLP_USERDATA,
            reinterpret_cast<LONG_PTR>(pMPBt)
        );

        hr = pMPBt->CreateD2D1Factory(*pMPBt);

        if (SUCCEEDED(hr))
        {
            hr = pMPBt->CreateD3D11Device(*pMPBt);

            hr = pMPBt->CreateSwapChain(*pMPBt, NULL);
            if (SUCCEEDED(hr))
            {
                hr = pMPBt->ConfigureSwapChain(*pMPBt, hwnd);
                hr = pMPBt->CreateDirectComposition(*pMPBt, hwnd);
            }
        }
        // So that the variables "select Button" and "pressing Button" are equal to zero 
        // each time the window is created, it was decided to place them here.
        selectButton = 0;
        pressingButton = 0;

        // Since the mouse cursor tracking area is the entire window, 
        // the width and height parameters are zero.
        rc = mouseEvents.controlElementArea(hwnd, 0, 0, 0, 0);
        result = 1;
    }
    else
    {
        Button* pMPBt = reinterpret_cast<Button*>(
            ::GetWindowLongPtrW(
                hwnd,
                GWLP_USERDATA
            ));

        bool wasHandled = false;

        if (pMPBt)
        {
            switch (message)
            {
            case WM_LBUTTONDOWN:
                pressingButton = mouseEvents.OnButtonDown(hwnd, rc);

                return 0;
                break;
            case WM_LBUTTONUP:
                pressingButton = mouseEvents.OnButtonUp(hwnd, rc);

                if (selectButton)
                {
                    // Finding the parent window.
                    HWND parent = GetParentWindow(hwnd);

                    // We send a message to the parent window.
                    // Instead of WM_COMMAND there may be something else, 
                    // for example WM_LBUTTONDOWN, etc.
                    SendMessageW(parent, WM_COMMAND, pMPBt->m_message, lParam);
                }
                return 0;
                break;
            case WM_RBUTTONDOWN:
            {
            }
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
                    selectButton = mouseEvents.OnMouseMove(
                        mouseEvents,
                        hwnd,
                        rc,
                        GET_X_LPARAM(lParam),
                        GET_Y_LPARAM(lParam)
                    );
                }
                return 0;
                break;
            case WM_MOUSELEAVE:

                // TODO: Handle the mouse-leave message.
                selectButton = mouseEvents.Reset(mouseEvents, hwnd);
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
                    break;
                case 1:
                    break;
                default:
                    return DefWindowProc(hwnd, message, wParam, lParam);
                }
            }
            return 0;
            break;
            case WM_SIZE:
            {
                UINT nWidth = GET_X_LPARAM(lParam);
                UINT nHeight = GET_Y_LPARAM(lParam);
                pMPBt->OnResize(*pMPBt, hwnd, nWidth, nHeight);
            }
            result = 0;
            wasHandled = true;
            break;
            case WM_PAINT:
            case WM_DISPLAYCHANGE:
            {
                BeginPaint(hwnd, &ps);
                pMPBt->DrawRoundedRectButton(*pMPBt, selectButton, pressingButton);
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