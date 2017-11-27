using System;
using System.IO;

namespace com_b_velop.Common
{
    public class SomModel
    {
        private static SomModel _model;
        private ValueTracker Tracker { get; }

        private SomModel()
        {
        }
        public static SomModel GetInstance()
        {
            if(_model == null)
                _model = new SomModel();
            return _model;
        }

 
        public static SourceInfo GetSourceInfo()
        {
            if (_model == null)
                _model = new SomModel();
            return null;
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

        ~SomModel()
        {
        }
    }
}