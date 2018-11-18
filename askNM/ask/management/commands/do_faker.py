from random import choice

from django.contrib.auth.models import User
from django.core.management.base import BaseCommand
from faker import Faker

from ask.models import Profile, Question, Tag, Answer, QuestionVote


class Command(BaseCommand):
    USERS_COUNT = 3
    TAGS_COUNT = 3
    QUESTIONS_COUNT = 20
    ANSWERS_COUNT = 3
    QUESTION_VOTES_COUNT = 50
    MAX_TAGS_COUNT_FOR_ONE_QUESTIONS = 3

    fake = Faker()

    def ProfilesGenerator(self):
        for _ in range(0, self.USERS_COUNT):
            u = User.objects.create(username=self.fake.name())
            u.save()
            p = Profile.objects.create(user=u)
            p.save()

    def QuestionsGenerator(self):
        profiles = Profile.objects.all()
        for _ in range(self.QUESTIONS_COUNT):
            q = Question()
            q.author = choice(profiles)
            q.title = self.fake.text(16)
            q.text = self.fake.text(128)
            q.save()

    def TagsGenerator(self):
        questions = Question.objects.all()
        for _ in range(self.TAGS_COUNT):
            t = Tag.objects.create(name=self.fake.color_name())
            for _ in range(self.QUESTIONS_COUNT):
                t.questions.add(choice(questions))
            t.save()

    def AnswersGenerator(self):
        profiles = Profile.objects.all()
        questions = Question.objects.all()
        for _ in range(self.ANSWERS_COUNT):
            a = Answer()
            a.author = choice(profiles)
            a.question = choice(questions)
            a.text = self.fake.text(128)
            a.save()

    def QuestionVotesGenerator(self):
        profiles = Profile.objects.all()
        questions = Question.objects.all()
        for question in questions:
            for _ in range(self.USERS_COUNT):
                v = QuestionVote()
                v.author = choice(profiles)
                v.question = question
                v.value = choice([-1, 1])
                v.save()

    def Generator(self):
        self.ProfilesGenerator()
        self.QuestionsGenerator()
        self.TagsGenerator()
        self.AnswersGenerator()
        self.QuestionVotesGenerator()

    def handle(self, *args, **options):
        self.Generator()
