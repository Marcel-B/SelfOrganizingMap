namespace com_b_velop
{
    public interface ISomSettings
    {
        string SomName { get; set; }
        double Alpha { get; set; }
        int Radius { get; set; }
        int XNeurons { get; set; }
        int YNeurons { get; set; }
        int Iterations { get; set; }
    }
}
