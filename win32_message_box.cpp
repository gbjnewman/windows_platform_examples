/* 
 * https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-messagebox
 * needs user32.lib for compilation, ie: cl win32_message_box.cpp user32.lib
 */
#include <windows.h>

int CALLBACK
WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow)
{
	MessageBox(0, "This is the Message", "This is the title",
		   MB_OK | MB_ICONINFORMATION); // message box options flags

	return(0);
}
