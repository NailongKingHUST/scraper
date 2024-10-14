import requests
import numpy as np
from dataclasses import dataclass


PROXY_DIST_FILE="ProxyList"
TEST_URL="https://www.google.com/ncr"

Proxy_Type=np.dtype([
    ('proto','str_',10),
    ('addr','str_',30),
    ('port','int16')
])

def loadProxyList(path: str) -> np.ndarray:
    proxys=np.load(PROXY_DIST_FILE)
    return proxys

def checkProxy(proto: str, address: str, port: int) -> bool:
    URL=f"{proto}://{address}:{port}"
    res=requests.get(url=TEST_URL,headers={
        "accept":"text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,image/apng,*/*;q=0.8,application/signed-exchange;v=b3;q=0.7",
        "accept-encoding":"gzip, deflate, br, zstd",
        "accept-language":"zh-CN,zh;q=0.9",
        "connection":"keep-alive",
        "sec-ch-ua":'"Google Chrome";v="129", "Not=A?Brand";v="8", "Chromium";v="129"',
        "sec-ch-ua-mobile":"?0",
        "sec-ch-ua-platform":'"Windows"',
        "sec-fetch-dest":"document",
        "sec-fetch-mode":"navigate",
        "sec-fetch-site":"none",
        "sec-fetch-user":"?1",
        "user-agent":"Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/129.0.0.0 Safari/537.36",
    },proxies={
        'https':URL
    })
    return res.status_code==200

if __name__=='__main__':
    