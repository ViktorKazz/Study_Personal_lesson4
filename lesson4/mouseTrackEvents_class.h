#ifndef MOUSE_TRACK_EVENTS_CLASS_H
#define MOUSE_TRACK_EVENTS_CLASS_H

#include <windows.h>
//#include <tchar.h>
#include "DPIScale_class.h"

// Below is the class which is used to manage mouse tracking events.

class MouseTrackEvents
{
public:

	MouseTrackEvents();

	int OnButtonDown(HWND hwnd, RECT rc);
	int OnButtonUp(HWND hwnd, RECT rc);
	int OnMouseMove(MouseTrackEvents& object, HWND hwnd, RECT rc, int pixelX, int pixelY);
	int OnMouseMoveOut(MouseTrackEvents& object, HWND hwnd);

	int Reset(MouseTrackEvents& object, HWND hwnd);

	RECT controlElementArea(
		HWND hwnd,
		unsigned int positionX,
		unsigned int positionY,
		unsigned int widthControl,
		unsigned int heightControl
	);

private:
	bool m_bMouseTracking;
};

#endif // !MOUSE_TRACK_EVENTS_CLASS_H