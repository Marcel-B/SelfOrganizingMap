namespace com_b_velop.Common
{
    public class SourceInfo : ISourceInfo
    {
        public string SourcePath { get; set; }
        public bool HasHeader { get; set; }
        public char SplitChar { get; set; }
    }
}