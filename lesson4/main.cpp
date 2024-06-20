#include "window_class.h"
#include "button_class.h"
#include "text_class.h"
#include "mouseTrackEvents_class.h"
#include "globalVariables.h"

// Provides the entry point to the application.
int WINAPI WinMain(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE /* hPrevInstance */,
	_In_ LPSTR /* lpCmdLine */,
	_In_ int /* nCmdShow */
)
{
	// Using WS_CLIPCHILDREN.
	// Excludes the area occupied by child windows when drawing occurs within the parent window. 
	// This style is used when creating the parent window.
	//
	//Returns the width of the screen(monitor)
	unsigned int xres = GetSystemMetrics(SM_CXSCREEN);
	//Returns the height of the screen(monitor)
	unsigned int yres = GetSystemMetrics(SM_CYSCREEN);

    // To each side we add six pixels.
    // This is necessary in order to draw the shadow that the window casts. 
    // The shadow takes up exactly six pixels on each side.
	Window mainWindow(
		CS_HREDRAW | CS_VREDRAW,
		WS_EX_NOREDIRECTIONBITMAP | WS_EX_APPWINDOW,
		WS_POPUP | WS_CLIPCHILDREN,
		NULL,
        (xres / 2) - ((1280 + 12) / 2),
        (yres / 2) - ((720 + 12) / 2),
		1280 + 12,
		720 + 12,
        0,
		L"mainWindowClass",
		L"2D Graphics Editor"
	);

	// Ignore the return value because we want to continue running even in the
	// unlikely event that HeapSetInformation fails.
	HeapSetInformation(NULL, HeapEnableTerminationOnCorruption, NULL, 0);
    
    //HRESULT hr = CoInitializeEx(NULL, COINIT_MULTITHREADED);
    HRESULT hr = RoInitialize(RO_INIT_MULTITHREADED);

    if (SUCCEEDED(hr))
    {
        {
            if (mainWindow.Initialize(mainWindow, mainWindow.MainWindowProc, hInstance, NULL))
            {
                mainWindow.RunMessageLoop();
            }
        }
        RoUninitialize();
    }  

	return 0;
}

// The main window message handler.
//
LRESULT CALLBACK Window::MainWindowProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    LRESULT result = 0;
    PAINTSTRUCT ps;

    static Button closeButton;
    static Button maximizeRestoreButton;
    static Button minimizeButton;

    static Button helpButton;
    static Button createButton;

    static Window aboutWindow;
    static Window createPlaneWindow;

    //
    wchar_t msg[32]{};
    HWND test;
    //
  

    static int nonClientAreaSize{ 6 };
    static int mainMenuBarWidth{ 38 };
    static int buttonWidthHeight{ 32 };

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
                L"closeButtonWindowClass_0", L""
        };
        closeButton.Initialize(
            closeButton, 
            closeButton.MinMaxResClosButtonWindowProc, 
            NULL, 
            hwnd
        );

        maximizeRestoreButton = {
                CS_HREDRAW | CS_VREDRAW, NULL, WS_VISIBLE | WS_CHILD, hwnd,
                rc.right - ((buttonWidthHeight * 2) + (nonClientAreaSize * 2)),
                nonClientAreaSize,
                buttonWidthHeight,
                buttonWidthHeight,
                2000,
                L"maximizeRestoreButtonWindowClass_0", L""
        };
        maximizeRestoreButton.Initialize(
            maximizeRestoreButton, 
            maximizeRestoreButton.MinMaxResClosButtonWindowProc, 
            NULL, 
            hwnd
        );

        minimizeButton = {
               CS_HREDRAW | CS_VREDRAW, NULL, WS_VISIBLE | WS_CHILD, hwnd,
               rc.right - ((buttonWidthHeight * 3) + (nonClientAreaSize * 2)),
               nonClientAreaSize,
               buttonWidthHeight,
               buttonWidthHeight,
               3000,
               L"minimizeButtonWindowClass_0", L""
        };
        minimizeButton.Initialize(
            minimizeButton, 
            minimizeButton.MinMaxResClosButtonWindowProc, 
            NULL, 
            hwnd
        );
        //
        // The main panel buttons.
        createButton = {
               CS_HREDRAW | CS_VREDRAW, NULL, WS_VISIBLE | WS_CHILD, hwnd,
               6 + 6 + 32,
               6,
               72,
               32,
               4000,
               L"createButtonWindowClass_0", L"Create"
        };
        createButton.Initialize(
            createButton, 
            createButton.MainPanelButtonWindowProc, 
            NULL, 
            hwnd
        );

        helpButton = {
               CS_HREDRAW | CS_VREDRAW, NULL, WS_VISIBLE | WS_CHILD, hwnd,
               6 + 6 + 32 + 72,
               6,
               72,
               32,
               5000,
               L"helpButtonWindowClass_0", L"Help"
        };
        helpButton.Initialize(
            helpButton, 
            helpButton.MainPanelButtonWindowProc, 
            NULL, 
            hwnd
        );
        //

        //Returns the width of the screen(monitor)
        int xres = GetSystemMetrics(SM_CXSCREEN);
        //Returns the height of the screen(monitor)
        int yres = GetSystemMetrics(SM_CYSCREEN);

        // To each side we add six pixels.
        // This is necessary in order to draw the shadow that the window casts. 
        // The shadow takes up exactly six pixels on each side.
        aboutWindow = {
            CS_HREDRAW | CS_VREDRAW,
            WS_EX_NOREDIRECTIONBITMAP,
            WS_POPUP | WS_CLIPCHILDREN,
            NULL,
            (xres / 2) - ((400 + 12) / 2),
            (yres / 2) - ((600 + 12) / 2),
            400 + 12,
            600 + 12,
            0,
            L"aboutWindowClass",
            L"About Program"
        };

        createPlaneWindow = {
            CS_HREDRAW | CS_VREDRAW,
            WS_EX_NOREDIRECTIONBITMAP,
            WS_POPUP | WS_CLIPCHILDREN,
            NULL,
            (xres / 2) - ((400 + 12) / 2),
            (yres / 2) - ((600 + 12) / 2),
            400 + 12,
            600 + 12,
            0,
            L"createPlaneWindowClass",
            L"Polygon Plane Options"
        };        
       
        LPCREATESTRUCT pcs = (LPCREATESTRUCT)lParam;
        Window* mPWindow = (Window*)pcs->lpCreateParams;
        // The "SetWindowLongPtrW" function allows you to create several windows
        // using one "WindowProc" function for all.
        //
        ::SetWindowLongPtrW(
            hwnd,
            GWLP_USERDATA,
            reinterpret_cast<LONG_PTR>(mPWindow)
        );
      
        HRESULT hr = RoInitialize(RO_INIT_MULTITHREADED);
        
        if (SUCCEEDED(hr))
        {
            hr = mPWindow->CreateD2D1Factory(*mPWindow);

            if (SUCCEEDED(hr))
            {
                hr = mPWindow->CreateD3D11Device(*mPWindow);

                hr = mPWindow->CreateSwapChain(*mPWindow, NULL);
                if (SUCCEEDED(hr))
                {
                    hr = mPWindow->ConfigureSwapChain(*mPWindow, hwnd);
                    hr = mPWindow->CreateDirectComposition(*mPWindow, hwnd);
                }
            }
        }
        
        result = 1;
    }
    else
    {
        Window* mPWindow = reinterpret_cast<Window*>(
            ::GetWindowLongPtrW(
                hwnd,
                GWLP_USERDATA
            ));

        bool wasHandled = false;

        if (mPWindow)
        {
            switch (message)
            {
            case WM_GETMINMAXINFO:
            {
                // We set the minimum and maximum window dimensions.
                // We set the minimum values arbitrarily.
                // The maximum values are the size of the entire working area of the screen excluding the taskbar strip.
                // The function (SystemParametersInfoW) is needed to define a work area without a taskbar bar. 
                RECT workAreaSize{};
                SystemParametersInfoW(SPI_GETWORKAREA, 0, &workAreaSize, 0);
                
                MINMAXINFO* mmi = (MINMAXINFO*)lParam;
                mmi->ptMinTrackSize.x = 1280;
                mmi->ptMinTrackSize.y = 720;
                mmi->ptMaxSize.x = workAreaSize.right;
                mmi->ptMaxSize.y = workAreaSize.bottom;
                return 0;
            }
            return 0;
            break;
            case WM_NCLBUTTONDBLCLK:
            {
                POINT pt{};
                pt.x = GET_X_LPARAM(lParam);
                pt.y = GET_Y_LPARAM(lParam);
                ScreenToClient(hwnd, &pt);

                RECT workAreaSize{};
                SystemParametersInfoW(SPI_GETWORKAREA, 0, &workAreaSize, 0);
                RECT clientRc;
                GetClientRect(hwnd, &clientRc);

                // We determine the place where there will be a double click with the mouse.
                if (pt.y > nonClientAreaSize && pt.y < mainMenuBarWidth)
                {
                    // If the window is already maximized, it returns to its previous size and vice versa.
                    if(clientRc.right == workAreaSize.right && clientRc.bottom == workAreaSize.bottom)
                    {
                        ShowWindow(hwnd, SW_RESTORE);
                    }
                    else
                    {
                        ShowWindow(hwnd, SW_MAXIMIZE);
                    }
                }              
            }
            return 0;
            break;
            case WM_NCHITTEST:
            {
                RECT clientRc;
                GetClientRect(hwnd, &clientRc);
        
                POINT pt{};
                pt.x = LOWORD(lParam);
                pt.y = HIWORD(lParam);
                ScreenToClient(hwnd, &pt);
                
                // We define non-client areas -> top-left, top and top-right.
                if (pt.y < nonClientAreaSize)
                {
                    if (pt.x < nonClientAreaSize)
                    {
                        return HTTOPLEFT;
                    }
                    else if (pt.x > (clientRc.right - nonClientAreaSize))
                    {
                        return HTTOPRIGHT;
                    }
                    return HTTOP;
                }
                // We define non-client areas -> bottom-left, bottom and bottom-right.
                if (pt.y > (clientRc.bottom - nonClientAreaSize))
                {
                    if (pt.x < nonClientAreaSize)
                    {
                        return HTBOTTOMLEFT;
                    }
                    else if (pt.x > (clientRc.right - nonClientAreaSize))
                    {
                        return HTBOTTOMRIGHT;
                    }
                    return HTBOTTOM;
                }
                if (pt.x < nonClientAreaSize)
                {
                    return HTLEFT;
                }
                if (pt.x > (clientRc.right - nonClientAreaSize))
                {
                    return HTRIGHT;
                }
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
                //std::ofstream out("hello.txt", std::ios::app);
                //if (!out.is_open()) {
                //    //Errroooorr!!!
                //}
                //if (out.is_open()) {
                //    out << color << std::endl;
                //}
                //out.close();
            }   
            return 0;
            break;
            case WM_RBUTTONDOWN:

                /*if (IsWindow(aboutWindow.m_hwnd) != NULL)
                {
                    swprintf_s(msg, L"m_hwnd: %d\n", 1);
                    OutputDebugString(msg);
                }
                if (IsWindow(aboutWindow.m_hwnd) == NULL)
                {
                    swprintf_s(msg, L"m_hwnd: %d\n", 0);
                    OutputDebugString(msg);
                }*/
                return 0;
                break;
            case WM_RBUTTONUP:

                return 0;
                break;
            case WM_MBUTTONDOWN:

                test = FindWindow(
                    L"aboutWindowClass", // pointer to class name
                    L"About 2D Graphics Editor" // pointer to window name
                );

                if (test != NULL)
                {
                    swprintf_s(msg, L"aboutWindowClass: % d\n", 1);
                    OutputDebugString(msg);
                }
                if (test == NULL)
                {
                    swprintf_s(msg, L"aboutWindowClass: % d\n", 0);
                    OutputDebugString(msg);
                }

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
                case 0:                   
                    break;
                case 1000:
                    break;
                case 2000:
                {
                    RECT workAreaSize{};
                    SystemParametersInfoW(SPI_GETWORKAREA, 0, &workAreaSize, 0);
                    RECT clientRc;
                    GetClientRect(hwnd, &clientRc);

                    // If the window is already maximized, it returns to its previous size and vice versa.
                    if (clientRc.right == workAreaSize.right && clientRc.bottom == workAreaSize.bottom)
                    {
                        SendMessage(hwnd, WM_SYSCOMMAND, SC_RESTORE, NULL);
                    }
                    else
                    {
                        SendMessage(hwnd, WM_SYSCOMMAND, SC_MAXIMIZE, NULL);
                    }
                }
                break;
                case 3000:
                    SendMessage(hwnd, WM_SYSCOMMAND, SC_MINIMIZE, NULL);
                    break;   
                    break;
                case 4000:
                    createPlaneWindow.Initialize(
                        createPlaneWindow,
                        CreatePlaneWindowProc,
                        createPlaneWindow.m_hInstance,
                        hwnd
                    );
                    break;
                case 5000:
                    aboutWindow.Initialize(
                        aboutWindow,
                        AboutWindowProc,
                        aboutWindow.m_hInstance,
                        hwnd
                    );
                    break;
                case 6000:                    
                    break;
                default:
                    return DefWindowProc(hwnd, message, wParam, lParam);
                }
            }

            break;
            case WM_SIZE:
            {                
                SetWindowPos(closeButton.m_hwnd, 0,
                    GET_X_LPARAM(lParam) - (buttonWidthHeight + (nonClientAreaSize * 2)),
                    nonClientAreaSize, buttonWidthHeight, buttonWidthHeight,
                    SWP_NOZORDER | SWP_NOACTIVATE
                );
                SetWindowPos(maximizeRestoreButton.m_hwnd, 0,
                    GET_X_LPARAM(lParam) - ((buttonWidthHeight * 2) + (nonClientAreaSize * 2)),
                    nonClientAreaSize, buttonWidthHeight, buttonWidthHeight,
                    SWP_NOZORDER | SWP_NOACTIVATE
                );
                SetWindowPos(minimizeButton.m_hwnd, 0,
                    GET_X_LPARAM(lParam) - ((buttonWidthHeight * 3) + (nonClientAreaSize * 2)),
                    nonClientAreaSize, buttonWidthHeight, buttonWidthHeight,
                    SWP_NOZORDER | SWP_NOACTIVATE
                );
                SetWindowPos(createButton.m_hwnd, 0,
                    6 + 6 + 32, 6, 72, 32,
                    SWP_NOZORDER | SWP_NOACTIVATE
                );
                SetWindowPos(helpButton.m_hwnd, 0,
                    6 + 6 + 32 + 72, 6, 72, 32,
                    SWP_NOZORDER | SWP_NOACTIVATE
                );

                UINT nWidth = GET_X_LPARAM(lParam);
				UINT nHeight = GET_Y_LPARAM(lParam);
                mPWindow->OnResize(*mPWindow, hwnd, nWidth, nHeight);            
            }
            result = 0;
            wasHandled = true;
            break;
            case WM_PAINT:
            case WM_DISPLAYCHANGE:
            {				
				BeginPaint(hwnd, &ps);
                mPWindow->DrawingMainWindowContents(*mPWindow, hwnd);
				EndPaint(hwnd, &ps);
            }
            result = 0;
            wasHandled = true;
            break;
            case WM_DESTROY:
            {				               
                RoUninitialize();
                DestroyWindow(closeButton.m_hwnd);
                DestroyWindow(maximizeRestoreButton.m_hwnd);
                DestroyWindow(minimizeButton.m_hwnd);
                DestroyWindow(createButton.m_hwnd);
                DestroyWindow(helpButton.m_hwnd);
                PostQuitMessage(0);
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
