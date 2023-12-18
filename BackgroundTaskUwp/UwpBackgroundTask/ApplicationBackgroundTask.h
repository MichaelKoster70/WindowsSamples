#pragma once

#include "ApplicationBackgroundTask.g.h"

namespace winrt::UwpBackgroundTask::implementation
{
    struct ApplicationBackgroundTask :ApplicationBackgroundTaskT<ApplicationBackgroundTask>
    {
       ApplicationBackgroundTask() = default;

        void Run(Windows::ApplicationModel::Background::IBackgroundTaskInstance const& taskInstance);

    private:
        void ShowToast(hstring const& message);
    };
}

namespace winrt::UwpBackgroundTask::factory_implementation
{
    struct ApplicationBackgroundTask : ApplicationBackgroundTaskT<ApplicationBackgroundTask, implementation::ApplicationBackgroundTask>
    {
    };
}
