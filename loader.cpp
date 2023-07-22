#include "loader.h"
#include "translator.h"
#include "d3d9/proxydirectx.h"
#include <QFileInfo>

stGlobalHandles g_handle;
stGlobalClasses g_class;
stGlobalPVars g_vars;

static LPTOP_LEVEL_EXCEPTION_FILTER hOrigUEF;
static WNDPROC hOrigProc = NULL;
static translator *ptranslator = static_cast<translator*>(nullptr);
static CCallHook *sampShowCursor;
static IDirect3DDevice9* device;

void InstallD3DHook()
{
	static bool isDxHooked = false;
	if (isDxHooked)
		return;
	isDxHooked = true;
	device = new proxyIDirect3DDevice9( *reinterpret_cast<IDirect3DDevice9 **>(0xC97C28));
	*reinterpret_cast<IDirect3DDevice9 **>(0xC97C28) = dynamic_cast<IDirect3DDevice9*>(device);
	g_class.DirectX = new CDirectX(device);
}

LONG WINAPI unhandledExceptionFilter ( struct _EXCEPTION_POINTERS* )
{
	/* The game can crash on the D3D destructor if another
	 * plugin installs the D3D hook after this plugin,
	 * and this plugin will be unloaded without unloading
	 * the other plugin.
	*/
	TerminateProcess(GetCurrentProcess(), 0);
}

LRESULT WINAPI WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if (hwnd == g_vars.hwnd)
	{
		for ( int i = static_cast<int>(MenuList.size() - 1); i >= 0; --i )
			if ( MenuList[static_cast<size_t>(i)]->isShowed() ){
				eLockEvent menuEv = MenuList[static_cast<size_t>(i)]->onEvents( hwnd, uMsg, wParam, lParam );
				if ( menuEv != eLe_noLock ){

					if (menuEv == eLe_lockAll)
						return CallWindowProc(hOrigProc, hwnd, 0, 0, 0);
					else if (menuEv == eLe_lockKeyboard && (uMsg == WM_KEYDOWN || uMsg == WM_KEYUP))
						return CallWindowProc(hOrigProc, hwnd, 0, 0, 0);
					else if (menuEv == eLe_lockChar && uMsg == WM_CHAR)
						return CallWindowProc(hOrigProc, hwnd, 0, 0, 0);
					else if (menuEv == eLe_lockMouseScroll && uMsg == WM_MOUSEWHEEL)
						return CallWindowProc(hOrigProc, hwnd, 0, 0, 0);
					else if (menuEv == eLe_lockMouseMove && uMsg == WM_MOUSEMOVE)
						return CallWindowProc(hOrigProc, hwnd, 0, 0, 0);
					else if (menuEv == eLe_lockMouseClick)
						if (uMsg == WM_LBUTTONDBLCLK ||
							uMsg == WM_LBUTTONDOWN   ||
							uMsg == WM_LBUTTONUP     ||
							uMsg == WM_RBUTTONDBLCLK ||
							uMsg == WM_RBUTTONDOWN   ||
							uMsg == WM_RBUTTONUP     ||
							uMsg == WM_MBUTTONDBLCLK ||
							uMsg == WM_MBUTTONDOWN   ||
							uMsg == WM_MBUTTONUP     )
							return CallWindowProc(hOrigProc, hwnd, 0, 0, 0);
				}
			}

		g_class.keys.onEvent(uMsg, wParam);

		if (!ptranslator->Event(uMsg, wParam, lParam))
			return CallWindowProc(hOrigProc, hwnd, 0, 0, 0);
	}
	return CallWindowProc(hOrigProc, hwnd, uMsg, wParam, lParam);
}

static CALLHOOK ShowCursor()
{
	if (!g_vars.isLocalCursorShowed)
		return;

	if (cursorType == eCursorType::System)
		SetCursor(LoadCursor(NULL, IDC_ARROW));
	else if (cursorType == eCursorType::Girl)
		SetCursor(LoadCursor(NULL, NULL));
}

CALLHOOK GameLoop()
{
	g_handle.d3d9 = GetModuleHandleA("d3d9.dll");
	if (g_handle.d3d9 == nullptr || g_handle.d3d9 == INVALID_HANDLE)
		return;
	//InstallD3DHook();

	g_handle.samp = GetModuleHandleA("samp.dll");
	if (g_handle.samp == nullptr || g_handle.samp == INVALID_HANDLE)
		return;

	g_class.samp = *reinterpret_cast<stSAMP**>(g_handle.dwSAMP + SAMP_INFO_OFFSET);
//	if (g_class.samp == nullptr)
//		return;

	static bool hooked = false;
	if (hooked && ptranslator)
		return ptranslator->Loop();
	hooked = true;

	//g_class.samp->misc()->toggleCursor(false); // For reload cersor
	g_class.SF = new SAMPFUNCS();
	ptranslator = new translator();
	sampShowCursor = new CCallHook(reinterpret_cast<void*>(g_handle.dwSAMP + 0x9BD99), 8, cp_before);
	sampShowCursor->enable(ShowCursor);
	hOrigUEF = SetUnhandledExceptionFilter( unhandledExceptionFilter );
	hOrigProc = reinterpret_cast<WNDPROC>(SetWindowLongA(g_vars.hwnd, GWL_WNDPROC,
														 reinterpret_cast<LONG>(WndProc)));
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD dwReasonForCall, LPVOID)
{
	static CCallHook *gameloopHook;

	if (dwReasonForCall == DLL_PROCESS_ATTACH){

		if (sizeof(CPed) != 1988){
			MessageBox("Incorrect CPed == " + QString::number(sizeof(CPed)), PROJECT_NAME, MB_OK);
			return FALSE;
		}
		if (sizeof(CVehicle) != 2584){
			MessageBox("Incorrect CVehicle == " + QString::number(sizeof(CVehicle)), PROJECT_NAME, MB_OK);
			return FALSE;
		}

		if (GetModuleHandleA((QString(PROJECT_NAME) + ".asi").toStdString().c_str()) != hModule){
			char name[256];
			GetModuleFileNameA(hModule, name, 256);
			MessageBox("Incorrect file name.\n"
					   "Please rename " + QFileInfo(name).fileName() +
					   " to " + QString(PROJECT_NAME) + ".asi",
					   PROJECT_NAME, MB_OK);
			return FALSE;
		}


		gameloopHook = new CCallHook(reinterpret_cast<void*>(0x00748DA3), 6);
		gameloopHook->enable(GameLoop);
	}
	else if (dwReasonForCall == DLL_PROCESS_DETACH){
		delete gameloopHook;
		delete sampShowCursor;
		SetWindowLongA(g_vars.hwnd, GWL_WNDPROC, reinterpret_cast<LONG>(hOrigProc));
		delete ptranslator;
		ptranslator = nullptr;
		delete g_class.SF;
		delete dynamic_cast<proxyIDirect3DDevice9*>(device);
		delete g_class.DirectX;
		SetUnhandledExceptionFilter( hOrigUEF );
	}

	return TRUE;
}

int MessageBox(QString text, QString title, UINT type)
{
	return MessageBoxA(g_vars.hwnd, text.toStdString().c_str(), title.toStdString().c_str(), type);
}
