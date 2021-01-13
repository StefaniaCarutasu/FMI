using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.Linq;
using System.Web;
using System.Web.Mvc;

namespace CarutasuAdrianaS43.Models
{
    public class Student
    {
        [Key]
        public int Id { get; set; }

        [Required(ErrorMessage = "Numele studentului este obligatoriu!")]
        public string Nume { get; set; }

        [Required(ErrorMessage = "Email-ul studentului este obligatoriu!")]
        [MaxLength(25, ErrorMessage = "Email-ul nu poate avea mai mult de 25 de caractre!")]
        public string Email { get; set; }

        [Required(ErrorMessage = "Data nasterii este obligatorie!")]
        public DateTime DataNastere { get; set; }

        [Required(ErrorMessage = "Domeniul este obligatoriu!")]
        public int DomainId { get; set; }
        public virtual Domain Domain { get; set; } 

        public IEnumerable<SelectListItem> Dom { get; set; }

    }
}