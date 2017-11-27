using System;
using System.Windows;
using System.Windows.Input;
using com_b_velop.Common;

namespace com_b_velop.Commands
{
    public class StartIterationCommand : ICommand
    {
        public bool CanExecute(object parameter)
        {
            return true;
        }

        public void Execute(object parameter)
        {
            //MessageBox.Show("Et jeht loss");
            //app.StartIteration(SomModel.GetInstance());
        }

        public event EventHandler CanExecuteChanged;
    }
}