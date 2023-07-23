#define _CRT_SECURE_NO_WARNINGS

#include <windows.h>
#include <stdlib.h>
#include <stdio.h>

#include "../../SDK/cleo_redux_sdk.h"

class DylibPlugin {
public:
	DylibPlugin() {
		Log("Dylib plugin 2.0");

		RegisterCommand("LOAD_DYNAMIC_LIBRARY", LoadDynamicLibrary, "dll");
		RegisterCommand("FREE_DYNAMIC_LIBRARY", FreeDynamicLibrary, "dll");
		RegisterCommand("GET_DYNAMIC_LIBRARY_PROCEDURE", GetDynamicLibraryProcedure, "dll");
	}

	// https://library.sannybuilder.com/#/unknown_x86/dylib/LOAD_DYNAMIC_LIBRARY
	static HandlerResult LoadDynamicLibrary(Context ctx) 
	{
		wchar_t libname[MAX_PATH];
		char buf[STR_MAX_LEN];

		GetStringParam(ctx, buf, sizeof(buf));

		char message[STR_MAX_LEN * 2];
		sprintf(message, "Loading dynamic library %s", buf);
		Log(message);

		// if libname is just a file name then load it as is - subject to DLL search order
		// https://docs.microsoft.com/en-us/windows/win32/dlls/dynamic-link-library-search-order
		if ((strrchr(buf, '/') || strchr(buf, '\\'))) {
			char path[MAX_PATH];

			ResolvePath(buf, path);
			MultiByteToWideChar(CP_UTF8, 0, path, -1, libname, MAX_PATH);
		}
		else {
			MultiByteToWideChar(CP_UTF8, 0, buf, -1, libname, MAX_PATH);
		}
		
		auto libHandle = LoadLibrary(libname);
		SetIntParam(ctx, (isize)libHandle);
		UpdateCompareFlag(ctx, libHandle != nullptr);

		return HandlerResult::CONTINUE;
	}

	// https://library.sannybuilder.com/#/unknown_x86/dylib/FREE_DYNAMIC_LIBRARY
	static HandlerResult FreeDynamicLibrary(Context ctx) 
	{
		FreeLibrary((HMODULE)GetIntParam(ctx));
		return HandlerResult::CONTINUE;
	}

	// https://library.sannybuilder.com/#/unknown_x86/dylib/GET_DYNAMIC_LIBRARY_PROCEDURE
	static HandlerResult GetDynamicLibraryProcedure(Context ctx) 
	{
		char buf[STR_MAX_LEN];

		GetStringParam(ctx, buf, sizeof(buf));
		auto libHandle = GetIntParam(ctx);

		void* funcAddr = (void*)GetProcAddress((HMODULE)libHandle, buf);
		SetIntParam(ctx, (isize)funcAddr);
		UpdateCompareFlag(ctx, funcAddr != nullptr);

		return HandlerResult::CONTINUE;
	}
} DylibPlugin;