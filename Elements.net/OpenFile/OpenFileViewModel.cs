using System;
using System.Collections.ObjectModel;
using System.IO;
using com_b_velop.Common;
using com_b_velop.Events;
using Microsoft.Practices.ServiceLocation;
using Prism.Commands;
using Prism.Events;
using Prism.Mvvm;
using Prism.Regions;

namespace com_b_velop.OpenFile
{
    public class OpenFileViewModel : BindableBase, IOpenFileViewModel, INavigationAware
    {
        private string _sourcePath;
        private string _sourceText;
        private bool? _hasHeader;
        private char _split;

        private ObservableCollection<IImportRow> _sourceTable;
        private IRegionManager _regionManager;
        private IServiceLocator _serviceLocator;
        public event EventHandler<DialogReadyEventArgs> DialogRdy;

        public ObservableCollection<IImportRow> SourceTable
        {
            get => _sourceTable;
            set => SetProperty(ref _sourceTable, value);
        }
        public string SourcePath
        {
            get => _sourcePath;
            set => SetProperty(ref _sourcePath, value);
        }
        public string SourceText
        {
            get => _sourceText;
            set => SetProperty(ref _sourceText, value);
        }
        public bool? HasHeader
        {
            get => _hasHeader;
            set => SetProperty(ref _hasHeader, value);
        }
        public char Split
        {
            get => _split;
            set => SetProperty(ref _split, value);
        }

        public bool Fully { get; set; }
        public DelegateCommand OpenSource { get; set; }
        public DelegateCommand OkCommand { get; set; }


        public OpenFileViewModel(IServiceLocator serviceLocator, IRegionManager regionManager)
        {
            _regionManager = regionManager;
            _serviceLocator = serviceLocator;
            HasHeader = false;
            Fully = true;
            OpenSource = new DelegateCommand(OpenFile);
            OkCommand = new DelegateCommand(Ok);
        }
        public void Ok()
        {
            var e = new DialogReadyEventArgs(SourcePath, Split, (bool)HasHeader, true);
            var eventAggregator = _serviceLocator.GetInstance<EventAggregator>();
            eventAggregator.GetEvent<OpenFileReadyEvent>().Publish(e);

            _regionManager.RequestNavigate("Main", typeof(MainView.MainView).ToString());
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

        public void OnNavigatedTo(NavigationContext navigationContext)
        {
        }

        public bool IsNavigationTarget(NavigationContext navigationContext) => true;

        public void OnNavigatedFrom(NavigationContext navigationContext)
        {
        }
    }
}
