from django.db.models import Count

from .models import Profile, Question, Tag
from . import paginator


def new_questions(request):
    return paginator.paginate(Question.objects.all().order_by("-creation_time"), 3, request)


def hot_questions(request):
    return paginator.paginate(Question.objects.all().order_by("-votes"), 3, request)


def popular_tags(request):
    tags = Tag.objects.annotate(questions_count=Count("questions")).order_by("-questions_count")[:3]
    return tags


def best_members(request):
    members = Profile.objects.order_by("-votes")[:3]
    return members


def question_by_id(question_id, request):
    question = Question.objects.get(id=question_id)
    return question


def questions_by_tag(tag, request):
    tag = Tag.objects.get(name=tag)
    return tag.questions.all()


def answers_by_questions(question, request):
    answers = paginator.paginate(Question.objects.order_by("-votes"), 2, request)
    return answers
