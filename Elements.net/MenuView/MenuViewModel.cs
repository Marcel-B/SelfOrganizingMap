using Elements.net.Commands;
using Elements.net.Common;

namespace Elements.net.MenuView
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
