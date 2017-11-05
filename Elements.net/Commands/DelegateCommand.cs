using System;
using System.Windows.Input;

namespace com_b_velop.Commands
{
    public class DelegateCommand : ICommand
    {
        private readonly Action _eventHandler;

        public DelegateCommand(Action handler)
        {
            _eventHandler = handler;
        }

        public bool CanExecute(object parameter)
        {
            if (parameter == null)
            {
                Console.WriteLine("CanExecute parameter is null");
                return false;
            }
            Console.WriteLine($"Hey, CanExecute = {parameter.ToString()}");
            Console.WriteLine(parameter);
            return true;
        }

        public void Execute(object parameter)
        {
            Console.WriteLine($"Hey, Execute = {parameter.ToString()}");
            Console.WriteLine(parameter);
            _eventHandler();
        }

        public event EventHandler CanExecuteChanged;
    }
}
