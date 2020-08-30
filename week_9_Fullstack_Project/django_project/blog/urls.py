from django.urls import path
# views from views.py
from . import views

urlpatterns = [
    # home route (blog/)
    path('', views.home, name="blog-home"),
    # about route (blog/about/)
    path('about/', views.about, name="blog-about"),
]