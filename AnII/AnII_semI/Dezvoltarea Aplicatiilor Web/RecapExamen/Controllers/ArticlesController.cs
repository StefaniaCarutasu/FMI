using RecapExamen.Models;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.Mvc;

namespace RecapExamen.Controllers
{
    public class ArticlesController : Controller
    {
        private Models.AppContext db = new Models.AppContext();
        // GET: Articles
        public ActionResult Index()
        {
            var articles = db.Articles.Include("Category");
            ViewBag.Articles = articles;
            if (TempData.ContainsKey("message"))
                ViewBag.Message = TempData["message"].ToString();
            return View();
        }

        public ActionResult Show(int id)
        {
            Article article = db.Articles.Find(id);

            return View(article);
        }

        public ActionResult New()
        {
            Article article = new Article();

            article.Categ = GetAllCategories();

            return View(article);
        }

        [HttpPost]
        public ActionResult New(Article article)
        {
            article.Date = DateTime.Now;
            try
            {
                if(ModelState.IsValid)
                {
                    db.Articles.Add(article);
                    db.SaveChanges();
                    TempData["message"] = "Articolul a fost adaugat";
                    return RedirectToAction("Index");
                }
                else
                {
                    article.Categ = GetAllCategories();
                    return View(article);
                }
            }
            catch(Exception e)
            {
                article.Categ = GetAllCategories();
                return View(article);
            }

        }

        public ActionResult Edit(int id)
        {
            Article article = db.Articles.Find(id);
            article.Categ = GetAllCategories();

            return View(article);
        }

        [HttpPut]
        public ActionResult Edit (int id, Article requestArticle)
        {
            //requestArticle.Categ = GetAllCategories();
            try
            {
                if(ModelState.IsValid)
                {
                    Article article = db.Articles.Find(id);
                    if(TryUpdateModel(article))
                    {
                        article.Title = requestArticle.Title;
                        article.Content = requestArticle.Content;
                        article.CategoryId = requestArticle.CategoryId;
                        db.SaveChanges();
                        TempData["message"] = "Articolul a fost modificat cu succes!";
                    }
                    return RedirectToAction("Index");
                }
                else
                {
                    requestArticle.Categ = GetAllCategories();
                    return View(requestArticle);
                }
            }
            catch (Exception e)
            {
                requestArticle.Categ = GetAllCategories();
                return View(requestArticle);
            }
        }

        [HttpDelete]
        public ActionResult Delete (int id)
        {
            Article article = db.Articles.Find(id);
            db.Articles.Remove(article);
            db.SaveChanges();
            TempData["message"] = "Articolul a fost sters!";
            return RedirectToAction("Index");
        }

        [NonAction]
        public IEnumerable<SelectListItem> GetAllCategories()
        {
            // generam o lista goala
            var selectList = new List<SelectListItem>();

            // extragem toate categoriile din baza de date
            var categories = from cat in db.Categories
                             select cat;

            // iteram prin categorii
            foreach (var category in categories)
            {
                // adaugam in lista elementele necesare pentru dropdown
                selectList.Add(new SelectListItem
                {
                    Value = category.CategoryId.ToString(),
                    Text = category.CategoryName.ToString()
                });
            }

            // returnam lista de categorii
            return selectList;
        }
    }
}