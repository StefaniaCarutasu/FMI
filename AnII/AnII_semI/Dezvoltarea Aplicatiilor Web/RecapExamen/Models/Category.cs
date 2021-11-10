﻿using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.Linq;
using System.Web;

namespace RecapExamen.Models
{
    public class Category
    {
        [Key]
        public int CategoryId { get; set; }
        [Required(ErrorMessage = "Numele este obligatoriu!")]
        public string CategoryName { get; set; }
        public virtual ICollection<Article> Articles { get; set; }
    }
}