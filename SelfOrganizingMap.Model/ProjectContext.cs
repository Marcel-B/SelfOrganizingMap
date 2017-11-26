using System.Collections.Generic;
using System.Data.Entity;

namespace com_b_velop
{
    public class ProjectContext : DbContext
    {
        public ProjectContext () : base("TestContext") {} //the name of your c
        public DbSet<Project> Projects { get; set; }   
    }
}