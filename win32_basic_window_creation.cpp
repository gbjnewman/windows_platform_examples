#include <windows.h>

LRESULT CALLBACK
Win32MainWindowCallback(HWND Window,
						UINT Message,
						WPARAM WParam,
						LPARAM LParam)
{
	LRESULT Result = 0;

	switch(Message)
	{

		case WM_SIZE:
		{
		} break;

		case WM_CLOSE:
		{
		} break;

		case WM_ACTIVATEAPP:
		{
		} break;

		case WM_DESTROY:
		{
		} break;

		case WM_PAINT:
		{
		} break;

		default :
		{
			Result = DefWindowProc(	Window,
									Message,
									WParam,
									LParam);
		} break;
	}

	return(Result);

}

// windows entry point(the main function for windows graphical programs)
int CALLBACK
WinMain(HINSTANCE hInstance,
		HINSTANCE hPrevInstance,
		LPSTR lpCmdLine,
		int nCmdShow)
{
	// casey's explaination of how to open a window in windows
	// https://youtu.be/4ROiWonnWGk?si=voZuPeSIwZlMzviy&t=179

	// WNDCLASS is a struct, it's members are being initialised
	// with zeros here. https://youtu.be/4ROiWonnWGk?si=jPsLze0-AGLYj0rQ&t=579
	// https://learn.microsoft.com/en-us/windows/win32/api/winuser/ns-winuser-wndclassa
	WNDCLASS WindowClass = {};

	/* vvv https://youtu.be/4ROiWonnWGk?si=Qf2dO9mtxbIDKxDG&t=993 */
	WindowClass.style;
	WindowClass.lpfnWndProc = Win32MainWindowCallback;
	//WindowClass.cbClsExtra;
	//WindowClass.cbWndExtra;
	/* vvv https://youtu.be/4ROiWonnWGk?si=dhLFqqhGgYQ0HuyS&t=882/ */
	WindowClass.hInstance = hInstance; // or GetModuleHandle(0);
	//WindowClass.hIcon;
	//WindowClass.hCursor;
	//WindowClass.hbrBackground;
	//WindowClass.lpszMenuName;
	WindowClass.lpszClassName = "ANameForTheWindowClass";

	if(RegisterClass(&WindowClass))
	{
		//casey create window explanation
		//https://youtu.be/4ROiWonnWGk?si=kHx4s38HZ_ZHbceN&t=2334
		HWND WindowHandle = CreateWindowExA(
			0,									//DWORD dwExStyle
			WindowClass.lpszClassName,			//LPCTSTR lpClassName
			"Handmade Hero",					//LPCTSTR lpWindowName
			WS_OVERLAPPEDWINDOW|WS_VISIBLE,		//DWORD dwStyle
			CW_USEDEFAULT,						//int x
			CW_USEDEFAULT,						//int y
			CW_USEDEFAULT,						//int nWidth
			CW_USEDEFAULT,						//int nHeight
			0,									//HWND hWndParent
			0,									//HMENU hMenu
			hInstance,							//HINSTANCE hInstance
			0);									//LPVOID lpParam
		if(WindowHandle)
		{
			Running = true;
			while(Running)
			{
				MSG Message;
				BOOL MessageResult = GetMessageA(&Message, 0, 0, 0);
				if(MessageResult > 0)
				{
					TranslateMessage(&Message);
					DispatchMessageA(&Message);
				}
				else
				{
					break;
				}
			}
		}
		else
		{
			//TODO: logging
		}
	}
	else
	{
		//TODO: logging
	}

	return(0);

}
