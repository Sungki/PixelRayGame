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
//				WindowCreateParam param;
			}

			void WinPCPlatformApplication::_InitializeEGLView()
			{
//				m_glView.reset(new Graphics::EGLView(m_gameWindow->GetHWND()));
			}
		}
	}
}