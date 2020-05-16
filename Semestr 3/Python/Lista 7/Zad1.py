import urllib.request
import re
import threading
import queue


def wrapper(function, url, threads_results_queue):
    threads_results_queue.put((url, function(url)))


def add_new_urls(url, lock, new_to_process, automat):
    html = ""
    new_urls_to_add = []
    try:
        response = urllib.request.urlopen(url)
        html = str(response.read())
        new_urls_to_add = [u.group() for u in automat.finditer(html)]
    except urllib.error.HTTPError:
        pass
    except urllib.error.URLError:
        pass
    except Exception:
        pass
    lock.acquire()
    new_to_process += new_urls_to_add
    lock.release()


def crawl(start_page, distance, action):
    adres = '(?:(?:https?|ftp):\/\/|\b(?:[a-z\d]+\.))(?:(?:[^\s()<>]+|\((?:[^\s()<>]+|(?:\([^\s()<>]+\)))?\))+(?:\((?:[^\s()<>]+|(?:\(?:[^\s()<>]+\)))?\)|[^\s`!()\[\]{};:".,<>?«»“”‘’]))?'
    automat = re.compile(adres)
    to_process = [start_page]
    processed = {start_page}
    for i in range(distance):

        threads_number = len(to_process)
        threads_results_queue = queue.Queue()
        threads = [threading.Thread(target=wrapper,
                                    args=(action, url, threads_results_queue))
                   for url in to_process]

        for thr in threads:
            thr.start()

        for url in to_process:
            processed.add(url)

        for i in range(threads_number):
            yield threads_results_queue.get(block=True, timeout=None)

        new_to_process = []
        lock = threading.Lock()
        threads = [threading.Thread(target=add_new_urls,
                                    args=(url, lock, new_to_process, automat))
                   for url in to_process]

        for thr in threads:
            thr.start()

        for thr in threads:
            thr.join()

        to_process = list(filter(lambda x: x not in processed,
                                 list(set(new_to_process))))


def add1():
    count = 1
    while True:
        yield count
        count = count + 1


def find_Python(url):
    html = ""
    helper = []
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
    except Exception:
        pass
    return helper


p = add1()
# it = crawl("http://python.org/", 2, lambda x: next(p))
it = crawl("http://python.org/", 2, find_Python)
for i in it:
    print(i)
# "https://www.google.com"
# "http://python.org/"
# with urllib.request.urlopen(url) as response:
#                 html = str(response.read())
#                 helper = helper + [u.group() for u in automat.finditer(html)]
# "\s*([^!.?]*?NSF[^!.?]*?[?])"
# "([A-Z]+[a-zA-Z0-9 ]*?Python[a-zA-Z0-9 ]*?[?.!])|[.?!]\s(Python[a-zA-Z0-9 ]*?[?.!])"
