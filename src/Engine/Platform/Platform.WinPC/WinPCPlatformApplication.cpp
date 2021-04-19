#include "WinPCPlatformApplication.h"

namespace PixelRay
{
	namespace Platform
	{
		namespace Windows
		{
			WinPCPlatformApplication::WinPCPlatformApplication(HINSTANCE hInstance, int nCmdShow, LPCTSTR className, LPCTSTR windowName, HICON hIcon, HICON hIconSm, int screenWidth, int screenHeight, float simulatedXPPI, float simulatedYPPI)
				: m_hInstance(hInstance), m_isRunning(true)
			{
			}

			WinPCPlatformApplication::~WinPCPlatformApplication()
			{
			}

			void WinPCPlatformApplication::_InitializeGameWindow()
			{

			}
		}
	}
}