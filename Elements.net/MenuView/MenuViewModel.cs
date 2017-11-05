using com_b_velop.Commands;
using com_b_velop.Common;

namespace com_b_velop.MenuView
{
    public class MenuViewModel : ViewModelBase
    {
        public DelegateCommand ExitApp { get; set; }
        public OpenSourceCommand OpenSource { get; set; }


        public MenuViewModel()
        {
            ExitApp = new DelegateCommand(BasicFunctions.Exit);
            OpenSource = new OpenSourceCommand();
        }
    }
}
