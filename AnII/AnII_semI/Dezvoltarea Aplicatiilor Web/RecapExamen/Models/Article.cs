using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.Linq;
using System.Web;
using System.Web.Mvc;

namespace RecapExamen.Models
{
    public class Article
    {
        [Key]
        public int Id { get; set; }
        [Required(ErrorMessage = "Titlul articolului este obligatoriu!")]
        [StringLength(100, ErrorMessage = "Titlul nu poate depasi 100 de caractere")]
        public string Title { get; set; }
        [Required(ErrorMessage = "Continutul articolului este obligatoriu!")]
        [DataType(DataType.MultilineText)]
        public string Content { get; set; }
        public DateTime Date { get; set; }

        public int CategoryId { get; set; }
        public virtual Category Category { get; set; }
        public IEnumerable<SelectListItem> Categ { get; set; }
    }
}