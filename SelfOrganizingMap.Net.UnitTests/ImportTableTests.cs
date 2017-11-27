using System;
using com_b_velop;
using NSubstitute;
using NUnit.Framework;

namespace SelfOrganizingMap.Net.UnitTests
{
    [TestFixture]
    public class ImportTableTests
    {
        [Test]
        public void ConstructorTest()
        {
            var sut = new ImportTable();

            Assert.IsInstanceOf<ImportTable>(sut);
            Assert.IsInstanceOf<IImportTable>(sut);
        }

        [Test]
        public void Import_ImportTable_AsStrinig()
        {
            var b = new string[2];
            b[0] = "Col_1;Col_2;Col_3";
            b[1] = "1,5;5,5;9,8";

            var sut = new ImportTable();
            var stub = Substitute.For<IFileReader>();
            stub.ReadFile("test.txt").Returns(b);
            sut.FileReader = stub;

            var actual = sut.GetTable("test.txt");

            var expected = new string[2][];
            expected[0] = new string[3];
            expected[1] = new string[3];
            expected[0][0] = "Col_1";
            expected[0][1] = "Col_2";
            expected[0][2] = "Col_3";
            expected[1][0] = "1,5";
            expected[1][1] = "5,5";
            expected[1][2] = "9,8";

            Assert.IsNotNull(actual);
            CollectionAssert.AreEqual(expected, actual);
  
        }

        [Test]
        public void ImportTable_ParseTable()
        {
            var values = new string[2][];
            values[0] = new string[3];
            values[1] = new string[3];
            values[0][0] = "Col_1";
            values[0][1] = "Col_2";
            values[0][2] = "Col_3";
            values[1][0] = "1,5";
            values[1][1] = "5,5";
            values[1][2] = "9,8";


            var v = new string[1][];
            v[0] = new string[3];
            v[0][0] = "1,5";
            v[0][1] = "5,5";
            v[0][2] = "9,8";

            var expected = new double[1][];
            expected[0] = new double[3];
            expected[0][0] = 1.5;
            expected[0][1] = 5.5;
            expected[0][2] = 9.8;

            var sut = new ImportTable();

            var actual = sut.ParseTableToDouble(v);

            CollectionAssert.AreEqual(expected, actual);
        }
    }
}