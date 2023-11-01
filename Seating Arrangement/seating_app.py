from flask import Flask, request, jsonify, make_response
import pandas as pd
import joblib
from flask_cors import CORS

app = Flask(__name__)
CORS(app) 

# Load regression models
regression_models = joblib.load('regression_models.joblib')

# Load classifier model and label encoder
classifier_model = joblib.load('classifier_model_and_label_encoder.joblib')
seating_type_model = classifier_model['seating_type_model']
le = classifier_model['label_encoder']

def adjust_predictions(seats_per_row, number_of_rows, total_seats):
    # Adjust seats_per_row and number_of_rows to ensure they multiply to total_seats
    while seats_per_row * number_of_rows != total_seats:
        if seats_per_row * number_of_rows < total_seats:
            seats_per_row += 1
        else:
            number_of_rows -= 1
    return seats_per_row, number_of_rows

@app.route('/', methods=['POST'])
def predict_seating():
    try:
        data = request.get_json()

        if data is None:
            return make_response(jsonify({'error': 'No data provided'}), 400)

        test_data = {
            'height_of_video_wall': float(data.get('height_of_video_wall', 0.0)),
            'width_of_video_wall': float(data.get('width_of_video_wall', 0.0)),
            'room_length': float(data.get('room_length', 0.0)),
            'room_width': float(data.get('room_width', 0.0)),
            'room_height': float(data.get('room_height', 0.0)),
            'number_of_seats': int(data.get('number_of_seats', 0))
        }

        test_data_df = pd.DataFrame([test_data])

        seating_type_prediction = seating_type_model.predict(test_data_df)[0]
        seating_type = le.inverse_transform([seating_type_prediction])[0]

        response = {"seating_type": seating_type}

        if seating_type == 'row':
            seats_per_row_prediction = regression_models['seats_per_row'].predict(test_data_df)[0]
            number_of_rows_prediction = regression_models['number_of_rows'].predict(test_data_df)[0]
            
            # Adjust the predictions
            seats_per_row_prediction, number_of_rows_prediction = adjust_predictions(seats_per_row_prediction, number_of_rows_prediction, test_data['number_of_seats'])
            
            response["seats_per_row"] = seats_per_row_prediction
            response["number_of_rows"] = number_of_rows_prediction
        elif seating_type == 'cluster':
            response["seats_per_cluster"] = regression_models['seats_per_cluster'].predict(test_data_df)[0]
            response["number_of_clusters"] = regression_models['number_of_clusters'].predict(test_data_df)[0]
        else:
            response["message"] = "Seating type not recognized"

        return jsonify(response)
    except Exception as e:
        return make_response(jsonify({'error': str(e)}), 500)

if __name__ == '__main__':
    app.run(debug=True)
