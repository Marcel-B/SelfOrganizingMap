using com_b_velop.Commands;
using com_b_velop.Common;

namespace com_b_velop.SideBar
{
    public class SideBarViewModel : ViewModelBase
    {
        public StartIterationCommand StartIterationCommand { get; set; }
        public SideBarViewModel()
        {
            StartIterationCommand = new StartIterationCommand();
        }
    }
}