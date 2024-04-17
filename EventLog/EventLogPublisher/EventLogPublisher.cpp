// ----------------------------------------------------------------------------
// <copyright company="Michael Koster">
//   Copyright (c) Michael Koster. All rights reserved.
//   Licensed under the MIT License.
// </copyright>
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// Includes
// ----------------------------------------------------------------------------
#include <windows.h>
#include <winevt.h>
#include <evntprov.h>
#include <iostream>
#include "Generated/EventLogPublisher.h"

// ----------------------------------------------------------------------------
// Linker Directives
// ----------------------------------------------------------------------------
#pragma comment(lib, "wevtapi.lib")

// ----------------------------------------------------------------------------
// Function Definitions
// ----------------------------------------------------------------------------
void WriteEventLogApplication();

int main()
{
    WriteEventLogApplication();
    return 0;
}

void WriteEventLogApplication()
{
    HANDLE hEventLog = NULL;
    REGHANDLE hRegHandle = NULL;
    LPCWSTR lpszStrings[2] = {NULL, NULL};

    if (EventRegister(&mko_sample, nullptr, nullptr, &hRegHandle) != ERROR_SUCCESS)
    {
       wprintf(L"EventRegister failed");
       return;
    }

    hEventLog = RegisterEventSource(NULL, L"MyCompany-App");

    if (NULL == hEventLog)
    {
       wprintf(L"RegisterEventSource failed with 0x%x.\n", GetLastError());
       return;
    }

    lpszStrings[0] = L"EventLogPublisher";
    lpszStrings[1] = L"EventLogPublisher is starting.";

    if (!ReportEvent(hEventLog, // Event log handle
       EVENTLOG_INFORMATION_TYPE, // Event type
       0, // Event category
       0, // Event identifier
       NULL, // No security identifier
       2, // Size of lpszStrings array
       0, // No binary data
       lpszStrings, // Array of strings
       NULL)) // No binary data
    {
        wprintf(L"ReportEvent failed with 0x%x.\n", GetLastError());
    }
    else
    {
       wprintf(L"ReportEvent succeeded.\n");
    }

    EVENT_DATA_DESCRIPTOR eventDataDescriptor[2] = {0};

    ULONG result;
    if (EventEnabled(hRegHandle, &EventInfo))
    {
         result = EventWrite(hRegHandle, &EventInfo, 0, nullptr);
    }

    // Error event, no data
    result = EventWrite(hRegHandle, &EventError, 0, nullptr);

    // Warning event, with a single uint32 value
    ULONG value = 42;
    EventDataDescCreate(eventDataDescriptor, &value, sizeof(value));
    result = EventWrite(hRegHandle, &EventErrorWithParam, 1, eventDataDescriptor);

    // Critical event, with 2 parameters, a uin32 and a string
    value = 42;
    EventDataDescCreate(&eventDataDescriptor[0], &value, sizeof(value));
    LPCWSTR message = L"Hello World";
    EventDataDescCreate(&eventDataDescriptor[1], message, ((ULONG)wcslen(message) + 1) * 2);
    result = EventWrite(hRegHandle, &EventErrorTwoParams, 2, eventDataDescriptor);

    DeregisterEventSource(hEventLog);
    EventUnregister(hRegHandle);
}