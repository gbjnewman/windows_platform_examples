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

		/* commented out so x closes the window(becasue the close message hasn't
		 * been handled properly here)
		 * https://youtu.be/d003_D-9EnY?si=PJ3C-_vLFscsB4Gk&t=1125 */
		case WM_SIZE:
		{
			OutputDebugStringA("WM_SIZE\n");
		} break;

		case WM_CLOSE:
		{
			OutputDebugStringA("WM_CLOSE\n");
		} break;

		case WM_ACTIVATEAPP:
		{
			OutputDebugStringA("WM_ACTIVATEAPP\n");
		} break;

		/* https://youtu.be/d003_D-9EnY?si=u87h-Jq-_flj8lYL&t=1162 */
		case WM_DESTROY:
		{
			PostQuitMessage(0);
			OutputDebugStringA("WM_DESTROY\n");
		} break;

		/* https://youtu.be/4ROiWonnWGk?si=b18VbjZjH_qZJvoe&t=3052 */
		case WM_PAINT:
		{
			/* https://youtu.be/4ROiWonnWGk?si=CkI9eK6BMvUBTJgs&t=3088 */
			PAINTSTRUCT Paint;
			HDC DeviceContext =
				BeginPaint(	hwnd,		//_In_ HWND hwnd
							&Paint);	//_Out_ LPPAINTSTRUCT lpPaint
			/* https://youtu.be/4ROiWonnWGk?si=tdFLm9XTFAjQC9Bd&t=3258 */
			int X = Paint.rcPaint.left;
			int Y = Paint.rcPaint.top;
			int Width = Paint.rcPaint.right - Paint.rcPaint.left;
			int Height = Paint.rcPaint.bottom - Paint.rcPaint.top;
			/* https://youtu.be/4ROiWonnWGk?si=yNO39Jw5lfVyuDtn&t=3176
			 * https://youtu.be/4ROiWonnWGk?si=laGlyp_DIacl7rj5&t=3300
			 * PatBlt needs Gdi32.lib */
			PatBlt(	DeviceContext,	//_in_ HDC hdc
					X,				//_in_ int nXLeft
					Y,				//_in_ int nYLeft
					Width,			//_in_ nWidth
					Height,			//_in_ nHeight
					BLACKNESS);		//_in_ DWORD dwRop
			/* https://youtu.be/4ROiWonnWGk?si=hgJBeZVCJgYT0VHa&t=3126 */
			EndPaint(	hwnd,		//_In_ HWND hWnd
						&Paint);	//_In_ const PAINTSTRUCT *lpPaint
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
	/* casey's explaination of how to open a window in windows
	 * https://youtu.be/4ROiWonnWGk?si=voZuPeSIwZlMzviy&t=179 */

	/* WNDCLASS is a struct, it's members are being initialised
	 * with zeros here. https://youtu.be/4ROiWonnWGk?si=jPsLze0-AGLYj0rQ&t=579
	 * https://learn.microsoft.com/en-us/windows/win32/api/winuser/ns-winuser-wndclassa */
	WNDCLASS WindowClass = {};

	/* https://youtu.be/4ROiWonnWGk?si=Qf2dO9mtxbIDKxDG&t=993 */
	/* https://youtu.be/d003_D-9EnY?si=LSVJ6eP2lGzOzgiX&t=607
	 * vvv style was not needed, see ^^^ */
	//WindowClass.style = CS_OWNDC|CS_HREDRAW|CS_VREDRAW;
	/* https://youtu.be/4ROiWonnWGk?si=JYJ_nGNNEjWlrlsS&t=1274 */
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
	if(RegisterClassA(&WindowClass))
	{
		/* casey create window breakdown
		 * https://youtu.be/4ROiWonnWGk?si=kHx4s38HZ_ZHbceN&t=2334 */
		HWND WindowHandle =
			/* vvv https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-createwindowexa */
			CreateWindowExA(
				0,								//_In_		DWORD dwExStyle
				WindowClass.lpszClassName,		//_In_opt_	LPCTSTR lpClassName
				"A window name",				//_In_opt_	LPCTSTR lpWindowName
				WS_OVERLAPPEDWINDOW|WS_VISIBLE,	//_In_		DWORD dwStyle
				CW_USEDEFAULT,					//_In_		int x
				CW_USEDEFAULT,					//_In_		int y
				CW_USEDEFAULT,					//_In_		int nWidth
				CW_USEDEFAULT,					//_In_		int nHeight
				0,								//_In_opt_	HWND hWndParent
				0,								//_In_opt_	HMENU hMenu
				hInstance,						//_In_opt_	HINSTANCE hInstance
				0);								//_In_opt_	LPVOID lpParam
		/* vvv https://youtu.be/4ROiWonnWGk?si=tKcq71cy18bp6ZA1&t=2568 */
		if(WindowHandle)
		{
			/* vvv https://youtu.be/4ROiWonnWGk?si=9uNndbY7MNHBjIt5&t=2618 */
			for(;;)
			{
				MSG Message;
			/* vvv https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-getmessage */
				BOOL MessageResult =
					/* https://youtu.be/d003_D-9EnY?si=FkW_9FuH0zVCy4cc&t=1003
					 * A vs W */
					GetMessageA(	&Message,	//_Out_		LPMSG lpMsg
						0,			//_In_opt_	HWND hWnd
						0,			//_In_		wMsgFilterMin
						0);			//_In_		wMsgFilterMax
				if(MessageResult > 0)
				{
					/* https://youtu.be/4ROiWonnWGk?si=XV87ckUwxtwkmGi6&t=2886 */
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
