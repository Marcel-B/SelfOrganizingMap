using System.Windows;
using System.Windows.Input;
using com_b_velop.Commands;
using com_b_velop.Common;
using com_b_velop.MenuView;
using com_b_velop.OpenFile;
using com_b_velop.Settings;
using com_b_velop.SourceView;
using Microsoft.Practices.ServiceLocation;
using Microsoft.Practices.Unity;
using Prism.Events;
using Prism.Regions;
using Prism.Unity;

namespace com_b_velop
{
    public class Bootstrapper : UnityBootstrapper
    {
        protected override DependencyObject CreateShell() => new MainWindow();

        // UnityBootstrapper.cs
        protected override void ConfigureContainer()
        {
            base.ConfigureContainer();



            //var eventAggregator = new EventAggregator();
            //Container.RegisterInstance(typeof(IEventAggregator), eventAggregator);

            //Container.RegisterType<IEventAggregator, EventAggregator>(new ContainerControlledLifetimeManager());
            Container.RegisterType<ISourceViewModel, SourceViewModel>();
            Container.RegisterType<ISettingsViewModel, SettingsViewModel>();
            Container.RegisterType<IMenuViewModel, MenuViewModel>();
            Container.RegisterType<OpenFileView, OpenFileView>();
            Container.RegisterType<IOpenFileViewModel, OpenFileViewModel>();
            Container.RegisterType<ICommand, OpenSourceCommand>();

            Container.RegisterInstance(typeof(AppController), new AppController(Container.Resolve<IEventAggregator>(), Container.Resolve<IServiceLocator>()));
        }


        protected override void InitializeShell()
        {
            var window = (MainWindow)Shell;

            var regionManager = Container.Resolve<IRegionManager>();

            regionManager.RegisterViewWithRegion("MainRegion", typeof(MainView.MainView));
            regionManager.RegisterViewWithRegion("Settings", typeof(SettingsView));
            regionManager.RegisterViewWithRegion("SourceRegion", typeof(SourceView.SourceView));
            regionManager.RegisterViewWithRegion("MenuRegion", typeof(MenuView.MenuView));

            Application.Current.MainWindow = window;
            window.Show();
        }
    }
}
