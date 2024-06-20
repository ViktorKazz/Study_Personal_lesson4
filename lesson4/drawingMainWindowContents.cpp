#include "window_class.h"

//  Note that this function will not render anything if the window
//  is occluded (e.g. when the screen is locked).
//  Also, this function will automatically discard device-specific
//  resources if the Direct3D device disappears during function
//  invocation, and will recreate the resources the next time it's
//  invoked.
HRESULT Window::DrawingMainWindowContents(Window& object, HWND hwnd)
{
	HRESULT hr = S_OK;

	if (object.m_pD2DDeviceContext.Get() && object.m_pDXGISwapChain.Get())
	{
		D2D1_SIZE_F size = object.m_pD2DDeviceContext.Get()->GetSize();

		object.m_pD2DDeviceContext.Get()->BeginDraw();
		object.m_pD2DDeviceContext.Get()->Clear();


		// Drawing a main window shadow.
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

		// Drawing a main window background.
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

		// Drawing the status bar. 
		// 
		// We draw a partition using three different gradients 
		// to separate the main part of the working area from the lower part.		
		Microsoft::WRL::ComPtr<ID2D1GradientStopCollection> pGradientStopsDownStripOne;

		D2D1_GRADIENT_STOP gradientStopsDownStripOne[4]{};

		gradientStopsDownStripOne[0].color = D2D1::ColorF(D2D1::ColorF::Black, 0.10f);
		gradientStopsDownStripOne[0].position = 1.0f;
		gradientStopsDownStripOne[1].color = D2D1::ColorF(D2D1::ColorF::Black, 0.05f);
		gradientStopsDownStripOne[1].position = 0.75f;
		gradientStopsDownStripOne[2].color = D2D1::ColorF(0xFEE3EE, 0.05f);
		gradientStopsDownStripOne[2].position = 0.25f;
		gradientStopsDownStripOne[3].color = D2D1::ColorF(0xFEE3EE, 0.0f);
		gradientStopsDownStripOne[3].position = 0.0f;

		//
		hr = object.m_pD2DDeviceContext.Get()->CreateGradientStopCollection(
			gradientStopsDownStripOne,
			4,
			D2D1_GAMMA_2_2,
			D2D1_EXTEND_MODE_CLAMP,
			pGradientStopsDownStripOne.ReleaseAndGetAddressOf()
		);
		//
		Microsoft::WRL::ComPtr<ID2D1LinearGradientBrush> pLinearGradientBrushDownStripOne;

		if (SUCCEEDED(hr))
		{
			hr = object.m_pD2DDeviceContext.Get()->CreateLinearGradientBrush(
				D2D1::LinearGradientBrushProperties(
					D2D1::Point2F(size.width, (size.height - 46.0f)),
					D2D1::Point2F(size.width, (size.height - 38.0f))
				),
				pGradientStopsDownStripOne.Get(),
				pLinearGradientBrushDownStripOne.ReleaseAndGetAddressOf()
			);

			object.m_pD2DDeviceContext.Get()->FillRectangle(
				D2D1::RectF(
					6.0f, (size.height - 46.0f),
					size.width - 6.0f, (size.height - 38.0f)
				),
				pLinearGradientBrushDownStripOne.Get()
			);
		}
		//
		//
		Microsoft::WRL::ComPtr<ID2D1GradientStopCollection> pGradientStopsDownStripTwo;

		D2D1_GRADIENT_STOP gradientStopsDownStripTwo[4]{};

		gradientStopsDownStripTwo[0].color = D2D1::ColorF(D2D1::ColorF::Black, 0.10f);
		gradientStopsDownStripTwo[0].position = 0.0f;
		gradientStopsDownStripTwo[1].color = D2D1::ColorF(D2D1::ColorF::Black, 0.30f);
		gradientStopsDownStripTwo[1].position = 0.25f;
		gradientStopsDownStripTwo[2].color = D2D1::ColorF(0xFEE3EE, 0.30f);
		gradientStopsDownStripTwo[2].position = 0.75f;
		gradientStopsDownStripTwo[3].color = D2D1::ColorF(0xFEE3EE, 0.0f);
		gradientStopsDownStripTwo[3].position = 1.0f;

		//
		hr = object.m_pD2DDeviceContext.Get()->CreateGradientStopCollection(
			gradientStopsDownStripTwo,
			4,
			D2D1_GAMMA_2_2,
			D2D1_EXTEND_MODE_CLAMP,
			pGradientStopsDownStripTwo.ReleaseAndGetAddressOf()
		);
		//
		Microsoft::WRL::ComPtr<ID2D1LinearGradientBrush> pLinearGradientBrushDownStripTwo;

		if (SUCCEEDED(hr))
		{
			hr = object.m_pD2DDeviceContext.Get()->CreateLinearGradientBrush(
				D2D1::LinearGradientBrushProperties(
					D2D1::Point2F(size.width, (size.height - 36.0f)),
					D2D1::Point2F(size.width, (size.height - 28.0f))
				),
				pGradientStopsDownStripTwo.Get(),
				pLinearGradientBrushDownStripTwo.ReleaseAndGetAddressOf()
			);

			object.m_pD2DDeviceContext.Get()->FillRectangle(
				D2D1::RectF(
					6.0f, (size.height - 36.0f),
					size.width - 6.0f, (size.height - 28.0f)
				),
				pLinearGradientBrushDownStripTwo.Get()
			);
		}
		//
		//
		Microsoft::WRL::ComPtr<ID2D1GradientStopCollection> pGradientStopsDownStripThree;

		D2D1_GRADIENT_STOP gradientStopsDownStripThree[4]{};

		gradientStopsDownStripThree[0].color = D2D1::ColorF(D2D1::ColorF::Black, 0.3f);
		gradientStopsDownStripThree[0].position = 0.0f;
		gradientStopsDownStripThree[1].color = D2D1::ColorF(D2D1::ColorF::Black, 0.1f);
		gradientStopsDownStripThree[1].position = 0.20f;
		gradientStopsDownStripThree[2].color = D2D1::ColorF(0xFEE3EE, 0.1f);
		gradientStopsDownStripThree[2].position = 0.75f;
		gradientStopsDownStripThree[3].color = D2D1::ColorF(0xFEE3EE, 0.0f);
		gradientStopsDownStripThree[3].position = 1.0f;

		//
		hr = object.m_pD2DDeviceContext.Get()->CreateGradientStopCollection(
			gradientStopsDownStripThree,
			4,
			D2D1_GAMMA_2_2,
			D2D1_EXTEND_MODE_CLAMP,
			pGradientStopsDownStripThree.ReleaseAndGetAddressOf()
		);
		//
		Microsoft::WRL::ComPtr<ID2D1LinearGradientBrush> pLinearGradientBrushDownStripThree;

		if (SUCCEEDED(hr))
		{
			hr = object.m_pD2DDeviceContext.Get()->CreateLinearGradientBrush(
				D2D1::LinearGradientBrushProperties(
					D2D1::Point2F(size.width, (size.height - 34.0f)),
					D2D1::Point2F(size.width, (size.height - 26.0f))
				),
				pGradientStopsDownStripThree.Get(),
				pLinearGradientBrushDownStripThree.ReleaseAndGetAddressOf()
			);

			object.m_pD2DDeviceContext.Get()->FillRectangle(
				D2D1::RectF(
					6.0f, (size.height - 34.0f),
					size.width - 6.0f, (size.height - 26.0f)
				),
				pLinearGradientBrushDownStripThree.Get()
			);
		}

		// Create an icon for the status bar. 
		// First, let's draw a small circle(ellipse) in the lower left part of the work area.
		Microsoft::WRL::ComPtr<ID2D1SolidColorBrush> m_pEllipseBrush;

		D2D1_COLOR_F const ellipseBrushColor = D2D1::ColorF(0xDC8095, 1.0f);

		hr = object.m_pD2DDeviceContext.Get()->CreateSolidColorBrush(
			ellipseBrushColor,
			m_pEllipseBrush.ReleaseAndGetAddressOf()
		);

		if (SUCCEEDED(hr))
		{
			object.m_pD2DDeviceContext.Get()->FillEllipse(
				D2D1::Ellipse(
					D2D1::Point2F(
						20.0f,
						(size.height - 20.0f)
					),
					10.0f,
					10.0f
				),
				m_pEllipseBrush.Get()
			);
		}

		// Next, create an inner shadow inside the ellipse using a gradient.
		// Create an array of gradient stops to put in the gradient stop
		// collection that will be used in the gradient brush.
		Microsoft::WRL::ComPtr<ID2D1GradientStopCollection> pGradientStops;

		D2D1_GRADIENT_STOP gradientStops[4]{};

		gradientStops[0].color = D2D1::ColorF(D2D1::ColorF::Black, 0.45f);
		gradientStops[0].position = 1.0f;
		gradientStops[1].color = D2D1::ColorF(D2D1::ColorF::Black, 0.2f);
		gradientStops[1].position = 0.85f;
		gradientStops[2].color = D2D1::ColorF(0xDC8095, 0.2f);
		gradientStops[2].position = 0.45f;
		gradientStops[3].color = D2D1::ColorF(0xDC8095, 0.0f);
		gradientStops[3].position = 0.0f;

		// Create the ID2D1GradientStopCollection from a previously
		// declared array of D2D1_GRADIENT_STOP structs.
		hr = m_pD2DDeviceContext.Get()->CreateGradientStopCollection(
			gradientStops,
			4,
			D2D1_GAMMA_2_2,
			D2D1_EXTEND_MODE_CLAMP,
			pGradientStops.ReleaseAndGetAddressOf()
		);

		Microsoft::WRL::ComPtr<ID2D1RadialGradientBrush> pRadialGradientBrush;

		// The center of the gradient is in the center of the box.
		// The gradient origin offset was set to zero(0, 0) or center in this case.
		if (SUCCEEDED(hr))
		{
			hr = m_pD2DDeviceContext.Get()->CreateRadialGradientBrush(
				D2D1::RadialGradientBrushProperties(
					D2D1::Point2F(20.0f, (size.height - 20.0f)),
					D2D1::Point2F(12.0f, 12.0f),
					10.0f,
					10.0f),
				pGradientStops.Get(),
				pRadialGradientBrush.ReleaseAndGetAddressOf()
			);

			object.m_pD2DDeviceContext.Get()->FillEllipse(
				D2D1::Ellipse(
					D2D1::Point2F(
						20.0f,
						(size.height - 20.0f)
					),
					10.0f,
					10.0f
				),
				pRadialGradientBrush.Get()
			);
		}

		//Creating text in to icon.
		
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
				pButtonTextFormat.Get()->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
				// and vertically.
				pButtonTextFormat.Get()->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);

				hr = object.m_pD2DDeviceContext.Get()->CreateSolidColorBrush(
					D2D1::ColorF(D2D1::ColorF(0xFEE3EE, 1.0f)),
					pIconTextBrush.ReleaseAndGetAddressOf()
				);

				if (SUCCEEDED(hr))
				{
					object.m_pD2DDeviceContext.Get()->DrawText(
						L"?",
						lstrlen(L"?"),
						pButtonTextFormat.Get(),
						D2D1::RectF(
							11.0f,
							(size.height - 30.0f),
							30.0f,
							(size.height - 11.0f)
						),
						pIconTextBrush.Get()
					);
				}
			}
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