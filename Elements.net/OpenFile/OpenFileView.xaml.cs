using System;
using System.Windows;
using System.Windows.Controls;
using com_b_velop.Common;
using com_b_velop.Enums;

namespace com_b_velop.OpenFile
{
    public partial class OpenFileView : Window
    {
        public OpenFileVm ViewModel { get; set; }

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
            {
                var appState = AppState.GetInstance();
                ISourceInfo sourceInfo = SomModel.GetInstance();
                sourceInfo.SourcePath = e.Filepath;
                sourceInfo.SplitChar = e.Split;
                sourceInfo.HasHeader = e.HasHeader;
                appState.SourceInfo = sourceInfo;
                appState.Message(ObserverType.SourceInfo);
            }
            DialogResult = e.Result;
        }

        private void TextBoxBase_OnTextChanged(object sender, TextChangedEventArgs e)
        {
            Console.WriteLine("Text has Changed");
        }
    }
}
