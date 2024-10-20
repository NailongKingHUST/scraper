import json,os

with open("data.json","r") as f:
    games=json.load(f)


for game in games:
    try:
        with open(f"data/week/{game['appid']}.json","r") as f:
            json.load(f)
    except:
        game['doneweek']=False
        os.remove(f"data/week/{game['appid']}.json")

with open("data.json","w") as f:
    json.dump(games,f,indent=4)