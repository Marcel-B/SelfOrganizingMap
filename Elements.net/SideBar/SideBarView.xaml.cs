using System.Windows;
using System.Windows.Controls;

namespace com_b_velop.SideBar
{
    /// <summary>
    /// Interaktionslogik für SideBarView.xaml
    /// </summary>
    public partial class SideBarView : UserControl
    {
        public SideBarView(ISideBarViewModel viewModel)
        {
            InitializeComponent();
            DataContext = viewModel;
        }
    }
}
