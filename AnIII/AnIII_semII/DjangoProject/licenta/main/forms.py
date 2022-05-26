from django import forms 
from django.contrib.auth.forms import UserCreationForm, AuthenticationForm, UsernameField
from django.contrib.auth.models import User
from .models import Course, LectureHall
import datetime


# class LoginForm(AuthenticationForm):
#     def __init__(self, *args, **kwargs):
#         super(LoginForm, self).__init__(*args, **kwargs)
#     class Meta:
#         model = User
#         labels = {"username": "Email", "password": "Parola"}
#         fields = ["email", "password"]


class UserLoginForm(AuthenticationForm):
    def __init__(self, *args, **kwargs):
        super(UserLoginForm, self).__init__(*args, **kwargs)

    username = UsernameField(widget=forms.TextInput(
        attrs={'class': 'form-control', 'placeholder': '', 'id': 'hello'}))
    password = forms.CharField(widget=forms.PasswordInput(
        attrs={
            'class': 'form-control',
            'placeholder': '',
            'id': 'hi',
        }
))


class RegisterForm(UserCreationForm):
    # email = forms.EmailField(required=True)

    class Meta:
        model = User
        labels = {"username": "Email", "password1": "Parola", "password2": "Repetati parola"}
        fields = ["username", "email", "password1", "password2"]


class CourseForm(forms.ModelForm):
    def __init__(self, *args, **kwargs):
        super().__init__(*args, **kwargs)
        self.fields['topic'].label = 'Tematica'
        self.fields['description'].label = 'Descriere'
        self.fields['date'].label = 'Data'
        self.fields['startTime'].label = 'Ora de inceput'
        self.fields['duration'].label = 'Durata'
        self.fields['lectureHall'].label = 'Sala de curs'
        self.fields['lectureHall'].choices = LectureHall.getAllLectureHalls()


    date = forms.DateField(required=False, widget=forms.DateInput(attrs={'type': 'date', 'min': datetime.date.today()}), help_text='Future date only.')
    startTime = forms.TimeField(required=False, widget=forms.TimeInput(attrs={'type': 'time'}))

    class Meta:
        model = Course
        fields = ["topic", "description", "date", "startTime", "duration", "lectureHall"]


class LectureHallForm(forms.ModelForm):
    class Meta:
        model = LectureHall
        fields = ["name", "floor", "maxCapacity"]