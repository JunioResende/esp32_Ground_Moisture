import requests
from time import sleep
import sqlite3
from time import sleep
import pandas as pd

ip_address = '192.168.0.133'


sensor_data = requests.get('http://'+ip_address+':80').json()

# Conecta-se ao banco de dados SQLite
while True:
    conn = sqlite3.connect("dados_sensor.db")
    cursor = conn.cursor()

    # Cria a tabela se ainda não existir
    cursor.execute('''
        CREATE TABLE IF NOT EXISTS leituras (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            umidade REAL,
            timestamp TIMESTAMP DEFAULT CURRENT_TIMESTAMP
        )
    ''')

    # Insere os dados obtidos do sensor no banco de dados
    # Certifique-se de adaptar essa linha ao formato real dos seus dados
    umidade = sensor_data
    cursor.execute("INSERT INTO leituras (umidade) VALUES (?)", (umidade,))
    conn.commit()

    # Fecha a conexão com o banco de dados
    conn.close()
    sleep(30)
