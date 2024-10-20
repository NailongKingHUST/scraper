import asyncio,random,atexit,queue
import nodriver as uc

from genGameList import *


DATA_FOLDER="data"
BaseUrl='https://steamdb.info/'

class Scraper:
    def __init__(self):
        self.lock=asyncio.Lock()

    

    async def handler(self, event: uc.cdp.network.ResponseReceived):
        if self.apiCategory not in event.response.url:
            return
        print(event.request_id)
        async with self.lock:
            self.requestQueue.put(event.request_id)

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
        print("开始爬取.")
        await asyncio.sleep(5)
        await genGameList(await page.get_content())
        print(await page.get_content())
        print("已生成 data.json 文件.")

    async def getData(self, dataPath: str, max: bool):
        self.category=("max" if max else "week")
        self.apiCategory=("GetGraphMax" if max else "GetGraphWeek")
        self.requestQueue=queue.Queue()
        with open(dataPath,"r") as f:
            gamesList=json.load(f)
        length=len(gamesList)
        browser = await uc.start()
        page = await browser.get(BaseUrl)
        self.tab=page
        await page.sleep(5)
        while True:
            s=await page.get_content()
            if "等待" in s:
                await page.sleep(2)
            else:
                break
        print("开始爬取.")

        def onExit():
            with open(dataPath,"w") as f:
                json.dump(gamesList,f,indent=4)
        atexit.register(onExit)

        await asyncio.sleep(2)
        page.add_handler(uc.cdp.network.ResponseReceived,self.handler)
        for idx,game in enumerate(gamesList):
            try:
                if game['done'+self.category]:
                    continue
                await page.get(f"https://steamdb.info/app/{game['appid']}/charts/")
                with open(f"{DATA_FOLDER}/"+self.category+f"/{game['appid']}.json","w") as f:
                    count=0
                    while True:
                        async with self.lock:
                            if not self.requestQueue.empty():
                                request_id=self.requestQueue.get_nowait()
                                command=uc.cdp.network.get_response_body(request_id=request_id)
                                body,b64_encoded = await page.send(command)
                                print(body)
                                break
                        count+=1
                        if count >= 10:
                            break
                        await asyncio.sleep(0.5)
                    res=json.loads(body)
                    if res['success']!=True:
                        raise SyntaxError
                    f.write(body)
                game['done'+self.category]=True
                print(f"{idx} / {length}",end="\r")
                await asyncio.sleep(random.uniform(15.0,20.0))
            except Exception as e:
                print(f"Eror: Index: {idx} Appid: {game['appid']}  Name: {game['name']}")
                await asyncio.sleep(2)
    

                
        

if __name__ == '__main__':
    # since asyncio.run never worked (for me)
    #uc.loop().run_until_complete(getGameList())
    uc.loop().run_until_complete(Scraper().getData("data.json",0))