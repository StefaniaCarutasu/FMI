using Lab3.Models;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.Mvc;

namespace Lab3.Controllers
{
    public class ArticlesController : Controller
    {
        private ArticleDBContext db = new ArticleDBContext();
        //GET: Articles
        public ActionResult Index()
        {
            var articles = db.Articles.Include("Category");
            ViewBag.Articles = articles;
            return View();
        }

        //show - GET

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
            catch(Exception e)
            {
                return View();
            }
        }


       /* // GET: Aricles
        [ActionName("listare")]
        public ActionResult Index()
        {
            Article[] articles = GetArticles();
            //Adaugam array ul de articole in view
            ViewBag.Articles = articles; 
            return View("Index");
        }

        //Implicit GET
        public ActionResult Show(int id)
        {
            Article[] articles = GetArticles();
            try
            {
                ViewBag.Article = articles[id];
                return View();
            }
            catch(Exception e)
            {
                ViewBag.ErrorMessage = e.Message;
                return View("Error");
            }
        }

        //Implicit GET
        public ActionResult New()
        {
            return View();
        }

        [HttpPost]
        public ActionResult New(Article article)
        {
            // ... cod creare articol ...
            return View("NewPostMethod");
        }

        //GET: Afisarea datelor unui articol pt editare
        public ActionResult Edit(int id)
        {
            ViewBag.id = id;
            return View();
        }
        [HttpPut]
        public ActionResult Edit(Article article)
        {
            // ... cod update articol ...
            return View("EditPutMethod");
        }

        [NonAction]
        public Article[] GetArticles()
        {
            // Instantiem un array de articole
            Article[] articles = new Article[3];
            // Cream articole
            for (int i = 0; i < 3; i++)
            {
                Article article = new Article();
                article.Id = i;
                article.Title = "Articol " + (i + 1).ToString();
                article.Content = "Continut articol " + (i + 1).ToString();
                article.Date = DateTime.Now;

                // Adaugam articolul in array
                articles[i] = article;
            }
            return articles;
        }*/
    }

}