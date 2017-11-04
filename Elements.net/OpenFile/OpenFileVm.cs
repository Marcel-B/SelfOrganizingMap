using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.ComponentModel;
using System.Data;
using System.IO;
using System.Net.Configuration;
using System.Windows.Controls;
using System.Windows.Media;
using Elements.net.Commands;
using Elements.net.Common;

namespace Elements.net.OpenFile
{
    public class OpenFileVm : ViewModelBase
    {
        private string _sourcePath;
        private string _sourceText;
        private ObservableCollection<IImportRow> _sourceTable;

        public ObservableCollection<IImportRow> SourceTable
        {
            get => _sourceTable;
            set { _sourceTable = value; OnPropertyChanged(); }
        }
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
        public DelegateCommand OpenSource { get; set; }


        public OpenFileVm()
        {
            Fully = true;
            OpenSource = new DelegateCommand(OpenFile);
        }

        public void Exit()
        {
            Environment.Exit(0);
        }

        public async void OpenFile()
        {
            var ofd = new Microsoft.Win32.OpenFileDialog();
            var result = (bool)ofd.ShowDialog();
            if (!result) return;
            SourcePath = ofd.FileName;
            var fi = new FileInfo(SourcePath);
            if (SourceTable == null) SourceTable = new ObservableCollection<IImportRow>();
            if (fi.Exists)
            {
                using (var fr = fi.OpenText())
                {
                    while (!fr.EndOfStream)
                    {
                        var line = await fr.ReadLineAsync();
                        var ff = new ImportRow() {Value = line};
                        SourceTable.Add(ff);
                    }
                }
            }
        }
    }
}
