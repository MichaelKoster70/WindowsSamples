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
#include "ApplicationBackgroundTask.h"
#include "ApplicationBackgroundTask.g.cpp"
#include <winrt/Windows.UI.Notifications.h>
#include <winrt/Windows.Data.Xml.Dom.h>
#include <iostream>

// ----------------------------------------------------------------------------
// Implementation
// ----------------------------------------------------------------------------

namespace winrt::UwpBackgroundTask::implementation
{
   void ApplicationBackgroundTask::Run(Windows::ApplicationModel::Background::IBackgroundTaskInstance const& taskInstance)
   {
      taskInstance.Progress(0);
      ShowToast(L"Application Task Triggered!!!");
      taskInstance.GetDeferral().Complete();
   }

   void ApplicationBackgroundTask::ShowToast(hstring const& message)
   {
      auto toastTemplate = Windows::UI::Notifications::ToastTemplateType::ToastText01;
      auto toastXml = Windows::UI::Notifications::ToastNotificationManager::GetTemplateContent(toastTemplate);
      auto toastTextElements = toastXml.GetElementsByTagName(L"text");
      toastTextElements.Item(0).AppendChild(toastXml.CreateTextNode(message));
      auto toast = Windows::UI::Notifications::ToastNotification(toastXml);
      Windows::UI::Notifications::ToastNotificationManager::CreateToastNotifier().Show(toast);
   }
}
