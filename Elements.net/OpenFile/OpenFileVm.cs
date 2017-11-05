using System;
using System.Collections.ObjectModel;
using System.IO;
using com_b_velop.Commands;
using com_b_velop.Common;

namespace com_b_velop.OpenFile
{
    public class OpenFileVm : ViewModelBase
    {
        private string _sourcePath;
        private string _sourceText;
        private bool? _hasHeader;
        private char _split;

        private ObservableCollection<IImportRow> _sourceTable;
        public event EventHandler<DialogReadyEventArgs> DialogRdy;

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
        public bool? HasHeader
        {
            get => _hasHeader;
            set { _hasHeader = value; OnPropertyChanged(); }
        }
        public char Split
        {
            get => _split;
            set { _split = value; OnPropertyChanged(); }
        }

        public bool Fully { get; set; }
        public DelegateCommand OpenSource { get; set; }
        public DelegateCommand OkCommand { get; set; }


        public OpenFileVm()
        {
            HasHeader = false;
            Fully = true;
            OpenSource = new DelegateCommand(OpenFile);
            OkCommand = new DelegateCommand(Ok);
        }
        public void Ok()
        {
            DialogRdy?.Invoke(this, new DialogReadyEventArgs(SourcePath, Split, (bool)HasHeader, true));
        }
        public async void OpenFile()
        {
            var ofd = new Microsoft.Win32.OpenFileDialog();
            var path = Properties.Settings.Default.OpenFileSource;

            if (Directory.Exists(path))
                ofd.InitialDirectory = path;

            var result = (bool)ofd.ShowDialog();
            if (!result) return;
            SourcePath = ofd.FileName;

            Properties.Settings.Default.OpenFileSource = Path.GetDirectoryName(SourcePath);
            Properties.Settings.Default.Save();


            var fi = new FileInfo(SourcePath);
            if (SourceTable == null) SourceTable = new ObservableCollection<IImportRow>();
            if (fi.Exists)
            {
                using (var fr = fi.OpenText())
                {
                    while (!fr.EndOfStream)
                    {
                        var line = await fr.ReadLineAsync();
                        var ff = new ImportRow { Value = line };
                        SourceTable.Add(ff);
                    }
                }
            }
        }
    }
}
