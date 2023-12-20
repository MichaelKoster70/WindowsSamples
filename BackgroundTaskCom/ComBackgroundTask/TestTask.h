// ----------------------------------------------------------------------------
// <copyright company="Michael Koster">
//   Copyright (c) Michael Koster. All rights reserved.
//   Licensed under the MIT License.
// </copyright>
// ----------------------------------------------------------------------------
#pragma once

// ----------------------------------------------------------------------------
// Usings
// ----------------------------------------------------------------------------
using namespace winrt::Windows::ApplicationModel::Background;

// ----------------------------------------------------------------------------
// Defines
// ----------------------------------------------------------------------------

// GUID for the background task class
#define CLSID_TestTask "B2BCEBC2-8ED5-44B3-8866-AF29A6EC258F"

// ----------------------------------------------------------------------------
// Declarations
// ----------------------------------------------------------------------------

/// <summary>
/// Class providing the COM interface for the background task.
/// </summary>
struct __declspec(uuid(CLSID_TestTask))
   TestTask : implements<TestTask, IBackgroundTask>
{
   /// <summary>
   ///  Performs the work of a background task. The system calls this method when the associated background task has been triggered.)
   /// 
   /// </summary>
   /// <param name="taskInstance">An interface to an instance of the background task. The system creates this instance when the task has been triggered to run.</param>
   void __stdcall Run(_In_ IBackgroundTaskInstance taskInstance);

   /// <summary>
   /// Handles the cancellation of a background task.
   /// </summary>
   /// <param name="sender">The background task instance that was cancelled.</param>
   /// <param name="">The reason the background task instance was cancelled.</param>
   void __stdcall OnCanceled(_In_ IBackgroundTaskInstance sender, _In_ BackgroundTaskCancellationReason reason);

private:
   unsigned int GetNextPrime(_In_ unsigned int lastPrime);

   BackgroundTaskDeferral taskDeferral = nullptr;
   volatile bool isCanceled = false;
};