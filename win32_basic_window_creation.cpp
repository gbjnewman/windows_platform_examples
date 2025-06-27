#include <windows.h>

/* vvv https://youtu.be/4ROiWonnWGk?si=Eq7hJHUh7uLoB90K&t=1304 */
LRESULT CALLBACK
MainWindowCallback(	HWND hwnd,
					UINT uMsg,
					WPARAM wParam,
					LPARAM lParam)
{
	LRESULT Result = 0;

	/* vvv https://youtu.be/4ROiWonnWGk?si=zSr8pAbFO1XSdXhE&t=1477 */
	switch(uMsg)
	{

		case WM_SIZE:
		{
			OutputDebugStringA("WM_SIZE\n");
		} break;

		case WM_DESTROY:
		{
			OutputDebugStringA("WM_DESTROY\n");
		} break;

		case WM_CLOSE:
		{
			OutputDebugStringA("WM_CLOSE\n");
		} break;

		case WM_ACTIVATEAPP:
		{
			OutputDebugStringA("WM_ACTIVATEAPP\n");
		} break;

		case WM_PAINT:
		{
			OutputDebugStringA("WM_PAINT\n");
		} break;

		/* vvv https://youtu.be/4ROiWonnWGk?si=h1ZA5NwAo5Ux4KEP&t=1838 */
		default:
		{
			Result = DefWindowProc(	hwnd,
									uMsg,
									wParam,
									lParam);
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
	WindowClass.style = CS_OWNDC|CS_HREDRAW|CS_VREDRAW;
	/* vvv https://youtu.be/4ROiWonnWGk?si=JYJ_nGNNEjWlrlsS&t=1274 */
	WindowClass.lpfnWndProc = MainWindowCallback;
	//WindowClass.cbClsExtra;
	//WindowClass.cbWndExtra;
	/* vvv https://youtu.be/4ROiWonnWGk?si=dhLFqqhGgYQ0HuyS&t=882/ */
	WindowClass.hInstance = hInstance; // or GetModuleHandle(0);
	//WindowClass.hIcon;
	//WindowClass.hCursor;
	//WindowClass.hbrBackground;
	//WindowClass.lpszMenuName;
	WindowClass.lpszClassName = "ANameForTheWindowClass";

	/* https://youtu.be/4ROiWonnWGk?si=gs990BE36ZkYjvVo&t=2135 */
	if(RegisterClass(&WindowClass))
	{
		//casey create window explanation
		//https://youtu.be/4ROiWonnWGk?si=kHx4s38HZ_ZHbceN&t=2334
		HWND WindowHandle = CreateWindowExA(
			0,									//DWORD dwExStyle
			WindowClass.lpszClassName,			//LPCTSTR lpClassName
			"A window name",					//LPCTSTR lpWindowName
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
