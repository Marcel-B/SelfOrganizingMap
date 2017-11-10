using System.Windows.Controls;

namespace com_b_velop.SourceView
{
    /// <summary>
    /// Interaktionslogik für SourceView.xaml
    /// </summary>
    public partial class SourceView : UserControl
    {
        public SourceView(ISourceViewModel viewModel)
        {
            InitializeComponent();
            this.DataContext = viewModel;
        }
    }
}
