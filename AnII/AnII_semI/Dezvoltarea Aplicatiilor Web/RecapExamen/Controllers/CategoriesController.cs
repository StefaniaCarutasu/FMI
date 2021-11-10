using RecapExamen.Models;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.Mvc;

namespace RecapExamen.Controllers
{
    public class CategoriesController : Controller
    {
        private Models.AppContext db = new Models.AppContext();
        // GET: Categories
        public ActionResult Index()
        {
            if (TempData.ContainsKey("message"))
            {
                ViewBag.Message = TempData["message"].ToString();
            }

            var categories = from category in db.Categories
                             orderby category.CategoryName
                             select category;

            ViewBag.Categories = categories;
            return View();
        }

        public ActionResult Show(int id)
        {
            Category category = db.Categories.Find(id);
            return View(category);
        }

        public ActionResult New()
        {
            return View();
        }

        [HttpPost]
        public ActionResult New(Category categ)
        {
            try
            {
                if (ModelState.IsValid)
                {
                    db.Categories.Add(categ);
                    db.SaveChanges();
                    TempData["message"] = "Categoria a fost adaugata!";
                    return RedirectToAction("Index");
                }
                else
                {
                    return View(categ);
                }
            }
            catch (Exception e)
            {
                return View(categ);
            }
        }

        public ActionResult Edit(int id)
        {
            Category category = db.Categories.Find(id);
            return View(category);
        }

        [HttpPut]
        public ActionResult Edit (int id, Category requestCateg)
        {
            try
            {
                Category category = db.Categories.Find(id);

                if(TryUpdateModel(category))
                {
                    category.CategoryName = requestCateg.CategoryName;
                    db.SaveChanges();
                    TempData["message"] = "Categoria a fost modificata!";
                    return RedirectToAction("Index");
                }
                return View(requestCateg);
            }
            catch (Exception e)
            {
                return View(requestCateg);
            }
        }

        [HttpDelete]
        public ActionResult Delete (int id)
        {
            Category categ = db.Categories.Find(id);
            db.Categories.Remove(categ);
           
            TempData["message"] = "Categoria a fost stearsa!";
            db.SaveChanges();
            return RedirectToAction("Index");
        }
    }
}