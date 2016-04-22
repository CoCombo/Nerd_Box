from django.conf.urls import patterns, url
from combo import views

urlpatterns = patterns('',
	url(r'^$', views.index, name = 'index'),
	url(r'^shit/', views.shit, name = 'shit'),
)