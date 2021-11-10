using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.Linq;
using System.Web;

namespace CarutasuAdrianaS43.Models
{
    public class Subject
    {
        [Key]
        public int Id { get; set; }

        [Required(ErrorMessage = "Introduceti un nume al subiectului")]
        public string NumeSub { get; set; }

        public virtual ICollection<Meeting> Meetings { get; set; }
    }
}