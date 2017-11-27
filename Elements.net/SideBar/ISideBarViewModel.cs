using com_b_velop.Commands;
using Prism.Commands;

namespace com_b_velop.SideBar
{
    public interface ISideBarViewModel
    {
        DelegateCommand StartIteration { get; set; }
    }
}