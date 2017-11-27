using System.Data;
using com_b_velop.Common;
using com_b_velop.Events;
using Prism.Events;
using Prism.Mvvm;

namespace com_b_velop.SourceView
{
    public class SourceViewModel : BindableBase, ISourceViewModel
    {
        public SourceViewModel(EventAggregator eventAggregator)
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

        private void OnOpenFileReadyEvent(DialogReadyEventArgs obj)
        {
        }
    }
}