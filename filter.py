import json,os

with open("data.json","r") as f:
    games=json.load(f)


for game in games:
    if game['done']==False:
        continue
    try:
        with open(f"data/{game['appid']}.json") as f:
            s=json.load(f)
    
    except:
        game['done']=False
        os.remove(f"data/{game['appid']}.json")

with open("data.json","w") as f:
    json.dump(games,f,indent=4)