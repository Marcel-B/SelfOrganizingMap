using System.Windows;
using System.Windows.Controls;
using com_b_velop.Common;
using com_b_velop.Enums;

namespace com_b_velop
{
    /// <summary>
    /// Interaktionslogik für MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window, IObserver
    {
        public MainWindow()
        {
            InitializeComponent();
            var app = AppState.GetInstance();
            app.Register(this);
        }

        private void MainWindow_OnTextChanged(object sender, TextChangedEventArgs e)
        {
            this.Title += '*';
        }

        public void Update(ObserverType obj)
        {
            if (obj == ObserverType.TrainDataInfo)
            {
                var info = SomModel.GetTrainDataInfo();
                Title = info.Features + " Spalten - " + info.TrainDataSize + " Zeilen";
            }
        }
    }
}
