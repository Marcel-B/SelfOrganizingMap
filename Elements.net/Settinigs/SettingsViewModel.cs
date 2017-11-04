using Elements.net.Common;

namespace Elements.net.Settinigs
{
    public class SettingsViewModel : ViewModelBase
    {
        private string _projectName;
        private string _alpha;
        private string _xNeurons;
        private string _yNeurons;
        private string _iterations;
        private string _radius;

        public string ProjectName
        {
            get =>  _projectName; 
            set { _projectName = value; OnPropertyChanged(); }
        }
        public string Alpha
        {
            get => _alpha;
            set { _alpha = value; OnPropertyChanged(); }
        }
        public string XNeurons
        {
            get => _xNeurons;
            set { _xNeurons = value; OnPropertyChanged(); }
        }
        public string YNeurons
        {
            get => _yNeurons; 
            set { _yNeurons = value; OnPropertyChanged(); }
        }
        public string Iterations
        {
            get => _iterations; 
            set { _iterations = value; OnPropertyChanged(); }
        }
        public string Radius
        {
            get => _radius; 
            set { _radius = value; OnPropertyChanged();}
        }

        public SettingsViewModel()
        {
            Alpha = "0,7";
            XNeurons = "50";
            YNeurons = "70";
            Iterations = "20";
            Radius = "5";
            ProjectName = "Neues Projekt";
        }
    }
}