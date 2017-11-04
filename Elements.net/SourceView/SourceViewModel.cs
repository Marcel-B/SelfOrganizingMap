using System;
using System.Data;
using Elements.net.Common;

namespace Elements.net.SourceView
{
    public class SourceViewModel : ViewModelBase
    {
        private DataTable _table;

        public DataTable Table
        {
            get => _table;
            set { _table = value; OnPropertyChanged(); }
        }

    }
}