#define _CRT_SECURE_NO_WARNINGS

#include <windows.h>
#include <stdlib.h>
#include <stdio.h>

#include "../SDK/cleo_redux_sdk.h"

class IniFilesPlugin {
public:
	IniFilesPlugin() {
		Log("IniFiles plugin 1.1");
		RegisterCommand("READ_INT_FROM_INI_FILE", IniFileReadInt, "fs");
		RegisterCommand("WRITE_INT_TO_INI_FILE", IniFileWriteInt, "fs");
		RegisterCommand("READ_FLOAT_FROM_INI_FILE", IniFileReadFloat, "fs");
		RegisterCommand("WRITE_FLOAT_TO_INI_FILE", IniFileWriteFloat, "fs");
		RegisterCommand("READ_STRING_FROM_INI_FILE", IniFileReadString, "fs");
		RegisterCommand("WRITE_STRING_TO_INI_FILE", IniFileWriteString, "fs");
	}

	static HandlerResult IniFileReadInt(Context ctx)
		/****************************************************************
		Opcode Format
		0AF0=4,%4d% = get_int_from_ini_file %1s% section %2s% key %3s%
		****************************************************************/
	{
		wchar_t iniPath[STR_MAX_LEN];
		wchar_t sectionName[STR_MAX_LEN];
		wchar_t key[STR_MAX_LEN];

		GetPath(ctx, iniPath);
		GetString(ctx, sectionName);
		GetString(ctx, key);

		int result = GetPrivateProfileInt(sectionName, key, 0x80000000, iniPath);
		SetIntParam(ctx, result);

		UpdateCompareFlag(ctx, result != 0x80000000);
		return HandlerResult::CONTINUE;
	}

	static HandlerResult IniFileWriteInt(Context ctx)
		/****************************************************************
		Opcode Format
		0AF1=4,write_int %1d% to_ini_file %2s% section %3s% key %4s%
		****************************************************************/
	{
		wchar_t iniPath[STR_MAX_LEN];
		wchar_t sectionName[STR_MAX_LEN];
		wchar_t key[STR_MAX_LEN];
		wchar_t strValue[STR_MAX_LEN];

		GetIntAsString(ctx, strValue);
		GetPath(ctx, iniPath);
		GetString(ctx, sectionName);
		GetString(ctx, key);

		BOOL result = WriteStringToIni(iniPath, sectionName, key, strValue);

		UpdateCompareFlag(ctx, result != 0);
		return HandlerResult::CONTINUE;
	}

	static HandlerResult IniFileReadFloat(Context ctx)
		/****************************************************************
		Opcode Format
		0AF2=4,%4d% = get_float_from_ini_file %1s% section %2s% key %3s%
		****************************************************************/
	{
		wchar_t iniPath[STR_MAX_LEN];
		wchar_t sectionName[STR_MAX_LEN];
		wchar_t key[STR_MAX_LEN];
		wchar_t strValue[STR_MAX_LEN];

		GetPath(ctx, iniPath);
		GetString(ctx, sectionName);
		GetString(ctx, key);

		BOOL result = ReadStringFromIni(iniPath, sectionName, key, strValue);

		if (result)
		{
			float value = (float)wcstof(strValue, NULL);
			SetFloatParam(ctx, value);
		}
		else
		{
			SetFloatParam(ctx, 0.0f);
		}

		UpdateCompareFlag(ctx, result != 0);
		return HandlerResult::CONTINUE;
	}

	static HandlerResult IniFileWriteFloat(Context ctx)
		/****************************************************************
		Opcode Format
		0AF3=4,write_float %1d% to_ini_file %2s% section %3s% key %4s%
		****************************************************************/
	{
		wchar_t iniPath[STR_MAX_LEN];
		wchar_t sectionName[STR_MAX_LEN];
		wchar_t key[STR_MAX_LEN];
		wchar_t strValue[STR_MAX_LEN];

		GetFloatAsString(ctx, strValue);
		GetPath(ctx, iniPath);
		GetString(ctx, sectionName);
		GetString(ctx, key);

		BOOL result = WriteStringToIni(iniPath, sectionName, key, strValue);

		UpdateCompareFlag(ctx, result != 0);
		return HandlerResult::CONTINUE;
	}

	static HandlerResult IniFileReadString(Context ctx)
		/****************************************************************
		Opcode Format
		0AF4=4,%4d% = read_string_from_ini_file %1s% section %2s% key %3s%
		****************************************************************/
	{
		wchar_t iniPath[STR_MAX_LEN];
		wchar_t sectionName[STR_MAX_LEN];
		wchar_t key[STR_MAX_LEN];
		wchar_t strValue[STR_MAX_LEN];

		GetPath(ctx, iniPath);
		GetString(ctx, sectionName);
		GetString(ctx, key);

		BOOL result = ReadStringFromIni(iniPath, sectionName, key, strValue);
		
		char res[STR_MAX_LEN];
		wtoa(strValue, res);

		SetStringParam(ctx, res);
		UpdateCompareFlag(ctx, result != 0);
		return HandlerResult::CONTINUE;
	}

	static HandlerResult IniFileWriteString(Context ctx)
		/****************************************************************
		Opcode Format
		0AF5=4,write_string %1s% to_ini_file %2s% section %3s% key %4s%
		****************************************************************/
	{
		wchar_t iniPath[STR_MAX_LEN];
		wchar_t sectionName[STR_MAX_LEN];
		wchar_t key[STR_MAX_LEN];
		wchar_t strValue[STR_MAX_LEN];

		GetString(ctx, strValue);
		GetPath(ctx, iniPath);
		GetString(ctx, sectionName);
		GetString(ctx, key);

		BOOL result = WriteStringToIni(iniPath, sectionName, key, strValue);

		UpdateCompareFlag(ctx, result != 0);
		return HandlerResult::CONTINUE;
	}

	static void GetIntAsString(Context ctx, wchar_t* res) {
		char buf[STR_MAX_LEN];
		_itoa(GetIntParam(ctx), buf, 10);
		MultiByteToWideChar(CP_UTF8, 0, buf, -1, res, STR_MAX_LEN);
	}

	static void GetFloatAsString(Context ctx, wchar_t* res) {
		swprintf(res, STR_MAX_LEN, L"%g", GetFloatParam(ctx));
	}

	static void GetString(Context ctx, wchar_t* res) {
		char buf[STR_MAX_LEN];
		GetStringParam(ctx, buf, sizeof(buf));
		MultiByteToWideChar(CP_UTF8, 0, buf, -1, res, STR_MAX_LEN);
	}

	static void GetPath(Context ctx, wchar_t* res) {
		char buf[STR_MAX_LEN];
		char path[STR_MAX_LEN];
		GetStringParam(ctx, buf, sizeof(buf));
		ResolvePath(buf, path);
		MultiByteToWideChar(CP_UTF8, 0, path, -1, res, STR_MAX_LEN);
	}

	static BOOL ReadStringFromIni(wchar_t* iniPath, wchar_t* sectionName, wchar_t* key, wchar_t* strValue) {
		return GetPrivateProfileString(sectionName, key, NULL, strValue, STR_MAX_LEN, iniPath);
	}

	static BOOL WriteStringToIni(wchar_t* iniPath, wchar_t* sectionName, wchar_t* key, wchar_t* strValue) {
		return WritePrivateProfileString(sectionName, key, strValue, iniPath);
	}

	static void wtoa(wchar_t* in, char* out) {
		WideCharToMultiByte(CP_UTF8, 0, in, -1, out, STR_MAX_LEN, NULL, NULL);
	}

} IniFilePlugin;
