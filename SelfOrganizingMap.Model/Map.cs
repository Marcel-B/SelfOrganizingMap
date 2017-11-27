using System.ComponentModel.DataAnnotations;
using System.ComponentModel.DataAnnotations.Schema;

namespace com_b_velop
{
    public class Map
    {
        [Key]
        public int Id { get; set; }
        public string Name { get; set; }
        public string Comment { get; set; }
        public double CreationDate { get; set; }
        public double LastEdit { get; set; }

        //public int ProjectsId { get; set; }
    }
}