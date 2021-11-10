using BDProiect.Models;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.Mvc;

namespace BDProiect.Controllers
{
    public class PostsController : Controller
    {
        private Models.AppContext db = new Models.AppContext();
        // GET: Posts
        public ActionResult Index()
        {
            var posts = db.Posts.Include("Group");
            ViewBag.Posts = posts;
            if (TempData.ContainsKey("message"))
            {
                ViewBag.Message = TempData["message"];
            }
            return View();
        }

        public ActionResult Show(int id)
        {
            Post post = db.Posts.Find(id);
            ViewBag.Post = post;
            ViewBag.Group = post.Group;

            return View();
        }

        public ActionResult New()
        {
            Post post = new Post();
            return View(post);
        }

        [HttpPost]
        public ActionResult New (Post post)
        {
            post.Date = DateTime.Now;
            post.GroupId = 1;
            try
            {
                if(ModelState.IsValid)
                {
                    db.Posts.Add(post);
                    db.SaveChanges();
                    TempData["message"] = "Postarea a fost adaugata";
                    return RedirectToAction("Index");
                }
                else
                {
                    return View(post);
                }
               
            }
            catch (Exception e)
            {
                return View(post);
            }
        }

        public ActionResult Edit(int id)
        {
            Post post = db.Posts.Find(id);
            return View(post);
        }

        [HttpPut]
        public ActionResult Edit(int id, Post requestPost)
        {
            try
            {
                Post post = db.Posts.Find(id);
                if(TryUpdateModel(post))
                {
                    post.Content = requestPost.Content;
                    post.Date = requestPost.Date;
                    post.GroupId = requestPost.GroupId;
                    db.SaveChanges();
                    TempData["message"] = "Postarea a fost editat cu succes";
                    return RedirectToAction("Index");

                }
                return View(requestPost);
            }
            catch(Exception e)
            {
                return View(requestPost);
            }
        }


        [HttpDelete]
        public ActionResult Delete(int id)
        {
            Post post = db.Posts.Find(id);
            db.Posts.Remove(post);
            db.SaveChanges();
            return RedirectToAction("Index");
        }


    }
}