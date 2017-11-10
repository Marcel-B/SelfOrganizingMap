using System;
using System.Windows;
using System.Windows.Controls;
using com_b_velop.Common;
using com_b_velop.Enums;
using com_b_velop.Events;
using Prism.Events;

namespace com_b_velop.OpenFile
{
    public partial class OpenFileView : Window
    {
        public OpenFileView(IOpenFileViewModel viewModel, IEventAggregator eventAggregator)
        {
            InitializeComponent();
            DataContext = viewModel;
            eventAggregator.GetEvent<OpenFileReadyEvent>().Subscribe(OnOpenFileReady);
        }

        private void OnOpenFileReady(DialogReadyEventArgs e)
        {
            DialogResult = e.Result;
        }
        private void TextBoxBase_OnTextChanged(object sender, TextChangedEventArgs e)
        {
            Console.WriteLine("Text has Changed");
        }
    }
}
