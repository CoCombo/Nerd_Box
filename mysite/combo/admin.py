from django.contrib import admin
from combo.models import Category, Page
# Register your models here.
class PageAdmin(admin.ModelAdmin):
	list_display = ('title', 'category', 'url')
class CategoryAdmin(admin.ModelAdmin):
	#list_display = ('name', 'views', 'likes')
	prepopulated_fields = {'slug': ('name',)}

admin.site.register(Category, CategoryAdmin)
admin.site.register(Page, PageAdmin)
