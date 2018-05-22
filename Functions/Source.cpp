#include <Shlobj.h>
#include <Windows.h>
#include <iostream>
#include <string.h>
#include <tchar.h>

using namespace std;

HRESULT GetKnownFolderName(int csidl, PWSTR* dispayName)
{
	PIDLIST_ABSOLUTE pidList;

	HRESULT hr = SHGetFolderLocation(0, csidl, 0, 0, &pidList);

	if (S_OK == hr)
	{
		IShellItem* item;

		hr = SHCreateItemFromIDList(pidList, IID_PPV_ARGS(&item));

		ILFree(pidList);

		if (S_OK == hr)
		{
			hr = item->GetDisplayName(SIGDN_NORMALDISPLAY, dispayName);
			item->Release();
		}
	}

	return hr;
}

PWSTR GetComputerWCharFolderName()
{
	PWSTR szName = new wchar_t[20];
	if (0 <= CoInitialize(0))
	{
		// CSIDL_DRIVES - "My Computer"
		GetKnownFolderName(CSIDL_DRIVES, &szName);
		CoUninitialize();
	}
	return szName;
}

extern "C"
__declspec(dllexport)
wchar_t* GetLiteral()
{
	return new wchar_t[10]{ L"Hello" };
}


extern "C"
__declspec(dllexport)
wchar_t* GetComputerFolderName1()
{
	return GetComputerWCharFolderName();

}

extern "C"
__declspec(dllexport)
char* GetComputerFolderName2()
{
	return new char[10]{ "Hello" };
}

extern "C"
__declspec(dllexport)
char* GetComputerFolderName3()
{
	wchar_t* wcharName = GetComputerWCharFolderName();

	int capacity = WideCharToMultiByte(CP_ACP, 0U, wcharName, -1, nullptr, 0, nullptr, nullptr);
	int length = capacity - 1;

	char* name = (char*)::CoTaskMemAlloc(capacity);

	WideCharToMultiByte(CP_ACP, 0U, wcharName, -1, name, capacity, nullptr, nullptr);
	return name;
}


extern "C"
__declspec(dllexport)
void __stdcall GetString(char* buffer, size_t bufferSize)
{
	wchar_t* wcharName = GetComputerWCharFolderName();

	int capacity = WideCharToMultiByte(CP_ACP, 0U, wcharName, -1, nullptr, 0, nullptr, nullptr);
	int length = capacity - 1;

	char* name = (char*)::CoTaskMemAlloc(capacity);

	WideCharToMultiByte(CP_ACP, 0U, wcharName, -1, name, capacity, nullptr, nullptr);

	strcpy_s(buffer, bufferSize, name); // entry is a char * that has allocated 250 chars
}