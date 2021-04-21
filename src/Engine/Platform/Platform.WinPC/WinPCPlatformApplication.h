#pragma once

#include <memory>

#include "WindowsCommon.h"

namespace PixelRay
{
	namespace Platform
	{
		namespace Windows
		{
			class WinPCPlatformApplication
			{
			public:
				WinPCPlatformApplication(HINSTANCE hInstance, int nCmdShow, LPCTSTR className, LPCTSTR windowName, HICON hIcon, HICON hIconSm, int screenWidth, int screenHeight, float simulatedXPPI, float simulatedYPPI)
					noexcept(false);
				virtual ~WinPCPlatformApplication();

			public:
				void Run();

			protected:
				HINSTANCE					m_hInstance;
//				std::shared_ptr<Window>		m_gameWindow;

				bool						m_isRunning;

			private:
				void _InitializeGameWindow(HINSTANCE hInstance, int nCmdShow, LPCTSTR className, LPCTSTR windowName, HICON hIcon, HICON hIconSm, int windowWidth, int windowHeight)
					noexcept(false);


			};
		}
	}
}

