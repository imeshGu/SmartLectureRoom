from flask import Flask,jsonify
from pymongo import MongoClient,DESCENDING
from datetime import datetime, date, timedelta
import json 



mongoURL = "mongodb+srv://app:app@cluster0.tsl0vdw.mongodb.net/?retryWrites=true&w=majority"
DBname = 'SmartLectureRoom'
collection = 'SensorReading'

client = MongoClient(mongoURL)
db = client.get_database(DBname)             
collection = db.SensorReading

latest = []

main = Flask(__name__)

@main.route('/')
def hello():
    return 'Hello, Flask World'

@main.route('/latest_packet', methods=['GET'])
def latest_packet():
    doc = collection.find_one(sort=[("time", DESCENDING)])
    date_time = doc.get("time")
    if isinstance(date_time,datetime):
        print("in")
        str_datetime = date_time.strftime("%Y-%m-%d %H:%M:%S")
        doc.update([('time',str(str_datetime)),('_id',str(doc.get("_id")))])

    print(doc)
    return json.dumps(doc)

@main.route('/last_packet', methods=['GET'])
def last_packet():
    current_time = datetime.now()
    two_hours_ago = current_time - timedelta(hours=24)

    ##query
    query = {"timestamp": {"$gte": two_hours_ago}}
    results = collection.find(query)

    arr = list(results)
    
    return json.dumps(arr)


@main.route('/LUX/Ratio', methods=['GET'])
def luxRatio():


    return 0


@main.route('/LUX/control/', methods=['GET'])
def LastHrLux():

    return 0.9



if __name__ == '__main__':
    main.run()

