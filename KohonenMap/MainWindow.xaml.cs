using System.Windows;
using System.Windows.Controls;

namespace KohonenMap
{
    /// <summary>
    /// Interaktionslogik für MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        public MainWindow()
        {
            InitializeComponent();
        }

        private void MainWindow_OnTextChanged(object sender, TextChangedEventArgs e)
        {
            this.Title += '*';
        }
    }
}
