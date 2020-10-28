using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.Data.Entity;
using System.Linq;
using System.Web;

namespace Lab3.Models
{
    public class Article
    {
        [Key]
        public int Id { get; set; }
        [Required]
        public string Title { get; set; }
        [Required]
        public string Content { get; set; }
        public DateTime Date { get; set; }
        public int CategoryId { get; set; }
        public virtual Category Category { get; set; }
    }
    public class ArticleDBContext : DbContext
    {
        public ArticleDBContext() : base("DBConnectionString") { }
        public DbSet<Article> Articles { get; set; }
        public DbSet<Category> Categories { get; set; }
    }

}