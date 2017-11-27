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
            pr.CreateDate = DateTime.Now.ToOADate();
            pr.LastEdit = DateTime.Now.ToOADate();
            pr.Comment = "a little comment";
            

            var map = new Map
            {
                Name = "First try",
                LastEdit = DateTime.Now.ToOADate(),
                CreationDate = DateTime.Now.ToOADate(),
                Comment = "Gnihii"
            };

            pr.Maps.Add(map);
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