using System.ComponentModel;

namespace com_b_velop.Common
{
    interface IViewModelBase
    {
        event PropertyChangedEventHandler PropertyChanged;
    }
}