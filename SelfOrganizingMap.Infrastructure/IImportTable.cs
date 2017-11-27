namespace com_b_velop
{
    public interface IImportTable
    {
        IFileReader FileReader { get; set; }
        char Separator { get; set; }

        string[][] GetTable(string path, char separator = ';');
        double[][] ParseTableToDouble(string[][] stringTable);
    }
}