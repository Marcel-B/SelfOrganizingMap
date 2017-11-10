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
            var sut = new DataIo();

            var actual = sut.ImportData(filePath).Result;
            Assert.AreEqual(expected, actual, "Import data doesn't the same");

            //for (int i = 0; i < expected.Length; i++)
            //{
            //    Assert.AreEqual(expected[i], actual[i], "Import data doesn't the same");

            //}

        }
    }
}
