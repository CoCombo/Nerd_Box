from django.shortcuts import render
from combo.models import Category, Page
#from django.http import HttpResponse

# Create your views here.
def index(request):
	category_list = Category.objects.order_by('-likes')[:5]
	context_dict = {'categories': category_list}
	
	return render(request, 'combo/index.html', context_dict)

def shit(request):
	context_dict = {'boldmessage': "media!"}
	
	return render(request, 'combo/shit.html', context_dict)
	#return HttpResponse("bull shit.")

def combo(request, category_name_slug):
	context_dict = {}
	
	try:
		category = Category.objects.get(slug = category_name_slug)
		context_dict['category_name'] = category.name
		
		pages = Page.objects.filter(category = category)
		
		context_dict['pages'] = pages
		context