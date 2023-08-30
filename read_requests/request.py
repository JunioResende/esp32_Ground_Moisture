import requests
from time import sleep
import sqlite3

ip_server = 'http://192.168.0.133'


while True:
    sensor_data = requests.get(ip_server).json()
    conn = sqlite3.connect("dados_sensor.db")
    cursor = conn.cursor()

    cursor.execute('''
            CREATE TABLE IF NOT EXISTS leituras (
                id INTEGER PRIMARY KEY AUTOINCREMENT,
                umidade REAL,
                timestamp TIMESTAMP DEFAULT CURRENT_TIMESTAMP
            )
        ''')

    umidade = sensor_data
    cursor.execute("INSERT INTO leituras (umidade) VALUES (?)", (umidade,))
    conn.commit()

    conn.close()
    sleep(1)
