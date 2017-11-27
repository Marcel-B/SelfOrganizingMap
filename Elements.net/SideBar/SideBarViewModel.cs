using com_b_velop.Commands;
using com_b_velop.Common;
using com_b_velop.OpenFile;
using Prism.Commands;
using Prism.Regions;

namespace com_b_velop.SideBar
{
    public class SideBarViewModel : ViewModelBase, ISideBarViewModel, INavigationAware
    {
        private IRegionManager _regionManager;
        public DelegateCommand StartIteration { get; set; }
        public SideBarViewModel(IRegionManager regionManager)
        {
            _regionManager = regionManager;
            StartIteration = new DelegateCommand(OnStartIteration);
        }

        private void OnStartIteration()
        {
            _regionManager.RequestNavigate("Main", typeof(OpenFileView).ToString());
        }

        public void OnNavigatedTo(NavigationContext navigationContext)
        {
        }

        public bool IsNavigationTarget(NavigationContext navigationContext) => true;

        public void OnNavigatedFrom(NavigationContext navigationContext)
        {
        }
    }
}