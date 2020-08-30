from django.shortcuts import render # looks in templated folder
from django.http import HttpResponse

posts = [
    {
        'author': 'Nick',
        'title': 'Blog Post 1',
        'content': 'First post content',
        'date_posted': 'Aug 30, 2020'
    },
    {
        'author': 'Jim',
        'title': 'Blog Post 2',
        'content': 'Second post content',
        'date_posted': 'Aug 31, 2020'
    }
]

def home(request):
    context = {
        'posts': posts
    }
    return render(request, 'blog/home.html', context)

def about(request):
    return render(request, 'blog/about.html', {'title': 'About'})
