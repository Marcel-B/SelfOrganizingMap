using System;
using System.Collections.ObjectModel;
using com_b_velop.Common;
using Prism.Commands;

namespace com_b_velop.OpenFile
{
    public interface IOpenFileViewModel
    {
        bool Fully { get; set; }
        bool? HasHeader { get; set; }
        DelegateCommand OkCommand { get; set; }
        DelegateCommand OpenSource { get; set; }
        string SourcePath { get; set; }
        ObservableCollection<IImportRow> SourceTable { get; set; }
        string SourceText { get; set; }
        char Split { get; set; }

        event EventHandler<DialogReadyEventArgs> DialogRdy;

        void Ok();
        void OpenFile();
    }
}