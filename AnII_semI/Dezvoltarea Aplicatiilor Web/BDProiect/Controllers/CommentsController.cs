using BDProiect.Models;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.Mvc;

namespace BDProiect.Controllers
{
    public class CommentsController : Controller
    {

        private Models.AppContext db = new Models.AppContext();
        // GET: Comments
        public ActionResult Index()
        {
            return View();
        }

        public ActionResult New()
        {
            Comment comment = new Comment();
            return View(comment);
        }

        [HttpPost]
        public ActionResult New(Comment comment)
        {
            comment.Date = DateTime.Now;
            try
            {
                db.Comments.Add(comment);
                db.SaveChanges();
                return Redirect("/Posts/Show/" + comment.PostId);
            }
            catch(Exception e)
            {
                ViewBag.ErrorMessage = e.Message;
                return Redirect("/Posts/Show/" + comment.PostId);
            }
        }

        [HttpDelete]

        public ActionResult Delete(int id)
        {
            Comment comment = db.Comments.Find(id);
            db.Comments.Remove(comment);
            db.SaveChanges();
            return Redirect("/Posts/Show/" + comment.PostId);
        }

        public ActionResult Edit(int id)
        {
            Comment comment = db.Comments.Find(id);
            ViewBag.Comment = comment;
            return View();
        }

        [HttpPut]
        public ActionResult Edit(int id, Comment reqComment)
        {
            try
            {
                Comment comm = db.Comments.Find(id);
                if(TryUpdateModel(comm))
                {
                    comm.Content = reqComment.Content;
                    db.SaveChanges();
                }
                return Redirect("/Posts/Show/" + comm.PostId);
            }
            catch(Exception e)
            {
                return View();
            }
        }

    }
}