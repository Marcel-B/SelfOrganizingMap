using System;
using System.Windows;
using System.Windows.Input;
using Elements.net.OpenFile;

namespace Elements.net.Commands
{
    public class OpenSourceCommand : ICommand
    {
        public bool CanExecute(object parameter)
        {
            return true;
        }

        public void Execute(object parameter)
        {
            var width = Properties.Settings.Default.OpenFileWidth;
            var height = Properties.Settings.Default.OpenFileHeigth;

            var win = new OpenFileView()
            {
                WindowStartupLocation = WindowStartupLocation.CenterScreen,
                Width = width,
                Height = height
            };

            var result = (bool)win.ShowDialog();

            Properties.Settings.Default.OpenFileHeigth = win.ActualHeight;
            Properties.Settings.Default.OpenFileWidth = win.ActualWidth;
            Properties.Settings.Default.Save();

            if (!result) return;
            var source = win.SourcePath;
        }

        public event EventHandler CanExecuteChanged;
    }
}
