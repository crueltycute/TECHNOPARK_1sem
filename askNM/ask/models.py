from django.db import models
from django.contrib.auth.models import User


class Profile(models.Model):
    user = models.OneToOneField(User, on_delete=models.CASCADE)
    avatar = models.ImageField()
    votes = models.IntegerField(default=0)

    def __str__(self):
        return self.user.username


class Question(models.Model):
    title = models.CharField(max_length=32)
    text = models.TextField()
    author = models.ForeignKey(Profile, on_delete=models.CASCADE)
    creation_time = models.DateTimeField(auto_now_add=True)
    votes = models.IntegerField(default=0)

    def __str__(self):
        return self.title


class Answer(models.Model):
    question = models.ForeignKey(Question, on_delete=models.CASCADE)
    text = models.TextField()
    author = models.ForeignKey(Profile, on_delete=models.CASCADE)
    creation_time = models.DateTimeField(auto_now_add=True)

    def __str__(self):
        return self.text


class Tag(models.Model):
    name = models.CharField(max_length=16)
    questions = models.ManyToManyField(Question)

    def __str__(self):
        return self.name


class QuestionVote(models.Model):
    value = models.IntegerField(default=0)
    question = models.ForeignKey(Question, on_delete=models.CASCADE)
    author = models.ForeignKey(Profile, on_delete=models.CASCADE)


class AnswerVote(models.Model):
    value = models.IntegerField(default=0)
    answer = models.ForeignKey(Answer, on_delete=models.CASCADE)
    author = models.ForeignKey(Profile, on_delete=models.CASCADE)