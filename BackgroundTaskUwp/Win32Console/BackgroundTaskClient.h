// ----------------------------------------------------------------------------
// <copyright company="Michael Koster">
//   Copyright (c) Michael Koster. All rights reserved.
//   Licensed under the MIT License.
// </copyright>
// ----------------------------------------------------------------------------
// This file contains the declaration of the BackgroundTaskClient class.
// ----------------------------------------------------------------------------
#pragma once

// ----------------------------------------------------------------------------
// Include 
// ----------------------------------------------------------------------------
#include <string>
#include "winrt/Windows.ApplicationModel.Background.h"

using namespace winrt::Windows::ApplicationModel::Background;

// ----------------------------------------------------------------------------
// Declaration
// ----------------------------------------------------------------------------

/// <summary>
/// Utility class to register a background tasks
/// </summary>
class BackgroundTaskClient
{
public:
   BackgroundTaskClient() = delete;
   ~BackgroundTaskClient() = delete;

   /// <summary>
   /// Registers a background task
   /// </summary>
   /// <param name="taskName">The task name.</param>
   /// <param name="taskEntryPoint">The UWP entry point</param>
   /// <param name="trigger"></param>
   static void Register(std::wstring taskName, std::wstring taskEntryPoint, IBackgroundTrigger trigger);

private:
   /// <summary>
   /// Returns a value indicating whether the task is registered.
   /// </summary>
   /// <param name="taskName">The task name.</param>
   /// <returns>true if registered, else false.</returns>
   static bool IsTaskRegistered(std::wstring taskName);
};
