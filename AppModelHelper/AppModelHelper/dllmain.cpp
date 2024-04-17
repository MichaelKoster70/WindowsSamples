// ----------------------------------------------------------------------------
// <copyright company="Michael Koster">
//   Copyright (c) Michael Koster. All rights reserved.
//   Licensed under the MIT License.
// </copyright>
// ----------------------------------------------------------------------------
// Defines the entry point for the DLL application.
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// Includes
// ----------------------------------------------------------------------------
#include "framework.h"

// ----------------------------------------------------------------------------
// Includes
// ----------------------------------------------------------------------------

/// <summary>
/// Entry point for the DLL application called by the OS.
/// </summary>
/// <param name="hModule">A handle to the DLL module</param>
/// <param name="fdwReason">reason for calling function</param>
/// <param name="lpReserved">reserved</param>
/// <returns>TRUE if initialized successfully, else FALSE.</returns>

BOOL APIENTRY DllMain([[maybe_uused]] HMODULE hModule, DWORD fdwReason, [[maybe_uused]] LPVOID lpReserved)
{
   switch (fdwReason)
   {
   case DLL_PROCESS_ATTACH:
   case DLL_THREAD_ATTACH:
   case DLL_THREAD_DETACH:
   case DLL_PROCESS_DETACH:
      break;
   }
   return TRUE;
}

