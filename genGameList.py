from bs4 import BeautifulSoup
import re,json


async def genGameList(string: str,filePath: str):

    Uri_matcher=re.compile("/app/([0-9]*)/charts/")

    def match_href(href: str):
        return href and Uri_matcher.search(href)

    def match_string(string: str):
        return string and "<" not in string
    soup=BeautifulSoup(string,"lxml")
    games=soup.find_all(href=match_href,string=match_string)
    gamesList=[]
    for game in games:
        gamesList.append({
            'appid': int(game['href'][5:-8]),
            'name': game.string,
            'allTimePeak': int(game.parent.next_sibling.next_sibling.next_sibling.next_sibling.next_sibling.next_sibling.string.replace(",","")),
            'donemax': False,
            'doneweek': False
        })

    gamesList.sort(key=lambda game:game['allTimePeak'],reverse=True)
    gamesList=gamesList[:1000]

    with open(filePath,"w") as f:
        json.dump(gamesList,f,indent=4)

    
