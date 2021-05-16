#pragma once

#include <exception>

//#include <pthread.h>

//#include <Basic/LeggieroBasic.h>

#include "../WindowsCommon.h"
#include "WindowEventObserver.h"


namespace PixelRay
{
	namespace Platform
	{
		namespace Windows
		{
			struct WindowCreateParam;
			class WindowCreateFailException;

			class Window
			{
			public:
//				Window(const WindowCreateParam& createParam)
//					noexcept(false)
//					: Window(createParam, NULL) { }

//				Window(const WindowCreateParam& createParam, IWindowEventObserver* messageObserver)
//					noexcept(false);

				virtual ~Window();

			public:
				HWND					GetHWND() const { return m_hWnd; }

				bool					IsValidWindow() const { return m_isValidWindow; }
				DWORD					GetWindowError() const { return m_lastError; }

//				IWindowEventObserver* GetMessageObserver() const { return m_messageObserver; }
//				void					SetMessageObserver(IWindowEventObserver* observer) { m_messageObserver = observer; }

			private:
				HWND					m_hWnd;

				bool					m_isValidWindow;
				DWORD					m_lastError;

				bool					m_isTouchEnabled;

//				IWindowEventObserver* m_messageObserver;

//				pthread_t* m_messageLoopThread;
				HANDLE					m_createWaitEvent;

			private:
//				static void* __PTW32_CDECL WindowThreadFunction(void* Args);

				static bool WindowRegisterClass(Window* _this, const WindowCreateParam& createParam);
				static bool WindowCreateWindow(Window* _this, const WindowCreateParam& createParam);

				static bool DisableWindowGestures(Window* _this);

				static void MessageLoopFunction(Window* _this);
			};
		}
	}
}