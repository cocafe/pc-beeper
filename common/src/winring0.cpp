#include <stdio.h>

#include <Windows.h>

#include <winring0.h>

#define lpWinRing0LoaderTitle L"WinRing0 Loader"

#pragma comment(lib, "../common/lib/WinRing0x64.lib")

int WinRing0_init(void)
{
	if (!InitializeOls()) {
		fprintf_s(stderr, "%s(): failed to load WinRing0 dll and driver\n", __func__);
		return -EFAULT;
	}

	switch (GetDllStatus())
	{
		case OLS_DLL_NO_ERROR:
			break;

		case OLS_DLL_UNSUPPORTED_PLATFORM:
			fprintf_s(stderr, "%s(): DLL Status Error!! UNSUPPORTED_PLATFORM\n", __func__);
			goto dll_deinit;

		case OLS_DLL_DRIVER_NOT_LOADED:
			fprintf_s(stderr, "%s(): DLL Status Error!! DRIVER_NOT_LOADED\n", __func__);
			goto dll_deinit;

		case OLS_DLL_DRIVER_NOT_FOUND:
			fprintf_s(stderr, "%s(): DLL Status Error!! DRIVER_NOT_FOUND\n", __func__);
			goto dll_deinit;

		case OLS_DLL_DRIVER_UNLOADED:
			fprintf_s(stderr, "%s(): DLL Status Error!! DRIVER_UNLOADED\n", __func__);
			goto dll_deinit;

		case OLS_DLL_DRIVER_NOT_LOADED_ON_NETWORK:
			fprintf_s(stderr, "%s(): DLL Status Error!! DRIVER_NOT_LOADED_ON_NETWORK\n", __func__);
			goto dll_deinit;

		case OLS_DLL_UNKNOWN_ERROR:
		default:
			fprintf_s(stderr, "%s(): DLL Status Error!! UNKNOWN_ERROR\n", __func__);
			goto dll_deinit;
	}

	return 0;

dll_deinit:
	DeinitializeOls();

	return -EFAULT;
}

void WinRing0_deinit(void)
{
	DeinitializeOls();
}