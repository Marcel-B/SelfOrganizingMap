using com_b_velop;

namespace SelfOrganizingMap.Net
{
    public class SomData : ISomSettings
    {
        public string SomName { get; set; }
        public double Alpha { get; set; }
        public int Radius { get; set; }
        public int XNeurons { get; set; }
        public int YNeurons { get; set; }
        public int Iterations { get; set; }
    }
}