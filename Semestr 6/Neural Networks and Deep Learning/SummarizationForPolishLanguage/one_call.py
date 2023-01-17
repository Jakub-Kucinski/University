import csv 
from datasets import Dataset
import pandas as pd
import datasets
import wandb

list_of_texts_train = []
list_of_summaries_train = []
list_of_texts_val = []
list_of_summaries_val = []
list_of_texts_test = []
list_of_summaries_test = []



with open('tvn24/train.csv') as csv_file:
    csv_reader = csv.DictReader(csv_file)
    idx = 0
    # print(len(csv_reader))
    list_of_summaries = []
    list_of_texts = []
    for i in csv_reader:
        list_of_texts.append(i['summary'])
        list_of_summaries.append(i["body_text"])

    for text,summary in set(list(zip(list_of_texts,list_of_summaries))):
        list_of_texts_train.append(text)
        list_of_summaries_train.append(summary)
    print(len(list_of_texts_train),len(list_of_summaries_train))
        
    
with open('tvn24/train2.csv') as csv_file:
    csv_reader = csv.DictReader(csv_file)
    idx = 0
    # print(len(csv_reader))
    list_of_summaries = []
    list_of_texts = []

    
    for i in csv_reader:
        list_of_texts.append(i['body_text'])
        list_of_summaries.append(i["summary"])

    total_texts = len(list_of_texts)
    train_length = int(total_texts * 0.85)
    val_length = int(total_texts * 0.9) - train_length
    test_length = total_texts - train_length - val_length

    i = 0
    for text,summary in set(list(zip(list_of_texts,list_of_summaries))):
        if i < train_length:
                list_of_texts_train.append(text)
                list_of_summaries_train.append(summary)
        elif i < train_length + val_length:
                list_of_texts_val.append(text)
                list_of_summaries_val.append(summary)
        else:
                list_of_texts_test.append(text)
                list_of_summaries_test.append(summary)
        i += 1


   
with open('artifacts/test.csv') as csv_file:
    csv_reader = csv.DictReader(csv_file)
    # idx = 0
    list_of_summaries = []
    list_of_texts = []
    for i in csv_reader:
        list_of_texts.append(i['body_text'])
        list_of_summaries.append(i["summary"])

    for text,summary in zip(list_of_texts,list_of_summaries):
        list_of_texts_test.append(text)
        list_of_summaries_test.append(summary)



with open('artifacts/train.csv') as csv_file:
    csv_reader = csv.DictReader(csv_file)
    # idx = 0
    list_of_summaries = []
    list_of_texts = []
    for i in csv_reader:
        list_of_texts.append(i['body_text'])
        list_of_summaries.append(i["summary"])

    for text,summary in zip(list_of_texts,list_of_summaries):
        list_of_texts_train.append(text)
        list_of_summaries_train.append(summary)


with open('artifacts/validation.csv') as csv_file:
    csv_reader = csv.DictReader(csv_file)
    # idx = 0
    list_of_summaries = []
    list_of_texts = []
    for i in csv_reader:
        list_of_texts.append(i['body_text'])
        list_of_summaries.append(i["summary"])

    for text,summary in zip(list_of_texts,list_of_summaries):
        list_of_texts_val.append(text)
        list_of_summaries_val.append(summary)

print(len(list_of_texts_train))
print(len(list_of_texts_test))
print(len(list_of_texts_val))

train_dict = {}
train_dict["body_text"] = list_of_texts_train
train_dict["summary"] = list_of_summaries_train
val_dict = {}
val_dict["body_text"] = list_of_texts_val
val_dict["summary"] = list_of_summaries_val
test_dict = {}
test_dict["body_text"] = list_of_texts_test
test_dict["summary"] = list_of_summaries_test




train_data = Dataset.from_dict(train_dict)
val_data = Dataset.from_dict(val_dict)
test_data = Dataset.from_dict(test_dict)

df = pd.DataFrame.from_dict(train_dict)
df.to_csv('mk/train.csv', index=False)
df = pd.DataFrame.from_dict(val_dict)
df.to_csv('mk/validation.csv', index=False)
df = pd.DataFrame.from_dict(test_data)
df.to_csv('mk/test.csv', index=False)


train_data = datasets.load_dataset('csv', data_files={'train': 'mk/train.csv'})
val_data = datasets.load_dataset('csv', data_files={'validation': 'mk/validation.csv'})
test_data = datasets.load_dataset('csv',data_files={'test': 'mk/test.csv'})


WANDB_PROJECT="psc"
WANDB_LOG_MODEL="true"
wandb.login()

with wandb.init(job_type="dataset", project='psc',    
            name="herbert-klej-polsum", entity='pns') as run:
    artifact = wandb.Artifact('tvn_psc', type='dataset')
    artifact.add_file('mk/train.csv', name='tvn_train.csv')
    artifact.add_file('mk/validation.csv', name='tvn_validation.csv')
    artifact.add_file('mk/test.csv', name='tvn_test.csv')
    wandb.log_artifact(artifact)
    artifact.wait()

wandb.finish()
