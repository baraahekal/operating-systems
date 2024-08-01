from fastapi import FastAPI, Request
from fastapi.middleware.cors import CORSMiddleware
import scheduler_wrapper as ds

app = FastAPI()

origins = ["http://localhost:3000"]

app.add_middleware(
    CORSMiddleware,
    allow_origins=origins,
    allow_credentials=True,
    allow_methods=["*"],
    allow_headers=["*"],
)


@app.post("/fcfs")
async def fcfs(request: Request):
    data = await request.json()
    requests = data['requests']
    starting_head = data['starting_head']
    result = ds.fcfs(requests, starting_head)
    return result


@app.post("/sstf")
async def sstf(request: Request):
    data = await request.json()
    requests = data['requests']
    starting_head = data['starting_head']
    result = ds.sstf(requests, starting_head)
    return result


@app.post("/scan")
async def scan(request: Request):
    data = await request.json()
    requests = data['requests']
    starting_head = data['starting_head']
    cylinders = data['cylinders']
    result = ds.scan(requests, starting_head, cylinders)
    return result


@app.post("/look")
async def look(request: Request):
    data = await request.json()
    requests = data['requests']
    starting_head = data['starting_head']
    result = ds.look(requests, starting_head)
    return result


@app.post("/c_scan")
async def c_scan(request: Request):
    data = await request.json()
    requests = data['requests']
    starting_head = data['starting_head']
    cylinders = data['cylinders']
    result = ds.c_scan(requests, starting_head, cylinders)
    return result


@app.post("/c_look")
async def c_look(request: Request):
    data = await request.json()
    requests = data['requests']
    starting_head = data['starting_head']
    result = ds.c_look(requests, starting_head)
    return result
