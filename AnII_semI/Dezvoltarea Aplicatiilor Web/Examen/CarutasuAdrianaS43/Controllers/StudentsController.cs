using CarutasuAdrianaS43.Models;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.Mvc;

namespace CarutasuAdrianaS43.Controllers
{
    public class StudentsController : Controller
    {
        private Models.AppContext db = new Models.AppContext();
        // GET: Students
        public ActionResult Index()
        {
            var students = db.Students.Include("Domain");
            ViewBag.Students = students;
            if(TempData.ContainsKey("message"))
            {
                ViewBag.Message = TempData["message"];
            }
            return View();
        }

        public ActionResult Show(int id)
        {
            Student student = db.Students.Find(id);
            return View(student);
        }

        public ActionResult New()
        {
            Student student = new Student();

           student.Dom = GetAllDomains();

           return View(student);
        }

        [HttpPost]
        public ActionResult New (Student student)
        {
            student.Dom = GetAllDomains();
           
            try
            {
                if (ModelState.IsValid && student.DataNastere < DateTime.Now.Date)
                {
                    db.Students.Add(student);
                    db.SaveChanges();
                    TempData["message"] = "Studentul cu numele " + student.Nume + " a fost adaugat cu succes";
                    return RedirectToAction("Index");
                }
                else
                {
                    TempData["message"] = "Introduceti o data de nastere valida!";
                    return View(student);
                }
            }
            catch (Exception e)
            {
                return View(student);
            }
        }

        public ActionResult Edit (int id)
        {
            Student student = db.Students.Find(id);
            student.Dom = GetAllDomains();
            return View(student);
        }

        [HttpPut]
        public ActionResult Edit (int id, Student requestStudent)
        {
            requestStudent.Dom = GetAllDomains();

            try
            {
                if(ModelState.IsValid)
                {
                    Student student = db.Students.Find(id);

                    if(TryUpdateModel(student))
                    {
                        student.Nume = requestStudent.Nume;
                        student.Email = requestStudent.Email;
                        student.DataNastere = requestStudent.DataNastere;
                        student.DomainId = requestStudent.DomainId;
                        db.SaveChanges();
                        TempData["message"] = "Studentul cu numele " + requestStudent.Nume + " a fost modificat cu succes!";

                    }
                    return RedirectToAction("Index");
                }
                else
                {
                    return View(requestStudent);
                }
            }
            catch (Exception e)
            {
                return View(requestStudent);
            }
        }

        [HttpDelete]
        public ActionResult Delete(int id)
        {
            Student student = db.Students.Find(id);
            db.Students.Remove(student);
            db.SaveChanges();
            TempData["message"] = "Studentul cu numele " + student.Nume + " a fost sters";
            return RedirectToAction("Index");
        }

        public ActionResult Search (string nume, string domeniu)
        {
           
            var searchName = "";
            var searchDomain = "";

            if (Request.Params.Get("searchName") != null && Request.Params.Get("searchDomain") != null)
            {
                searchName = Request.Params.Get("searchName").Trim();
                searchDomain = Request.Params.Get("searchDomain").Trim();
                List<int> studentsIdName = db.Students.Where(
                    st => st.Nume.Contains(searchName)).Select(s => s.Id).ToList();
                List<int> studentsIdDomain = db.Students.Where(
                    st => st.Domain.Denumire.Contains(searchDomain)).Select(s => s.Id).ToList();
                var students = (IOrderedQueryable<Student>)db.Students.Where(student => studentsIdName.Contains(student.Id) && studentsIdDomain.Contains(student.Id));
                ViewBag.CountStudents = students.Count();
                if (students.Count() > 0)
                    ViewBag.Gasit = 1;
                else if (students.Count() == 0)
                    ViewBag.Gasit = 0;
                ViewBag.StudentsList = students;
            }
            else
            {
                ViewBag.CountStudents = 0;
            }

            return View();

        }

        [NonAction]
        public IEnumerable<SelectListItem> GetAllDomains()
        {
            // generam o lista goala
            var selectList = new List<SelectListItem>();

            // extragem toate domeniile din baza de date
            var domains = from dom in db.Domains
                             select dom;

            // iteram prin domenii
            foreach (var domain in domains)
            {
                // adaugam in lista elementele necesare pentru dropdown
                selectList.Add(new SelectListItem
                {
                    Value = domain.Id.ToString(),
                    Text = domain.Denumire.ToString()
                });
            }

            // returnam lista de domenii
            return selectList;
        }
    }
}