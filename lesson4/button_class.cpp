#include "button_class.h"

Button::~Button()
{
}

HRESULT Button::DrawingCloseButton(
    Button& object,
    int buttonSelection,
    int pressingButton
)
{
    HRESULT hr = S_OK;

    if (object.m_pD2DDeviceContext.Get() && object.m_pDXGISwapChain.Get())
    {
        if (buttonSelection < 0 || pressingButton < 0)
        {
            MessageBox(NULL,
                L"DrawingMinimizeButton: One or more parameters are less than zero!",
                object.m_windowTitle,
                NULL);

            return hr = 1;
        }

        D2D1_SIZE_F size = object.m_pD2DDeviceContext.Get()->GetSize();

        object.m_pD2DDeviceContext.Get()->BeginDraw();
        object.m_pD2DDeviceContext.Get()->Clear();

        // Drawing a close button.
        Microsoft::WRL::ComPtr<ID2D1SolidColorBrush> pBackgroundBrush;
        Microsoft::WRL::ComPtr<ID2D1SolidColorBrush> pCloseButtonBrush;

        D2D1_POINT_2F pointA{};
        D2D1_POINT_2F pointB{};

        hr = object.m_pD2DDeviceContext.Get()->CreateSolidColorBrush(
            D2D1::ColorF(0xFEE3EE, 1.0),
            pBackgroundBrush.ReleaseAndGetAddressOf()
        );

        if (SUCCEEDED(hr))
        {
            object.m_pD2DDeviceContext.Get()->FillRectangle(
                D2D1::RectF(
                    0.f,
                    0.f,
                    size.width,
                    size.height
                ),
                pBackgroundBrush.Get()
            );

            if (buttonSelection == 0 && pressingButton == 0)
            {
                hr = object.m_pD2DDeviceContext.Get()->CreateSolidColorBrush(
                    D2D1::ColorF(0xDC8095, 1.0),
                    pCloseButtonBrush.ReleaseAndGetAddressOf()
                );

                if (SUCCEEDED(hr))
                {
                    pointA = { 10, 10 };
                    pointB = { 22, 22 };

                    object.m_pD2DDeviceContext.Get()->DrawLine(
                        pointA, pointB, pCloseButtonBrush.Get(), 2
                    );

                    pointA = { 10, 22 };
                    pointB = { 22, 10 };

                    object.m_pD2DDeviceContext.Get()->DrawLine(
                        pointA, pointB, pCloseButtonBrush.Get(), 2
                    );
                }
            }
            if (buttonSelection == 1 && pressingButton == 0)
            {
                hr = object.m_pD2DDeviceContext.Get()->CreateSolidColorBrush(
                    D2D1::ColorF(0xDC8095, 1.0),
                    pCloseButtonBrush.ReleaseAndGetAddressOf()
                );

                if (SUCCEEDED(hr))
                {
                    pointA = { 9, 9 };
                    pointB = { 23, 23 };

                    object.m_pD2DDeviceContext.Get()->DrawLine(
                        pointA, pointB, pCloseButtonBrush.Get(), 2
                    );

                    pointA = { 9, 23 };
                    pointB = { 23, 9 };

                    object.m_pD2DDeviceContext.Get()->DrawLine(
                        pointA, pointB, pCloseButtonBrush.Get(), 2
                    );
                }
            }
            if (pressingButton == 1)
            {
                hr = object.m_pD2DDeviceContext.Get()->CreateSolidColorBrush(
                    D2D1::ColorF(0x315B96, 1.0),
                    pCloseButtonBrush.ReleaseAndGetAddressOf()
                );

                if (SUCCEEDED(hr))
                {
                    pointA = { 9, 9 };
                    pointB = { 23, 23 };

                    object.m_pD2DDeviceContext.Get()->DrawLine(
                        pointA, pointB, pCloseButtonBrush.Get(), 2
                    );

                    pointA = { 9, 23 };
                    pointB = { 23, 9 };

                    object.m_pD2DDeviceContext.Get()->DrawLine(
                        pointA, pointB, pCloseButtonBrush.Get(), 2
                    );
                }
            }
        }

        hr = object.m_pD2DDeviceContext.Get()->EndDraw();
        // Make the swap chain available to the composition engine.
        hr = object.m_pDXGISwapChain.Get()->Present(0, 0);
    }

    return hr;
}

HRESULT Button::DrawingMaximizeRestoreButton(
    Button& object,
    int buttonSelection,
    int pressingButton,
    int changeIcon
)
{
    HRESULT hr = S_OK;

    if (object.m_pD2DDeviceContext.Get() && object.m_pDXGISwapChain.Get())
    {
        if (buttonSelection < 0 || pressingButton < 0)
        {
            MessageBox(NULL,
                L"DrawingMinimizeButton: One or more parameters are less than zero!",
                object.m_windowTitle,
                NULL);

            return hr = 1;
        }

        D2D1_SIZE_F size = object.m_pD2DDeviceContext.Get()->GetSize();

        object.m_pD2DDeviceContext.Get()->BeginDraw();
        object.m_pD2DDeviceContext.Get()->Clear();

        // Drawing a maximize/restore button.
        Microsoft::WRL::ComPtr<ID2D1SolidColorBrush> m_pBackgroundBrush;
        Microsoft::WRL::ComPtr<ID2D1SolidColorBrush> m_pMaxRestButtonBrush;

        hr = object.m_pD2DDeviceContext.Get()->CreateSolidColorBrush(
            D2D1::ColorF(0xfEE3EE, 1.0),
            m_pBackgroundBrush.ReleaseAndGetAddressOf()
        );

        if (SUCCEEDED(hr))
        {
            object.m_pD2DDeviceContext.Get()->FillRectangle(
                D2D1::RectF(
                    0.f,
                    0.f,
                    size.width,
                    size.height
                ),
                m_pBackgroundBrush.Get()
            );

            if (changeIcon == 0)
            {
                if (buttonSelection == 0 && pressingButton == 0)
                {
                    hr = object.m_pD2DDeviceContext.Get()->CreateSolidColorBrush(
                        D2D1::ColorF(0xDC8095, 1.0),
                        m_pMaxRestButtonBrush.ReleaseAndGetAddressOf()
                    );

                    if (SUCCEEDED(hr))
                    {
                        object.m_pD2DDeviceContext.Get()->DrawRoundedRectangle(
                            D2D1::RoundedRect(
                                D2D1::RectF(10.0f, 10.0f, 22.0f, 22.0f),
                                2.f,
                                2.f
                            ),
                            m_pMaxRestButtonBrush.Get(), 2
                        );
                    }
                }
                if (buttonSelection == 1 && pressingButton == 0)
                {
                    hr = object.m_pD2DDeviceContext.Get()->CreateSolidColorBrush(
                        D2D1::ColorF(0xDC8095, 1.0),
                        m_pMaxRestButtonBrush.ReleaseAndGetAddressOf()
                    );

                    if (SUCCEEDED(hr))
                    {
                        object.m_pD2DDeviceContext.Get()->DrawRoundedRectangle(
                            D2D1::RoundedRect(
                                D2D1::RectF(9.0f, 9.0f, 23.0f, 23.0f),
                                2.f,
                                2.f
                            ),
                            m_pMaxRestButtonBrush.Get(), 2
                        );
                    }
                }
                if (pressingButton == 1)
                {
                    hr = object.m_pD2DDeviceContext.Get()->CreateSolidColorBrush(
                        D2D1::ColorF(0x315B96, 1.0),
                        m_pMaxRestButtonBrush.ReleaseAndGetAddressOf()
                    );

                    if (SUCCEEDED(hr))
                    {
                        object.m_pD2DDeviceContext.Get()->DrawRoundedRectangle(
                            D2D1::RoundedRect(
                                D2D1::RectF(9.0f, 9.0f, 23.0f, 23.0f),
                                2.f,
                                2.f
                            ),
                            m_pMaxRestButtonBrush.Get(), 2
                        );
                    }
                }
            }
            if (changeIcon == 1)
            {
                if (buttonSelection == 0 && pressingButton == 0)
                {
                    hr = object.m_pD2DDeviceContext.Get()->CreateSolidColorBrush(
                        D2D1::ColorF(0xDC8095, 1.0),
                        m_pMaxRestButtonBrush.ReleaseAndGetAddressOf()
                    );

                    if (SUCCEEDED(hr))
                    {
                        object.m_pD2DDeviceContext.Get()->DrawRoundedRectangle(
                            D2D1::RoundedRect(
                                D2D1::RectF(10.0f, 10.0f, 22.0f, 22.0f),
                                2.f,
                                2.f
                            ),
                            m_pMaxRestButtonBrush.Get(), 2
                        );

                        object.m_pD2DDeviceContext.Get()->DrawRoundedRectangle(
                            D2D1::RoundedRect(
                                D2D1::RectF(15.0f, 7.0f, 25.0f, 17.0f),
                                2.f,
                                2.f
                            ),
                            m_pMaxRestButtonBrush.Get(), 2
                        );
                    }
                }
                if (buttonSelection == 1 && pressingButton == 0)
                {
                    hr = object.m_pD2DDeviceContext.Get()->CreateSolidColorBrush(
                        D2D1::ColorF(0xDC8095, 1.0),
                        m_pMaxRestButtonBrush.ReleaseAndGetAddressOf()
                    );

                    if (SUCCEEDED(hr))
                    {
                        object.m_pD2DDeviceContext.Get()->DrawRoundedRectangle(
                            D2D1::RoundedRect(
                                D2D1::RectF(9.0f, 9.0f, 23.0f, 23.0f),
                                2.f,
                                2.f
                            ),
                            m_pMaxRestButtonBrush.Get(), 2
                        );

                        object.m_pD2DDeviceContext.Get()->DrawRoundedRectangle(
                            D2D1::RoundedRect(
                                D2D1::RectF(14.0f, 6.0f, 26.0f, 18.0f),
                                2.f,
                                2.f
                            ),
                            m_pMaxRestButtonBrush.Get(), 2
                        );
                    }
                }
                if (pressingButton == 1)
                {
                    hr = object.m_pD2DDeviceContext.Get()->CreateSolidColorBrush(
                        D2D1::ColorF(0x315B96, 1.0),
                        m_pMaxRestButtonBrush.ReleaseAndGetAddressOf()
                    );

                    if (SUCCEEDED(hr))
                    {
                        object.m_pD2DDeviceContext.Get()->DrawRoundedRectangle(
                            D2D1::RoundedRect(
                                D2D1::RectF(9.0f, 9.0f, 23.0f, 23.0f),
                                2.f,
                                2.f
                            ),
                            m_pMaxRestButtonBrush.Get(), 2
                        );

                        object.m_pD2DDeviceContext.Get()->DrawRoundedRectangle(
                            D2D1::RoundedRect(
                                D2D1::RectF(14.0f, 6.0f, 26.0f, 18.0f),
                                2.f,
                                2.f
                            ),
                            m_pMaxRestButtonBrush.Get(), 2
                        );
                    }
                }
            }
        }

        hr = object.m_pD2DDeviceContext.Get()->EndDraw();
        // Make the swap chain available to the composition engine.
        hr = object.m_pDXGISwapChain.Get()->Present(0, 0);
    }

    return hr;
}

HRESULT Button::DrawingMinimizeButton(
    Button& object,
    int buttonSelection,
    int pressingButton
)
{
    HRESULT hr = S_OK;

    if (object.m_pD2DDeviceContext.Get() && object.m_pDXGISwapChain.Get())
    {
        if (buttonSelection < 0 || pressingButton < 0)
        {
            MessageBox(NULL,
                L"DrawingMinimizeButton: One or more parameters are less than zero!",
                object.m_windowTitle,
                NULL);

            return hr = 1;
        }

        D2D1_SIZE_F size = object.m_pD2DDeviceContext.Get()->GetSize();

        object.m_pD2DDeviceContext.Get()->BeginDraw();
        object.m_pD2DDeviceContext.Get()->Clear();

        // Drawing a minimize button.
        Microsoft::WRL::ComPtr<ID2D1SolidColorBrush> m_pBackgroundBrush;
        Microsoft::WRL::ComPtr<ID2D1SolidColorBrush> m_pMinimizeButtonBrush;

        hr = object.m_pD2DDeviceContext.Get()->CreateSolidColorBrush(
            D2D1::ColorF(0xfEE3EE, 1.0),
            m_pBackgroundBrush.ReleaseAndGetAddressOf()
        );

        if (SUCCEEDED(hr))
        {
            object.m_pD2DDeviceContext.Get()->FillRectangle(
                D2D1::RectF(
                    0.f,
                    0.f,
                    size.width,
                    size.height
                ),
                m_pBackgroundBrush.Get()
            );

            if (buttonSelection == 0 && pressingButton == 0)
            {
                hr = object.m_pD2DDeviceContext.Get()->CreateSolidColorBrush(
                    D2D1::ColorF(0xDC8095, 1.0),
                    m_pMinimizeButtonBrush.ReleaseAndGetAddressOf()
                );

                if (SUCCEEDED(hr))
                {
                    object.m_pD2DDeviceContext.Get()->FillRoundedRectangle(
                        D2D1::RoundedRect(
                            D2D1::RectF(9.0f, 21.0f, 23.0f, 23.0f),
                            2.f,
                            2.f
                        ),
                        m_pMinimizeButtonBrush.Get()
                    );
                }
            }
            if (buttonSelection == 1 && pressingButton == 0)
            {
                hr = object.m_pD2DDeviceContext.Get()->CreateSolidColorBrush(
                    D2D1::ColorF(0xDC8095, 1.0),
                    m_pMinimizeButtonBrush.ReleaseAndGetAddressOf()
                );

                if (SUCCEEDED(hr))
                {
                    object.m_pD2DDeviceContext.Get()->FillRoundedRectangle(
                        D2D1::RoundedRect(
                            D2D1::RectF(8.0f, 21.0f, 24.0f, 23.0f),
                            2.f,
                            2.f
                        ),
                        m_pMinimizeButtonBrush.Get()
                    );
                }
            }
            if (pressingButton == 1)
            {
                hr = object.m_pD2DDeviceContext.Get()->CreateSolidColorBrush(
                    D2D1::ColorF(0x315B96, 1.0),
                    m_pMinimizeButtonBrush.ReleaseAndGetAddressOf()
                );

                if (SUCCEEDED(hr))
                {
                    object.m_pD2DDeviceContext.Get()->FillRoundedRectangle(
                        D2D1::RoundedRect(
                            D2D1::RectF(8.0f, 21.0f, 24.0f, 23.0f),
                            2.f,
                            2.f
                        ),
                        m_pMinimizeButtonBrush.Get()
                    );
                }
            }
        }

        hr = object.m_pD2DDeviceContext.Get()->EndDraw();
        // Make the swap chain available to the composition engine.
        hr = object.m_pDXGISwapChain.Get()->Present(0, 0);
    }

    return hr;
}

HRESULT Button::DrawingMainPanelButton(
    Button& object,
    int buttonSelection,
    int pressingButton
)
{
    HRESULT hr = S_OK;

    if (object.m_pD2DDeviceContext.Get() && object.m_pDXGISwapChain.Get())
    {
        if (buttonSelection < 0 || pressingButton < 0)
        {
            MessageBox(NULL,
                L"DrawingMainPanelButton: One or more parameters are less than zero!",
                object.m_windowTitle,
                NULL);

            return hr = 1;
        }

        D2D1_SIZE_F size = object.m_pD2DDeviceContext.Get()->GetSize();

        object.m_pD2DDeviceContext.Get()->BeginDraw();
        object.m_pD2DDeviceContext.Get()->Clear(D2D1::ColorF(D2D1::ColorF(0xfEE3EE)));

        // Drawing a button.

        float transparent[7]{ 0.4f, 0.25f, 0.15f, 0.05f, 0.025f, 0.01f };

        // Six pixels is the size of the non-client area, as well as the size of the shadow.
        float left{ 6.0f };
        float top{ 6.0f };
        float right{ size.width - 6.0f };
        float bottom{ size.height - 6.0f };

        Microsoft::WRL::ComPtr<ID2D1SolidColorBrush> pButtonSelectedBrush;
        Microsoft::WRL::ComPtr<ID2D1SolidColorBrush> pButtonPressedBrush;
        Microsoft::WRL::ComPtr<ID2D1SolidColorBrush> pBackgroundShadowBrush;
        Microsoft::WRL::ComPtr<ID2D1SolidColorBrush> pButtonTextBrush;

        D2D1_ROUNDED_RECT roundedRectButton{};

        // To make the rounded corners look neater, 
        // it was decided to reduce the area in which the button is drawn by six pixels.
        //
        roundedRectButton = D2D1::RoundedRect(
            D2D1::RectF(
                6.0f,
                6.0f,
                size.width - 6.0f,
                size.height - 6.0f
            ),
            6.0f,
            6.0f
        );

        // Creating text format.
        static wchar_t msc_buttonFontName[] = L"Verdana";
        static float msc_buttonFontSize = 12;

        Microsoft::WRL::ComPtr<IDWriteTextFormat> pButtonTextFormat;

        // When using "GetAddressOf" memory leaks were noticed when the window was redrawn, 
        // so it was decided to use "ReleaseAndGetAddressOf".

        // Create a DirectWrite text format object.
        hr = object.m_pDWriteFactory->CreateTextFormat(
            msc_buttonFontName,
            NULL,
            DWRITE_FONT_WEIGHT_MEDIUM,
            DWRITE_FONT_STYLE_NORMAL,
            DWRITE_FONT_STRETCH_NORMAL,
            msc_buttonFontSize,
            L"", //locale
            pButtonTextFormat.ReleaseAndGetAddressOf()
        );

        if (SUCCEEDED(hr))
        {
            if (SUCCEEDED(hr))
            {
                // Center the text horizontally and vertically.
                pButtonTextFormat.Get()->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
                // and vertically.
                pButtonTextFormat.Get()->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
            }

            if (buttonSelection == 0)
            {
                // Drawing text in to button.
                hr = object.m_pD2DDeviceContext.Get()->CreateSolidColorBrush(
                    D2D1::ColorF(D2D1::ColorF(0x233567, 1.0f)),
                    pButtonTextBrush.ReleaseAndGetAddressOf()
                );

                if (SUCCEEDED(hr))
                {
                    object.m_pD2DDeviceContext.Get()->DrawText(
                        object.m_windowTitle,
                        lstrlen(object.m_windowTitle),
                        pButtonTextFormat.Get(),
                        D2D1::RectF(
                            2.0f,
                            2.0f,
                            size.width - 2.0f,
                            size.height - 2.0f
                        ),
                        pButtonTextBrush.Get()
                    );
                }
            }
            if (buttonSelection == 1 && pressingButton == 0)
            {
                // Drawing a shadow.
                for (int i = 0; i < 6; i++)
                {
                    hr = object.m_pD2DDeviceContext.Get()->CreateSolidColorBrush(
                        D2D1::ColorF(0x3E3E3E, transparent[i]),
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
                // Drawing a button with rounded Corners.
                hr = object.m_pD2DDeviceContext.Get()->CreateSolidColorBrush(
                    D2D1::ColorF(D2D1::ColorF(0xFEE3EE, 1.0f)),
                    pButtonSelectedBrush.ReleaseAndGetAddressOf()
                );

                if (SUCCEEDED(hr))
                {
                    object.m_pD2DDeviceContext.Get()->FillRoundedRectangle(roundedRectButton, pButtonSelectedBrush.Get());
                }

                // Drawing text in to button.
                hr = object.m_pD2DDeviceContext.Get()->CreateSolidColorBrush(
                    D2D1::ColorF(D2D1::ColorF(0x315B96, 1.0f)),
                    pButtonTextBrush.ReleaseAndGetAddressOf()
                );

                if (SUCCEEDED(hr))
                {
                    object.m_pD2DDeviceContext.Get()->DrawText(
                        object.m_windowTitle,
                        lstrlen(object.m_windowTitle),
                        pButtonTextFormat.Get(),
                        D2D1::RectF(
                            2.0f,
                            2.0f,
                            size.width - 2.0f,
                            size.height - 2.0f
                        ),
                        pButtonTextBrush.Get()
                    );
                }
            }
            if (pressingButton == 1)
            {
                // Drawing a shadow.
                for (int i = 0; i < 6; i++)
                {
                    hr = object.m_pD2DDeviceContext.Get()->CreateSolidColorBrush(
                        D2D1::ColorF(0x3E3E3E, transparent[i]),
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
                // Drawing a button with rounded Corners.
                hr = object.m_pD2DDeviceContext.Get()->CreateSolidColorBrush(
                    D2D1::ColorF(D2D1::ColorF(0x4264C2, 1.0f)),
                    pButtonPressedBrush.ReleaseAndGetAddressOf()
                );

                if (SUCCEEDED(hr))
                {
                    object.m_pD2DDeviceContext.Get()->FillRoundedRectangle(roundedRectButton, pButtonPressedBrush.Get());
                }

                // Drawing text in to button.
                hr = object.m_pD2DDeviceContext.Get()->CreateSolidColorBrush(
                    D2D1::ColorF(D2D1::ColorF(0xFEE3EE, 1.0f)),
                    pButtonTextBrush.ReleaseAndGetAddressOf()
                );

                if (SUCCEEDED(hr))
                {
                    object.m_pD2DDeviceContext.Get()->DrawText(
                        object.m_windowTitle,
                        lstrlen(object.m_windowTitle),
                        pButtonTextFormat.Get(),
                        D2D1::RectF(
                            2.0f,
                            2.0f,
                            size.width - 2.0f,
                            size.height - 2.0f
                        ),
                        pButtonTextBrush.Get()
                    );
                }
            }
        }

        hr = object.m_pD2DDeviceContext.Get()->EndDraw();
        // Make the swap chain available to the composition engine.
        hr = object.m_pDXGISwapChain.Get()->Present(0, 0);
    }

    return hr;
}

HRESULT Button::DrawRoundedRectButton(
    Button& object,
    int buttonSelection,
    int pressingButton
)
{
    HRESULT hr = S_OK;

    if (object.m_pD2DDeviceContext.Get() && object.m_pDXGISwapChain.Get())
    {
        if (buttonSelection < 0 || pressingButton < 0)
        {
            MessageBox(NULL,
                L"DrawingMainPanelButton: One or more parameters are less than zero!",
                object.m_windowTitle,
                NULL);

            return hr = 1;
        }

        D2D1_SIZE_F size = object.m_pD2DDeviceContext.Get()->GetSize();

        object.m_pD2DDeviceContext.Get()->BeginDraw();
        object.m_pD2DDeviceContext.Get()->Clear(D2D1::ColorF(D2D1::ColorF(0xfEE3EE)));

        // Drawing a button.

        float transparent[7]{ 0.4f, 0.25f, 0.15f, 0.05f, 0.025f, 0.01f };

        // Six pixels is the size of the non-client area, as well as the size of the shadow.
        float left{ 6.0f };
        float top{ 6.0f };
        float right{ size.width - 6.0f };
        float bottom{ size.height - 6.0f };

        Microsoft::WRL::ComPtr<ID2D1SolidColorBrush> pButtonSelectedBrush;
        Microsoft::WRL::ComPtr<ID2D1SolidColorBrush> pButtonPressedBrush;
        Microsoft::WRL::ComPtr<ID2D1SolidColorBrush> pBackgroundShadowBrush;
        Microsoft::WRL::ComPtr<ID2D1SolidColorBrush> pOutlinerButtonBrush;
        Microsoft::WRL::ComPtr<ID2D1SolidColorBrush> pButtonTextBrush;

        D2D1_ROUNDED_RECT roundedRectButton{};

        // To make the rounded corners look neater, 
        // it was decided to reduce the area in which the button is drawn by six pixels.
        roundedRectButton = D2D1::RoundedRect(
            D2D1::RectF(
                6.0f,
                6.0f,
                size.width - 6.0f,
                size.height - 6.0f
            ),
            6.0f,
            6.0f
        );

        // Creating text format.
        static wchar_t msc_buttonFontName[] = L"Verdana";
        static float msc_buttonFontSize = 12;

        Microsoft::WRL::ComPtr<IDWriteTextFormat> pButtonTextFormat;

        // When using "GetAddressOf" memory leaks were noticed when the window was redrawn, 
        // so it was decided to use "ReleaseAndGetAddressOf".

        // Create a DirectWrite text format object.
        hr = object.m_pDWriteFactory->CreateTextFormat(
            msc_buttonFontName,
            NULL,
            DWRITE_FONT_WEIGHT_MEDIUM,
            DWRITE_FONT_STYLE_NORMAL,
            DWRITE_FONT_STRETCH_NORMAL,
            msc_buttonFontSize,
            L"", //locale
            pButtonTextFormat.ReleaseAndGetAddressOf()
        );

        if (SUCCEEDED(hr))
        {
            if (SUCCEEDED(hr))
            {
                // Center the text horizontally and vertically.
                pButtonTextFormat.Get()->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
                // and vertically.
                pButtonTextFormat.Get()->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
            }

            if (buttonSelection == 0)
            {
                // Drawing the outline of a button.
                hr = object.m_pD2DDeviceContext.Get()->CreateSolidColorBrush(
                    D2D1::ColorF(0x233567, 1),
                    pOutlinerButtonBrush.ReleaseAndGetAddressOf()
                );

                if (SUCCEEDED(hr))
                {
                    object.m_pD2DDeviceContext.Get()->DrawRoundedRectangle(
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
                        pOutlinerButtonBrush.Get(), 0.5
                    );
                }

                // Drawing text in to button.
                hr = object.m_pD2DDeviceContext.Get()->CreateSolidColorBrush(
                    D2D1::ColorF(D2D1::ColorF(0x233567, 1.0f)),
                    pButtonTextBrush.ReleaseAndGetAddressOf()
                );

                if (SUCCEEDED(hr))
                {
                    object.m_pD2DDeviceContext.Get()->DrawText(
                        object.m_windowTitle,
                        lstrlen(object.m_windowTitle),
                        pButtonTextFormat.Get(),
                        D2D1::RectF(
                            2.0f,
                            2.0f,
                            size.width - 2.0f,
                            size.height - 2.0f
                        ),
                        pButtonTextBrush.Get()
                    );
                }
            }
            if (buttonSelection == 1 && pressingButton == 0)
            {
                // Drawing a shadow.
                for (int i = 0; i < 6; i++)
                {
                    hr = object.m_pD2DDeviceContext.Get()->CreateSolidColorBrush(
                        D2D1::ColorF(0x3E3E3E, transparent[i]),
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
                // Drawing a button with rounded Corners.
                hr = object.m_pD2DDeviceContext.Get()->CreateSolidColorBrush(
                    D2D1::ColorF(D2D1::ColorF(0xFEE3EE, 1.0f)),
                    pButtonSelectedBrush.ReleaseAndGetAddressOf()
                );

                if (SUCCEEDED(hr))
                {
                    object.m_pD2DDeviceContext.Get()->FillRoundedRectangle(roundedRectButton, pButtonSelectedBrush.Get());
                }

                // Drawing text in to button.
                hr = object.m_pD2DDeviceContext.Get()->CreateSolidColorBrush(
                    D2D1::ColorF(D2D1::ColorF(0x315B96, 1.0f)),
                    pButtonTextBrush.ReleaseAndGetAddressOf()
                );

                if (SUCCEEDED(hr))
                {
                    object.m_pD2DDeviceContext.Get()->DrawText(
                        object.m_windowTitle,
                        lstrlen(object.m_windowTitle),
                        pButtonTextFormat.Get(),
                        D2D1::RectF(
                            2.0f,
                            2.0f,
                            size.width - 2.0f,
                            size.height - 2.0f
                        ),
                        pButtonTextBrush.Get()
                    );
                }
            }
            if (pressingButton == 1)
            {
                // Drawing a shadow.
                for (int i = 0; i < 6; i++)
                {
                    hr = object.m_pD2DDeviceContext.Get()->CreateSolidColorBrush(
                        D2D1::ColorF(0x3E3E3E, transparent[i]),
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
                // Drawing a button with rounded Corners.
                hr = object.m_pD2DDeviceContext.Get()->CreateSolidColorBrush(
                    D2D1::ColorF(D2D1::ColorF(0x4264C2, 1.0f)),
                    pButtonPressedBrush.ReleaseAndGetAddressOf()
                );

                if (SUCCEEDED(hr))
                {
                    object.m_pD2DDeviceContext.Get()->FillRoundedRectangle(roundedRectButton, pButtonPressedBrush.Get());
                }

                // Drawing text in to button.
                hr = object.m_pD2DDeviceContext.Get()->CreateSolidColorBrush(
                    D2D1::ColorF(D2D1::ColorF(0xFEE3EE, 1.0f)),
                    pButtonTextBrush.ReleaseAndGetAddressOf()
                );

                if (SUCCEEDED(hr))
                {
                    object.m_pD2DDeviceContext.Get()->DrawText(
                        object.m_windowTitle,
                        lstrlen(object.m_windowTitle),
                        pButtonTextFormat.Get(),
                        D2D1::RectF(
                            2.0f,
                            2.0f,
                            size.width - 2.0f,
                            size.height - 2.0f
                        ),
                        pButtonTextBrush.Get()
                    );
                }
            }
        }

        hr = object.m_pD2DDeviceContext.Get()->EndDraw();
        // Make the swap chain available to the composition engine.
        hr = object.m_pDXGISwapChain.Get()->Present(0, 0);
    }

    return hr;
}