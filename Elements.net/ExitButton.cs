using System.Windows;
using System.Windows.Controls;

namespace com_b_velop
{
    public class ExitButton : Button
    {
        public static RoutedEvent ExitEvent = 
            EventManager.
            RegisterRoutedEvent("Exit", RoutingStrategy.Bubble, typeof(RoutedEventHandler), typeof(ExitButton));

        public event RoutedEventHandler Exit
        {
            add { AddHandler(ExitEvent, value);}
            remove { RemoveHandler(ExitEvent, value);}
        }

        protected override void OnClick()
        {
            RoutedEventArgs routedEventArgs = new RoutedEventArgs(ExitEvent);
            RaiseEvent(routedEventArgs);
        }
    }
}
