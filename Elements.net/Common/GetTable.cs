using System.Data;
using System.IO;
using System.Linq;
using System.Threading.Tasks;
using com_b_velop.Enums;

namespace com_b_velop.Common
{
    public class GetTable
    {
        public static async Task<DataTable> GetDataTable(string source, bool header, char split)
        {
            var table = new DataTable(Path.GetFileNameWithoutExtension(source));
            var file = new FileInfo(source);
            using (var fr = file.OpenText())
            {
                if (header)
                {
                    var headers = fr.ReadLine().Split(split).ToList();
                    headers.ForEach(head => table.Columns.Add(new DataColumn(head, typeof(string))));
                }
                else
                {
                    var firstLine = fr.ReadLine().Split(split).ToArray<object>();
                    foreach (var o in firstLine)
                    {
                        table.Columns.Add(new DataColumn());
                    }
                    table.Rows.Add(firstLine);
                }
                while (!fr.EndOfStream)
                {
                    var line = await fr.ReadLineAsync();
                    var cells = line.Split(split).ToArray<object>();
                    table.Rows.Add(cells);
                }
            }
            return table;
        }
    }
}