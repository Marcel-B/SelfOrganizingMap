using System;
using System.IO;
using Newtonsoft.Json;

namespace com_b_velop.Common
{
    public class SomModel : ISomSettings, ISourceInfo, ITrainDataInfo
    {
        private static SomModel _model;
        private ValueTracker Tracker { get; }

        private SomModel()
        {
            Tracker = ValueTracker.GetInstance();
        }
        public static SomModel GetInstance()
        {
            if(_model == null)
                _model = new SomModel();
            return _model;
        }

        public static ISomSettings GetSettings()
        {
            if(_model == null)
                _model = new SomModel();
            return _model;
        }
        public static ISourceInfo GetSourceInfo()
        {
            if (_model == null)
                _model = new SomModel();
            return _model;
        }
        public static ITrainDataInfo GetTrainDataInfo()
        {
            if (_model == null)
                _model = new SomModel();
            return _model;
        }
        public string SomName { get; set; }
        public double Alpha { get; set; }
        public int Radius { get; set; }
        public int XNeurons { get; set; }
        public int YNeurons { get; set; }
        public int Iterations { get; set; }
        public string SourcePath { get; set; }
        public bool HasHeader { get; set; }
        public char SplitChar { get; set; }
        public int TrainDataSize { get; set; }
        public int Features { get; set; }
        public void DataUpdated()
        {
            Tracker.CallObservers(this);
        }

        ~SomModel()
        {
            string json = JsonConvert.SerializeObject(this);
            File.WriteAllText("foo.json", json);
        }
    }
}