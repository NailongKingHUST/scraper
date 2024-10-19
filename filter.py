import json,os

with open("data.json","r") as f:
    games=json.load(f)


for game in games:
    game['donemax']=game['done']
    del game['done']
    game['doneweek']=False

with open("data.json","w") as f:
    json.dump(games,f,indent=4)