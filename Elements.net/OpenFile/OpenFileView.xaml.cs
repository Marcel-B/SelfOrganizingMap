using System;
using System.Windows.Controls;
using com_b_velop.Common;
using com_b_velop.Events;
using Prism.Events;

namespace com_b_velop.OpenFile
{
    public partial class OpenFileView : UserControl
    {
        public OpenFileView(IOpenFileViewModel viewModel)
        {
            InitializeComponent();
            DataContext = viewModel;
        }

        private void TextBoxBase_OnTextChanged(object sender, TextChangedEventArgs e)
        {
            Console.WriteLine("Text has Changed");
        }
    }
}
