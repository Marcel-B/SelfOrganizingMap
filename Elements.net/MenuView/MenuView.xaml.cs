using System.Windows.Controls;
using Prism.Events;

namespace com_b_velop.MenuView
{
    /// <summary>
    /// Interaktionslogik für MenuView.xaml
    /// </summary>
    public partial class MenuView : UserControl
    {

        public MenuView(IMenuViewModel viewModel)
        {
            InitializeComponent();
            DataContext = viewModel;
        }
    }
}
