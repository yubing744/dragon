#include <dragon.h>

BOOL APIENTRY DllMain(HANDLE hModule,DWORD dwReason,LPVOID lpReserved) {

	if (dwReason == DLL_PROCESS_ATTACH) {
		if(LM::GetInstance()->getLibrary(L"dragon_osgi") == (P<Library>)null) {
			P<Library> syslib=new DllLibrary((HMODULE)hModule);
			LM::GetInstance()->registLibrary(L"dragon_osgi",syslib);
		}
	}

	return TRUE;
}
