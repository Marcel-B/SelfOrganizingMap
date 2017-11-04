using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Elements.net.Common
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
