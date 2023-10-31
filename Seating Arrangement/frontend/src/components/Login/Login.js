import React, { useContext, useState } from "react";
import axios from "axios";
import Card from "react-bootstrap/Card";
import { useNavigate } from "react-router-dom";
import { Link } from "react-router-dom";
import './Login.css';

const Login = () => {

  const navigate = useNavigate();
  const [user, setUserData] = useState({
    email: "",
    password: "",
  });

  // const { email, password } = user;
  // const handleSubmit = async (e) => {
  //   e.preventDefault();

  //   const body = {
  //     email,
  //     password,
  //   };
  //   try {
  //     const response = await axios.post(
  //       `${process.env.REACT_APP_BASE_URL}/api/auth/login`,
  //       body,
  //       {
  //         ContentType: "application/json",
  //       }
  //     );

  //     if (response.data.token != null) {
  //       auth.authenticate(
  //         response.data.token,
  //         response.data.firstName + " " + response.data.lastName,
  //         response.data.id,
  //         response.data.role,
  //         response.data.user
  //       );
  //       navigate("/home");  
  //     } else {
  //       notification.showNotification("please check your credentials", true);
  //     }
  //   } catch (error) {
  //     notification.showNotification("Server error please reload", true);
  //   }
  // };

  // const handleChange = (e) => {
  //   setUserData({
  //     ...user,
  //     [e.target.name]: e.target.value,
  //   });
  // };
  return (
    <div>
      <div className="login-container">
        <div className="login-box">
          <h2 className="login-title">Log In</h2>

          <form className="login-form">
            <div className="form-group">
              <input
                type="email"
                name="email"
                className="form-input"
                id="email"
                required
                placeholder="Email"
              />
              <label htmlFor="email">Email</label>
            </div>

            <div className="form-group">
              <input
                type="password"
                name="password"
                className="form-input"
                id="password"
                required
                placeholder="Password"
              />
              <label htmlFor="password">Password</label>
            </div>

            <button className="login-btn">Login</button>
          </form>

          <div className="signup-footer">
            Need an account?{" "}
            <Link to="/signup" className="signup-link">
              Sign Up
            </Link>
          </div>
        </div>
      </div>
    </div>
  );
};

export default Login;
