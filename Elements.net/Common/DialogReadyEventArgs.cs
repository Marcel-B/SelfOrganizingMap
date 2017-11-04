using System;

namespace Elements.net.Common
{
    public class DialogReadyEventArgs : EventArgs
    {
        public DialogReadyEventArgs(string filepath, bool result)
        {
            this.Filepath = filepath;
            this.Result = result;
        }
        public string Filepath { get; set; }
        public bool Result { get; set; }
    }
}