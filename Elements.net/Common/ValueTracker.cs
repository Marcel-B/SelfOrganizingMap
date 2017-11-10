using System;
using System.Collections.Generic;

namespace com_b_velop.Common
{
    public class ValueTracker : IObservable<ISomSettings>
    {
        private static ValueTracker _instance;

        public static ValueTracker GetInstance()
        {
            if(_instance == null)
                _instance = new ValueTracker();
            return _instance;
        }

        private ValueTracker() { Observers = new List<IObserver<ISomSettings>>(); }
        private List<IObserver<ISomSettings>> Observers { get; }

        public void CallObservers(ISomSettings settings)
        {
            foreach (var observer in Observers)
            {
                observer.OnNext(settings);
            }
        }

        public void RemoveAllObservers()
        {
            foreach (var observer in Observers.ToArray())
                if (Observers.Contains(observer))
                    observer.OnCompleted();
            Observers.Clear();
        }

        private class Unsubscriber : IDisposable
        {
            private List<IObserver<ISomSettings>> _observers;
            private IObserver<ISomSettings> _observer;

            public Unsubscriber(List<IObserver<ISomSettings>> observers, IObserver<ISomSettings> observer)
            {
                this._observers = observers;
                this._observer = observer;
            }

            public void Dispose()
            {
                if (_observer != null && _observers.Contains(_observer))
                    _observers.Remove(_observer);
            }
        }
        public IDisposable Subscribe(IObserver<ISomSettings> observer)
        {
            if (!Observers.Contains(observer))
                Observers.Add(observer);
            return new Unsubscriber(Observers, observer);
        }
    }
}