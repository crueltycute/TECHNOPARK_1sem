from django.shortcuts import render

from . import model_manager


def index(request):
	context = {
		'title': "New Questions",
		'questions_to_show': model_manager.new_questions(request),
		'questions_switcher': {
			'title': "Hot Questions",
			'href': "/hot",
		},
		'popular_tags': model_manager.popular_tags(request),
		'best_members': model_manager.best_members(request),
	}

	return render(request, 'index.html', context)


def hot(request):
	context = {
		'title': "Hot Questions",
		'questions_to_show': model_manager.hot_questions(request),
		'questions_switcher': {
			'title': "New Questions",
			'href': "/",
		},
		'popular_tags': model_manager.popular_tags(request),
		'best_members': model_manager.best_members(request),
	}

	return render(request, 'index.html', context)


def tag(request, tag):
	title = "Tag: %s" % tag

	context = {
		'title': title,
		'questions_to_show': model_manager.questions_by_tag(tag, request),
		'questions_switcher': {
			'title': "",
			'href': "",
		},
		'popular_tags': model_manager.popular_tags(request),
		'best_members': model_manager.best_members(request),
	}

	return render(request, 'index.html', context)


def question(request, question_id):
	question = model_manager.question_by_id(question_id, request)

	context = {
		'question': question,
		'answers': model_manager.answers_by_questions(question, request),
		'popular_tags': model_manager.popular_tags(request),
		'best_members': model_manager.best_members(request),
	}

	return render(request, 'question.html', context)


def login(request):
	context = {
		'popular_tags': model_manager.popular_tags(request),
		'best_members': model_manager.best_members(request),
	}

	return render(request, 'login.html', context)


def signup(request):
	context = {
		'popular_tags': model_manager.popular_tags(request),
		'best_members': model_manager.best_members(request),
	}

	return render(request, 'signup.html', context)


def ask(request):
	context = {
		'popular_tags': model_manager.popular_tags(request),
		'best_members': model_manager.best_members(request),
	}

	return render(request, 'ask.html', context)
