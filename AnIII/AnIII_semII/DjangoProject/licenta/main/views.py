from django.shortcuts import render, redirect
from  .forms import RegisterForm, CourseForm, LectureHallForm
from django.contrib.auth import login, logout, authenticate
from django.contrib.auth.decorators import login_required

from django.views.generic.list import ListView
from django.views.generic.detail import DetailView


from .models import Course

# Create your views here.
@login_required(login_url='/login')
def home(request):
    return render(request, 'main/home.html')

# register form
def register(request):
    if request.method == 'POST':
        form = RegisterForm(request.POST)
        if form.is_valid():
            user = form.save()
            login(request, user)

            return redirect('/home')
    else:
        form = RegisterForm()

    return render(request, 'registration/register.html', {"form": form})


# # login form
# def login(request):
#     if request.method == 'POST':
#         form = LoginForm(request.POST)
#         if form.is_valid():
#             login(request, user)

#             return redirect('/home')
#     else:
#         form = LoginForm()

#     return render(request, 'registration/login.html', {"form": form})




# new lecture hall form
@login_required(login_url='/login')
def new_lecture_hall(request):
    if request.method == 'POST':
        form = LectureHallForm(request.POST)
        
        if form.is_valid():
            lecture_hall = form.save()

            return redirect('/home')
        
    else:
        form = LectureHallForm()

    return render(request, 'main/new_lecture_hall.html', {"form": form})

# COURSES CRUD
# list courses
# @login_required(login_url='/login')
class CoursesList(ListView):
    model = Course
    template_name = 'main/list-courses.html'

# new course form
@login_required(login_url='/login')
def new_course(request):
    if request.method == 'POST':
        form = CourseForm(request.POST)
        
        if form.is_valid():
            course = form.save(commit=False)
            course.professor = request.user
            course.save()

            return redirect('/home')
        
    else:
        form = CourseForm()

    return render(request, 'main/new_course.html', {"form": form})

class ViewCourse(DetailView):
    model = Course

    context_object_name = "course"

     # override context data
    def get_context_data(self, *args, **kwargs):
        context = super(GeeksDetailView,
             self).get_context_data(*args, **kwargs)
        # add extra field 
        context["lectureHall"] = get_object_or_404(LectureHall, id=context["course"].lectureHall)      
        return context


