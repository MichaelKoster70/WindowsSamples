// ----------------------------------------------------------------------------
// <copyright company="Michael Koster">
//   Copyright (c) Michael Koster. All rights reserved.
//   Licensed under the MIT License.
// </copyright>
// ----------------------------------------------------------------------------
// This sample demonstrates how to register a COM based background task
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// Includes
// ----------------------------------------------------------------------------
#include <iostream>
#include <string>
#include <filesystem>
#include <windows.h>
#include "BackgroundTaskClient.h"
#include "winrt/Windows.ApplicationModel.Background.h"
#include "winrt/Windows.Foundation.h"
#include "winrt/windows.foundation.collections.h"
#include "./../ComBackgroundTask/TestTask.h"
#include "ExecutionMode.h"
#include "MsixPackageHelper.h"

// ----------------------------------------------------------------------------
// Usings
// ----------------------------------------------------------------------------
using namespace winrt::Windows::ApplicationModel::Background;

// ----------------------------------------------------------------------------
// Implementations
// ----------------------------------------------------------------------------

/// <summary>
/// The application entry point
/// </summary>
/// <returns>always 0</returns>
int main()
{
   // if we are not running with identity, then we need to register the sparse package
   if (!ExecutionMode::IsRunningWithIdentity())
   {
      auto exePath = std::wstring(MAX_PATH, L'\0');
      std::wstring externalLocation;
      std::wstring sparsePkgPath = L"Win32ConsoleSparsePackage.msix";
      const std::wstring sparseAppxPackage(L"Win32ConsoleCom-Sparse_1.0.0.0_x64__sgy29b93sak7e");
      if (GetModuleFileName(nullptr, exePath.data(), (DWORD)exePath.size()) == 0)
      {
         std::cout << "Failed to get module file name\n";
         return 1;
      }

      {
         std::filesystem::path exePathPath(exePath);
         exePathPath.remove_filename();
         externalLocation = exePathPath.wstring();
         exePathPath.append(sparsePkgPath);
         sparsePkgPath = exePathPath.wstring();
      }

      std::cout << "STEP 0: Install sparse package\n";
      auto registered = MsixPackageHelper::RegisterSparsePackage(externalLocation, sparsePkgPath);
      if (registered)
      {
         std::cout << "Sparse package registered - relaunching\n";
         STARTUPINFO si = {  };
         PROCESS_INFORMATION pi = {  };
         si.cb = sizeof(si);
         if (CreateProcess(exePath.c_str(), nullptr, nullptr, nullptr, FALSE, 0, nullptr, nullptr, &si, &pi))
         {
            CloseHandle(pi.hProcess);
            CloseHandle(pi.hThread);
            return 0;
         }
      }
      else
      {
         std::cout << "Failed to register sparse package\n";
         return 1;
      }
   }

   std::cout << "STEP 1: Initialize\n";
   winrt::init_apartment();

   std::cout << "STEP 2: Request Background Access\n";
   BackgroundExecutionManager::RemoveAccess();
   auto asyncOperation = BackgroundExecutionManager::RequestAccessAsync();
   auto access = asyncOperation.get();

   if (access == BackgroundAccessStatus::AllowedMayUseActiveRealTimeConnectivity ||
      access == BackgroundAccessStatus::AllowedWithAlwaysOnRealTimeConnectivity ||
      access == BackgroundAccessStatus::AlwaysAllowed ||
      access == BackgroundAccessStatus::AllowedSubjectToSystemPolicy)
   {
      std::cout << "Background access granted\n";

      std::cout << "STEP 3: Register Background Task\n";
      auto registration = BackgroundTaskClient::Register(L"TimeBackgroundTaskCom", _uuidof(TestTask), TimeTrigger(15, false));
      registration.Completed([](auto&&, auto&&)
      {
         std::cout << "Background task completed\n";
      });

      registration.Progress([](auto&&, BackgroundTaskProgressEventArgs args)
      {
         std::cout << "Background task progress =" << args.Progress() << std::endl;
      });

      // Application triggers are not supported in Win32 apps
   }
   else
   {
      std::cout << "Background access denied\n";
   }

   // wait for a keypress to exit
   std::cout << "Press any key to exit\n";
   (void)getchar();

   return 0;
}

