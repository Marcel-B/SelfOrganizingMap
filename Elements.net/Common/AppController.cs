using System;
using System.Windows;
using com_b_velop.Commands;
using com_b_velop.Events;
using Microsoft.Practices.ServiceLocation;
using Prism.Events;

namespace com_b_velop.Common
{
    public class AppController
    {
        private readonly OpenSourceCommand _openSourceCommand;
        private IServiceLocator _serviceLocator;
        private EventAggregator eventAggregator;
        public AppController(IServiceLocator serviceLocator)
        {
            _serviceLocator = serviceLocator;
            eventAggregator = serviceLocator.GetInstance<EventAggregator>();
            _openSourceCommand = serviceLocator.GetInstance<OpenSourceCommand>();
            eventAggregator.GetEvent<ExitEvent>().Subscribe((obj) =>
            {
                Environment.Exit(0);
            });
            eventAggregator.GetEvent<OpenFileReadyEvent>().Subscribe(OnOpenFileReady);
            eventAggregator.GetEvent<OpenSourceEvent>().Subscribe(OnOpenSource);
        }

        private void OnOpenFileReady(DialogReadyEventArgs obj)
        {
            var fileReader = _serviceLocator.GetInstance<FileReader>();
            var import = _serviceLocator.GetInstance<ImportTable>();
            import.FileReader = fileReader;
            import.Separator = obj.Split;
            var table = import.GetTable(obj.Filepath);
            var doubleValues = import.ParseTableToDouble(table);
        }

        private void OnOpenSource(object obj)
        {
            _openSourceCommand.Execute(obj);
        }
    }
}