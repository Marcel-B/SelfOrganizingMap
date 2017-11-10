using System;
using System.Collections.Generic;
using System.IO;
using System.Text;
using System.Threading.Tasks;

namespace SelfOrganizingMap.Net
{
    public class DataIo
    {
        public async Task<double[]> ImportData(string filePath)
        {


            var fi = new FileInfo(filePath);
            if (!fi.Exists)
            {
                throw new FileNotFoundException($"{filePath} doesn't exists");
            }
            List<double> result = new List<double>();
            try
            {
                using (var fr = fi.OpenText())
                {
                    List<double> tmpLine;
                    double tmp;
                    while (!fr.EndOfStream)
                    {
                        tmpLine = new List<double>();
                        var line = await fr.ReadLineAsync();
                        var fields = line.Split(';');
                        for (int index = 0; index < fields.Length; index++)
                        {
                            if(double.TryParse(fields[index], out tmp))
                                tmpLine.Add(tmp);
                        }
                        if(tmpLine.Count == fields.Length)
                            result.AddRange(tmpLine);
                    }
                }
            }
            catch (Exception ex)
            {

            }
            return result.ToArray();
        }
    }
}
