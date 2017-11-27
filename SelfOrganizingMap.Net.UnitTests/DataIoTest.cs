using NUnit.Framework;

namespace SelfOrganizingMap.Net.UnitTests
{
    [TestFixture]
    public class DataIoTest
    {
        [Test]
        [TestCase(@"C: \Users\marce\Documents\source\SelfOrganizingMap\SelfOrganizingMap.Net.UnitTests\test.csv", new[]{1.1, 2.2, 3.3, 5.5, 5.5, 3.3})]
        [TestCase("test.cs", new[]{1.1, 2.2, 3.3, 5.5, 5.5, 3.3})]
        public void TestMethod(string filePath, double[] expected)
        {

        }
    }
}
