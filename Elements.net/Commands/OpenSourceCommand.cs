using System;
using System.Windows;
using System.Windows.Input;
using com_b_velop.Common;
using com_b_velop.OpenFile;

namespace com_b_velop.Commands
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

            win.ShowDialog();
            Properties.Settings.Default.OpenFileHeigth = win.ActualHeight;
            Properties.Settings.Default.OpenFileWidth = win.ActualWidth;
            Properties.Settings.Default.Save();
        }

        public event EventHandler CanExecuteChanged;
    }
}
