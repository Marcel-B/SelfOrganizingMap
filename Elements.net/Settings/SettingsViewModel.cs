using com_b_velop.Common;
using Newtonsoft.Json;

namespace com_b_velop.Settings
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
            get => _projectName;
            set
            {
                _projectName = value; OnPropertyChanged();
                _model.SomName = value;
            }
        }
        public string Alpha
        {
            get => _alpha;
            set
            {
                _alpha = value; OnPropertyChanged();
                _model.Alpha = double.Parse(value);
            }
        }
        public string XNeurons
        {
            get => _xNeurons;
            set
            {
                _xNeurons = value; OnPropertyChanged();
                _model.XNeurons = int.Parse(value);
            }
        }
        public string YNeurons
        {
            get => _yNeurons;
            set
            {
                _yNeurons = value; OnPropertyChanged();
                _model.YNeurons = int.Parse(value);
            }
        }
        public string Iterations
        {
            get => _iterations;
            set
            {
                _iterations = value; OnPropertyChanged();
                _model.Iterations = int.Parse(value);
            }
        }
        public string Radius
        {
            get => _radius;
            set
            {
                _radius = value; OnPropertyChanged();
                _model.Radius = int.Parse(value);
            }
        }

        public void Serialize()
        {
            string json = JsonConvert.SerializeObject(this);
        }

        private SomModel _model;

        public SettingsViewModel()
        {
            _model = SomModel.GetInstance();
            Alpha = "0,7";
            XNeurons = "50";
            YNeurons = "70";
            Iterations = "20";
            Radius = "5";
            ProjectName = "Neues Projekt";
        }
    }
}