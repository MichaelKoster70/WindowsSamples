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
using namespace winrt;

// ----------------------------------------------------------------------------
// Externals
// ----------------------------------------------------------------------------
extern handle g_taskFactoryCompletionEvent;
extern handle g_processExitEvent;

/// <summary>
/// Utility class responsible for registering the process for COM activation
/// </summary>
template <typename T>
class RegisterProcessForComType
{
public:
   RegisterProcessForComType() = default;
   ~RegisterProcessForComType()
   {
      // Revoke the class factory registration, ignoring any error.
      if (registrationToken != 0)
      {
         (void)CoRevokeClassObject(registrationToken);
      }
   };

   /// <summary>
   /// Register the given class id for single invocation.
   /// </summary>
   /// <param name="classId">The class id to register</param>
   /// <returns>HRESULT indicating success or failure.</returns>
   hresult RegisterSingleUse(guid classId)
   {
      hresult hr;
      try
      {
         // Verify the global handle is correctly constructed.
         check_bool(bool{ g_taskFactoryCompletionEvent });

         com_ptr<IClassFactory> taskFactory = make<T>();
         check_hresult(CoRegisterClassObject(classId, winrt::make<T>().get(), CLSCTX_LOCAL_SERVER, REGCLS_MULTIPLEUSE, &registrationToken));

         check_hresult(WaitForSingleObject(g_taskFactoryCompletionEvent.get(), INFINITE));

         hr = S_OK();
      }
      catch (...)
      {
         hr = to_hresult();
      }

      return hr;
   };

   /// <summary>
   /// Register the given class id for multiple invocations.
   /// </summary>
   /// <param name="classId">The class id to register.</param>
   /// <returns>HRESULT indicating success or failure.</returns>
   hresult RegisterMultiUse(guid classId)
   {
      hresult hr;

      try
      {
         check_bool(bool{ g_processExitEvent });

         com_ptr<IClassFactory> taskFactory = make<T>();
         check_hresult(CoRegisterClassObject(classId, taskFactory.get(), CLSCTX_LOCAL_SERVER, REGCLS_MULTIPLEUSE, &registrationToken));

         check_hresult(WaitForSingleObject(g_processExitEvent.get(), INFINITE));

         hr = S_OK;
      }
      catch (...)
      {
         hr = to_hresult();
      }

      return hr;
   };

private:
   DWORD registrationToken = 0;
};

