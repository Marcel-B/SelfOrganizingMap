using System;

namespace com_b_velop.Common
{
    public class DialogReadyEventArgs : EventArgs
    {
        public DialogReadyEventArgs(string filepath, char split, bool hasHeader, bool result)
        {
            this.Filepath = filepath;
            this.Result = result;
            this.HasHeader = hasHeader;
            this.Split = split;
        }

        public char Split { get; set; }
        public bool HasHeader { get; set; }
        public string Filepath { get; set; }
        public bool Result { get; set; }
    }
}