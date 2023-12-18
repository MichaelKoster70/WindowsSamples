using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using Windows.ApplicationModel.Background;

namespace WpfApp1
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
         public MainWindow()
        {
            InitializeComponent();

        }

        private async void Button_Click(object sender, RoutedEventArgs e)
        {
            await BackgroundExecutionManager.RequestAccessAsync();

            // Check if the task is already registered
            foreach (var cur in BackgroundTaskRegistration.AllTasks)
            {
                if (cur.Value.Name == "ApplicationBackgroundTask")
                {
                    // The task is already registered.
                    var task2 = new ApplicationTrigger();
                    var resul2t = await task2.RequestAsync();
                    return;
                }
            }

            BackgroundTaskBuilder builder = new BackgroundTaskBuilder();
            builder.Name = "ApplicationBackgroundTask";
            builder.SetTrigger(new ApplicationTrigger());
            builder.TaskEntryPoint = "UwpBackgroundTask.ApplicationBackgroundTask";
            builder.Register();

             var task = new ApplicationTrigger();
             var result = await task.RequestAsync();
        }
    }
}