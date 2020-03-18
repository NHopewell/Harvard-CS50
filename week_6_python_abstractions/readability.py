import re
import string

letters = string.ascii_letters
punctuation = string.punctuation

def letters_per_hundred_words(n_chars, n_words):
    return (n_chars / n_words) * 100

def sentences_per_hundred_words(n_sentences, n_words):
    return (n_sentences / n_words) * 100

def compute_CLI(lets_per_hundred, sents_per_hundred):
    return round((0.0588 * lets_per_hundred) - (0.296 * sents_per_hundred) - 15.8)

def print_reading_level(CLI):
    if CLI < 1:
        print("Before Grade 1")
    elif CLI >= 16:
        print("Grade 16+")
    else:
        print(f"Grade {CLI}")

input_text = input("Text: ")

sentences = re.split("[.!?]+", input_text)
n_sentences = len(sentences) -1

words = input_text.split(' ')
n_words = len(words)

chars = [char for word in words for char in word if char not in punctuation]
n_chars = len(chars)

L = letters_per_hundred_words(n_chars, n_words)
S = sentences_per_hundred_words(n_sentences, n_words)
CLI = compute_CLI(L, S)

print_reading_level(CLI)