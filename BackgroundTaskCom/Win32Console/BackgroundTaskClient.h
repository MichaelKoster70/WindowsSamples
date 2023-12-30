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

using namespace winrt;
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
   /// Registers a COM based background task
   /// </summary>
   /// <param name="taskName">The task name.</param>
   /// <param name="classId">The COM class ID</param>
   /// <param name="trigger">The task trigger</param>
   static IBackgroundTaskRegistration Register(std::wstring taskName, guid classId, IBackgroundTrigger trigger);

private:
   /// <summary>
   /// Returns a value indicating whether the task is registered.
   /// </summary>
   /// <param name="taskName">The task name.</param>
   /// <returns>true if registered, else false.</returns>
   static bool IsTaskRegistered(std::wstring taskName);
};
