using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.Linq;
using System.Web;

namespace BDProiect.Models
{
    public class Group
    {
        [Key]
        public int GroupId { get; set; }

        [Required(ErrorMessage = "Numele Grupului este obligatoriu!")]
        [StringLength(30, ErrorMessage = "Numele grupului nu poate avea mai mult de 30 de caractere")]
        public string GroupName { get; set; }

        [DataType(DataType.MultilineText)]
        [StringLength(100, ErrorMessage = "Descrierea grupului nu poate avea mai mult de 100 de caractere")]
        public string GroupDescription { get; set; }

        public virtual ICollection<Post> Posts { get; set; }
    }
}