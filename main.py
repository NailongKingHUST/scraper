import asyncio,random,atexit
import nodriver as uc

from genGameList import *

DATA_FOLDER="data"
BaseUrl='https://steamdb.info/'

async def getGameList():
    browser = await uc.start()
    page = await browser.get(BaseUrl+"charts/?sort=peak")
    await page.sleep(5)
    while True:
        s=await page.get_content()
        if "等待" in s:
            await page.sleep(2)
        else:
            break
    print("enter!")
    await asyncio.sleep(10)
    await genGameList(await page.get_content())
    print(await page.get_content())
    print("已生成data.json")

async def getData(dataPath: str):
    with open(dataPath,"r") as f:
        gamesList=json.load(f)
    browser = await uc.start()
    page = await browser.get(BaseUrl)
    await page.sleep(5)
    while True:
        s=await page.get_content()
        if "等待" in s:
            await page.sleep(2)
        else:
            break
    print("enter!")
    await asyncio.sleep(random.uniform(2.0,5.0))
    def onExit():
        with open(dataPath,"w") as f:
            json.dump(gamesList,f,indent=4)
    atexit.register(onExit)
    try:
        l=len(gamesList)
        for idx,game in enumerate(gamesList):
            if game['done']:
                continue
            await page.get(BaseUrl+f"api/GetGraphMax/?appid={game['appid']}")
            with open(f"{DATA_FOLDER}/{game['appid']}.json","w") as f:
                f.write((await page.get_content())[99:-64])
            game['done']=True
            print(f"{idx} / {l}",end="\r")
            await asyncio.sleep(random.uniform(15.0,20.0))
    except Exception as e:
        print(e)
    

if __name__ == '__main__':
    # since asyncio.run never worked (for me)
    #uc.loop().run_until_complete(getGameList())
    uc.loop().run_until_complete(getData("data.json"))