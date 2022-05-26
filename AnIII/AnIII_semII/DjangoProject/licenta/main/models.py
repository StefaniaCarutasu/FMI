from django.db import models
from django.contrib.auth.models import User

# Create your models here.
# Model for the lecture hall
class LectureHall(models.Model):
    name = models.CharField(max_length = 30)
    floor = models.IntegerField()
    maxCapacity = models.IntegerField()

    @classmethod
    def getAllLectureHalls(cls):
        objectlist = LectureHall.objects.all()

        hallsTuple = [(object.id, object.name) for object in objectlist]

        return hallsTuple  

# Model for the course
class Course(models.Model):
    professor = models.ForeignKey(User, on_delete=models.CASCADE)
    topic = models.CharField(max_length=50)
    description = models.CharField(max_length=200)
    lectureHall = models.ForeignKey(LectureHall, on_delete=models.CASCADE)
    date = models.DateTimeField()
    startTime = models.TimeField()
    duration = models.IntegerField()


# Model for professor profile
class Professor(models.Model):
    userId = models.OneToOneField(User, on_delete=models.CASCADE)
    description = models.CharField(max_length=200)
    specialization = models.CharField(max_length=50)
    title = models.CharField(max_length=50)

class Student(models.Model):
    userId = models.ForeignKey(User, on_delete=models.CASCADE)
    grade = models.IntegerField()
    school= models.CharField(max_length=50)
    city = models.CharField(max_length=50)
    county = models.CharField(max_length=50)





