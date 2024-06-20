#ifndef TEXT_CLASS_H
#define TEXT_CLASS_H

#include "window_class.h"

class Text : public Window
{
public:
	Text();
    Text(
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
    );
    ~Text();

    // Ordinary text.
    static LRESULT CALLBACK TextWindowProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

    HRESULT DrawingText(
        Text& object,
        const wchar_t* inputTitle,
        HWND hwnd
    );

private:
    const wchar_t* m_fontName{ nullptr };
    float m_fontSize{};
    UINT32 m_fontRGB{};
    UINT32 m_backgroundRGB{};
    UINT32 m_outlineRGB{};
    DWRITE_FONT_WEIGHT m_fontWeight{};
    DWRITE_FONT_STYLE m_fontStyle{};
    DWRITE_FONT_STRETCH m_fontStretch{};
};





#endif // !TEXT_CLASS_H
