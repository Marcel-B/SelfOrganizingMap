using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;

namespace Elements.net
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
