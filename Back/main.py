from flask import Flask,jsonify
from pymongo import MongoClient,DESCENDING
from datetime import datetime, timedelta
import json 
from predict_func import loadDF,add_lags,create_features,loadFutureDF,predict_val



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

#############prediction 
@main.route('/Prediction', methods=['GET'])
def Prediction():
    today = datetime.today()
    d1 = today.strftime("%d/%m/%Y")


    two_months = timedelta(days=60)  # Approximately 30 days per month
    date_after_2_months = today + two_months
    df = loadDF()
    last_date = df.index[-1].strftime('%Y-%m-%d %H:%M:%S')
    future = loadFutureDF(last_date,date_after_2_months,df)
    predicted_future = predict_val(future)

    parsed_date = datetime.strptime(d1, "%d/%m/%Y")
    dat = str(parsed_date.year)

    query_str = f'Datetime > "{dat}"'
    new_df = df.query(query_str).copy()

    filtered_df = new_df[['Datetime', 'pred']]
    json_array = filtered_df.to_json(orient='records', date_format='iso', default_handler=str)

    return json_array


@main.route('/LUX/control/', methods=['GET'])
def LastHrLux():

    return 0.9



if __name__ == '__main__':
    main.run()

