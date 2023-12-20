// ----------------------------------------------------------------------------
// <copyright company="Michael Koster">
//   Copyright (c) Michael Koster. All rights reserved.
//   Licensed under the MIT License.
// </copyright>
// ----------------------------------------------------------------------------
#pragma once

// ----------------------------------------------------------------------------
// Declarations
// ----------------------------------------------------------------------------

/// <summary>
/// COM class factory for creating the background task instances.
/// </summary>
struct TaskFactory : implements<TaskFactory, IClassFactory>
{
   HRESULT __stdcall CreateInstance(_In_opt_ IUnknown* aggregateInterface, _In_ REFIID interfaceId, _Outptr_ VOID** object) noexcept final;

   HRESULT __stdcall LockServer(BOOL lock) noexcept final;
};
