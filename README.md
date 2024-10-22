### Phase 1 抓取数据
#### 开发历程
说实话SteamDB的数据非常不好爬取，**SteamDB**使用了**Cloudflare Turnstile**盾进行防御爬虫，众所周知，Cloudflare在防范机器人、DDOS这一方面属于行业龙头，Turnstile的反爬虫检测机制非常强大，一开始我采用了Playwright的Firefox（**Webdriver**协议）、Chrome（**CDP**, Chrome Devtools Protocol）操控浏览器进行数据爬取，但都被Turnstile检测出来了浏览器为爬虫所操控，我当场就裂开了。在网上查阅大量资料后发现**Turnstile会扫描Javascript Runtime**来检测是否存在CDP协议，在绝望之时，我找到了一篇浏览量非常小的文章，文章里提到了这个检测机制，并指出可以使用一个比较冷门的规避了CDP检测的库: nodriver。再次向文章的作者及nodriver的作者致谢，没有他们我就无法抓取到我们所需的数据。
#### 具体使用
python -g <list|data> -f <data.json> [-d <max|week>]
并在弹出的浏览器窗口手动点击验证按钮
例如：
想要生成list，请使用`main.py [-h] -g GET -f FILE [-d DATA] [-p PROXY]`
程序内置了自动代理获取，如需使用代理，请在后面加上参数`-p 1`，即可自动获取代理列表并随机选择一个来使用。
生成list后，想要获取max data，请使用`python main.py -g data -f data.json -d max`
