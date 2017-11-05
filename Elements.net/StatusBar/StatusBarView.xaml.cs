using System.Windows.Controls;

namespace com_b_velop.StatusBar
{
    /// <summary>
    /// Interaktionslogik für StatusBarView.xaml
    /// </summary>
    public partial class StatusBarView : UserControl
    {
        public StatusBarView()
        {
            InitializeComponent();
            this.DataContext = new StatusBarViewModel(); ;
        }
    }
}
