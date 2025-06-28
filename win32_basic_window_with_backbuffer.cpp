#include <windows.h>

/* https://youtu.be/GAi_nTx1zG8?si=N49yu5rWUBhu9x9a&t=1182 */
#define internal_function static 
/* https://youtu.be/GAi_nTx1zG8?si=ZfEdC6daYdRzcY7w&t=1078 */
#define local_persist static 
#define global_variable static 

/* https://youtu.be/GAi_nTx1zG8?si=CA0DppVGPG7d_tJH&t=833 */
/* https://youtu.be/GAi_nTx1zG8?si=HRn5QW0-FgsfUTcB&t=1236 */
global_variable bool Running;
global_variable BITMAPINFO BitmapInfo;
global_variable void *BitmapMemory;
global_variable HBITMAP BitmapHandle;
global_variable HDC BitmapDeviceContext;

/* https://youtu.be/GAi_nTx1zG8?si=CcB70WFrqiPPTfqM&t=1416
 * DIB means device independant bitmap */
internal_function void
Win32ResizeDIBSection(int Width, int Height)
{
	/* https://youtu.be/GAi_nTx1zG8?si=G9vO8cEmlbxR4z_7&t=3080 */
	if(BitmapHandle)
	{
		/* https://youtu.be/GAi_nTx1zG8?si=9virVjKHqwdJvk4F&t=3149 */
		DeleteObject(BitmapHandle);
	}
	if(!BitmapDeviceContext)
	{
		BitmapDeviceContext = CreateCompatibleDC(0);
	}

	/* https://youtu.be/GAi_nTx1zG8?si=4iwGvX-xzNnm_XbF&t=2477 */
	BitmapInfo.bmiHeader.biSize = sizeof(BitmapInfo.bmiHeader);
	BitmapInfo.bmiHeader.biWidth = Width;
	BitmapInfo.bmiHeader.biHeight = Height;
	BitmapInfo.bmiHeader.biPlanes = 1;
	BitmapInfo.bmiHeader.biBitCount = 32;
	BitmapInfo.bmiHeader.biCompression = BI_RGB;

	/* https://youtu.be/GAi_nTx1zG8?si=hHKLswfckdPCydYY&t=2334 */
	BitmapHandle = CreateDIBSection(
				BitmapDeviceContext,//[in]  HDC              hdc,
				&BitmapInfo,		//[in]  const BITMAPINFO *pbmi,
				DIB_RGB_COLORS,		//[in]  UINT             usage,
				/* https://youtu.be/GAi_nTx1zG8?si=bru4uZGMNSst-A6M&t=2417 */
				&BitmapMemory,		//[out] VOID             **ppvBits,
				0,					//[in]  HANDLE           hSection,
				0);					//[in]  DWORD            offset

}

/* https://youtu.be/GAi_nTx1zG8?si=v8CEBbIFQk9YxCbf&t=1803 */
internal_function void
Win32UpdateWindow(HDC DeviceContext, int X, int Y, int Width, int Height)
{
	/* https://youtu.be/GAi_nTx1zG8?si=XRQXVptVJ08V4dsc&t=1926 */
	/* https://youtu.be/GAi_nTx1zG8?si=ZdWdKmWLk64y2S43&t=2015 */
	StretchDIBits(
			DeviceContext,	//HDC              hdc,        [in]
			X,				//int              xDest,      [in]
			Y,				//int              yDest,      [in]
			Width,			//int              DestWidth,  [in]
			Height,			//int              DestHeight, [in]
			X,				//int              xSrc,       [in]
			Y,				//int              ySrc,       [in]
			Width,			//int              SrcWidth,   [in]
			Height,			//int              SrcHeight,  [in]
			BitmapMemory,	//const VOID       *lpBits,    [in]
			&BitmapInfo,	//const BITMAPINFO *lpbmi,     [in]
			/* https://youtu.be/GAi_nTx1zG8?si=6hUCpHlfGr1rj49k&t=2092 */
			DIB_RGB_COLORS,	//UINT             iUsage,     [in]
			/* https://youtu.be/GAi_nTx1zG8?si=LBafSzE7PDo7l0Vw&t=2253 */
			SRCCOPY);		//DWORD            rop         [in]

}
/* vvv https://youtu.be/4ROiWonnWGk?si=Eq7hJHUh7uLoB90K&t=1304 */
LRESULT CALLBACK
Win32MainWindowCallback(HWND hwnd, //Window
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
			/* https://youtu.be/GAi_nTx1zG8?si=YSPfqwD-Wh1PlorY&t=1508 */
			/* https://youtu.be/GAi_nTx1zG8?si=7HHnRaTUltHQtw8d&t=1548 */
			RECT ClientRect;
			GetClientRect(
					hwnd,			//_In_ HWNDhWnd
					&ClientRect);	//_Out_ LPRECT lpRect
			/* https://youtu.be/GAi_nTx1zG8?si=AD5E-cioNNh--H08&t=1623 */
			int Width = ClientRect.right - ClientRect.left;
			int Height = ClientRect.bottom - ClientRect.top;
			/* https://youtu.be/GAi_nTx1zG8?si=Y8MUCBSdv73ydnef&t=1447 */
			Win32ResizeDIBSection(Height, Width);
			OutputDebugStringA("WM_SIZE\n");
		} break;

		case WM_CLOSE:
		{
			/* https://youtu.be/GAi_nTx1zG8?si=Ebzo66opMiq9reSy&t=850 */
			Running = false;
		} break;

		case WM_ACTIVATEAPP:
		{
			OutputDebugStringA("WM_ACTIVATEAPP\n");
		} break;

		case WM_DESTROY:
		{
			/* https://youtu.be/GAi_nTx1zG8?si=MrSn_fs3WMpkNUh1&t=858 */
			Running = false;
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
			/* https://youtu.be/GAi_nTx1zG8?si=QLmuWnIPGu6aEP-0&t=1760 */
			Win32UpdateWindow(DeviceContext, X, Y, Width, Height);
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
			/* https://youtu.be/GAi_nTx1zG8?si=7i6u2-w0waOGF-wv&t=1061 */
			Running = true;
			/* https://youtu.be/GAi_nTx1zG8?si=y03DwoiZD-VAObHs&t=818 */
			while(Running)
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
