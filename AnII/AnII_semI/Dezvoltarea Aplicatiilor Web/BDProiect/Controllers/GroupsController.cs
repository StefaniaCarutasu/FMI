using BDProiect.Models;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.Mvc;

namespace BDProiect.Controllers
{
    public class GroupsController : Controller
    {
        private BDProiect.Models.AppContext db = new BDProiect.Models.AppContext();
        // GET: Groups
        public ActionResult Index()
        {
            if (TempData.ContainsKey("message"))
            {
                ViewBag.message = TempData["message"].ToString();
            }
            var groups = db.Groups;
            ViewBag.Groups = groups;
            return View();
        }

        public ActionResult Show(int id)
        {
            Group group = db.Groups.Find(id);
            ViewBag.Group = group;
            return View(group);
        }

        public ActionResult New()
        {
            return View();
        }

        [HttpPost]
        public ActionResult New (Group gr)
        {
            try
            {
                if(ModelState.IsValid)
                {
                    db.Groups.Add(gr);
                    db.SaveChanges();
                    TempData["message"] = "Grupul a fost adaugat!";
                    return RedirectToAction("Index");
                }
                else
                {
                    return View(gr);
                }
               
            }
            catch (Exception e)
            {
                return View();
            }
        }


    }
}