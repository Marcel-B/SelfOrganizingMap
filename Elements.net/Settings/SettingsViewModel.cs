using Prism.Mvvm;

namespace com_b_velop.Settings
{
    public class SettingsViewModel : BindableBase, ISettingsViewModel
    {
        private string _projectName;
        private string _alpha;
        private string _xNeurons;
        private string _yNeurons;
        private string _iterations;
        private string _radius;

        public string ProjectName
        {
            get => _projectName;
            set => SetProperty(ref _projectName, value);
        }
        public string Alpha
        {
            get => _alpha;
            set => SetProperty(ref _alpha, value);
        }
        public string XNeurons
        {
            get => _xNeurons;
            set => SetProperty(ref _xNeurons, value);
        }
        public string YNeurons
        {
            get => _yNeurons;
            set  => SetProperty(ref _yNeurons, value);
        }
        public string Iterations
        {
            get => _iterations;
            set => SetProperty(ref _iterations, value);
        }
        public string Radius
        {
            get => _radius;
            set => SetProperty(ref _radius, value);
        }
        public SettingsViewModel()
        {
            _alpha = "0,7";
            XNeurons = "50";
            YNeurons = "70";
            Iterations = "20";
            Radius = "5";
            ProjectName = "Neues Projekt";
        }
    }
}