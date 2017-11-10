using System;
using com_b_velop.Commands;
using com_b_velop.Events;
using Microsoft.Practices.ServiceLocation;
using Prism.Events;

namespace com_b_velop.Common
{
    public class AppController
    {
        private readonly OpenSourceCommand _openSourceCommand;

        public AppController(IEventAggregator eventAggregator, IServiceLocator serviceLocator)
        {
            _openSourceCommand = serviceLocator.GetInstance<OpenSourceCommand>();

            eventAggregator.GetEvent<ExitEvent>().Subscribe((obj) =>
            {
                Environment.Exit(0);
            });
            eventAggregator.GetEvent<OpenSourceEvent>().Subscribe(OnOpenSource);
       
        }

        private void OnOpenSource(object obj)
        {
            _openSourceCommand.Execute(obj);
        }
    }
}