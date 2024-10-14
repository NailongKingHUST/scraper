import requests
import numpy as np
from dataclasses import dataclass


PROXY_DIST_FILE="ProxyList"

Proxy_Type=np.dtype([
    ('proto','str_',10),
    ('addr','str_',30),
    ('port','int16')
])

def loadProxyList(path: str) -> np.ndarray:
    proxys=np.load(PROXY_DIST_FILE)
    return proxys

def checkProxy():
    pass

if __name__=='__main__':
    a=np.array([('http','localhost',8888)],dtype=Proxy_Type)
    np.savez_compressed("ProxyList",a)