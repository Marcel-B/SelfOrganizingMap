using System.Windows.Input;

namespace com_b_velop.Commands
{
    public class Commands
    {
    }

    public class ExitCommand
    {
        public static RoutedUICommand Exit { get; }

        static ExitCommand()
        {
            Exit = new RoutedUICommand("Exit Command", "Exit", typeof(ExitCommand));
            Exit.InputGestures.Add(new KeyGesture(Key.F4, ModifierKeys.Alt));
        }
    }

    public class MyCommand
    {
        public static RoutedUICommand Launch { get; }

        static MyCommand()
        {
            Launch = new RoutedUICommand("My Launch Command", "Launch", typeof(MyCommand));
            Launch.InputGestures.Add(new KeyGesture(Key.L, ModifierKeys.Control));
        }
    }
}

