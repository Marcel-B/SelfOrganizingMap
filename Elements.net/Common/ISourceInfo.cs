namespace com_b_velop.Common
{
    public interface ISourceInfo
    {
        bool HasHeader { get; set; }
        string SourcePath { get; set; }
        char SplitChar { get; set; }
    }
}