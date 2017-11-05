namespace com_b_velop
{
    public interface ISourceInfo
    {
        string SourcePath { get; set; }
        bool HasHeader { get; set; }
        char SplitChar { get; set; }
    }
}