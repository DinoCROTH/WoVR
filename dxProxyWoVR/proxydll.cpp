#include "proxydll.h"
#include "game_extras.h"

cIDirect3DDevice9* glIDirect3DDevice9;
cIDirect3DDevice9Ex* glIDirect3DDevice9Ex;
cIDirect3D9* glIDirect3D9;
HINSTANCE glOriginalDll;
HINSTANCE glThisInstance;

std::ofstream ofOut;
std::stringstream logError;
bool doLog = false;
bool detoursInitialized = false;

bool HasErrors()
{
	return (logError.str().length() > 0);
}

std::string GetErrors()
{
	std::string curLog = logError.str();
	logError.str("");
	return curLog;
}

void PrintErrors()
{
	if (HasErrors()) {
		ofOut << GetErrors();
		ofOut.flush();
	}
}

void LoadOriginalDll(void)
{
	if (glOriginalDll) return;
	char buffer[MAX_PATH];
	GetSystemDirectory(buffer, MAX_PATH);
	strcat_s(buffer, MAX_PATH, "\\d3d9.dll");

	if (!glOriginalDll) glOriginalDll = LoadLibrary(buffer);
	if (!glOriginalDll) {
		ExitProcess(0);
	}

	return;
}

void InitInstance(HANDLE hModule)
{
	glThisInstance = (HINSTANCE)hModule;
	glOriginalDll = NULL;
	glIDirect3D9 = NULL;
	glIDirect3DDevice9 = NULL;
	glIDirect3DDevice9Ex = NULL;
	detoursInitialized = false;

	char dllPath[MAX_PATH];
	GetModuleFileNameA((HMODULE)hModule, dllPath, MAX_PATH);
	std::string dllDir = std::string(dllPath);
	dllDir = dllDir.substr(0, dllDir.find_last_of("\\/") + 1);
	std::string logPath = dllDir + "vr\\output.txt";

	ofOut.open(logPath.c_str(), std::ios::out);
	ofOut.precision(5);
}

void ExitInstance()
{
	ExitDetours();
	if (glOriginalDll)
	{
		FreeLibrary(glOriginalDll);
		glOriginalDll = NULL;
	}
	PrintErrors();
	ofOut.close();
	return;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH: InitInstance(hModule); break;
	case DLL_PROCESS_DETACH: ExitInstance(); break;
	case DLL_THREAD_ATTACH:  break;
	case DLL_THREAD_DETACH:  break;
	}
	return TRUE;
}


void EnsureOriginalDll()
{
	if (!glOriginalDll) {
		LoadOriginalDll();
	}
}

int WINAPI D3DPERF_BeginEvent(D3DCOLOR col, LPCWSTR wszName)
{
	EnsureOriginalDll();
	if (!glOriginalDll) return 0;
	typedef int (WINAPI* D3D9_Type)(D3DCOLOR col, LPCWSTR wszName);
	D3D9_Type D3D9_fn = (D3D9_Type)GetProcAddress(glOriginalDll, "D3DPERF_BeginEvent");
	return D3D9_fn ? D3D9_fn(col, wszName) : 0;
}

int WINAPI D3DPERF_EndEvent(void)
{
	EnsureOriginalDll();
	if (!glOriginalDll) return 0;
	typedef int (WINAPI* D3D9_Type)();
	D3D9_Type D3D9_fn = (D3D9_Type)GetProcAddress(glOriginalDll, "D3DPERF_EndEvent");
	return D3D9_fn ? D3D9_fn() : 0;
}

DWORD WINAPI D3DPERF_GetStatus(void)
{
	EnsureOriginalDll();
	if (!glOriginalDll) return 0;
	typedef DWORD(WINAPI* D3D9_Type)();
	D3D9_Type D3D9_fn = (D3D9_Type)GetProcAddress(glOriginalDll, "D3DPERF_GetStatus");
	return D3D9_fn ? D3D9_fn() : 0;
}

BOOL WINAPI D3DPERF_QueryRepeatFrame(void)
{
	EnsureOriginalDll();
	if (!glOriginalDll) return FALSE;
	typedef BOOL(WINAPI* D3D9_Type)();
	D3D9_Type D3D9_fn = (D3D9_Type)GetProcAddress(glOriginalDll, "D3DPERF_QueryRepeatFrame");
	return D3D9_fn ? D3D9_fn() : FALSE;
}

void WINAPI D3DPERF_SetMarker(D3DCOLOR col, LPCWSTR wszName)
{
	EnsureOriginalDll();
	if (!glOriginalDll) return;
	typedef void (WINAPI* D3D9_Type)(D3DCOLOR col, LPCWSTR wszName);
	D3D9_Type D3D9_fn = (D3D9_Type)GetProcAddress(glOriginalDll, "D3DPERF_SetMarker");
	if (D3D9_fn) D3D9_fn(col, wszName);
}

void WINAPI D3DPERF_SetOptions(DWORD dwOptions)
{
	EnsureOriginalDll();
	if (!glOriginalDll) return;
	typedef void (WINAPI* D3D9_Type)(DWORD dwOptions);
	D3D9_Type D3D9_fn = (D3D9_Type)GetProcAddress(glOriginalDll, "D3DPERF_SetOptions");
	if (D3D9_fn) D3D9_fn(dwOptions);
}

void WINAPI D3DPERF_SetRegion(D3DCOLOR col, LPCWSTR wszName)
{
	EnsureOriginalDll();
	if (!glOriginalDll) return;
	typedef void (WINAPI* D3D9_Type)(D3DCOLOR col, LPCWSTR wszName);
	D3D9_Type D3D9_fn = (D3D9_Type)GetProcAddress(glOriginalDll, "D3DPERF_SetRegion");
	if (D3D9_fn) D3D9_fn(col, wszName);
}

IDirect3D9* WINAPI Direct3DCreate9(UINT SDKVersion)
{
	if (doLog) logError << "Direct3DCreate9 called" << std::endl;
	PrintErrors();

	if (!detoursInitialized) {
		detoursInitialized = true;
		LoadOriginalDll();
		InitDetours(glThisInstance);
	}

	typedef HRESULT(WINAPI* D3D9_Type)(UINT SDKVersion, IDirect3D9Ex**);
	D3D9_Type D3D9_fn = (D3D9_Type)GetProcAddress(glOriginalDll, "Direct3DCreate9Ex");

	if (!D3D9_fn) {
		ExitProcess(0);
	}

	IDirect3D9Ex* pIDirect3D9Ex_orig = nullptr;
	HRESULT result = D3D9_fn(SDKVersion, &pIDirect3D9Ex_orig);
	glIDirect3D9 = new cIDirect3D9(pIDirect3D9Ex_orig, doLog, &logError);
	PrintErrors();
	return glIDirect3D9;
}

HRESULT WINAPI Direct3DCreate9Ex(UINT SDKVersion, IDirect3D9Ex** pIDirect3D9Ex_orig)
{
	if (doLog) logError << "Direct3DCreate9Ex called" << std::endl;
	PrintErrors();

	if (!detoursInitialized) {
		detoursInitialized = true;
		LoadOriginalDll();
		InitDetours(glThisInstance);
	}

	typedef HRESULT(WINAPI* D3D9_Type)(UINT SDKVersion, IDirect3D9Ex**);
	D3D9_Type D3D9_fn = (D3D9_Type)GetProcAddress(glOriginalDll, "Direct3DCreate9Ex");

	if (!D3D9_fn) {
		ExitProcess(0);
	}

	HRESULT result = D3D9_fn(SDKVersion, pIDirect3D9Ex_orig);
	glIDirect3D9 = new cIDirect3D9(*pIDirect3D9Ex_orig, doLog, &logError);
	*pIDirect3D9Ex_orig = glIDirect3D9;
	PrintErrors();
	return result;
}

void WINAPI Direct3DShaderValidatorCreate9()
{
	typedef void (WINAPI* D3D9_Type)();
	D3D9_Type D3D9_fn = (D3D9_Type)GetProcAddress(glOriginalDll, "Direct3DShaderValidatorCreate9");
	D3D9_fn();
}