#ifndef FIELD_CLASS_H
#define FIELD_CLASS_H

#include "window_class.h"

class Field : public Window
{
public:
    using Window::Window;
    ~Field();

    static const wchar_t* virtualKeyCodes(WPARAM wParam, int shiftDown);
    static bool writingTextToClipboardW(HWND hwnd, wchar_t* inputText);
    static const wchar_t* readingTextFromClipboardW(HWND hwnd);

    static LRESULT CALLBACK FieldWindowProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

    HRESULT DrawingField(
        Field& object,
        int buttonSelection,
        int setFocus,
        int drawingACaret,
        int movingACaret,
        int caretStartPosition,
        int permissionToRecordStartingPosition,
        const wchar_t* inputText
    );

private:
    RECT rc;
    wchar_t text[1000]{};

    // When you change the value - zero or one, the color of the frame changes, 
    // making it clear whether the input field is active or not.
    int setFocus{};

    // Timer number.
    UINT_PTR timeTheCaret{ 1 };
    int selectButton{};
    int pressingButton{};
    int drawingACaret{};
    int movingACaret{};
    int caretStartPosition{};
    int permissionToRecordStartingPosition{};
};

#endif // !FIELD_CLASS_H