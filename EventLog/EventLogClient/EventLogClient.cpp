#include <windows.h>
#include <winevt.h>
#include <iostream>

#pragma comment(lib, "wevtapi.lib")

#define ARRAY_SIZE 10

int main()
{
    std::cout << "Hello World!\n";

    // write code to read the event log Application log
    // and print the event log entries to the console

    //constexpr auto szQuery = 
    //   L"<QueryList>" \
    //   L"  <Query Path = \"Application\" >" \
    //   L"    <Select Path = \"Application\">*[System[Provider[@Name = 'Application Error']]]"\
    //   L" </Select>" \
    //   L"</Query>" \
    //   L"</QueryList>";

    constexpr auto szQuery =
    L"<QueryList>" \
    L"   <Query Path = \"Microsoft-Windows-AAD/Operational\">" \
    L"   <Select Path = \"Microsoft-Windows-AAD/Operational\">*</Select>" \
    L"   </Query>" \
    L"</QueryList>";

    //auto hEventLogResults = EvtQuery(nullptr, L"Application", szQuery, EvtQueryChannelPath);
    auto hEventLogResults = EvtQuery(nullptr, L"Microsoft-Windows-AAD/Operational", szQuery, EvtQueryChannelPath);
    if (hEventLogResults == nullptr)
    {
         std::cout << "EvtQuery failed with " << GetLastError() << "\n";
         return 1;
      }

    EVT_HANDLE hEvents[ARRAY_SIZE];
    DWORD dwReturned = 0;

#if false
    auto hContext = EvtCreateRenderContext(0, NULL, EvtRenderContextSystem);
    if (NULL == hContext)
    {
       return -2;
    }
#endif

    while (true)
    {
       if (!EvtNext(hEventLogResults, ARRAY_SIZE, hEvents, INFINITE, 0, &dwReturned))
       {
          auto error = GetLastError();
          if (error == ERROR_NO_MORE_ITEMS)
          {
             break;
          }
          else
          {
             std::cout << "EvtNext failed with " << error << "\n";
             return 1;
          }
       }

       for (DWORD i = 0; i < dwReturned; i++)
       {
          DWORD dwBufferUsed = 0;
          DWORD dwPropertyCount = 0;

          // Render XML
          auto hEvent = hEvents[i];
          auto success = EvtRender(nullptr, hEvent, EvtRenderEventXml, 0, nullptr, &dwBufferUsed, &dwPropertyCount);
          if (!success)
          {
             auto error = GetLastError();
             if (error == ERROR_INSUFFICIENT_BUFFER)
             {
                DWORD dwBufferSize = 0;

                // alllocate memory for the buffer, size is in dwBufferUsed
                dwBufferSize = dwBufferUsed;

                BYTE* pRenderingBuffer = new BYTE[dwBufferSize];

                success = EvtRender(nullptr, hEvent, EvtRenderEventXml, dwBufferSize, pRenderingBuffer, &dwBufferUsed, &dwPropertyCount);
                if (!success)
                {
                   std::cout << "EvtRender failed with " << GetLastError() << "\n";
                   return 1;
                }

                std::wcout << pRenderingBuffer << std::endl << (LPWSTR)pRenderingBuffer << std::endl;
             }
             else
             {
                std::cout << "EvtRender failed with " << error << "\n";
                return 1;
             }
          }

          auto publisher = EvtOpenPublisherMetadata(nullptr, L"Microsoft-Windows-AAD", nullptr, 0, 0);
          if (publisher != nullptr)
          {
             // Render the message
             success = EvtFormatMessage(publisher, hEvent, 0, 0, nullptr, EvtFormatMessageEvent, 0, nullptr, &dwBufferUsed);
             if (!success)
             {
                auto error = GetLastError();
                if (error == ERROR_INSUFFICIENT_BUFFER)
                {
                   DWORD dwBufferSize = 0;

                   // alllocate memory for the buffer, size is in dwBufferUsed
                   dwBufferSize = dwBufferUsed;

                   std::wstring messageString(dwBufferSize, L'\0');

                   success = EvtFormatMessage(publisher, hEvent, 0, 0, nullptr, EvtFormatMessageEvent, dwBufferSize, (LPWSTR)messageString.data(), &dwBufferUsed);
                   if (!success)
                   {
                      std::cout << "EvtFormatMessage failed with " << GetLastError() << "\n";
                      return 1;
                   }

                   std::wcout << messageString << std::endl;
                }
                else
                {
                   std::cout << "EvtFormatMessage failed with " << error << "\n";
                   return 1;
                }
             }
          }
          else
          {
             std::cout << "EvtOpenPublisherMetadata failed with " << GetLastError() << "\n";
             return 1;
          }




#if false
          // Render the system properties and user data properties.

          auto success = EvtRender(hContext, hEvent, EvtRenderEventValues, 0, nullptr, &dwBufferUsed, &dwPropertyCount);
          if (!success)
          {
             auto error = GetLastError();
             if (error == ERROR_INSUFFICIENT_BUFFER)
             {
                DWORD dwBufferSize = 0;

                // alllocate memory for the buffer, size is in dwBufferUsed
                dwBufferSize = dwBufferUsed;

                BYTE* pRenderingBuffer = new BYTE[dwBufferSize];

                success = EvtRender(hContext, hEvent, EvtRenderEventValues, dwBufferSize, pRenderingBuffer, &dwBufferUsed, &dwPropertyCount);
                if (!success)
                {
                   std::cout << "EvtRender failed with " << GetLastError() << "\n";
                   return 1;
                }

                EVT_VARIANT* pEvtVariant = (EVT_VARIANT*)pRenderingBuffer;
                for (DWORD j = 0; j < dwPropertyCount; j++)
                {
                   if (pEvtVariant[j].Type == EvtVarTypeString)
                   {
                      std::wcout << pEvtVariant[j].StringVal << std::endl;
                   }
                   else if (pEvtVariant[j].Type == EvtVarTypeAnsiString)
                   {
                      std::cout << pEvtVariant[j].AnsiStringVal << std::endl;
                   }
                   else if (pEvtVariant[j].Type == EvtVarTypeSByte)
                   {
                      std::wcerr << pEvtVariant[j].SByteVal << std::endl;
                   }
                   else if (pEvtVariant[j].Type == EvtVarTypeByte)
                   {
                      std::wcerr << pEvtVariant[j].ByteVal << std::endl;
                   }
                   else if (pEvtVariant[j].Type == EvtVarTypeInt16)
                   {
                      std::wcout << pEvtVariant[j].Int16Val << std::endl;
                   }
                   else if (pEvtVariant[j].Type == EvtVarTypeUInt16)
                   {
                      std::wcout << pEvtVariant[j].UInt16Val << std::endl;
                   }
                   else if (pEvtVariant[j].Type == EvtVarTypeInt32)
                   {
                      std::wcout << pEvtVariant[j].Int32Val << std::endl;
                   }
                   else if (pEvtVariant[j].Type == EvtVarTypeInt32)
                   {
                      std::wcout << pEvtVariant[j].UInt32Val << std::endl;
                   }
                   else if (pEvtVariant[j].Type == EvtVarTypeUInt32)
                   {
                      std::wcout << pEvtVariant[j].UInt32Val << std::endl;
                   }
                   else if (pEvtVariant[j].Type == EvtVarTypeInt64)
                   {
                      std::wcout << pEvtVariant[j].Int64Val << std::endl;
                   }
                   else if (pEvtVariant[j].Type == EvtVarTypeUInt64)
                   {
                      std::wcout << pEvtVariant[j].UInt64Val << std::endl;
                   }

                   //else if (pEvtVariant[j].Type == EvtVarTypeDouble)
                   //{
                   //   std::wcout << pEvtVariant[j].DoubleVal << std::endl;
                   //}
                   //else if (pEvtVariant[j].Type == EvtVarTypeBoolean)
                   //{
                   //   std::wcout << pEvtVariant[j].BooleanVal << std::endl;
                   //}
                   //else if (pEvtVariant[j].Type == EvtVarTypeBinary)
                   //{
                   //   std::wcout << pEvtVariant[j].BinaryVal << std::endl;
                   //}
                   //else if (pEvtVariant[j].Type == EvtVarTypeGuid)
                   //{
                   //   std::wcout << pEvtVariant[j].GuidVal << std::endl;
                   //}
                   //else if (pEvtVariant[j].Type == EvtVarTypeSizeT)
                   //{
                   //   std::wcout << pEvtVariant[j].SizeTVal << std::endl;
                   //}
                   //else if (pEvtVariant[j].Type == EvtVarTypeFileTime)
                   //{
                   //   std::wcout << pEvtVariant[j].FileTimeVal << std::endl;
                   //}
                   //else if (pEvtVariant[j].Type == EvtVarTypeSysTime)
                   //{
                   //   std::wcout << pEvtVariant[j].SysTimeVal << std::endl;
                   //}
                   //else if (pEvtVariant[j].Type == EvtVarTypeSid)
                   //{
                   //   std::wcout << pEvtVariant[j].SidVal << std::endl;
                   //}
                   //else if (pEvtVariant[j].Type == EvtVarTypeHexInt32)
                   //{
                   //   std::wcout << pEvtVariant[j].HexInt32Val << std::endl;
                   //}
                   //else if (pEvtVariant[j].Type == EvtVarTypeHexInt64)
                   //{
                   //   std::wcout << pEvtVariant[j].HexInt64Val << std::endl;
                   //}
                   //else if (pEvtVariant[j].Type == EvtVarTypeEvtHandle)
                   //{
                   //   std::wcout << pEvtVariant[j].EvtHandleVal << std::endl;
                   //}
                   //else if (pEvtVariant[j].Type == EvtVarTypeEvtXml)
                   //{
                   //   std::wcout << pEvtVariant[j].EvtXmlVal << std::endl;
                   //}
                   //else if (pEvtVariant[j].Type == EvtVarTypeStringArray)
                   //{
                   //   std::wcout << pEvtVariant[j].StringArr << std::endl;
                   //}
                } // end for
             } // end if
          }
#endif
       }
    }
}
