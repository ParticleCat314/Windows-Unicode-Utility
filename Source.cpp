#include <windows.h>

LRESULT CALLBACK WindowProcedure(HWND, UINT, WPARAM, LPARAM); \


wchar_t textSaved[20];
HWND text;
HWND button;
HWND Unicode_ouput;

char variable = 2230;

void copy(const wchar_t* code) {



	HGLOBAL hmem = GlobalAlloc(GMEM_MOVEABLE, 5);
	memcpy(GlobalLock(hmem), code, 5);
	GlobalUnlock(hmem);
	OpenClipboard(0);
	EmptyClipboard();
	SetClipboardData(CF_UNICODETEXT, hmem);
	CloseClipboard();

}



const wchar_t Introduction [55] = L"This is a unicode utility program. Programed by Lachan";



int WINAPI WinMain(HINSTANCE hInst, HINSTANCE previousInstance, LPSTR args, int ncmdshow) {

	
	MessageBoxA(NULL, "This program uses the clipboard. Please save any current clipboard data.", "Disclaimer", MB_OK | MB_ICONWARNING);


	WNDCLASS wc = { 0 };

	HBRUSH brush = CreateSolidBrush(RGB(10, 190, 10));

	wc.hbrBackground = (HBRUSH)brush;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.lpszClassName = L"window";
	wc.lpfnWndProc = WindowProcedure;




	RegisterClassW(&wc);


	CreateWindowW(L"window", L"Unicode Utility",  WS_OVERLAPPED |  WS_SYSMENU | WS_VISIBLE, 100, 100, 300, 400, NULL, NULL, NULL, NULL);

	RegisterHotKey(NULL, 100, MOD_ALT, 'S');

	RegisterHotKey(NULL, 200, MOD_ALT, 'D');

	MSG msg = {0};

	while (GetMessage(&msg, NULL, NULL, NULL)) {

		TranslateMessage(&msg);
		DispatchMessage(&msg);

	}



	return 0;

}




LRESULT CALLBACK WindowProcedure(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp) {

	switch (msg) {


	

	

	case WM_CREATE:

		CreateWindow(L"Static", Introduction, WS_VISIBLE | WS_CHILD, 10,0, 260,40, hWnd, NULL,NULL,NULL);



		text = CreateWindow(L"EDIT", L"\u2230", WS_VISIBLE | WS_CHILD | ES_AUTOHSCROLL, 10, 120, 50, 30, hWnd, NULL, NULL, NULL);


		button = CreateWindow(L"Button", L"Generate unicode!", WS_VISIBLE | WS_CHILD, 80, 120, 120, 30, hWnd, (HMENU) 1, NULL, NULL);


		Unicode_ouput = CreateWindow(L"EDIT", L"\u2230", WS_VISIBLE | WS_CHILD, 220, 120, 50, 30, hWnd, NULL, NULL, NULL);



		break;


	case WM_COMMAND:

		switch (LOWORD(wp)) {


		case 1:


			int gwtstate = 0;

			wchar_t *t = &textSaved[0];

			gwtstate = GetWindowText(text, t, 20);
			
			wchar_t* endString;


			unsigned long value = wcstoul(t, &endString, 16);

			wchar_t wstr[2] = { value, L'\0' };

			SetWindowText(Unicode_ouput, wstr);

			copy(wstr);


			break;


		}
		break;


	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, msg, wp, lp);
	}





}
