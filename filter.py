import json,os

with open("data.json","r") as f:
    games=json.load(f)


for game in games:
    try:
        with open(f"data/max/{game['appid']}.json","r") as f:
            json.load(f)
    except:
        game['donemax']=False
        os.remove(f"data/max/{game['appid']}.json")

with open("data.json","w") as f:
    json.dump(games,f,indent=4)