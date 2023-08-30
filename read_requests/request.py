import requests
import json
from time import sleep

ip_address = '192.168.0.133'

while True:
    response = requests.get('http://' + ip_address + ':80')
    print(response.json())
    sleep(1)