from flask import Flask, request, jsonify, make_response
import pandas as pd
from sklearn.tree import DecisionTreeRegressor, DecisionTreeClassifier
from sklearn.preprocessing import LabelEncoder
from sklearn.model_selection import train_test_split
from flask_cors import CORS

app = Flask(__name__)
CORS(app) 

def load_and_preprocess_data():
    df = pd.read_csv('video_wall_data.csv')
    le = LabelEncoder()
    df['seating_type'] = le.fit_transform(df['seating_type'])
    return df, le

def train_evaluate_regressor(train_data, features, target):
    X_train = train_data[features]
    y_train = train_data[target]

    model = DecisionTreeRegressor(random_state=42)
    model.fit(X_train, y_train)

    return model

def train_evaluate_classifier(train_data, features, target):
    X_train = train_data[features]
    y_train = train_data[target]

    model = DecisionTreeClassifier(random_state=42)
    model.fit(X_train, y_train)

    return model

df, le = load_and_preprocess_data()
features = ['height_of_video_wall', 'width_of_video_wall', 'room_length', 'room_width', 'room_height', 'number_of_seats']
targets = ['seating_type', 'distance_from_video_wall', 'seats_per_row', 'number_of_rows', 'seats_per_cluster', 'number_of_clusters']

train_set, _ = train_test_split(df, test_size=0.2, random_state=42)
for target in targets[1:]:
    train_set = train_set.dropna(subset=[target])

regression_models = {target: train_evaluate_regressor(train_set, features, target) for target in targets[1:]}
seating_type_model = train_evaluate_classifier(train_set, features, 'seating_type')

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

        if seating_type == 'row':
            seats_per_row_prediction = regression_models['seats_per_row'].predict(test_data_df)[0]
            number_of_rows_prediction = regression_models['number_of_rows'].predict(test_data_df)[0]
            response = {
                "seating_type": seating_type,
                "seats_per_row": seats_per_row_prediction,
                "number_of_rows": number_of_rows_prediction
            }
        elif seating_type == 'cluster':
            seats_per_cluster_prediction = regression_models['seats_per_cluster'].predict(test_data_df)[0]
            number_of_clusters_prediction = regression_models['number_of_clusters'].predict(test_data_df)[0]
            response = {
                "seating_type": seating_type,
                "seats_per_cluster": seats_per_cluster_prediction,
                "number_of_clusters": number_of_clusters_prediction
            }
        else:
            response = {"seating_type": seating_type, "message": "Seating type not recognized"}

        return jsonify(response)
    except Exception as e:
        return make_response(jsonify({'error': str(e)}), 500)

if __name__ == '__main__':
    app.run(debug=True)
