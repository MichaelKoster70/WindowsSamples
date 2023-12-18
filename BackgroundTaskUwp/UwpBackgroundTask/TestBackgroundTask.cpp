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
#include "TestBackgroundTask.h"
#include "TestBackgroundTask.g.cpp"
#include <winrt/Windows.UI.Notifications.h>
#include <winrt/Windows.Data.Xml.Dom.h>

// ----------------------------------------------------------------------------
// Implementation
// ----------------------------------------------------------------------------

namespace winrt::UwpBackgroundTask::implementation
{
   void TestBackgroundTask::Run(Windows::ApplicationModel::Background::IBackgroundTaskInstance const& taskInstance)
   {
      ShowToast(L"Background Task Triggered!!!");
      taskInstance.GetDeferral().Complete();
   }

   void TestBackgroundTask::ShowToast(hstring const& message)
   {
      auto toastTemplate = Windows::UI::Notifications::ToastTemplateType::ToastText01;
      auto toastXml = Windows::UI::Notifications::ToastNotificationManager::GetTemplateContent(toastTemplate);
      auto toastTextElements = toastXml.GetElementsByTagName(L"text");
      toastTextElements.Item(0).AppendChild(toastXml.CreateTextNode(message));
      auto toast = Windows::UI::Notifications::ToastNotification(toastXml);
      Windows::UI::Notifications::ToastNotificationManager::CreateToastNotifier().Show(toast);
   }
}
