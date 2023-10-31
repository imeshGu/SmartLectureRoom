import React, { useState } from "react";
import "./Home.css";
import axios from "axios";

const InputField = ({ label, value, onChange }) => (
  <div className="input-field">
    <input
      type="number"
      value={value}
      onChange={(e) => onChange(e.target.value)}
      required
    />
    <label>{label}</label>
  </div>
);

const Home = () => {
  const [formData, setFormData] = useState({
    height_of_video_wall: "",
    width_of_video_wall: "",
    room_length: "",
    room_width: "",
    room_height: "",
    number_of_seats: "",
  });

  const [predictions, setPredictions] = useState(null);

  const handleSubmit = async (e) => {
    e.preventDefault();

    try {
      const response = await axios.post(
        "http://localhost:5000",
        formData
      );

      if (response.data) {
        setPredictions(response.data); // Set predictions in state
        window.alert("Configurations sent!");
      } else {
        window.alert("Something went wrong. Please try again.");
      }
    } catch (err) {
      console.log(err);
      window.alert("Error sending data. Please check the console for details.");
    }
  };

  return (
    <div className="home-container">
      <h2>Video Wall Configuration</h2>

      <form onSubmit={handleSubmit} className="form-container">
        <div className="form-grid">
          <InputField
            label="Height of Video Wall"
            value={formData.height_of_video_wall}
            onChange={(value) =>
              setFormData({ ...formData, height_of_video_wall: value })
            }
          />
          <InputField
            label="Width of Video Wall"
            value={formData.width_of_video_wall}
            onChange={(value) =>
              setFormData({ ...formData, width_of_video_wall: value })
            }
          />
          <InputField
            label="Room Length"
            value={formData.room_length}
            onChange={(value) =>
              setFormData({ ...formData, room_length: value })
            }
          />
          <InputField
            label="Room Width"
            value={formData.room_width}
            onChange={(value) =>
              setFormData({ ...formData, room_width: value })
            }
          />
          <InputField
            label="Room Height"
            value={formData.room_height}
            onChange={(value) =>
              setFormData({ ...formData, room_height: value })
            }
          />
          <InputField
            label="Number of Seats"
            value={formData.number_of_seats}
            onChange={(value) =>
              setFormData({ ...formData, number_of_seats: value })
            }
          />
        </div>
        <button type="submit" className="submit-btn">
          Submit
        </button>
      </form>

      {predictions && (
        <div className="predictions-container" style={{textAlign:'center'}}>
          <h3>Predictions</h3>
          <pre>{JSON.stringify(predictions, null, 2)}</pre>
        </div>
      )}
    </div>
  );
};

export default Home;
