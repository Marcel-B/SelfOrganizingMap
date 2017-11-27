using com_b_velop.Commands;
using com_b_velop.Events;
using Prism.Commands;
using Prism.Events;
using Prism.Mvvm;

namespace com_b_velop.MenuView
{
    public class MenuViewModel : BindableBase, IMenuViewModel
    {
        public DelegateCommand ExitApp { get; set; }
        public DelegateCommand OpenSource { get; set; }

        public MenuViewModel(EventAggregator eventAggregator)
        {
            ExitApp = new DelegateCommand(() =>
            {
                eventAggregator.GetEvent<ExitEvent>().Publish(this);
            });

            OpenSource = new DelegateCommand(() =>
            {
                eventAggregator.GetEvent<OpenSourceEvent>().Publish(this);
            });
        }
    }
}
