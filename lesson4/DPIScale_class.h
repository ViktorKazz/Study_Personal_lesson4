#ifndef DPI_SCALE_CLASS_H
#define DPI_SCALE_CLASS_H

#include <d2d1.h>

// Mouse coordinates are given in physical pixels, 
// but Direct2D expects device-independent pixels (DIPs). 
// To handle high-DPI settings correctly,
// you must translate the pixel coordinates into DIPs. 
// The following code shows a helper class that converts pixels into DIPs.

class DPIScale
{
    
public:
    float Initialize(HWND hwnd)
    {
        float scale{};

        UINT dpi = GetDpiForWindow(hwnd);
        
        return scale = dpi / 96.0f;
    }

    template <typename T>
    D2D1_POINT_2F PixelsToDips(float setScale, T x, T y)
    {
        return D2D1::Point2F(static_cast<float>(x) / setScale, static_cast<float>(y) / setScale);
    }

    template <typename T>
    float PixelsToDipsX(float setScale, T x)
    {
        return static_cast<float>(x) / setScale;
    }

    template <typename T>
    float PixelsToDipsY(float setScale, T y)
    {
        return static_cast<float>(y) / setScale;
    }

};

#endif //!DPI_SCALE_CLASS_H