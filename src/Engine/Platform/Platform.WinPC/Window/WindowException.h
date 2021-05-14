#pragma once

#include <exception>

//#include <Basic/LeggieroBasic.h>

#include "../WindowsCommon.h"


namespace PixelRay
{
	namespace Platform
	{
		namespace Windows
		{
			class WindowCreateFailException : public std::exception
			{
			public:
				WindowCreateFailException()
					: WindowCreateFailException(false, false, ERROR_SUCCESS) { }

				WindowCreateFailException(
					bool isClassRegisterFailed, bool isWindowCreateFailed,
					DWORD lastError);

				virtual ~WindowCreateFailException() throw() { }

			public:
				virtual const char* what() const throw() { return "Failed to create window"; }

			public:
				bool	isClassRegisterFailed;
				bool	isWindowCreateFailed;

				DWORD	lastError;
			};
		}
	}
}
