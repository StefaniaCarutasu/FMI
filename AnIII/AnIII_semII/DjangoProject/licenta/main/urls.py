from django.urls import path
from . import views
from django.contrib.auth.views import LoginView
from . import forms
from .views import CoursesList

urlpatterns = [
    path("", views.home, name='home'),
    path("home", views.home, name='home'),
    path("register", views.register, name='register'),
    path("new-course", views.new_course, name='new-course'),
    path("new-lecture-hall", views.new_lecture_hall, name='new-lecture-hall'),
    # path('login/', LoginView.as_view( template_name="registration/login.html",  authentication_form=forms.LoginForm ), name='login')
     path(
        'login/', LoginView.as_view(
            template_name="registration/login.html",
            authentication_form=forms.UserLoginForm
            ),
        name='login'
        ),
     path("list-courses", CoursesList.as_view()),
]
