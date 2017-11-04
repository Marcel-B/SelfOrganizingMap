using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
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
            var win = new Window();
            win.Content = new OpenFileView();
            win.ShowDialog();
        }

        public event EventHandler CanExecuteChanged;
    }
}
