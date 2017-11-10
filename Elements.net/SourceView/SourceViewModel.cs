using System;
using System.Data;
using System.IO;
using System.Linq;
using com_b_velop.Common;
using com_b_velop.Enums;
using com_b_velop.Events;
using Prism.Events;
using Prism.Mvvm;

namespace com_b_velop.SourceView
{
    public class SourceViewModel : BindableBase, ISourceViewModel
    {
        public SourceViewModel(IEventAggregator eventAggregator)
        {
            eventAggregator.GetEvent<OpenFileReadyEvent>().Subscribe(OnOpenFileReadyEvent);
        }

        private DataTable _table;
        private string _input;

        public DataTable Table
        {
            get => _table;
            set => SetProperty(ref _table, value);
        }
        public string Input
        {
            get => _input;
            set => SetProperty(ref _input, value);
        }

        private async void OnOpenFileReadyEvent(DialogReadyEventArgs obj)
        {
            if (obj.Result)
            {
                var appState = AppState.GetInstance();

                ISourceInfo sourceInfo = SomModel.GetInstance();
                sourceInfo.SourcePath = obj.Filepath;
                sourceInfo.SplitChar = obj.Split;
                sourceInfo.HasHeader = obj.HasHeader;

                appState.SourceInfo = sourceInfo;
                appState.Message(ObserverType.SourceInfo);
            }
            Table = await GetTable.GetDataTable(obj.Filepath, obj.HasHeader, obj.Split);
        }
    }
}