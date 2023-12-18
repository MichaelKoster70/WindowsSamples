#pragma once

#include "TestBackgroundTask.g.h"

namespace winrt::UwpBackgroundTask::implementation
{
    struct TestBackgroundTask : TestBackgroundTaskT<TestBackgroundTask>
    {
        TestBackgroundTask() = default;

        void Run(Windows::ApplicationModel::Background::IBackgroundTaskInstance const& taskInstance);

    private:
        void ShowToast(hstring const& message);
    };
}

namespace winrt::UwpBackgroundTask::factory_implementation
{
    struct TestBackgroundTask : TestBackgroundTaskT<TestBackgroundTask, implementation::TestBackgroundTask>
    {
    };
}
