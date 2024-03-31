from fastapi import FastAPI
from fastapi.responses import HTMLResponse
from fastapi.middleware.cors import CORSMiddleware
import requests
import json

app = FastAPI()
origins = ['http://localhost:8000','*']

app.add_middleware(
    CORSMiddleware,
    allow_origins=origins,
    allow_credentials=True,
    allow_methods=["*"],
    allow_headers=["*"],
)

@app.get("/")
async def root():
    r = requests.get('https://passio3.com/www/mapGetData.php?eta=3&deviceId=20487385&stopIds=27767&userId=1268')
    data = r.json()
    finalData = []
    
    try:
        finalData = data['ETAs']['27767']

        final = []
        final.append(finalData[0]['theStop']['name'])
        for j in range(1, len(finalData)+1):
            final.append([])
            final[j].append(finalData[j-1]['busName'])
            final[j].append(finalData[j-1]['eta'])
            final[j].append(finalData[j-1]['theStop']['routeName'])
        pass
    except KeyError:
        print("too bad!")
        return "too bad!, so sad"

    return final
