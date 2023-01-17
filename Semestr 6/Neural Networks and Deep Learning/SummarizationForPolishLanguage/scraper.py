import requests
from bs4 import BeautifulSoup
import np
from datasets import Dataset
import pandas as pd
import time


links = set()
# j = 0
for j in range(1000):
    # print(j, "Site number")
    url = "https://tvn24.pl/najnowsze/"+str(j)
    print(j)
    r1 = requests.get(url)
    coverpage = r1.content

    # print(coverpage)
    soup1 = BeautifulSoup(coverpage, 'html.parser')
    # print(soup1.prettify())
    mydivs = soup1.find_all("div", {"class": "link"})
    # print(mydivs)

    for i in mydivs:
        test = i.find_all(href=True)
        link = str(test[0]).split(" ")[2][6:-1]
        if "https://tvn24.pl/" in link and ".html" not in link:
            if link.count('/') > 3 and link[-1].isnumeric():
                links.add(link)
# for l in links:
#     print(l)
# # print(len(links))
paragraphs = []
leads = [] 
forbidden = [
    "PRZECZYTAJ",
    "ZOBACZ",
    "CZYTAJ",
    "OGLĄDAJ",
    "NA ŻYWO"
]


for link in links:
    # print("----------------")
    r1 = requests.get(link)
    coverpage = r1.content
    soup1 = BeautifulSoup(coverpage, 'html.parser')
    y = soup1.find_all("p")
    sum = 0
    paragraphs_tmp = [] 

    done = False
    for i,j in enumerate(y):
        if "lead-text" in str(j):
            leads.append(j.text)
            done = True
        if "paragraph" in str(j):
            if any([f in str(j.text) for f in forbidden]):
                continue
            paragraphs_tmp.append(str(j.text))
    if done:     
            paragraphs.append(" ".join(paragraphs_tmp))
    
    if len(leads)!= len(paragraphs):
        leads = leads[:-1]

    # time.sleep(2)


print(len(set(leads)))
print(len(set(paragraphs)))

print(len(leads))
print(len(paragraphs))

# for i in range(len(leads)):
#     print(leads[i])
#     print("-------------------------------------")
#     print(paragraphs[i])
#     print("Next")

train_dict = {}
train_dict["body_text"] = paragraphs
train_dict["summary"] =leads

dataset_train = pd.DataFrame.from_dict(train_dict)
dataset_train.to_csv('tvn24/train2.csv', index=False)