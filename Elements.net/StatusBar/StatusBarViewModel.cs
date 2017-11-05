using com_b_velop.Common;
using com_b_velop.Enums;

namespace com_b_velop.StatusBar
{
    public class StatusBarViewModel : ViewModelBase, IObserver
    {
        private string _sourcePath;

        public string SourcePath
        {
            get => _sourcePath;
            set { _sourcePath = value; OnPropertyChanged(); }
        }

        public StatusBarViewModel()
        {
            var state = AppState.GetInstance();
            state.Register(this);
        }

        ~StatusBarViewModel()
        {
            var state = AppState.GetInstance();
            state.Remove(this);
        }
        public void Update(ObserverType obj)
        {
            if (obj == ObserverType.SourceInfo)
            {
                var info = SomModel.GetSourceInfo();
                SourcePath = info.SourcePath;
            }
        }
    }
}