using System.Data;

namespace com_b_velop.SourceView
{
    public interface ISourceViewModel
    {
        string Input { get; set; }
        DataTable Table { get; set; }
    }
}