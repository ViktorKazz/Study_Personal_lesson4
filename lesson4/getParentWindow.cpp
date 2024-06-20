#include "getParentWindow.h"

// Function to find the parent window.
//
HWND GetParentWindow(HWND hwnd)
{
    HWND hParent;

    // GetAncestor function.
    // Retrieves the handle to the ancestor of the specified window.
    //
    // GetParent function.
    // Retrieves a handle to the specified window's parent or owner.
    hParent = GetAncestor(hwnd, GA_PARENT);
    if (hParent == 0 || hParent == GetDesktopWindow())
    {
        hParent = GetParent(hwnd);
        if (hParent == 0 || hParent == GetDesktopWindow())
        {
            hParent = hwnd;
        }
    }

    return hParent;
}