#include "window_class.h"

// Default constructor.
Window::Window() :
	m_windowClassStyle{ CS_HREDRAW | CS_VREDRAW },
	m_dwExStyle{ WS_EX_NOREDIRECTIONBITMAP | WS_EX_APPWINDOW },
	m_dwStyle{ WS_POPUP | WS_CLIPCHILDREN },
	m_parentHwnd{ NULL },
	m_windowPositionX{ 0 },
	m_windowPositionY{ 0 },
	m_windowWidth{ 800 },
	m_windowHeight{ 600 },
	m_message{ 0 },
	m_windowClass{ L"defaultWindowClass" },
	m_windowTitle{ L"defaultWindowTitle" }
{
}

// Class constructor with parameters.
Window::Window(
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
	const wchar_t* windowTitle
) :
	m_windowClassStyle{ windowClassStyle },
	m_dwExStyle{ dwExStyle },
	m_dwStyle{ dwStyle },
	m_parentHwnd{ parentHwnd },
	m_windowPositionX{ windowPositionX },
	m_windowPositionY{ windowPositionY },
	m_windowWidth{ windowWidth },
	m_windowHeight{ windowHeight },
	m_message{ message },
	m_windowClass{ windowClass },
	m_windowTitle{ windowTitle }
{
}

// Release resources. Class destructor.
Window::~Window()
{
}

// Creates the application window and initializes
// device-independent resources.
BOOL Window::Initialize(
	Window& object,
	WNDPROC wndProc,
	HINSTANCE hInstance,
	HWND parentHwnd
)
{
	BOOL in = FALSE;

	if (IsWindow(object.m_hwnd) == NULL)
	{
		if (hInstance != NULL)
		{
			object.m_hInstance = hInstance;
		}
		if (object.m_windowPositionX < 0 ||
			object.m_windowPositionY < 0 ||
			object.m_windowWidth < 0 ||
			object.m_windowHeight < 0 ||
			object.m_message < 0
			)
		{
			MessageBox(NULL,
				L"Initialize: One or more parameters are less than zero!",
				object.m_windowTitle,
				NULL);

			return 1;
		}

		// Register the window class.
		WNDCLASSEX wcex = { sizeof(WNDCLASSEX) };
		wcex.style = object.m_windowClassStyle;
		wcex.lpfnWndProc = wndProc;
		wcex.cbClsExtra = 0;
		wcex.cbWndExtra = sizeof(LONG_PTR);
		wcex.hInstance = object.m_hInstance;
		wcex.hIcon = (HICON)LoadImage(NULL, TEXT("kittyLogo.ico"), IMAGE_ICON, 0, 0, LR_LOADFROMFILE);
		wcex.hCursor = LoadCursorW(object.m_hInstance, IDC_ARROW);
		wcex.hbrBackground = nullptr;
		wcex.lpszMenuName = NULL;
		wcex.lpszClassName = object.m_windowClass;
		wcex.hIconSm = NULL;

		RegisterClassEx(&wcex);

		/*if (!RegisterClassEx(&wcex))
		{
			MessageBox(NULL,
				L"Call to RegisterClassEx failed!",
				object.m_windowTitle,
				NULL);

			return 1;
		}*/

		// Create the application window.
		//
		// GetsySteMetrics returns information on various parameters in Windows. 
		// Most of them are dealing with the sizes of various objects (screen, badges, cursors, etc.). 
		// The returned function of the function depends on the value specified for Nindex. 
		// Keep in mind that all sizes (width and height) are measured in pixels
		int xres = GetSystemMetrics(SM_CXSCREEN);//Returns the width of the screen(monitor)
		int yres = GetSystemMetrics(SM_CYSCREEN);//Returns the height of the screen(monitor)

		// Because the CreateWindow function takes its size in pixels, we
		// obtain the system DPI and use it to scale the window size.
		int dpiX{};
		int dpiY{};

		HDC hdc = GetDC(NULL);
		if (hdc)
		{
			dpiX = GetDeviceCaps(hdc, LOGPIXELSX);
			dpiY = GetDeviceCaps(hdc, LOGPIXELSY);
			ReleaseDC(NULL, hdc);
		}

		object.m_hwnd = CreateWindowExW(
			object.m_dwExStyle,
			object.m_windowClass,//L"D2DDemoApp",
			object.m_windowTitle,//L"Direct2D Demo Application",
			object.m_dwStyle, //WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
			object.m_windowPositionX,
			object.m_windowPositionY,
			static_cast<UINT>(ceil(object.m_windowWidth * dpiX / 96.0f)),
			static_cast<UINT>(ceil(object.m_windowHeight * dpiY / 96.0f)),
			parentHwnd,
			NULL,
			object.m_hInstance,
			this
		);

		in = object.m_hwnd ? TRUE : FALSE;

		if (in)
		{
			ShowWindow(object.m_hwnd, SW_SHOWNORMAL);

			// The SetForegroundWindow function puts the thread that created 
			// the specified window into foreground mode and activates the window.
			// Keyboard input is directed to the window and various visual cues 
			// for the user are changed.The system assigns a slightly higher priority 
			// to the thread that created the priority window than it does to other threads.
			//
			SetForegroundWindow(object.m_hwnd);
			UpdateWindow(object.m_hwnd);
		}
		else
		{
			MessageBox(NULL,
				L"Call to CreateWindowExW failed!",
				object.m_windowTitle,
				NULL);

			return 1;
		}
	}
	else
	{
		SetForegroundWindow(object.m_hwnd);
	}

	return in;
}

//
// The main window message loop.
void Window::RunMessageLoop()
{
	MSG msg;

	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}

HRESULT Window::CreateD2D1Factory(Window& object)
{
	HRESULT hr;

	D2D1_FACTORY_OPTIONS options;

	ZeroMemory(&options, sizeof(D2D1_FACTORY_OPTIONS));

#if defined(_DEBUG)
	// If the project is in a debug build, enable debugging via SDK Layers with this flag.
	options.debugLevel = D2D1_DEBUG_LEVEL::D2D1_DEBUG_LEVEL_INFORMATION;
#endif

	// Create a Direct2D factory.
	hr = D2D1CreateFactory(
		D2D1_FACTORY_TYPE_MULTI_THREADED,
		__uuidof(ID2D1Factory7),
		&options,
		(void**)object.m_pD2DFactory.ReleaseAndGetAddressOf()
	);
	if (SUCCEEDED(hr))
	{
		// Create a DirectWrite factory.
		hr = DWriteCreateFactory(
			DWRITE_FACTORY_TYPE_SHARED,
			__uuidof(object.m_pDWriteFactory.Get()),
			reinterpret_cast<IUnknown**>(object.m_pDWriteFactory.ReleaseAndGetAddressOf())
		);
	}
	if (SUCCEEDED(hr))
	{
		// Create WIC factory.
		hr = CoCreateInstance(
			CLSID_WICImagingFactory2,
			NULL,
			CLSCTX_INPROC_SERVER,
			IID_IWICImagingFactory,
			reinterpret_cast<void**>(&object.m_pWICFactory)
		);
	}


	return hr;
}

HRESULT Window::CreateSwapChain(Window& object, HWND hwnd)
{
	HRESULT hr = S_OK;

	// If the swap chain does not exist, create it.
	DXGI_SWAP_CHAIN_DESC1 swapChainDesc = { 0 };

	swapChainDesc.Stereo = false;
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDesc.Scaling = (hwnd != NULL) ? DXGI_SCALING::DXGI_SCALING_NONE : DXGI_SCALING::DXGI_SCALING_STRETCH;
	swapChainDesc.Flags = 0;
	swapChainDesc.AlphaMode = DXGI_ALPHA_MODE_PREMULTIPLIED;

	// Use automatic sizing ???. 
	// I haven’t figured this out at the moment, so instead of the value 0 I put 1.
	//
	swapChainDesc.Width = 1;
	swapChainDesc.Height = 1;

	// This is the most common swap chain format.
	//
	swapChainDesc.Format = DXGI_FORMAT::DXGI_FORMAT_B8G8R8A8_UNORM;

	// Don't use multi-sampling.
	//
	swapChainDesc.SampleDesc.Count = 1; // don't use multi-sampling
	swapChainDesc.SampleDesc.Quality = 0;

	// Use two buffers to enable the flip effect.
	//
	swapChainDesc.BufferCount = 2;

	// We using this swap effect for all applications.
	//
	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT::DXGI_SWAP_EFFECT_FLIP_SEQUENTIAL;


	Microsoft::WRL::ComPtr<IDXGIAdapter> pDXGIAdapter;

	// Get the parent factory from the DXGI Device.
	//
	hr = object.m_pDXGIDevice.Get()->GetAdapter(&pDXGIAdapter);

	if (SUCCEEDED(hr))
	{
		Microsoft::WRL::ComPtr<IDXGIFactory5> pDXGIFactory2;

		hr = pDXGIAdapter->GetParent(IID_PPV_ARGS(&pDXGIFactory2));

		if (SUCCEEDED(hr))
		{
			if (hwnd != NULL)
			{
				//The DXGI factory will ask the window for the size of the client area.
				//
				hr = pDXGIFactory2->CreateSwapChainForHwnd(
					object.m_pD3D11Device.Get(),
					hwnd,
					&swapChainDesc,
					nullptr,
					nullptr,
					object.m_pDXGISwapChain.ReleaseAndGetAddressOf()
				);
			}
			else
			{
				// Creates a swap chain that you can use to send Direct3D content 
				// into the DirectComposition API.
				//
				hr = pDXGIFactory2->CreateSwapChainForComposition(
					object.m_pD3D11Device.Get(),
					&swapChainDesc,
					nullptr,
					object.m_pDXGISwapChain.ReleaseAndGetAddressOf()
				);
			}
			if (SUCCEEDED(hr))
			{
				// Ensure that DXGI does not queue more than one frame at a time. This both reduces
				// latency and ensures that the application will only render after each VSync, minimizing
				// power consumption.
				//
				hr = object.m_pDXGIDevice.Get()->SetMaximumFrameLatency(1);
			}
		}
	}

	return hr;
}

HRESULT Window::ConfigureSwapChain(Window& object, HWND hwnd)
{
	HRESULT hr = S_OK;

	//(GetDpiForWindow) Returns the dots per inch (dpi) value for the specified window.
	//
	UINT nDPI = GetDpiForWindow(hwnd);
	D2D1_BITMAP_PROPERTIES1 bitmapProperties = {};

	bitmapProperties.pixelFormat.alphaMode = D2D1_ALPHA_MODE_PREMULTIPLIED;
	bitmapProperties.pixelFormat.format = DXGI_FORMAT_B8G8R8A8_UNORM;
	bitmapProperties.bitmapOptions = D2D1_BITMAP_OPTIONS_TARGET | D2D1_BITMAP_OPTIONS_CANNOT_DRAW;

	bitmapProperties.dpiX = static_cast<FLOAT>(nDPI);
	bitmapProperties.dpiY = static_cast<FLOAT>(nDPI);

	Microsoft::WRL::ComPtr<IDXGISurface> pDXGISurface;

	if (object.m_pDXGISwapChain.Get())
	{
		hr = object.m_pDXGISwapChain.Get()->GetBuffer(
			0,
			IID_PPV_ARGS(&pDXGISurface)
		);

		if (SUCCEEDED(hr))
		{
			hr = object.m_pD2DDeviceContext.Get()->CreateBitmapFromDxgiSurface(
				pDXGISurface.Get(),
				bitmapProperties,
				object.m_pD2DTargetBitmap.ReleaseAndGetAddressOf()
			);

			if (SUCCEEDED(hr))
			{
				object.m_pD2DDeviceContext.Get()->SetTarget(object.m_pD2DTargetBitmap.Get());
			}
		}
	}
	return hr;
}

HRESULT Window::CreateD3D11Device(Window& object)
{
	HRESULT hr = S_OK;

	// Create the Direct3D device.
	//

	// This flag is required in order to enable compatibility with Direct2D.
	//
	UINT creationFlags = D3D11_CREATE_DEVICE_BGRA_SUPPORT;

#if defined(_DEBUG)
	// If the project is in a debug build, enable debugging via SDK Layers with this flag.
	creationFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

	// This array defines the set of DirectX hardware feature levels this app  supports.
	// The ordering is important and you should  preserve it.
	// Don't forget to declare your app's minimum required feature level in its
	// description.  All apps are assumed to support 9.1 unless otherwise stated.
	//
	D3D_FEATURE_LEVEL featureLevels[] =
	{
		D3D_FEATURE_LEVEL_11_1,
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_1,
		D3D_FEATURE_LEVEL_10_0,
		D3D_FEATURE_LEVEL_9_3,
		D3D_FEATURE_LEVEL_9_2,
		D3D_FEATURE_LEVEL_9_1
	};

	D3D_FEATURE_LEVEL featureLevel;

	hr = D3D11CreateDevice(
		nullptr,                                           // specify null to use the default adapter
		D3D_DRIVER_TYPE_HARDWARE,
		0,
		creationFlags,                                     // optionally set debug and Direct2D compatibility flags
		featureLevels,                                     // list of feature levels this app can support
		ARRAYSIZE(featureLevels),                          // number of possible feature levels
		D3D11_SDK_VERSION,
		object.m_pD3D11Device.ReleaseAndGetAddressOf(),              // returns the Direct3D device created
		&featureLevel,                                     // returns feature level of device created
		object.m_pD3D11DeviceContext.ReleaseAndGetAddressOf()        // returns the device immediate context
	);
	if (hr != S_OK)
	{
		MessageBox(object.m_hwnd, L"Error creating device", L"Error", MB_OK);
		return 1;
	}

	// Exit if it's not supported
	//
	if (featureLevel != D3D_FEATURE_LEVEL_11_0) {
		MessageBox(object.m_hwnd, L"Your computer does not support DirectX 11", L"Error", MB_OK);
		return 1;
	}

	if (SUCCEEDED(hr))
	{
		// Obtain the underlying DXGI device of the Direct3D11 device.
		hr = object.m_pD3D11Device.Get()->QueryInterface(
			(IDXGIDevice4**)object.m_pDXGIDevice.ReleaseAndGetAddressOf()
		);

		if (SUCCEEDED(hr))
		{
			// Obtain the Direct2D device for 2-D rendering.
			hr = object.m_pD2DFactory.Get()->CreateDevice(object.m_pDXGIDevice.Get(), object.m_pD2DDevice.ReleaseAndGetAddressOf());

			if (SUCCEEDED(hr))
			{
				// Get Direct2D device's corresponding device context object.
				//
				Microsoft::WRL::ComPtr<ID2D1DeviceContext> pD2DDeviceContext;

				hr = object.m_pD2DDevice.Get()->CreateDeviceContext(D2D1_DEVICE_CONTEXT_OPTIONS_NONE, &pD2DDeviceContext);

				if (SUCCEEDED(hr))
				{
					hr = pD2DDeviceContext->QueryInterface((ID2D1DeviceContext3**)object.m_pD2DDeviceContext.ReleaseAndGetAddressOf());
				}
			}
		}
	}
	return hr;
}


HRESULT Window::CreateDirectComposition(Window& object, HWND hwnd)
{
	HRESULT hr = S_OK;

	hr = DCompositionCreateDevice(
		object.m_pDXGIDevice.Get(),
		__uuidof(object.m_pDCompositionDevice.Get()),
		(void**)(object.m_pDCompositionDevice.ReleaseAndGetAddressOf())
	);

	if (SUCCEEDED(hr))
	{
		// TRUE if the visual tree should be displayed on top of the children 
		// of the window specified by the hwnd parameter; 
		// otherwise, the visual tree is displayed behind the children.
		//
		hr = object.m_pDCompositionDevice.Get()->CreateTargetForHwnd(
			hwnd,
			false,
			object.m_pDCompositionTarget.ReleaseAndGetAddressOf()
		);

		if (SUCCEEDED(hr))
		{
			Microsoft::WRL::ComPtr<IDCompositionVisual> pDCompositionVisual;

			hr = object.m_pDCompositionDevice.Get()->CreateVisual(&pDCompositionVisual);

			if (SUCCEEDED(hr))
			{
				hr = pDCompositionVisual->SetContent(object.m_pDXGISwapChain.Get());
				hr = object.m_pDCompositionTarget.Get()->SetRoot(pDCompositionVisual.Get());
				hr = object.m_pDCompositionDevice.Get()->Commit();
			}
		}
	}
	return hr;
}

void Window::OnResize(Window& object, HWND hwnd, UINT nWidth, UINT nHeight)
{
	if (object.m_pDXGISwapChain.Get())
	{
		HRESULT hr = S_OK;

		if (nWidth != 0 && nHeight != 0)
		{
			object.m_pD2DDeviceContext.Get()->SetTarget(nullptr);

			// All outstanding buffer references must be released.
			//
			object.m_pD2DTargetBitmap.Reset();

			// Resizing the app window and the swap chain’s buffer.
			//
			hr = object.m_pDXGISwapChain.Get()->ResizeBuffers(
				2, // Double-buffered swap chain.
				nWidth,
				nHeight,
				DXGI_FORMAT_B8G8R8A8_UNORM,
				0
			);
			if (hr == DXGI_ERROR_DEVICE_REMOVED || hr == DXGI_ERROR_DEVICE_RESET)
			{
				CreateD3D11Device(object);
				CreateSwapChain(object, NULL);
				return;
			}
			else
			{
				//DX::ThrowIfFailed(hr);
			}
			ConfigureSwapChain(object, hwnd);
		}
	}
}

// Creates a Direct2D bitmap from the specified
// file name.
//
HRESULT Window::LoadBitmapFromFile(
	Window& object,
	PCWSTR uri,
	UINT destinationWidth,
	UINT destinationHeight
)
{
	HRESULT hr = S_OK;

	Microsoft::WRL::ComPtr<IWICBitmapDecoder> pDecoder;
	Microsoft::WRL::ComPtr<IWICBitmapFrameDecode> pSource;
	Microsoft::WRL::ComPtr<IWICStream> pStream;
	Microsoft::WRL::ComPtr<IWICFormatConverter> pConverter;
	Microsoft::WRL::ComPtr<IWICBitmapScaler>pScaler;

	hr = object.m_pWICFactory->CreateDecoderFromFilename(
		uri,
		NULL,
		GENERIC_READ,
		WICDecodeMetadataCacheOnLoad,
		pDecoder.ReleaseAndGetAddressOf()
	);
	if (SUCCEEDED(hr))
	{

		// Create the initial frame.
		hr = pDecoder.Get()->GetFrame(0, pSource.ReleaseAndGetAddressOf());
	}

	if (SUCCEEDED(hr))
	{
		// Convert the image format to 32bppPBGRA
		// (DXGI_FORMAT_B8G8R8A8_UNORM + D2D1_ALPHA_MODE_PREMULTIPLIED).
		hr = object.m_pWICFactory->CreateFormatConverter(pConverter.ReleaseAndGetAddressOf());
	}
	if (SUCCEEDED(hr))
	{
		// If a new width or height was specified, create an
		// IWICBitmapScaler and use it to resize the image.
		if (destinationWidth != 0 || destinationHeight != 0)
		{
			UINT originalWidth, originalHeight;
			hr = pSource.Get()->GetSize(&originalWidth, &originalHeight);
			if (SUCCEEDED(hr))
			{
				if (destinationWidth == 0)
				{
					FLOAT scalar = static_cast<FLOAT>(destinationHeight) / static_cast<FLOAT>(originalHeight);
					destinationWidth = static_cast<UINT>(scalar * static_cast<FLOAT>(originalWidth));
				}
				else if (destinationHeight == 0)
				{
					FLOAT scalar = static_cast<FLOAT>(destinationWidth) / static_cast<FLOAT>(originalWidth);
					destinationHeight = static_cast<UINT>(scalar * static_cast<FLOAT>(originalHeight));
				}

				hr = object.m_pWICFactory->CreateBitmapScaler(pScaler.ReleaseAndGetAddressOf());
				if (SUCCEEDED(hr))
				{
					hr = pScaler.Get()->Initialize(
						pSource.Get(),
						destinationWidth,
						destinationHeight,
						WICBitmapInterpolationModeCubic
					);
				}
				if (SUCCEEDED(hr))
				{
					hr = pConverter.Get()->Initialize(
						pScaler.Get(),
						GUID_WICPixelFormat32bppPBGRA,
						WICBitmapDitherTypeNone,
						NULL,
						0.f,
						WICBitmapPaletteTypeMedianCut
					);
				}
			}
		}
		else // Don't scale the image.
		{
			hr = pConverter.Get()->Initialize(
				pSource.Get(),
				GUID_WICPixelFormat32bppPBGRA,
				WICBitmapDitherTypeNone,
				NULL,
				0.f,
				WICBitmapPaletteTypeMedianCut
			);
		}
	}
	if (SUCCEEDED(hr))
	{
		// Create a Direct2D bitmap from the WIC bitmap.
		hr = object.m_pD2DDeviceContext.Get()->CreateBitmapFromWicBitmap(
			pConverter.Get(),
			NULL,
			&object.m_pBitmap
		);
	}

	return hr;
}