namespace com_b_velop.Settings
{
    public interface ISettingsViewModel
    {
        string Alpha { get; set; }
        string Iterations { get; set; }
        string ProjectName { get; set; }
        string Radius { get; set; }
        string XNeurons { get; set; }
        string YNeurons { get; set; }
    }
}