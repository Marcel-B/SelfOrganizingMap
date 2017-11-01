using System.ComponentModel;

namespace Elements.net.Common
{
    interface IViewModelBase
    {
        event PropertyChangedEventHandler PropertyChanged;
    }
}