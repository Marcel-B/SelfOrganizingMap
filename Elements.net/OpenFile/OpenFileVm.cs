using System;
using System.ComponentModel;
using System.IO;
using Elements.net.Commands;
using Elements.net.Common;

namespace Elements.net.OpenFile
{
    public class OpenFileVm : ViewModelBase
    {
        private string _sourcePath;
        private string _sourceText;

        public string SourcePath
        {
            get => _sourcePath;
            set { _sourcePath = value; OnPropertyChanged(); }
        }
        public string SourceText
        {
            get => _sourceText;
            set { _sourceText = value; OnPropertyChanged(); }
        }
        public bool Fully { get; set; }
        public DelegateCommand ExitApp { get; set; }
        public DelegateCommand OpenSource { get; set; }


        public OpenFileVm()
        {
            Fully = true;
            ExitApp = new DelegateCommand(Exit);
            OpenSource = new DelegateCommand(OpenFile);
        }

        public void Exit()
        {
            Environment.Exit(0);
        }

        public void OpenFile()
        {
            var ofd = new Microsoft.Win32.OpenFileDialog();
            var result = (bool)ofd.ShowDialog();
            if (!result) return;
            SourcePath = ofd.FileName;
            SourceText = File.ReadAllText(SourcePath);
        }
    }
}
