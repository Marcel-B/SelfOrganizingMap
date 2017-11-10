using com_b_velop.Commands;
using Prism.Commands;

namespace com_b_velop.MenuView
{
    public interface IMenuViewModel
    {
        DelegateCommand ExitApp { get; set; }
        DelegateCommand OpenSource { get; set; }
    }
}