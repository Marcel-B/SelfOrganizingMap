using com_b_velop.Enums;

namespace com_b_velop.Common
{
    public interface IObservable
    {
        void Register(IObserver observer);
        void Remove(IObserver observer);
        void Message(ObserverType obj);
    }
}