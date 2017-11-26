using System;
using System.Linq;
using com_b_velop;
using NUnit.Framework;

namespace SelfOrganizingMap.Net.UnitTests
{
    [TestFixture]
    public class ProjectContextTest
    {
        [Test]
        public void TestProject()
        {
            var db = new ProjectContext();
            var pr = new Project();
            pr.Name = "Hallo";
            pr.CreateDate = (Int32)(DateTime.UtcNow.Subtract(new DateTime(1970, 1, 1))).TotalSeconds;
            db.Projects.Add(pr);
            db.SaveChanges();
        }

        [Test]
        public void TestProject2()
        {
            var db = new ProjectContext();
            var pr = (from p in db.Projects
                select p).FirstOrDefault();

            Assert.IsNotNull(pr);
            Console.WriteLine(pr.Name);

            var cnt = db.Projects;
            foreach (var project in cnt)
            {
                Console.WriteLine($"{project.Id}: {project.Name} from {project.CreateDate}");
            }
        }
    }
}