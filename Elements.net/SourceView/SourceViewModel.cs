using System;
using System.Data;
using System.IO;
using System.Linq;
using com_b_velop.Common;
using com_b_velop.Enums;

namespace com_b_velop.SourceView
{
    public class SourceViewModel : ViewModelBase, IObserver
    {
        public SourceViewModel()
        {
            var appState = AppState.GetInstance();
            appState.Register(this);
        }
        ~SourceViewModel()
        {
            var appState = AppState.GetInstance();
            appState.Remove(this);
        }
        private DataTable _table;
        private string _input;
        public DataTable Table
        {
            get => _table;
            set { _table = value; OnPropertyChanged(); }
        }
        public string Input
        {
            get => _input;
            set { _input = value; OnPropertyChanged(); }
        }

        public async void Update(ObserverType obj)
        {
            if (obj == ObserverType.SourceInfo)
            {
                    var info = SomModel.GetSourceInfo();
                    Input = (info.SourcePath);
                    Table = await GetTable.GetDataTable(Input, info.HasHeader, info.SplitChar);
            }
        }
    }
}