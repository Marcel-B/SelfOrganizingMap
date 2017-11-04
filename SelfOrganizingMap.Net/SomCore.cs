using System;
using System.Runtime.InteropServices;

namespace SelfOrganizingMap.Net
{


    public class SomCore
    {
        [DllImport("SelfOrganizingMap.Api.dll")]
        public static extern long PlusFive(long value);


    }
}
