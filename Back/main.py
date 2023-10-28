from flask import Flask,jsonify
from pymongo import MongoClient,ServerApi,DESCENDING


mongoURL = 'mongodb+srv://app:app@cluster0.tsl0vdw.mongodb.net/?retryWrites=true&w=majority'
DBname = 'SmartLectureRoom'
collection = 'SensorReading'

client = MongoClient(mongoURL)
db = client.get_database(DBname)             
collection = db[collection]


main = Flask(__name__)

@main.route('/')
def hello():
    return 'Hello, Flask World'

main.route('/LatestLUXVideo')
def reLatestLUXVideo():
    doc = collection.find_one(sort=[("time", DESCENDING)])
    return 0

main.route('/write')
def readData():
    return 0

main.route('/read')
def readData():
    return 0



if __name__ == '__main__':
    main.run()

