#include <windows.h>
#include <shobjidl.h>

#include "pch.h"
//#include "Engine\CPathMgr.h"

inline FILE* BrowserOpen()
{
    HRESULT hr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE);
    FILE* file = nullptr;


    if (SUCCEEDED(hr))
    {
        IFileOpenDialog* pFileOpen;

        // Create the FileOpenDialog object.
        hr = CoCreateInstance(CLSID_FileOpenDialog, NULL, CLSCTX_ALL,
            IID_IFileOpenDialog, reinterpret_cast<void**>(&pFileOpen));

        if (SUCCEEDED(hr))
        {
            // Show the Open dialog box.
            hr = pFileOpen->Show(NULL);

            // Get the file name from the dialog box.
            if (SUCCEEDED(hr))
            {
                IShellItem* pItem;
                hr = pFileOpen->GetResult(&pItem);
                if (SUCCEEDED(hr))
                {
                    PWSTR pszFilePath;
                    hr = pItem->GetDisplayName(SIGDN_FILESYSPATH, &pszFilePath);

                    // Display the file name to the user.
                    if (SUCCEEDED(hr))
                    {
                        MessageBoxW(NULL, pszFilePath, L"\\bin\\content\\obj\\", MB_OK);
                        CoTaskMemFree(pszFilePath);
                        _wfopen_s(&file, pszFilePath, L"rb");
                        pItem->Release();
                        pFileOpen->Release();
                        CoUninitialize();
                        return file;
                    }
                }
            }
        }
    }
    return nullptr;
}