using System.Collections.Generic;
using System.IO;
using System.Threading.Tasks;

namespace com_b_velop
{
    public class FileReader : IFileReader
    {
        public string[] ReadFile(string path)
        {
            var file = new FileInfo(path);
            if (file.Exists)
            {
                var l = new List<string>();
                using (var fr = file.OpenText())
                {
                    while (!fr.EndOfStream)
                    {
                        var line = fr.ReadLine();
                        l.Add(line);
                    }
                }
                return l.ToArray();
            }
            return null;
        }
    }
}