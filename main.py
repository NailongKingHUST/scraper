import asyncio,random,atexit,queue,argparse
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

    async def getGameList(filePath: str):
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
        await genGameList((await page.get_content()),filePath=filePath)
        print(await page.get_content())
        print("已生成 data.json 文件.")

    async def getData(self, filePath: str, max: bool):
        self.category=("max" if max else "week")
        self.apiCategory=("GetGraphMax" if max else "GetGraphWeek")
        self.requestQueue=queue.Queue()
        with open(filePath,"r") as f:
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
            with open(filePath,"w") as f:
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
    parser=argparse.ArgumentParser(description="A scraper for SteamAnalyze\
        example: python main.py --get <list | data> (optional: --data <max | week>)\
        ")
    parser.add_argument("-g","--get",help="获取列表|数据",type=str,required=True)
    parser.add_argument("-f","--file",help="索引文件",type=str,required=True)
    parser.add_argument("-d","--data",help="获取数据类型",type=str,required=False)
    args=parser.parse_args()
    if args.get == "list":
        task = Scraper().getGameList(args.file)
    else:
        if args.data == None:
            print("usage: main.py [-h] -g GET -f FILE [-d DATA]")
            exit(1)
        else:
            task= Scraper().getData(filePath=args.file,max=args.data=='max')
    uc.loop().run_until_complete(task)