#ifndef BUTTON_CLASS_H
#define BUTTON_CLASS_H

#include "window_class.h"

class Button : public Window
{
public:
    using Window::Window;
    ~Button();

    static LRESULT CALLBACK MinMaxResClosButtonWindowProc(
        HWND hwnd, 
        UINT message,
        WPARAM wParam, 
        LPARAM lParam
    );

    HRESULT DrawingCloseButton(
        Button& object,
        int buttonSelection,
        int pressingButton
    );

    HRESULT DrawingMaximizeRestoreButton(
        Button& object,
        int buttonSelection,
        int pressingButton,
        int changeIcon
    );

    HRESULT DrawingMinimizeButton(
        Button& object,
        int buttonSelection,
        int pressingButton
    );

    static LRESULT CALLBACK MainPanelButtonWindowProc(
        HWND hwnd,
        UINT message,
        WPARAM wParam,
        LPARAM lParam
    );

    HRESULT DrawingMainPanelButton(
        Button& object,
        int buttonSelection,
        int pressingButton
    );

    static LRESULT CALLBACK RoundedRectButtonWindowProc(
        HWND hwnd, 
        UINT message, 
        WPARAM wParam, 
        LPARAM lParam
    );

    HRESULT DrawRoundedRectButton(
        Button& object,
        int buttonSelection,
        int pressingButton
    );

private:

};

#endif // !BUTTON_CLASS_H