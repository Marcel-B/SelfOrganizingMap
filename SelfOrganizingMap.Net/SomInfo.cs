using System.Runtime.InteropServices;

namespace SelfOrganizingMap.Net
{
    [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Ansi)]
    public struct SomInfo
    {
        public long MapX;
        public long MapY;
        public long MapW;
        public long IterationMax;
        public long NeighborStart;
        public long TraindataSize;
        public double Alpha;
    }
}