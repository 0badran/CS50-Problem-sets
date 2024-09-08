from cs50 import get_string

text = get_string("Text: ")
sentences = 0
letters = 0
words = 1

# Count letters and words and sentences
for i in text:
    if i.isalpha():
        letters += 1
    elif i == ' ':
        words += 1
    elif i in ['!', '?', '.']:
        sentences += 1

L = letters/words*100
S = sentences/words*100
# Liau index
index = 0.0588 * L - 0.296 * S - 15.8
grade = round(index)
if grade > 16:
    print("Grade 16+\n")
elif grade < 1:
    print("Before Grade 1")
else:
    print("Grade", grade)
