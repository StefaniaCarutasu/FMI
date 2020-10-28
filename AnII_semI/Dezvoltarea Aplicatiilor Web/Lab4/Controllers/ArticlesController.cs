using Lab4.Models;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.Mvc;

namespace Lab4.Controllers
{
    public class ArticlesController : Controller
    {
        private ArticleDbContext db = new ArticleDbContext();
        //GET: Articles
        public ActionResult Index()
        {
           //var articles = db.Articles.Include("Category");
           //ViewBag.Articles = articles;
            return View();
        }

        //new - GET implicit
        public ActionResult New()
        {
            var categories = from cat in db.Categories
                             select cat;
            ViewBag.Categories = categories;
            return View();
        }
        [HttpPost]
        public ActionResult New(Article article)
        {
            try
            {
                db.Articles.Add(article);
                db.SaveChanges();
                return RedirectToAction("Index");
            }
            catch (Exception e)
            {
                return View();
            }
        }
        //show - GET
        public ActionResult Show(int id)
        {
            Article articol = db.Articles.Find(id);
            ViewBag.Articles = articol;
            ViewBag.Category = articol.Category;
            return View();
        }

      
    }
}