// ----------------------------------------------------------------------------
// <copyright company="Michael Koster">
//   Copyright (c) Michael Koster. All rights reserved.
//   Licensed under the MIT License.
// </copyright>
// ----------------------------------------------------------------------------
// This sample demonstrates how to register a background task
// for a UWP application using C++/WinRT.
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// Includes
// ----------------------------------------------------------------------------
#include <iostream>
#include <windows.h>
#include "BackgroundTaskClient.h"
#include <winrt/Windows.ApplicationModel.Background.h>
#include <winrt/Windows.Foundation.h>
#include <winrt/windows.foundation.collections.h>

using namespace winrt::Windows::ApplicationModel::Background;

/// <summary>
/// The application entry point
/// </summary>
/// <returns>always 0</returns>
int main()
{
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
      BackgroundTaskClient::Register (L"TimeBackgroundTask", L"UwpBackgroundTask.TestBackgroundTask", TimeTrigger(15, false));
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

