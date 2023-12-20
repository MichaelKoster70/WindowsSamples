// ----------------------------------------------------------------------------
// <copyright company="Michael Koster">
//   Copyright (c) Michael Koster. All rights reserved.
//   Licensed under the MIT License.
// </copyright>
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// Includes
// ----------------------------------------------------------------------------
#include "pch.h"
#include "TestTask.h"
#include "winrt/Windows.ApplicationModel.ExtendedExecution.h"
#include <iostream>

using namespace winrt::Windows::ApplicationModel::ExtendedExecution;

// ----------------------------------------------------------------------------
// Externals
// ----------------------------------------------------------------------------
extern handle g_taskFactoryCompletionEvent;

// ----------------------------------------------------------------------------
// Defines
// ----------------------------------------------------------------------------
const unsigned int MaximumPotentialPrime = 1000000000;

// ----------------------------------------------------------------------------
// Implementation
// ----------------------------------------------------------------------------

void __stdcall TestTask::Run(_In_ IBackgroundTaskInstance taskInstance)
{
   std::cout << "TestTask::Run" << std::endl;

   taskInstance.Canceled({ this, &TestTask::OnCanceled });

   taskDeferral = taskInstance.GetDeferral();

   //Enable the extendedBackgroundTaskTime capability
   //auto extendedExecutionSession = ExtendedExecutionSession();
   //extendedExecutionSession.Reason(ExtendedExecutionReason::Unspecified);
   //extendedExecutionSession.Description(L"Sample extended background task");
   //extendedExecutionSession.RequestExtensionAsync().get();

   unsigned int currentPrimeNumber = 1;
   while (!isCanceled && (currentPrimeNumber < MaximumPotentialPrime))
   {
      currentPrimeNumber = GetNextPrime(currentPrimeNumber);
      taskInstance.Progress(currentPrimeNumber);
      std::cout << "TestTask::Run - calculated on prime=" << currentPrimeNumber << std::endl;

   }

   std::cout << "TestTask::Run - completed on prime=" << currentPrimeNumber << std::endl;
   check_bool(SetEvent(g_taskFactoryCompletionEvent.get()));
   taskDeferral.Complete();
}

void  TestTask::OnCanceled(_In_ IBackgroundTaskInstance sender, _In_ BackgroundTaskCancellationReason reason)
{
   std::cout << "TestTask::OnCanceled" << std::endl;
   isCanceled = true;
}

unsigned int TestTask::GetNextPrime(_In_ unsigned int lastPrime)
{
   unsigned int nextPrime = lastPrime;
   unsigned int divisor;
   while (TRUE)
   {
      divisor = nextPrime;
      nextPrime += 1;
      while (divisor != 1)
      {
         if ((nextPrime % divisor) == 0) {
            break;
         }

         divisor -= 1;
      }

      if (divisor == 1)
      {
         break;
      }
   }

   return nextPrime;
}
