// ----------------------------------------------------------------------------
// <copyright company="Michael Koster">
//   Copyright (c) Michael Koster. All rights reserved.
//   Licensed under the MIT License.
// </copyright>
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// Includes
// ----------------------------------------------------------------------------
#include "BackgroundTaskClient.h"
#include <winrt/windows.foundation.collections.h>
#include <iostream>

// ----------------------------------------------------------------------------
// Implementation
// ----------------------------------------------------------------------------

/// <summary>
/// Registers a background task
/// </summary>
/// <param name="taskName">The task name.</param>
/// <param name="taskEntryPoint">The UWP entry point</param>
/// <param name="trigger"></param>
IBackgroundTaskRegistration BackgroundTaskClient::Register(std::wstring taskName, guid classId, IBackgroundTrigger trigger)
{
   // Check if the task is already registered.
   if (IsTaskRegistered(taskName))
   {
      return nullptr;
   }

   // Register the background task with name and trigger.
   auto builder = BackgroundTaskBuilder();
   builder.Name(taskName);
   builder.SetTrigger(trigger);
   builder.SetTaskEntryPointClsid(classId);

   builder.AddCondition(SystemCondition(SystemConditionType::InternetAvailable));
   builder.AddCondition(SystemCondition(SystemConditionType::UserPresent));

   auto registration = builder.Register();

   return registration;
}

/// <summary>
/// Returns a value indicating whether the task is registered.
/// </summary>
/// <param name="taskName">The task name.</param>
/// <returns>true if registered, else false.</returns>
bool BackgroundTaskClient::IsTaskRegistered(std::wstring taskName)
{
   // Iterate over all background tasks and check if the task is already registered.
   auto registeredTasks = BackgroundTaskRegistration::AllTasks();
   for (auto cur = registeredTasks.begin(); cur != registeredTasks.end(); cur++)
   {
      if (cur.Current().Value().Name() == taskName)
      {
         cur.Current().Value().Unregister(true);
         //return true;
      }
   }
   return false;
}
