using System.Collections.Generic;
using com_b_velop.Enums;
using SelfOrganizingMap.Net;

namespace com_b_velop.Common
{
    public class AppState : IObservable
    {
        public List<IObserver> Observers { get; set; }
        private static AppState _appState;

        public static AppState GetInstance()
        {
            if (_appState == null)
                _appState = new AppState();
            return _appState;
        }

        private AppState()
        {
            Observers = new List<IObserver>();
            SourceInfo = new SourceInfo();
        }

        public ISourceInfo SourceInfo { get; set; }
        public ISomSettings SomSettings { get; set; }

        public void StartIteration()
        {
            SomSettings = SomModel.GetInstance();
            SomCore.StartIteration(SomSettings);
        }

        public void Register(IObserver observer)
        {
            if (Observers == null)
                Observers = new List<IObserver>();
            Observers.Add(observer);
        }
        public void Remove(IObserver observer)
        {
            if (Observers == null) return;
            if (Observers.Contains(observer))
                Observers.Remove(observer);
        }
        public void Message(ObserverType obj)
        {
            Observers.ForEach(item => item.Update(obj));
        }
    }
}