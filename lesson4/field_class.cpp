#include "field_class.h"
#include "mouseTrackEvents_class.h"
#include "getParentWindow.h"
#include "globalVariables.h"

Field::~Field()
{
}

// The function returns the character that is defined in it.
const wchar_t* Field::virtualKeyCodes(WPARAM wParam, int shiftDown)
{
    const wchar_t* buffer{ L"" };

    if (!shiftDown)
    {
        if (wParam == 0xC0)
            buffer = L"`"; // ` key.
    }
    if (shiftDown)
    {
        if (wParam == 0xC0)
            buffer = L"~"; // ~ key.
    }

    // Numbers.
    if (!shiftDown)
    {
        if (wParam == 0x30)
            buffer = L"0"; // 0 key.

        if (wParam == 0x31)
            buffer = L"1"; // 1 key.

        if (wParam == 0x32)
            buffer = L"2"; // 2 key.

        if (wParam == 0x33)
            buffer = L"3"; // 3 key.

        if (wParam == 0x34)
            buffer = L"4"; // 4 key.

        if (wParam == 0x35)
            buffer = L"5"; // 5 key.

        if (wParam == 0x36)
            buffer = L"6"; // 6 key.

        if (wParam == 0x37)
            buffer = L"7"; // 7 key.

        if (wParam == 0x38)
            buffer = L"8"; // 8 key.

        if (wParam == 0x39)
            buffer = L"9"; // 9 key.
    }
    if (shiftDown)
    {
        if (wParam == 0x30)
            buffer = L")"; // ) key.

        if (wParam == 0x31)
            buffer = L"!"; // ! key.

        if (wParam == 0x32)
            buffer = L"@"; // @ key.

        if (wParam == 0x33)
            buffer = L"#"; // # key.

        if (wParam == 0x34)
            buffer = L"$"; // $ key.

        if (wParam == 0x35)
            buffer = L"%"; // % key.

        if (wParam == 0x36)
            buffer = L"^"; // ^ key.

        if (wParam == 0x37)
            buffer = L"&"; // & key.

        if (wParam == 0x38)
            buffer = L"*"; // * key.

        if (wParam == 0x39)
            buffer = L"("; // ( key.
    }

    if (!shiftDown)
    {
        // Lower case.
        if (wParam == 0x41)
            buffer = L"a"; // a key.

        if (wParam == 0x42)
            buffer = L"b"; // b key.

        if (wParam == 0x43)
            buffer = L"c"; // c key.

        if (wParam == 0x44)
            buffer = L"d"; // d key.

        if (wParam == 0x45)
            buffer = L"e"; // e key.

        if (wParam == 0x46)
            buffer = L"f"; // f key.

        if (wParam == 0x47)
            buffer = L"g"; // g key.

        if (wParam == 0x48)
            buffer = L"h"; // h key.

        if (wParam == 0x49)
            buffer = L"i"; // i key.

        if (wParam == 0x4A)
            buffer = L"j"; // j key.

        if (wParam == 0x4B)
            buffer = L"k"; // k key.

        if (wParam == 0x4C)
            buffer = L"l"; // l key.

        if (wParam == 0x4D)
            buffer = L"m"; // m key.    

        if (wParam == 0x4E)
            buffer = L"n"; // n key.

        if (wParam == 0x4F)
            buffer = L"o"; // o key.

        if (wParam == 0x50)
            buffer = L"p"; // p key.

        if (wParam == 0x51)
            buffer = L"q"; // q key.

        if (wParam == 0x52)
            buffer = L"r"; // r key.

        if (wParam == 0x53)
            buffer = L"s"; // s key.

        if (wParam == 0x54)
            buffer = L"t"; // t key.    

        if (wParam == 0x55)
            buffer = L"u"; // u key.

        if (wParam == 0x56)
            buffer = L"v"; // v key.

        if (wParam == 0x57)
            buffer = L"w"; // w key.

        if (wParam == 0x58)
            buffer = L"x"; // x key.

        if (wParam == 0x59)
            buffer = L"y"; // y key.

        if (wParam == 0x5A)
            buffer = L"z"; // z key.
    }
    if (shiftDown)
    {
        // Capital letters.
        if (wParam == 0x41)
            buffer = L"A"; // A key.

        if (wParam == 0x42)
            buffer = L"B"; // B key.

        if (wParam == 0x43)
            buffer = L"C"; // C key.

        if (wParam == 0x44)
            buffer = L"D"; // D key.

        if (wParam == 0x45)
            buffer = L"E"; // E key.

        if (wParam == 0x46)
            buffer = L"F"; // F key.

        if (wParam == 0x47)
            buffer = L"G"; // G key.

        if (wParam == 0x48)
            buffer = L"H"; // H key.

        if (wParam == 0x49)
            buffer = L"I"; // I key.

        if (wParam == 0x4A)
            buffer = L"J"; // J key.

        if (wParam == 0x4B)
            buffer = L"K"; // K key.

        if (wParam == 0x4C)
            buffer = L"L"; // L key.

        if (wParam == 0x4D)
            buffer = L"M"; // M key.    

        if (wParam == 0x4E)
            buffer = L"N"; // N key.

        if (wParam == 0x4F)
            buffer = L"O"; // O key.

        if (wParam == 0x50)
            buffer = L"P"; // P key.

        if (wParam == 0x51)
            buffer = L"Q"; // Q key.

        if (wParam == 0x52)
            buffer = L"R"; // R key.

        if (wParam == 0x53)
            buffer = L"S"; // S key.

        if (wParam == 0x54)
            buffer = L"T"; // T key.    

        if (wParam == 0x55)
            buffer = L"U"; // U key.

        if (wParam == 0x56)
            buffer = L"V"; // V key.

        if (wParam == 0x57)
            buffer = L"W"; // W key.

        if (wParam == 0x58)
            buffer = L"X"; // X key.

        if (wParam == 0x59)
            buffer = L"Y"; // Y key.

        if (wParam == 0x5A)
            buffer = L"Z"; // Z key.
    }

    if (!shiftDown)
    {
        if (wParam == 0xBD)
            buffer = L"-"; // - key.

        if (wParam == 0xBB)
            buffer = L"="; // = key.

        if (wParam == 0xDB)
            buffer = L"["; // [ key.

        if (wParam == 0xDD)
            buffer = L"]"; // ] key.

        if (wParam == 0xBA)
            buffer = L";"; // ; key.

        if (wParam == 0xDE)
            buffer = L"'"; // ' key.

        if (wParam == 0xDC)
            buffer = L"\\"; // \ key.

        if (wParam == 0xBC)
            buffer = L","; // , key.

        if (wParam == 0xBE)
            buffer = L"."; // . key.

        if (wParam == 0xBF)
            buffer = L"/"; // / key.
    }
    if (shiftDown)
    {
        if (wParam == 0xBD)
            buffer = L"_"; // _ key.

        if (wParam == 0xBB)
            buffer = L"+"; // + key.

        if (wParam == 0xDB)
            buffer = L"{"; // { key.

        if (wParam == 0xDD)
            buffer = L"}"; // } key.

        if (wParam == 0xBA)
            buffer = L":"; // : key.

        if (wParam == 0xDE)
            buffer = L"\""; // " key.

        if (wParam == 0xDC)
            buffer = L"|"; // | key.

        if (wParam == 0xBC)
            buffer = L"<"; // < key.

        if (wParam == 0xBE)
            buffer = L">"; // > key.

        if (wParam == 0xBF)
            buffer = L"?"; // ? key.
    }

    // Numbers(Numeric keypad).
    if (wParam == 0x60)
        buffer = L"0"; // 0 key.

    if (wParam == 0x61)
        buffer = L"1"; // 1 key.

    if (wParam == 0x62)
        buffer = L"2"; // 2 key.

    if (wParam == 0x63)
        buffer = L"3"; // 3 key.

    if (wParam == 0x64)
        buffer = L"4"; // 4 key.

    if (wParam == 0x65)
        buffer = L"5"; // 5 key.

    if (wParam == 0x66)
        buffer = L"6"; // 6 key.

    if (wParam == 0x67)
        buffer = L"7"; // 7 key.

    if (wParam == 0x68)
        buffer = L"8"; // 8 key.

    if (wParam == 0x69)
        buffer = L"9"; // 9 key.

    if (wParam == 0x6A)
        buffer = L"*"; // Multiply key.

    if (wParam == 0x6B)
        buffer = L"+"; // Add key.

    //if (wParam == 0x6C)
    //    buffer = L" "; // Separator key. ???

    if (wParam == 0x6D)
        buffer = L"-"; // Subtract key.

    if (wParam == 0x6E)
        buffer = L"."; // Decimal key.

    if (wParam == 0x6F)
        buffer = L"/"; // Divide key.


    if (wParam == 0x20)
        buffer = L" "; // space key.

    return buffer;
}

bool Field::writingTextToClipboardW(HWND hwnd, wchar_t* inputText)
{
    HGLOBAL hglbCopy{};
    wchar_t* wcharCopy{};
    UINT uFormat = CF_UNICODETEXT;

    if (hwnd == NULL)
        return FALSE;

    // Open the clipboard, and empty it. 
    if (!OpenClipboard(hwnd))
        return FALSE;
    EmptyClipboard();

    // If text is selected, copy it using the CF_UNICODETEXT format.
    size_t length = wcslen(inputText);

    if (length)
    {
        // Allocate a global memory object for the text. 
        hglbCopy = GlobalAlloc(GMEM_MOVEABLE,
            (length + 1) * sizeof(wchar_t));
        if (hglbCopy == NULL)
        {
            CloseClipboard();
            return FALSE;
        }

        // Lock the handle and copy the text to the buffer. 
        wcharCopy = (wchar_t*)GlobalLock(hglbCopy);

        if (wcharCopy) {
            wmemcpy(wcharCopy, inputText, length);
            // Null character manually added.
            wcharCopy[length] = L'\0';
        }
        else {
            CloseClipboard();
            return FALSE;
        }

        GlobalUnlock(hglbCopy);
        // If wide character string with a low-ASCII character, 
        // in UTF-16 it's going to be encoded as the low-ASCII byte followed by a NULL. 
        // Use CF_UNICODETEXT instead of CF_TEXT.
        SetClipboardData(uFormat, hglbCopy);
    }
    // If no text is selected, ?the label as a whole is copied?. 
    else
    {
        // Place a registered clipboard format, the owner-display 
        // format, and the CF_TEXT format on the clipboard using 
        // delayed rendering. 
        SetClipboardData(uFormat, NULL);
        SetClipboardData(CF_OWNERDISPLAY, NULL);
        SetClipboardData(CF_UNICODETEXT, NULL);
    }

    CloseClipboard();

    return TRUE;
}

const wchar_t* Field::readingTextFromClipboardW(HWND hwnd)
{
    const wchar_t* wcharPaste{ L"" };
    HGLOBAL hglb;

    // Checking the incoming format.
    if (!IsClipboardFormatAvailable(CF_UNICODETEXT))
        return FALSE;
    // Open the clipboard.
    if (!OpenClipboard(hwnd))
        return FALSE;
    // Extract text from clipboard.
    hglb = GetClipboardData(CF_UNICODETEXT);

    if (hglb != NULL)
    {
        // Block memory.
        wcharPaste = (wchar_t*)GlobalLock(hglb);
        if (wcharPaste != NULL)
        {
            // Unlock memory.
            GlobalUnlock(hglb);
        }
    }
    // Close the clipboard.
    CloseClipboard();

    return wcharPaste;
}

LRESULT CALLBACK Field::FieldWindowProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    LRESULT result = 0;
    PAINTSTRUCT ps;
    HRESULT hr;

    MouseTrackEvents mouseEvents;
    
    //wchar_t msg[32]{};

    SetCursor(LoadCursorW(0, IDC_IBEAM));

    if (message == WM_CREATE)
    {
        LPCREATESTRUCT pcs = (LPCREATESTRUCT)lParam;
        Field* pField = (Field*)pcs->lpCreateParams;

        // The "SetWindowLongPtrW" function allows you to create several windows
        // using one "WindowProc" function for all.
        ::SetWindowLongPtrW(
            hwnd,
            GWLP_USERDATA,
            reinterpret_cast<LONG_PTR>(pField)
        );

        hr = pField->CreateD2D1Factory(*pField);

        if (SUCCEEDED(hr))
        {
            hr = pField->CreateD3D11Device(*pField);

            hr = pField->CreateSwapChain(*pField, NULL);
            if (SUCCEEDED(hr))
            {
                hr = pField->ConfigureSwapChain(*pField, hwnd);
                hr = pField->CreateDirectComposition(*pField, hwnd);
            }
        }

        // Since the mouse cursor tracking area is the entire window, 
        // the width and height parameters are zero.
        pField->rc = mouseEvents.controlElementArea(hwnd, 0, 0, 0, 0);
        result = 1;
    }
    else
    {
        Field* pField = reinterpret_cast<Field*>(
            ::GetWindowLongPtrW(
                hwnd,
                GWLP_USERDATA
            ));

        bool wasHandled = false;

        if (pField)
        {
            switch (message)
            {
            case WM_SETFOCUS:
            {

            }
            return 0;
            break;
            case WM_KILLFOCUS:
            {
                // Returning keyboard focus to the parent window.
                HWND parent = GetParentWindow(hwnd);
                SetFocus(parent);
                pField->setFocus = 0;
                // When changing focus to the parent window, 
                // turn off the timer and hide the caret.
                if (pField->setFocus == 0)
                {
                    if (pField->permissionToRecordStartingPosition == 1)
                    {
                        // Write down the default value.
                        pField->caretStartPosition = 0;
                        // We cancel the ban on recording the position 
                        // where text selection began into the variable *caretStartPosition*.
                        pField->permissionToRecordStartingPosition = 0;
                    }
                    KillTimer(hwnd, pField->timeTheCaret);
                    pField->drawingACaret = 0;
                    InvalidateRect(hwnd, NULL, FALSE);
                }
            }
            return 0;
            break;
            case WM_KEYDOWN:
            {
                if (!HIBYTE(GetKeyState(VK_CONTROL)))
                {
                    if (HIBYTE(GetKeyState(VK_SHIFT)) && wcslen(pField->virtualKeyCodes(wParam, 1)) != 0)
                    {
                        wchar_t* pTextA = new wchar_t[wcslen(pField->text) + 1] {};
                        wchar_t* pTextB = new wchar_t[wcslen(pField->text) + 1] {};

                        int choicePosition{};
                        int deleteChar{};

                        // The caret is located to the left of the position where text selection began.
                        if (pField->caretStartPosition > pField->movingACaret && pField->permissionToRecordStartingPosition == 1)
                        {
                            // We write to a variable position that will divide the text into two parts.
                            choicePosition = pField->caretStartPosition;
                            // We determine the number of characters to be removed.
                            deleteChar = pField->caretStartPosition - pField->movingACaret;

                            // We cancel the ban on recording the position 
                            // where text selection began into the variable *caretStartPosition*.
                            pField->permissionToRecordStartingPosition = 0;
                            // Write down the default value.
                            pField->caretStartPosition = 0;
                        }
                        // The caret is located to the right of the position where text selection began.
                        else if (pField->movingACaret > pField->caretStartPosition && pField->permissionToRecordStartingPosition == 1)
                        {
                            // We write to a variable position that will divide the text into two parts.
                            choicePosition = pField->movingACaret;
                            // We determine the number of characters to be removed.
                            deleteChar = pField->movingACaret - pField->caretStartPosition;

                            // In order to move the carriage back by the number of characters to be deleted.
                            // This is only relevant when selecting text with Shift pressed to the right.
                            pField->movingACaret = pField->movingACaret - deleteChar;

                            // We cancel the ban on recording the position 
                            // where text selection began into the variable *caretStartPosition*.
                            pField->permissionToRecordStartingPosition = 0;
                            // Write down the default value.
                            pField->caretStartPosition = 0;
                        }
                        else if (pField->permissionToRecordStartingPosition == 0)
                        {
                            // Text not selected using Shift key.
                            choicePosition = pField->movingACaret;
                            // We remove only one character.
                            deleteChar = 0;
                        }
                        // Before the a caret...                        
                        for (size_t i = 0; i < choicePosition; i++)
                        {
                            pTextA[i] = pField->text[i];
                        }
                        // ...and after the a caret.                       
                        for (size_t i = 0; i < wcslen(pField->text) - choicePosition; i++)
                        {
                            pTextB[i] = pField->text[choicePosition + i];
                        }
                        // Copy the left part to the variable *text*.
                        wcsncpy_s(pField->text, pTextA, wcslen(pTextA));
                        // We subtract the characters that need to be removed from the total.
                        size_t sz = wcslen(pField->text) - deleteChar;
                        // And then we copy the remaining characters into the variable *text*.
                        wcsncpy_s(pField->text, pField->text, sz);
                        // Add a new symbol.
                        wcscat_s(pField->text, 1000, pField->virtualKeyCodes(wParam, 1));
                        // Copy the right side to the variable *text*.
                        wcscat_s(pField->text, 1000, pTextB);

                        pField->movingACaret++;

                        // When typing, the caret does not disappear.
                        pField->drawingACaret = 1;

                        delete[] pTextA;
                        delete[] pTextB;
                    }
                    else if (wcslen(pField->virtualKeyCodes(wParam, 1)) != 0)
                    {
                        wchar_t* pTextA = new wchar_t[wcslen(pField->text) + 1] {};
                        wchar_t* pTextB = new wchar_t[wcslen(pField->text) + 1] {};

                        int choicePosition{};
                        int deleteChar{};

                        // The caret is located to the left of the position where text selection began.
                        if (pField->caretStartPosition > pField->movingACaret && pField->permissionToRecordStartingPosition == 1)
                        {
                            // We write to a variable position that will divide the text into two parts.
                            choicePosition = pField->caretStartPosition;
                            // We determine the number of characters to be removed.
                            deleteChar = pField->caretStartPosition - pField->movingACaret;

                            // We cancel the ban on recording the position 
                            // where text selection began into the variable *caretStartPosition*.
                            pField->permissionToRecordStartingPosition = 0;
                            // Write down the default value.
                            pField->caretStartPosition = 0;
                        }
                        // The caret is located to the right of the position where text selection began.
                        else if (pField->movingACaret > pField->caretStartPosition && pField->permissionToRecordStartingPosition == 1)
                        {
                            // We write to a variable position that will divide the text into two parts.
                            choicePosition = pField->movingACaret;
                            // We determine the number of characters to be removed.
                            deleteChar = pField->movingACaret - pField->caretStartPosition;

                            // In order to move the carriage back by the number of characters to be deleted.
                            // This is only relevant when selecting text with Shift pressed to the right.
                            pField->movingACaret = pField->movingACaret - deleteChar;

                            // We cancel the ban on recording the position 
                            // where text selection began into the variable *caretStartPosition*.
                            pField->permissionToRecordStartingPosition = 0;
                            // Write down the default value.
                            pField->caretStartPosition = 0;
                        }
                        else if (pField->permissionToRecordStartingPosition == 0)
                        {
                            // Text not selected using Shift key.
                            choicePosition = pField->movingACaret;
                            // We remove only one character.
                            deleteChar = 0;
                        }
                        // Before the a caret...                        
                        for (size_t i = 0; i < choicePosition; i++)
                        {
                            pTextA[i] = pField->text[i];
                        }
                        // ...and after the a caret.                       
                        for (size_t i = 0; i < wcslen(pField->text) - choicePosition; i++)
                        {
                            pTextB[i] = pField->text[choicePosition + i];
                        }
                        // Copy the left part to the variable *text*.
                        wcsncpy_s(pField->text, pTextA, wcslen(pTextA));
                        // We subtract the characters that need to be removed from the total.
                        size_t sz = wcslen(pField->text) - deleteChar;
                        // And then we copy the remaining characters into the variable *text*.
                        wcsncpy_s(pField->text, pField->text, sz);
                        // Add a new symbol.
                        wcscat_s(pField->text, 1000, pField->virtualKeyCodes(wParam, 0));
                        // Copy the right side to the variable *text*.
                        wcscat_s(pField->text, 1000, pTextB);
                       
                        pField->movingACaret++;

                        // When typing, the caret does not disappear.
                        pField->drawingACaret = 1;

                        delete[] pTextA;
                        delete[] pTextB;
                    }
                }

                if (HIBYTE(GetKeyState(VK_BACK)) & 0x80)
                {
                    if (wcslen(pField->text))
                    {
                        wchar_t* pTextA = new wchar_t[wcslen(pField->text) + 1] {};
                        wchar_t* pTextB = new wchar_t[wcslen(pField->text) + 1] {};

                        int choicePosition{};
                        int deleteChar{};

                        // The caret is located to the left of the position where text selection began.
                        if (pField->caretStartPosition > pField->movingACaret && pField->permissionToRecordStartingPosition == 1)
                        {
                            // We write to a variable position that will divide the text into two parts.
                            choicePosition = pField->caretStartPosition;
                            // We determine the number of characters to be removed.
                            deleteChar = pField->caretStartPosition - pField->movingACaret;

                            // We cancel the ban on recording the position 
                            // where text selection began into the variable *caretStartPosition*.
                            pField->permissionToRecordStartingPosition = 0;
                            // Write down the default value.
                            pField->caretStartPosition = 0;
                        }
                        // The caret is located to the right of the position where text selection began.
                        else if (pField->movingACaret > pField->caretStartPosition && pField->permissionToRecordStartingPosition == 1)
                        {
                            // We write to a variable position that will divide the text into two parts.
                            choicePosition = pField->movingACaret;
                            // We determine the number of characters to be removed.
                            deleteChar = pField->movingACaret - pField->caretStartPosition;

                            // We cancel the ban on recording the position 
                            // where text selection began into the variable *caretStartPosition*.
                            pField->permissionToRecordStartingPosition = 0;
                            // Write down the default value.
                            pField->caretStartPosition = 0;
                        }
                        else if (pField->permissionToRecordStartingPosition == 0)
                        {
                            // Text not selected using Shift key.
                            choicePosition = pField->movingACaret;
                            // We remove only one character.
                            deleteChar = 1;
                        }
                        // Before the a caret...                        
                        for (size_t i = 0; i < choicePosition; i++)
                        {
                            pTextA[i] = pField->text[i];
                        }
                        // ...and after the a caret.                       
                        for (size_t i = 0; i < wcslen(pField->text) - choicePosition; i++)
                        {
                            pTextB[i] = pField->text[choicePosition + i];
                        }
                        // Copy the left part to the variable *text*.
                        wcsncpy_s(pField->text, pTextA, wcslen(pTextA));
                        // Copying the left side into the variable *text* excluding the last character.                                                                                            
                        size_t sz = wcslen(pField->text) - deleteChar;
                        wcsncpy_s(pField->text, pField->text, sz);

                        pField->movingACaret = static_cast<int>(wcslen(pField->text));

                        // Copy the right side to the variable *text*.
                        wcscat_s(pField->text, 1000, pTextB);

                        // When typing, the caret does not disappear.
                        pField->drawingACaret = 1;

                        delete[] pTextA;
                        delete[] pTextB;
                    }
                }

                if (HIBYTE(GetKeyState(VK_RETURN)) & 0x80)
                {
                    // Returning keyboard focus to the parent window.
                    HWND parent = GetParentWindow(hwnd);
                    SetFocus(parent);
                    pField->setFocus = 0;
                    // When changing focus to the parent window, 
                    // turn off the timer and hide the caret.
                    if (pField->setFocus == 0)
                    {
                        pField->drawingACaret = 0;

                        // When you press Enter, we remove the text selection 
                        // made when you pressed the Shift key.
                        if (pField->permissionToRecordStartingPosition == 1)
                        {
                            // Write down the default value.
                            pField->caretStartPosition = 0;
                            // We cancel the ban on recording the position 
                            // where text selection began into the variable *caretStartPosition*.
                            pField->permissionToRecordStartingPosition = 0;
                        }

                        KillTimer(hwnd, pField->timeTheCaret);
                    }
                }

                if (!HIBYTE(GetKeyState(VK_SHIFT)))
                {
                    if (HIBYTE(GetKeyState(VK_LEFT)))
                    {
                        if (pField->movingACaret > 0)
                        {
                            // Move the caret to the left.
                            pField->movingACaret--;
                            // When you press Enter, we remove the text selection 
                            // made when you pressed the Shift key.
                            if (pField->permissionToRecordStartingPosition == 1)
                            {
                                // Write down the default value.
                                pField->caretStartPosition = 0;
                                // We cancel the ban on recording the position 
                                // where text selection began into the variable *caretStartPosition*.
                                pField->permissionToRecordStartingPosition = 0;
                                // To prevent the carriage from moving one character to the left, 
                                // subtract one from the variable *movingACaret*.
                                pField->movingACaret = pField->movingACaret + 1;
                            }
                        }
                        else if (pField->movingACaret == 0)
                        {
                            // The carriage is in the extreme left position.

                            // When you press Enter, we remove the text selection 
                            // made when you pressed the Shift key.
                            if (pField->permissionToRecordStartingPosition == 1)
                            {
                                // Write down the default value.
                                pField->caretStartPosition = 0;
                                // We cancel the ban on recording the position 
                                // where text selection began into the variable *caretStartPosition*.
                                pField->permissionToRecordStartingPosition = 0;
                            }
                        }
                        // When typing, the caret does not disappear.
                        pField->drawingACaret = 1;
                    }
                }

                if (!HIBYTE(GetKeyState(VK_SHIFT)))
                {
                    if (HIBYTE(GetKeyState(VK_RIGHT)))
                    {
                        if (pField->movingACaret < wcslen(pField->text))
                        {
                            // Move the caret to the right.
                            pField->movingACaret++;
                            // When you press Enter, we remove the text selection 
                            // made when you pressed the Shift key.
                            if (pField->permissionToRecordStartingPosition == 1)
                            {
                                // Write down the default value.
                                pField->caretStartPosition = 0;
                                // We cancel the ban on recording the position 
                                // where text selection began into the variable *caretStartPosition*.
                                pField->permissionToRecordStartingPosition = 0;
                                // To prevent the carriage from moving one character to the right, 
                                // subtract one from the variable **.
                                pField->movingACaret = pField->movingACaret - 1;
                            }
                        }
                        else if (pField->movingACaret == wcslen(pField->text))
                        {
                            // The carriage is in the extreme left position.

                            // When you press Enter, we remove the text selection 
                            // made when you pressed the Shift key.
                            if (pField->permissionToRecordStartingPosition == 1)
                            {
                                // Write down the default value.
                                pField->caretStartPosition = 0;
                                // We cancel the ban on recording the position 
                                // where text selection began into the variable *caretStartPosition*.
                                pField->permissionToRecordStartingPosition = 0;
                            }
                        }
                        // When typing, the caret does not disappear.
                        pField->drawingACaret = 1;
                    }
                }

                if (HIBYTE(GetKeyState(VK_UP)) & 0x80)
                {
                    // Moving the caret to the far left position and remove the selection.
                    pField->movingACaret = 0;

                    // When you press Enter, we remove the text selection 
                    // made when you pressed the Shift key.
                    if (pField->permissionToRecordStartingPosition == 1)
                    {
                        // Write down the default value.
                        pField->caretStartPosition = 0;
                        // We cancel the ban on recording the position 
                         // where text selection began into the variable *caretStartPosition*.
                        pField->permissionToRecordStartingPosition = 0;
                    }
                }

                if (HIBYTE(GetKeyState(VK_DOWN)) & 0x80)
                {
                    // Moving the caret to the far right position and remove the selection.
                    pField->movingACaret = static_cast<int>(wcslen(pField->text));

                    // When you press Enter, we remove the text selection 
                    // made when you pressed the Shift key.
                    if (pField->permissionToRecordStartingPosition == 1)
                    {
                        // Write down the default value.
                        pField->caretStartPosition = 0;
                        // We cancel the ban on recording the position 
                         // where text selection began into the variable *caretStartPosition*.
                        pField->permissionToRecordStartingPosition = 0;
                    }
                }

                // Select text with the Shift key pressed and the left button pressed.
                if (HIBYTE(GetKeyState(VK_SHIFT)) && HIBYTE(GetKeyState(VK_LEFT)))
                {
                    if (pField->movingACaret > 0)
                    {
                        // The condition is met once.
                        if (pField->permissionToRecordStartingPosition == 0)
                        {
                            // Determine the starting position for selecting text.
                            pField->caretStartPosition = pField->movingACaret;
                            // In order for the condition to be fulfilled once, 
                            // we assign one to the variable *permissionToRecordStartingPosition*.
                            pField->permissionToRecordStartingPosition = 1;
                        }
                        // Move the caret to the left.
                        pField->movingACaret--;
                    }
                    // When typing, the caret does not disappear.
                    pField->drawingACaret = 1;
                }

                // Select the text with the Shift key pressed and the right button.
                if (HIBYTE(GetKeyState(VK_SHIFT)) && HIBYTE(GetKeyState(VK_RIGHT)))
                {
                    if (pField->movingACaret < wcslen(pField->text))
                    {
                        // The condition is met once.
                        if (pField->permissionToRecordStartingPosition == 0)
                        {
                            // Determine the starting position for selecting text.
                            pField->caretStartPosition = pField->movingACaret;
                            // In order for the condition to be fulfilled once, 
                            // we assign one to the variable *permissionToRecordStartingPosition*.
                            pField->permissionToRecordStartingPosition = 1;
                        }
                        // Move the caret to the left.
                        pField->movingACaret++;
                    }
                    // When typing, the caret does not disappear.
                    pField->drawingACaret = 1;
                }

                if (HIBYTE(GetKeyState(VK_CONTROL)) && HIBYTE(GetKeyState(0x43)))
                {
                    //
                    wchar_t* pTextA = new wchar_t[wcslen(pField->text) + 1] {};

                    int choicePosition{};
                    int deleteChar{};
                    wchar_t textBuffer[1000]{};

                    // The caret is located to the left of the position where text selection began.
                    if (pField->caretStartPosition > pField->movingACaret && pField->permissionToRecordStartingPosition == 1)
                    {
                        // We write to a variable position that will divide the text into two parts.
                        choicePosition = pField->caretStartPosition;
                        // We determine the number of characters to be removed.
                        deleteChar = pField->caretStartPosition - pField->movingACaret;
                    }
                    // The caret is located to the right of the position where text selection began.
                    else if (pField->movingACaret > pField->caretStartPosition && pField->permissionToRecordStartingPosition == 1)
                    {
                        // We write to a variable position that will divide the text into two parts.
                        choicePosition = pField->movingACaret;
                        // We determine the number of characters to be removed.
                        deleteChar = pField->movingACaret - pField->caretStartPosition;
                    }
                    else if (pField->permissionToRecordStartingPosition == 0)
                    {
                        // Text not selected using Shift key.
                        choicePosition = pField->movingACaret;

                        deleteChar = 0;
                    }

                    for (size_t i = 0; i < choicePosition; i++)
                    {
                        pTextA[i] = pField->text[i];
                    }
                    // Copy the left part to the variable *text*.
                    wcsncpy_s(textBuffer, pTextA, wcslen(pTextA));

                    //
                    wchar_t* pBufferText = new wchar_t[wcslen(textBuffer) + 1] {};

                    for (size_t i = 0; i < deleteChar; i++)
                    {
                        pBufferText[i] = textBuffer[(wcslen(textBuffer) - deleteChar) + i];
                    }

                    wcsncpy_s(textBuffer, pBufferText, wcslen(textBuffer));
                    //

                    pField->writingTextToClipboardW(hwnd, textBuffer);

                    delete[] pBufferText;
                    delete[] pTextA;
                }

                if (HIBYTE(GetKeyState(VK_CONTROL)) && HIBYTE(GetKeyState(0x58)))
                {
                    wchar_t* pTextA = new wchar_t[wcslen(pField->text) + 1] {};
                    wchar_t* pTextB = new wchar_t[wcslen(pField->text) + 1] {};

                    int choicePosition{};
                    int deleteChar{};
                    wchar_t textBuffer[1000]{};

                    // The caret is located to the left of the position where text selection began.
                    if (pField->caretStartPosition > pField->movingACaret && pField->permissionToRecordStartingPosition == 1)
                    {
                        // We write to a variable position that will divide the text into two parts.
                        choicePosition = pField->caretStartPosition;
                        // We determine the number of characters to be removed.
                        deleteChar = pField->caretStartPosition - pField->movingACaret;

                        // We cancel the ban on recording the position 
                        // where text selection began into the variable *caretStartPosition*.
                        pField->permissionToRecordStartingPosition = 0;
                        // Write down the default value.
                        pField->caretStartPosition = 0;
                    }
                    // The caret is located to the right of the position where text selection began.
                    else if (pField->movingACaret > pField->caretStartPosition && pField->permissionToRecordStartingPosition == 1)
                    {
                        // We write to a variable position that will divide the text into two parts.
                        choicePosition = pField->movingACaret;
                        // We determine the number of characters to be removed.
                        deleteChar = pField->movingACaret - pField->caretStartPosition;

                        // We cancel the ban on recording the position 
                        // where text selection began into the variable *caretStartPosition*.
                        pField->permissionToRecordStartingPosition = 0;
                        // Write down the default value.
                        pField->caretStartPosition = 0;
                    }
                    else if (pField->permissionToRecordStartingPosition == 0)
                    {
                        // Text not selected using Shift key.
                        choicePosition = pField->movingACaret;
                        // We remove only one character.
                        deleteChar = 0;
                    }
                    // Before the a caret...                        
                    for (size_t i = 0; i < choicePosition; i++)
                    {
                        pTextA[i] = pField->text[i];
                    }
                    // ...and after the a caret.                       
                    for (size_t i = 0; i < wcslen(pField->text) - choicePosition; i++)
                    {
                        pTextB[i] = pField->text[choicePosition + i];
                    }
                    // Copy the left part to the variable *text*.
                    wcsncpy_s(pField->text, pTextA, wcslen(pTextA));

                    // Copy the left part to the variable *textBuffer*.
                    wcsncpy_s(textBuffer, pTextA, wcslen(pTextA));

                    //
                    wchar_t* pBufferText = new wchar_t[wcslen(textBuffer) + 1] {};

                    for (size_t i = 0; i < deleteChar; i++)
                    {
                        pBufferText[i] = textBuffer[(wcslen(textBuffer) - deleteChar) + i];
                    }

                    wcsncpy_s(textBuffer, pBufferText, wcslen(textBuffer));
                    //

                    pField->writingTextToClipboardW(hwnd, textBuffer);

                    delete[] pBufferText;

                    // Copying the left side into the variable *text* excluding the last character.                                                                                            
                    size_t sz = wcslen(pField->text) - deleteChar;
                    wcsncpy_s(pField->text, pField->text, sz);

                    pField->movingACaret = static_cast<int>(wcslen(pField->text));

                    // Copy the right side to the variable *text*.
                    wcscat_s(pField->text, 1000, pTextB);

                    // When typing, the caret does not disappear.
                    pField->drawingACaret = 1;

                    delete[] pTextA;
                    delete[] pTextB;
                }

                if (HIBYTE(GetKeyState(VK_CONTROL)) && HIBYTE(GetKeyState(0x56)))
                {
                    wchar_t* pTextA = new wchar_t[wcslen(pField->text) + 1] {};
                    wchar_t* pTextB = new wchar_t[wcslen(pField->text) + 1] {};

                    int choicePosition{};
                    int deleteChar{};

                    // The caret is located to the left of the position where text selection began.
                    if (pField->caretStartPosition > pField->movingACaret && pField->permissionToRecordStartingPosition == 1)
                    {
                        // We write to a variable position that will divide the text into two parts.
                        choicePosition = pField->caretStartPosition;
                        // We determine the number of characters to be removed.
                        deleteChar = pField->caretStartPosition - pField->movingACaret;

                        // We cancel the ban on recording the position 
                        // where text selection began into the variable *caretStartPosition*.
                        pField->permissionToRecordStartingPosition = 0;
                        // Write down the default value.
                        pField->caretStartPosition = 0;
                    }
                    // The caret is located to the right of the position where text selection began.
                    else if (pField->movingACaret > pField->caretStartPosition && pField->permissionToRecordStartingPosition == 1)
                    {
                        // We write to a variable position that will divide the text into two parts.
                        choicePosition = pField->movingACaret;
                        // We determine the number of characters to be removed.
                        deleteChar = pField->movingACaret - pField->caretStartPosition;

                        // We cancel the ban on recording the position 
                        // where text selection began into the variable *caretStartPosition*.
                        pField->permissionToRecordStartingPosition = 0;
                        // Write down the default value.
                        pField->caretStartPosition = 0;
                    }
                    else if (pField->permissionToRecordStartingPosition == 0)
                    {
                        // Text not selected using Shift key.
                        choicePosition = pField->movingACaret;
                        // We remove only one character.
                        deleteChar = 0;
                    }
                    // Before the a caret...                        
                    for (size_t i = 0; i < choicePosition; i++)
                    {
                        pTextA[i] = pField->text[i];
                    }
                    // ...and after the a caret.                       
                    for (size_t i = 0; i < wcslen(pField->text) - choicePosition; i++)
                    {
                        pTextB[i] = pField->text[choicePosition + i];
                    }
                    // Copy the left part to the variable *text*.
                    wcsncpy_s(pField->text, pTextA, wcslen(pTextA));
                    // We subtract the characters that need to be removed from the total.
                    size_t sz = wcslen(pField->text) - deleteChar;
                    // And then we copy the remaining characters into the variable *text*.
                    wcsncpy_s(pField->text, pField->text, sz);
                    // Add a new symbol.
                    wcscat_s(pField->text, 1000, pField->readingTextFromClipboardW(hwnd));

                    pField->movingACaret = wcslen(pField->text);

                    // Copy the right side to the variable *text*.
                    wcscat_s(pField->text, 1000, pTextB);

                    // When typing, the caret does not disappear.
                    pField->drawingACaret = 1;

                    delete[] pTextA;
                    delete[] pTextB;
                }

                InvalidateRect(hwnd, NULL, FALSE);
            }
            return 0;
            break;
            case WM_TIMER:
            {
                // In order for the caret to disappear and reappear, 
                // we must fulfill the following conditions.
                if (pField->drawingACaret == 0)
                {
                    pField->drawingACaret = 1;
                    InvalidateRect(hwnd, NULL, FALSE);
                }
                else if (pField->drawingACaret == 1)
                {
                    pField->drawingACaret = 0;
                    InvalidateRect(hwnd, NULL, FALSE);
                }
            }
            return 0;
            break;
            case WM_LBUTTONDOWN:
                pField->pressingButton = mouseEvents.OnButtonDown(hwnd, pField->rc);

                if (pField->selectButton)
                {
                    // Returning keyboard focus to the parent window.
                    HWND parent = GetParentWindow(hwnd);
                    SetFocus(parent);

                    // Sets the keyboard focus to the specified window. 
                    // The window must be attached to the calling thread's message queue.
                    // HWND - A handle to the window that will receive the keyboard input. 
                    // If this parameter is NULL, keystrokes are ignored.                    
                    SetFocus(hwnd);
                    pField->setFocus = 1;
                                      
                    if (wcslen(pField->text) == 0)
                    {
                        // If the text is missing we just start the timer.
                        SetTimer(hwnd, pField->timeTheCaret, 800, (TIMERPROC)NULL);
                    }
                    else if (wcslen(pField->text) > 0 && pField->permissionToRecordStartingPosition == 0)
                    {
                        // If the text is present but not selected, 
                        // we move the caret to the extreme right, 
                        // highlight the text with color and turn on the timer.
                        pField->movingACaret = 0;

                        if (pField->permissionToRecordStartingPosition == 0)
                        {
                            // Determine the starting position for selecting text.
                            pField->caretStartPosition = static_cast<int>(wcslen(pField->text));
                            // In order for the condition to be fulfilled once, 
                            // we assign one to the variable *permissionToRecordStartingPosition*.
                            pField->permissionToRecordStartingPosition = 1;
                        }
                        SetTimer(hwnd, pField->timeTheCaret, 800, (TIMERPROC)NULL);
                    }
                    else if (wcslen(pField->text) > 0 && pField->permissionToRecordStartingPosition == 1)
                    {
                        // If the text is present and selected, 
                        // we move the caret to the far right position, 
                        // remove the text highlighting color and turn on the timer.
                        pField->movingACaret = static_cast<int>(wcslen(pField->text));

                        if (pField->permissionToRecordStartingPosition == 1)
                        {
                            // Write down the default value.
                            pField->caretStartPosition = 0;
                            // We cancel the ban on recording the position 
                            // where text selection began into the variable *caretStartPosition*.
                            pField->permissionToRecordStartingPosition = 0;
                        }
                        SetTimer(hwnd, pField->timeTheCaret, 800, (TIMERPROC)NULL);
                    }
                }
                return 0;
                break;
            case WM_LBUTTONUP:
                pField->pressingButton = mouseEvents.OnButtonUp(hwnd, pField->rc);

                if (pField->selectButton)
                {

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
                    pField->selectButton = mouseEvents.OnMouseMove(
                        mouseEvents,
                        hwnd,
                        pField->rc,
                        GET_X_LPARAM(lParam),
                        GET_Y_LPARAM(lParam)
                    );

                }
                return 0;
                break;
            case WM_MOUSELEAVE:

                // TODO: Handle the mouse-leave message.
                pField->selectButton = mouseEvents.Reset(mouseEvents, hwnd);

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
                pField->OnResize(*pField, hwnd, nWidth, nHeight);
            }
            result = 0;
            wasHandled = true;
            break;
            case WM_PAINT:
            case WM_DISPLAYCHANGE:
            {
                BeginPaint(hwnd, &ps);
                pField->DrawingField(
                    *pField,
                    pField->selectButton,
                    pField->setFocus,
                    pField->drawingACaret,
                    pField->movingACaret,
                    pField->caretStartPosition,
                    pField->permissionToRecordStartingPosition,
                    pField->text
                );
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

HRESULT Field::DrawingField(
    Field& object,
    int buttonSelection,
    int setFocus,
    int drawingACaret,
    int movingACaret,
    int caretStartPosition,
    int permissionToRecordStartingPosition,
    const wchar_t* inputText
)
{
    HRESULT hr = S_OK;

    if (object.m_pD2DDeviceContext.Get() && object.m_pDXGISwapChain.Get())
    {
        if (buttonSelection < 0 || setFocus < 0)
        {
            MessageBox(NULL,
                L"DrawingField: One or more parameters are less than zero!",
                object.m_windowTitle,
                NULL);

            return hr = 1;
        }

        D2D1_SIZE_F size = object.m_pD2DDeviceContext.Get()->GetSize();

        object.m_pD2DDeviceContext.Get()->BeginDraw();
        object.m_pD2DDeviceContext.Get()->Clear();

        // Drawing a input field.
        // Creating brushes.
        Microsoft::WRL::ComPtr<ID2D1SolidColorBrush> pBackgroundBrush;
        Microsoft::WRL::ComPtr<ID2D1SolidColorBrush> pOutlinerBrush;
        Microsoft::WRL::ComPtr<ID2D1SolidColorBrush> pRoundedRectangleBrush;
        Microsoft::WRL::ComPtr<ID2D1SolidColorBrush> pCaretBrush;
        Microsoft::WRL::ComPtr<ID2D1SolidColorBrush> pTextSelection;
        Microsoft::WRL::ComPtr<ID2D1SolidColorBrush> pTextBrush;

        // Drawing a background that matches the main color of the application.
        hr = object.m_pD2DDeviceContext.Get()->CreateSolidColorBrush(
            D2D1::ColorF(0xFEE3EE, 1.0),
            pBackgroundBrush.ReleaseAndGetAddressOf()
        );

        if (SUCCEEDED(hr))
        {
            object.m_pD2DDeviceContext.Get()->FillRectangle(
                D2D1::RectF(
                    0.0f,
                    0.0f,
                    size.width,
                    size.height
                ),
                pBackgroundBrush.Get()
            );
        
            // Drawing the background for the text.
            // An indent of two pixels is needed to neatly round the corners.
            hr = object.m_pD2DDeviceContext.Get()->CreateSolidColorBrush(
                D2D1::ColorF(0xDC8095, 1),
                pRoundedRectangleBrush.ReleaseAndGetAddressOf()
            );

            if (SUCCEEDED(hr))
            {
                object.m_pD2DDeviceContext.Get()->FillRoundedRectangle(
                    D2D1::RoundedRect(
                        D2D1::RectF(
                            0.0f + 2.0f,
                            0.0f + 2.0f,
                            size.width - 2.0f,
                            size.height - 2.0f
                        ),
                        6.f,
                        6.f
                    ),
                    pRoundedRectangleBrush.Get()
                );
                // If the text input field is not active, 
                // it is not highlighted with a colored frame.
                if (setFocus == 0)
                {
                    hr = object.m_pD2DDeviceContext.Get()->CreateSolidColorBrush(
                        D2D1::ColorF(0xA94F63, 1),
                        pOutlinerBrush.ReleaseAndGetAddressOf()
                    );
                }
                // If a text input field is active, it is highlighted with a colored frame.
                if (setFocus == 1)
                {
                    hr = object.m_pD2DDeviceContext.Get()->CreateSolidColorBrush(
                        D2D1::ColorF(0x4264C2, 1),
                        pOutlinerBrush.ReleaseAndGetAddressOf()
                    );
                }

                if (SUCCEEDED(hr))
                {
                    object.m_pD2DDeviceContext.Get()->DrawRoundedRectangle(
                        D2D1::RoundedRect(
                            D2D1::RectF(
                                0.0f + 2.0f,
                                0.0f + 2.0f,
                                size.width - 2.0f,
                                size.height - 2.0f
                            ),
                            6.f,
                            6.f
                        ),
                        pOutlinerBrush.Get(), 1
                    );
                }       
            }           
        }

        // Creating text format.
        Microsoft::WRL::ComPtr<IDWriteTextFormat> pTextFormat;
        Microsoft::WRL::ComPtr<IDWriteTextLayout> pTextLayout;
        Microsoft::WRL::ComPtr<IDWriteTextLayout> pCaretStartPosition;

        DWRITE_TEXT_METRICS textMetrics = { 0 };
        DWRITE_TEXT_METRICS partialTextSelection = { 0 };

        DWRITE_HIT_TEST_METRICS hitTestMetricsCaretPosition{};
       
        const wchar_t* text{ L"" };

        if (inputText != nullptr)
        {
            text = inputText;
        }

        // Create a DirectWrite text format object.
        hr = object.m_pDWriteFactory->CreateTextFormat(
            L"Verdana",
            NULL,
            DWRITE_FONT_WEIGHT_EXTRA_LIGHT,
            DWRITE_FONT_STYLE_NORMAL,
            DWRITE_FONT_STRETCH_NORMAL,
            12,
            L"", //locale
            pTextFormat.ReleaseAndGetAddressOf()
        );

        float caretX{};
        float caretY{};
        
        if (SUCCEEDED(hr))
        {
            // In this case, CreateTextLayout is needed to determine the size of the characters, 
            // namely the width.
            hr = object.m_pDWriteFactory->CreateTextLayout(
                text,
                lstrlenW(text) - (lstrlenW(text) - movingACaret),
                pTextFormat.Get(),
                size.width - 8.0f,
                size.height - 8.0f,
                pTextLayout.ReleaseAndGetAddressOf()
            );
            
            pTextLayout->GetMetrics(&textMetrics);

            bool isTrailingHitCaretPos = false;
            
            // Map text position index to caret coordinate and hit-test rectangle.
            pTextLayout->HitTestTextPosition(
                movingACaret,
                isTrailingHitCaretPos,
                OUT &caretX,
                OUT &caretY,
                OUT &hitTestMetricsCaretPosition
            );
            
            if (SUCCEEDED(hr))
            {
                hr = object.m_pDWriteFactory->CreateTextLayout(
                    text,
                    lstrlenW(text) - (lstrlenW(text) - caretStartPosition),
                    pTextFormat.Get(),
                    size.width - 8.0f,
                    size.height - 8.0f,
                    pCaretStartPosition.ReleaseAndGetAddressOf()
                );

                pCaretStartPosition->GetMetrics(&partialTextSelection);
                
                if (SUCCEEDED(hr))
                {
                    if (SUCCEEDED(hr))
                    {
                        // Center the text horizontally and vertically.
                        pTextFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_LEADING);
                        // and vertically.
                        pTextFormat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_NEAR);
                    }

                    if (permissionToRecordStartingPosition == 1)
                    {
                        // Drawing a frame to highlight text.
                        hr = object.m_pD2DDeviceContext.Get()->CreateSolidColorBrush(
                            D2D1::ColorF(0x4264C2, 1.0),
                            pTextSelection.ReleaseAndGetAddressOf()
                        );

                        if (SUCCEEDED(hr))
                        {
                            object.m_pD2DDeviceContext.Get()->FillRectangle(
                                D2D1::RectF(
                                    4.0f + caretX,
                                    4.0f + caretY,
                                    4.0f + partialTextSelection.widthIncludingTrailingWhitespace,
                                    caretY + 14.0f + 4.0f
                                ),
                                pTextSelection.Get()
                            );
                        }
                    }

                    // Drawing text.
                    hr = object.m_pD2DDeviceContext.Get()->CreateSolidColorBrush(
                        D2D1::ColorF(D2D1::ColorF(0xFEE3EE, 1.0f)),
                        pTextBrush.ReleaseAndGetAddressOf()
                    );

                    if (SUCCEEDED(hr))
                    {
                        object.m_pD2DDeviceContext.Get()->DrawTextW(
                            text,
                            lstrlenW(text),
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
        }

        // Drawing a caret.
        D2D1_POINT_2F pointA{};
        D2D1_POINT_2F pointB{};

        hr = object.m_pD2DDeviceContext.Get()->CreateSolidColorBrush(
            D2D1::ColorF(0x233567, static_cast<float>(drawingACaret)),
            pCaretBrush.ReleaseAndGetAddressOf()
        );

        if (SUCCEEDED(hr))
        {
            pointA = { 4.0f + caretX, 4.0f + caretY };
            pointB = { 4.0f + caretX, 4.0f + (caretY + 14) };
            
            object.m_pD2DDeviceContext.Get()->DrawLine(
                pointA, pointB, pCaretBrush.Get(), 1
            );
        }

        hr = object.m_pD2DDeviceContext.Get()->EndDraw();
        // Make the swap chain available to the composition engine.
        hr = object.m_pDXGISwapChain.Get()->Present(0, 0);
    }

    return hr;
}