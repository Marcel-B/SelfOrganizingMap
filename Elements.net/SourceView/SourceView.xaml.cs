using System.Windows.Controls;

namespace Elements.net.SourceView
{
    /// <summary>
    /// Interaktionslogik für SourceView.xaml
    /// </summary>
    public partial class SourceView : UserControl
    {
        public SourceViewModel ViewModel { get; set; }

        public SourceView()
        {
            InitializeComponent();
            this.DataContext = ViewModel;
        }
    }
}
