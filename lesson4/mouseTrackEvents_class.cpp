#include "mouseTrackEvents_class.h"

// Initialize members.
//
MouseTrackEvents::MouseTrackEvents() :
    m_bMouseTracking(false)
{
}
int MouseTrackEvents::OnButtonDown(HWND hwnd, RECT rc)
{
    // Capturing the coordinates of a left mouse button click.
    SetCapture(hwnd);

    InvalidateRect(hwnd, &rc, FALSE);

    return 1;
}

int MouseTrackEvents::OnButtonUp(HWND hwnd, RECT rc)
{
    // For the left-button-up message, 
    // simply call ReleaseCapture to release the mouse capture.
    ReleaseCapture();

    InvalidateRect(hwnd, &rc, FALSE);

    return 0;
}

// The function tracks the cursor only when it is inside the specified area.
//
int MouseTrackEvents::OnMouseMove(MouseTrackEvents& object, HWND hwnd, RECT rc, int pixelX, int pixelY)
{
    int hit{};

    if (!object.m_bMouseTracking)
    {
        // Enable mouse tracking.
        TRACKMOUSEEVENT tme{};
        tme.cbSize = sizeof(tme);
        tme.hwndTrack = hwnd;
        tme.dwFlags = TME_LEAVE | TME_HOVER;
        tme.dwHoverTime = HOVER_DEFAULT;
        TrackMouseEvent(&tme);
        object.m_bMouseTracking = true;

        DPIScale dpi;

        float scale{ dpi.Initialize(hwnd) };

        const float dipX = dpi.PixelsToDipsX(scale, pixelX);
        const float dipY = dpi.PixelsToDipsY(scale, pixelY);

        // If the cursor is in the specified area(RECT), 
        // then "1" is returned and the area is updated.
        //
        if (dipX >= rc.left && dipX <= rc.right)
        {
            if (dipY >= rc.top && dipY <= rc.bottom)
            {
                InvalidateRect(hwnd, &rc, FALSE);
                hit = 1;
            }
            else
            {
                InvalidateRect(hwnd, &rc, FALSE);
                hit = 0;
            }
        }
        else
        {
            InvalidateRect(hwnd, &rc, FALSE);
            hit = 0;
        }
    }

    return hit;
}

// The function tracks the cursor not only inside a given area but also outside it.
//
int MouseTrackEvents::OnMouseMoveOut(MouseTrackEvents& object, HWND hwnd)
{
    int hit{};

    if (!object.m_bMouseTracking)
    {
        // Enable mouse tracking.
        TRACKMOUSEEVENT tme{};
        tme.cbSize = sizeof(tme);
        tme.hwndTrack = hwnd;
        tme.dwFlags = TME_LEAVE | TME_HOVER;
        tme.dwHoverTime = HOVER_DEFAULT;
        TrackMouseEvent(&tme);
        object.m_bMouseTracking = true;

        hit = 1;
    }

    return hit;
}


int MouseTrackEvents::Reset(MouseTrackEvents& object, HWND hwnd)
{
    object.m_bMouseTracking = false;

    InvalidateRect(hwnd, NULL, FALSE);
    return 0;
}

RECT MouseTrackEvents::controlElementArea(
    HWND hwnd,
    unsigned int positionX,
    unsigned int positionY,
    unsigned int widthControl,
    unsigned int heightControl
)
{
    // The control's position is calculated from the top left corner.
    RECT rc;

    if (widthControl == 0 || heightControl == 0)
    {
        GetClientRect(hwnd, &rc);
    }
    else
    {
        rc.left = positionX;
        rc.top = positionY;
        rc.right = widthControl;
        rc.bottom = heightControl;
    }

    return rc;
}