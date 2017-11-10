using System;
using System.Runtime.InteropServices;
using com_b_velop;

namespace SelfOrganizingMap.Net
{


    public class SomCore
    {
        [DllImport("SelfOrganizingMap.Api.dll")]
        public static extern long PlusFive(long value);

        public static void StartIteration(ISomSettings settings)
        {
            DataIo foo = new DataIo();
        }

    }
}
