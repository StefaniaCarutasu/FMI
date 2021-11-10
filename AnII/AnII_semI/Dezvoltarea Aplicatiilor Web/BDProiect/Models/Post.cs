using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.Linq;
using System.Web;

namespace BDProiect.Models
{
    public class Post
    {
        [Key]
        public int PostId { get; set; }
        [Required(ErrorMessage = "Continutul este obligatoriu!")]
        [DataType(DataType.MultilineText)]
        public string Content { get; set; }
        public DateTime Date { get; set; }

        public int GroupId { get; set; }
        public virtual Group Group { get; set; }

        public virtual ICollection<Comment> Comments { get; set; }
    }
}