using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.Linq;
using System.Web;
using System.Web.Mvc;

namespace CarutasuAdrianaS43.Models
{
    public class Meeting
    {
        [Key]
        public int Id { get; set; }

        [Required(ErrorMessage = "Titlul conferintei este obligatoriu!")]
        public string TitluMeet { get; set; }

        [Required(ErrorMessage = "Descrierea conferintei este obligatorie!")]
        [StringLength(15, ErrorMessage = "Descrierea nu poate avea mai mult de 15 caractere")]
        public string Content { get; set; }

        [Required(ErrorMessage = "Introduceti o data pentru conferinta")]
        public DateTime DataMeet { get; set; }

        [Required(ErrorMessage = "Subiectul este obligatoriu!")]
        public int SubjectId { get; set; }
        public virtual Subject Subject { get; set; }

        public IEnumerable<SelectListItem> Subj { get; set; }
    }
}