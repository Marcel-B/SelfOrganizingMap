using System;

namespace com_b_velop
{
    public class ImportTable : IImportTable
    {
        public IFileReader FileReader { get; set; }
        public char Separator { get; set; }

        public string[][] GetTable(string path, char separator = ';')
        {
            var lines = FileReader.ReadFile(path);
            var returnValue = new string[lines.Length][];
            for (var line = 0; line < lines.Length; line++)
            {
                var cells = lines[line].Split(separator);
                var row = new string[cells.Length];
                Array.Copy(cells, row, cells.Length);
                returnValue[line] = row;
            }
            return returnValue;
        }

        public double[][] ParseTableToDouble(string[][] stringTable)
        {
            var returnValue = new double[stringTable.Length][];
            for (var row = 0; row < stringTable.Length; row++)
            {
                returnValue[row] = new double[stringTable[row].Length];
                for (var col = 0; col < stringTable[row].Length; col++)
                {
                    if (double.TryParse(stringTable[row][col], out var value))
                    {
                        returnValue[row][col] = value;
                    }
                    else
                    {
                        returnValue[row][col] = double.NaN;
                    }
                }
            }
            return returnValue;
        }
    }
}
