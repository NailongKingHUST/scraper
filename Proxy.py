import asyncio,json,random
import nodriver as uc

proxyList=None
PATH="proxy.json"

async def getProxyList():
    try:
        
        browser = await uc.start()
        page = await browser.get("https://api.proxyscrape.com/v2/?request=displayproxies&protocol=http&timeout=10000&country=us&ssl=all&anonymity=all")
        await page.sleep(5)
        text=(await page.get_content())[131:-21]
        proxyList=text.split('\n')
        with open(PATH,"w") as f:
            json.dump(proxyList,f,indent=4)
        print(f"Get Proxylist successfully.")
    except Exception as e:
        print(f"Get Proxylist failed.\n Error: {e}")

async def getAProxy() -> str:
    if proxyList == None:
        with open(PATH,"r") as f:
            proxyList=json.load(f)
    return random.choice(proxyList)

if __name__=="__main__":
    task = getProxyList()
    uc.loop().run_until_complete(task)