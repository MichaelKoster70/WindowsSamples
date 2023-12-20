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
#include "winrt/Windows.ApplicationModel.Background.h"
#include "TaskFactory.h"
#include "TestTask.h"

// ----------------------------------------------------------------------------
// Implementation
// ----------------------------------------------------------------------------

HRESULT __stdcall TaskFactory::CreateInstance(_In_opt_ IUnknown* aggregateInterface, _In_ REFIID interfaceId, _Outptr_ VOID** object) noexcept
{
   if (aggregateInterface != NULL)
   {
      return CLASS_E_NOAGGREGATION;
   }

   return make<TestTask>().as(interfaceId, object);
}

HRESULT __stdcall TaskFactory::LockServer(BOOL lock) noexcept
{
   UNREFERENCED_PARAMETER(lock);
   return S_OK;
}