#include "window_class.h"

//  Note that this function will not render anything if the window
//  is occluded (e.g. when the screen is locked).
//  Also, this function will automatically discard device-specific
//  resources if the Direct3D device disappears during function
//  invocation, and will recreate the resources the next time it's
//  invoked.
HRESULT Window::DrawingCreatePlaneWinContents(Window& object, HWND hwnd)
{
	HRESULT hr = S_OK;

	if (object.m_pD2DDeviceContext.Get() && object.m_pDXGISwapChain.Get())
	{
		D2D1_SIZE_F size = object.m_pD2DDeviceContext.Get()->GetSize();

		object.m_pD2DDeviceContext.Get()->BeginDraw();
		object.m_pD2DDeviceContext.Get()->Clear();


		// Drawing a about window shadow.
		Microsoft::WRL::ComPtr<ID2D1SolidColorBrush> pBackgroundShadowBrush;

		float transparent[7]{ 0.5f, 0.4f, 0.25f, 0.2f, 0.1f, 0.05f, 0.025f };

		// Six pixels is the size of the non-client area, as well as the size of the shadow.
		float left{ 6.0f };
		float top{ 6.0f };
		float right{ size.width - 6.0f };
		float bottom{ size.height - 6.0f };

		// When using "GetAddressOf" memory leaks were noticed when the window was redrawn, 
		// so it was decided to use "ReleaseAndGetAddressOf".

		for (int i = 0; i < 7; i++)
		{
			hr = object.m_pD2DDeviceContext.Get()->CreateSolidColorBrush(
				D2D1::ColorF(0x353535, transparent[i]),
				pBackgroundShadowBrush.ReleaseAndGetAddressOf()
			);

			if (SUCCEEDED(hr))
			{
				object.m_pD2DDeviceContext.Get()->DrawRoundedRectangle(
					D2D1::RoundedRect(
						D2D1::RectF(
							left - i,
							top - i,
							right + i,
							bottom + i
						),
						6.f,
						6.f
					),
					pBackgroundShadowBrush.Get(), 1
				);
			}
		}

		// Drawing a about window background.
		Microsoft::WRL::ComPtr<ID2D1SolidColorBrush> pBackgroundBrush;

		D2D1_COLOR_F const brushColor = D2D1::ColorF(0xFEE3EE, 1.0f);

		hr = object.m_pD2DDeviceContext.Get()->CreateSolidColorBrush(
			brushColor,
			pBackgroundBrush.ReleaseAndGetAddressOf()
		);

		if (SUCCEEDED(hr))
		{
			object.m_pD2DDeviceContext.Get()->FillRoundedRectangle(
				D2D1::RoundedRect(
					D2D1::RectF(
						6.0f,
						6.0f,
						size.width - 6.0f,
						size.height - 6.0f
					),
					6.f,
					6.f
				),
				pBackgroundBrush.Get()
			);
		}

		// Drawing the main menu area.
		// 
		// We Using a gradient, draw a strip of shadow 
		// that will separate the main menu area from the rest of the window.
		//
		// Create an array of gradient stops to put in the gradient stop
		// collection that will be used in the gradient brush.
		Microsoft::WRL::ComPtr<ID2D1GradientStopCollection> pGradientStopsUpStrip;

		D2D1_GRADIENT_STOP gradientStopsUpStrip[4]{};

		gradientStopsUpStrip[0].color = D2D1::ColorF(D2D1::ColorF::Black, 0.40f);
		gradientStopsUpStrip[0].position = 0.0f;
		gradientStopsUpStrip[1].color = D2D1::ColorF(D2D1::ColorF::Black, 0.20f);
		gradientStopsUpStrip[1].position = 0.20f;
		gradientStopsUpStrip[2].color = D2D1::ColorF(0xFEE3EE, 0.20f);
		gradientStopsUpStrip[2].position = 0.75f;
		gradientStopsUpStrip[3].color = D2D1::ColorF(0xFEE3EE, 0.0f);
		gradientStopsUpStrip[3].position = 1.0f;

		// Create the ID2D1GradientStopCollection from a previously
		// declared array of D2D1_GRADIENT_STOP structs.
		hr = object.m_pD2DDeviceContext.Get()->CreateGradientStopCollection(
			gradientStopsUpStrip,
			4,
			D2D1_GAMMA_2_2,
			D2D1_EXTEND_MODE_CLAMP,
			pGradientStopsUpStrip.ReleaseAndGetAddressOf()
		);

		// The line that determines the direction of the gradient starts at
		// the upper-left corner of the square and ends at the lower-right corner.
		Microsoft::WRL::ComPtr<ID2D1LinearGradientBrush> pLinearGradientBrushUpStrip;

		if (SUCCEEDED(hr))
		{
			hr = object.m_pD2DDeviceContext.Get()->CreateLinearGradientBrush(
				D2D1::LinearGradientBrushProperties(
					D2D1::Point2F(size.width, 38.0f),
					D2D1::Point2F(size.width, 46.0f)
				),
				pGradientStopsUpStrip.Get(),
				pLinearGradientBrushUpStrip.ReleaseAndGetAddressOf()
			);

			object.m_pD2DDeviceContext.Get()->FillRectangle(
				D2D1::RectF(
					6.0f, 38.0f,
					size.width - 6.0f, 46.0f
				),
				pLinearGradientBrushUpStrip.Get()
			);
		}

		//Creating title text.
		static wchar_t msc_buttonFontName[] = L"Verdana";
		static float msc_buttonFontSize = 14;

		Microsoft::WRL::ComPtr<IDWriteTextFormat> pButtonTextFormat;

		hr = object.m_pDWriteFactory.Get()->CreateTextFormat(
			msc_buttonFontName,
			NULL,
			DWRITE_FONT_WEIGHT_MEDIUM,
			DWRITE_FONT_STYLE_NORMAL,
			DWRITE_FONT_STRETCH_NORMAL,
			msc_buttonFontSize,
			L"", //locale
			pButtonTextFormat.ReleaseAndGetAddressOf()
		);

		Microsoft::WRL::ComPtr<ID2D1SolidColorBrush> pIconTextBrush;

		if (SUCCEEDED(hr))
		{
			if (SUCCEEDED(hr))
			{
				// Center the text horizontally and vertically.
				pButtonTextFormat.Get()->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_JUSTIFIED);
				// and vertically.
				pButtonTextFormat.Get()->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);

				hr = object.m_pD2DDeviceContext.Get()->CreateSolidColorBrush(
					D2D1::ColorF(D2D1::ColorF(0x233567, 1.0f)),
					pIconTextBrush.ReleaseAndGetAddressOf()
				);

				if (SUCCEEDED(hr))
				{
					object.m_pD2DDeviceContext.Get()->DrawText(
						object.m_windowTitle,
						lstrlen(object.m_windowTitle),
						pButtonTextFormat.Get(),
						D2D1::RectF(
							6.0f + 6.0f + 32.0f,
							10.0f,
							300.0f,
							32.0f
						),
						pIconTextBrush.Get()
					);
				}
			}
		}

		Microsoft::WRL::ComPtr<ID2D1SolidColorBrush> m_pCloseButtonBrush;

		D2D1_POINT_2F pointA{};
		D2D1_POINT_2F pointB{};

		hr = object.m_pD2DDeviceContext.Get()->CreateSolidColorBrush(
			D2D1::ColorF(0x353535, 1),
			m_pCloseButtonBrush.ReleaseAndGetAddressOf()
		);

		if (SUCCEEDED(hr))
		{
			pointA = { 6, size.height - 39 };
			pointB = { 406, size.height - 39 };

			object.m_pD2DDeviceContext.Get()->DrawLine(
				pointA, pointB, m_pCloseButtonBrush.Get(), 0.25f
			);
		}

		// Drawing the logo in the upper left corner.
		hr = LoadBitmapFromFile(
			object,
			L"kittyLogo.png",
			0,
			0
		);

		if (SUCCEEDED(hr))
		{
			// Draw a bitmap.
			object.m_pD2DDeviceContext.Get()->DrawBitmap(
				object.m_pBitmap,
				D2D1::RectF(10.0f, 10.0f, 36, 36)
			);

			SafeRelease(&object.m_pBitmap);
		}

		hr = object.m_pD2DDeviceContext.Get()->EndDraw();
		// Make the swap chain available to the composition engine.
		hr = object.m_pDXGISwapChain.Get()->Present(0, 0);
	}

	return hr;
}