import urllib.request
import re


def crawl(start_page, distance, action):

    # adres = "([a-zA-Z]+\.)+[a-zA-Z]+"
    # automat = re.compile(”http://” + adres)
    adres = '(?:(?:https?|ftp):\/\/|\b(?:[a-z\d]+\.))(?:(?:[^\s()<>]+|\((?:[^\s()<>]+|(?:\([^\s()<>]+\)))?\))+(?:\((?:[^\s()<>]+|(?:\(?:[^\s()<>]+\)))?\)|[^\s`!()\[\]{};:".,<>?«»“”‘’]))?'
    automat = re.compile(adres)
    to_process = [start_page]
    processed = {start_page}
    for i in range(distance):
        # print("HEJ", len(to_process))

        """Przetwarzanie jeszcze nieprzetworzonych stron"""
        for url in to_process:
            # action(url)
            yield (url, action(url))

        """Aktualizacja przetworzonych stron"""
        for url in to_process:
            processed.add(url)

        helper = []
        for url in to_process:
            html = ""
            try:
                response = urllib.request.urlopen(url)
                html = str(response.read())
                helper = helper + [u.group() for u in automat.finditer(html)]
                # break
            except urllib.error.HTTPError:
                pass
            except urllib.error.URLError:
                pass
        to_process = list(filter(lambda x: x not in processed,
                                 list(set(helper))))


def add1():
    count = 1
    while True:
        yield count
        count = count + 1


def find_Python(url):
    html = ""
    helper = []
    # automat = re.compile("(([A-Z]+[a-zA-Z0-9 ]*)*Python[a-zA-Z0-9 ]*?[?.!])")
    automat = re.compile("([A-Z]+[a-zA-Z0-9\-:,() ]*Python[a-zA-Z0-9\-:,() ]" +
                         "*[.?!])|(Python[a-zA-Z0-9\-:,() ]*[.?!])")
    try:
        response = urllib.request.urlopen(url)
        html = str(response.read())
        helper = [u.group() for u in automat.finditer(html)]
    except urllib.error.HTTPError:
        pass
    except urllib.error.URLError:
        pass
    return helper


p = add1()
# it = crawl("http://python.org/", 2, lambda x: next(p))
it = crawl("http://python.org/", 2, find_Python)
for i in it:
    print(i)
# "https://www.google.com"
# "http://python.org/"
# "https://www.ii.uni.wroc.pl/~marcinm/dyd/python/"
# with urllib.request.urlopen(url) as response:
#                 html = str(response.read())
#                 helper = helper + [u.group() for u in automat.finditer(html)]
# "\s*([^!.?]*?NSF[^!.?]*?[?])"
# "([A-Z]+[a-zA-Z0-9 ]*?Python[a-zA-Z0-9 ]*?[?.!])|[.?!]\s(Python[a-zA-Z0-9 ]*?[?.!])"
