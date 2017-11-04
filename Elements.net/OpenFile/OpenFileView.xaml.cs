using System;
using System.Windows;
using System.Windows.Controls;
using Elements.net.Common;

namespace Elements.net.OpenFile
{
    public partial class OpenFileView : Window
    {
        public OpenFileVm ViewModel { get; set; }

        public string SourcePath { get; private set; }

        public OpenFileView()
        {
            InitializeComponent();
            ViewModel = new OpenFileVm();
            ViewModel.DialogRdy -= ViewModel_DialogRdy;
            ViewModel.DialogRdy += ViewModel_DialogRdy;
            this.DataContext = ViewModel;
        }

        private void ViewModel_DialogRdy(object sender, DialogReadyEventArgs e)
        {
            if (e.Result)
                SourcePath = e.Filepath;
            DialogResult = e.Result;
        }

        private void TextBoxBase_OnTextChanged(object sender, TextChangedEventArgs e)
        {
            Console.WriteLine("Text has Changed");
        }
    }
}
