from django.shortcuts import render

# Create your views here.
def index(request):
	context_dict = {'boldmessage': "Fuck you."}
	
	return render(request, 'combo/index.html', context_dict)