using System.Windows;
using System.Windows.Controls;
using com_b_velop;
using com_b_velop.Common;
using com_b_velop.MainView;
using com_b_velop.MenuView;
using com_b_velop.OpenFile;
using com_b_velop.Settings;
using com_b_velop.SideBar;
using com_b_velop.SourceView;
using com_b_velop.StatusBar;
using Microsoft.Practices.ServiceLocation;
using Ninject;
using Prism.Events;
using Prism.Ninject;
using Prism.Regions;

namespace SelfOrganizingMap.Shell
{
    public class Bootstrapper : NinjectBootstrapper
    {
        protected override DependencyObject CreateShell()
        {
            return new Shell();
        }

        protected override void ConfigureKernel()
        {
            base.ConfigureKernel();
            var eventAggr = new EventAggregator();
            Kernel.Bind<EventAggregator>().ToConstant(eventAggr);
            Kernel.Bind<IImportTable>().To<ImportTable>();
            Kernel.Bind<IFileReader>().To<FileReader>();
            Kernel.Bind<IOpenFileViewModel>().To<OpenFileViewModel>();
            Kernel.Bind<ISideBarViewModel>().To<SideBarViewModel>();
            Kernel.Bind<ISourceViewModel>().To<SourceViewModel>();
            Kernel.Bind<ISettingsViewModel>().To<SettingsViewModel>();
            Kernel.Bind<StatusBarViewModel>().To<StatusBarViewModel>();
            Kernel.Bind<IMenuViewModel>().To<MenuViewModel>();

            Kernel.RegisterTypeForNavigation<OpenFileView>(typeof(OpenFileView).ToString());
            Kernel.RegisterTypeForNavigation<MainView>(typeof(MainView).ToString()); 
            Kernel.RegisterTypeForNavigation<SideBarView>(typeof(SideBarView).ToString());
            Kernel.RegisterTypeForNavigation<SourceView>(typeof(SourceView).ToString());
            Kernel.RegisterTypeForNavigation<SettingsView>(typeof(SettingsView).ToString());
            Kernel.RegisterTypeForNavigation<StatusBarView>(typeof(StatusBarView).ToString());
            Kernel.RegisterTypeForNavigation<MenuView>(typeof(MenuView).ToString());

            var app = new AppController(Kernel.Get<IServiceLocator>());
            Kernel.Bind<AppController>().ToConstant(app);
        }
        protected override void InitializeShell()
        {
            var shell = (Shell) Shell;
            var regionManager = Kernel.Get<IRegionManager>();
            regionManager.RegisterViewWithRegion("Main", typeof(MainView));
            regionManager.RegisterViewWithRegion("Sidebar", typeof(SideBarView)); 
            regionManager.RegisterViewWithRegion("SourceRegion", typeof(SourceView));
            regionManager.RegisterViewWithRegion("Settings", typeof(SettingsView));
            regionManager.RegisterViewWithRegion("Statusbar", typeof(StatusBarView));
            regionManager.RegisterViewWithRegion("Menu", typeof(MenuView));



            Application.Current.MainWindow = shell;
            Application.Current.MainWindow.ShowDialog();
        }
    }
}