namespace com_b_velop.Common
{
    public class ImportRow : ViewModelBase, IImportRow
    {
        private string _value;

        public string Value
        {
            get => _value;
            set { _value = value; OnPropertyChanged(); }
        }
    }
    public interface IImportRow
    {
        string Value { get; set; }
    }
}
