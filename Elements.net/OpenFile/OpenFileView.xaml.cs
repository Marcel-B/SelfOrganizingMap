using System;
using System.Windows.Controls;
using System.Windows.Input;

namespace Elements.net.OpenFile
{
    /// <inheritdoc />
    /// <summary>
    /// Interaktionslogik für OpenFileView.xaml
    /// </summary>
    public partial class OpenFileView : UserControl
    {
        public OpenFileView()
        {
            InitializeComponent();
        }
        private void TextBoxBase_OnTextChanged(object sender, TextChangedEventArgs e)
        {
            Console.WriteLine("Text has Changed");
        }
    }
}
