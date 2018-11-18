from django.urls import path
from . import views

app_name = 'ask'
urlpatterns = [
	path('', views.index, name='index'),
	path('hot/', views.hot, name='hot'),
	path('tag/<tag>/', views.tag, name='tag'),
	path('question/<question_id>/', views.question, name='question'),
	path('login/', views.login, name='login'),
	path('signup/', views.signup, name='signup'),
	path('ask/', views.ask, name='ask')
]
