#include "WinPCPlatformApplication.h"

#include "Window/WindowCreateParam.h"

namespace PixelRay
{
	namespace Platform
	{
		namespace Windows
		{
			WinPCPlatformApplication::WinPCPlatformApplication(HINSTANCE hInstance, int nCmdShow, LPCTSTR className, LPCTSTR windowName, HICON hIcon, HICON hIconSm, int screenWidth, int screenHeight, float simulatedXPPI, float simulatedYPPI)
				: m_hInstance(hInstance), m_isRunning(true)
			{
//				_InitializeApplicationComponent();
				_InitializeGameWindow(hInstance, nCmdShow, className, windowName, hIcon, hIconSm, screenWidth, screenHeight);
				_InitializeEGLView();
			}

			WinPCPlatformApplication::~WinPCPlatformApplication()
			{
//				m_glView = nullptr;
			}

			void WinPCPlatformApplication::_InitializeGameWindow(HINSTANCE hInstance, int nCmdShow, LPCTSTR className, LPCTSTR windowName, HICON hIcon, HICON hIconSm, int windowWidth, int windowHeight)
			{
				//Setting window parameter
				WindowCreateParam windowParam;
				windowParam.className = className;

				windowParam.hInstance = hInstance;

				windowParam.nCmdShow = nCmdShow;

				windowParam.hIcon = hIcon;
				windowParam.hIconSm = hIconSm;

				windowParam.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);

				windowParam.windowName = windowName;
				windowParam.windowStyle = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_BORDER
					| WS_CLIPSIBLINGS | WS_CLIPCHILDREN; // for EGL

				windowParam.width = windowWidth;
				windowParam.height = windowHeight;
				windowParam.isSetContentsSize = true;

//				m_gameWindow.reset(new Window(windowParam));
//				m_gameWindow->SetMessageObserver(this);
			}

			void WinPCPlatformApplication::_InitializeEGLView()
			{
//				m_glView.reset(new Graphics::EGLView(m_gameWindow->GetHWND()));
			}
		}
	}
}