from django.conf.urls import patterns, url
from combo import views

urlpatterns = patterns('',
	url(r'^$', views.index, name = 'index'),
	url(r'^shit/', views.shit, name = 'shit'),
	url(r'^category/(?P<category_name_slug>[\w\-]+)/$', views.category, name = 'category')
)