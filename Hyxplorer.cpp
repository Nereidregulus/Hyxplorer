#include "Hyxplorer.h"
#include "NodeRegion.h"

#include <windows.h>
#include <shobjidl.h>

Hyxplorer::Hyxplorer()
{
}

Hyxplorer::~Hyxplorer() {}

void Hyxplorer::loadFile() {
    HRESULT hr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED |
        COINIT_DISABLE_OLE1DDE);
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

                    std::wstring ws(pszFilePath);
                    std::string file_path(ws.begin(), ws.end());
                    loadFile(file_path);

                    pItem->Release();
                }
            }
            pFileOpen->Release();
        }
        CoUninitialize();
    }
}

void Hyxplorer::loadFile(std::string file_path) {
    file_opened = true;

    m_region = new NodeRegion(file_path);
}


void Hyxplorer::display()
{
    if (ImGui::BeginMainMenuBar())
    {
        if (ImGui::BeginMenu("File"))
        {
            if (ImGui::MenuItem("Open Region File"))
            {
                loadFile();
            }
            //ImGui::MenuItem("Main menu bar", NULL, &demo_data->ShowMainMenuBar);
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Edit"))
        {
            ImGui::MenuItem("Dummy");
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Search"))
        {
            ImGui::MenuItem("Dummy");
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("About"))
        {
            ImGui::MenuItem("Dummy");
            ImGui::EndMenu();
        }
        ImGui::EndMainMenuBar();
    }


    // Node viewer
    if (file_opened)
    {
        ImGui::Begin("Region Viewer");

        m_region->display();

        ImGui::End();
    }
}