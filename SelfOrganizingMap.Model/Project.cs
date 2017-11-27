using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;

namespace com_b_velop
{
    public class Project
    {
        public Project() { Maps = new List<Map>();}

        [Key]
        public int Id { get; set; }
        public string Name { get; set; }
        public string Comment { get; set; }
        public double CreateDate { get; set; }
        public double LastEdit { get; set; }
        public ICollection<Map> Maps { get; set; }
    }
}