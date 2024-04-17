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
#include "pch.h"
#include <iostream>
#include "RegisterProcessForComType.h"
#include "TaskFactory.h"
#include "TestTask.h"

// ----------------------------------------------------------------------------
// Usings
// ----------------------------------------------------------------------------
using namespace winrt;

// ----------------------------------------------------------------------------
// Globals
// ----------------------------------------------------------------------------

/// <summary>Auto Reset Event that gets signaled when a background task completes.</summary>
handle g_taskFactoryCompletionEvent{ CreateEvent(nullptr, FALSE, FALSE, nullptr) };

/// <summary>Manual Reset Event that gets signaled when the process should exit.</summary>
handle g_processExitEvent{ CreateEvent(nullptr, TRUE, FALSE, nullptr) };

int main()
{
   hresult hr;
   RegisterProcessForComType<TaskFactory> registerForCom;

   std::cout << "STEP 1: Initialize" << std::endl;
   init_apartment();

   std::cout << "STEP 2: Register COM Class Factory" << std::endl;
   hr = registerForCom.RegisterMultiUse(__uuidof(TestTask));

   return (int)hr;
}
