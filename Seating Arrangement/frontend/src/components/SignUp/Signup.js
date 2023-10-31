import React, { useRef, useContext } from "react";
import Card from "react-bootstrap/Card";
import axios from "axios";
import { useNavigate } from "react-router-dom";
import { Link } from "react-router-dom";
import './SignUp.css';

const Signup = () => {

  const fname = useRef();
  const lname = useRef();
  const password = useRef();
  const email = useRef();
  const mobile = useRef();
  const city = useRef();
  const zip = useRef();

  // const submitHandler = async (e) => {
  //   e.preventDefault();
  //   let newCustomer;

  //   const newUser = {
  //     firstName: fname.current.value,
  //     lastName: lname.current.value,
  //     password: password.current.value,
  //     email: email.current.value,
  //     mobile: mobile.current.value,
  //     city: city.current.value,
  //     zip: zip.current.value,
  //   };

  //   try {
  //     newCustomer = await axios.post(
  //       "http://localhost:5000/api/auth/",
  //       newUser,
  //     );
  //     if (newCustomer) {
  //       window.alert("Signed up Successfully!");
  //       navigate("/login");  
  //     } else {
  //       notification.showNotification(
  //         "something went wrong. please try again",
  //         true
  //       );
  //     }
  //   } catch (err) {
  //     console.log(err);
  //   }
  // };

  return (
    <div>
      <div className="signup-container">
        <div className="signup-box">
          <h2 className="signup-title">Sign Up</h2>

          <form className="signup-form">
            <div className="form-group">
              <input
                type="email"
                name="email"
                className="form-input"
                id="email"
                ref={email}
                required
                placeholder="Email"
              />
              <label htmlFor="email">Email</label>
            </div>

            <div className="form-group">
              <input
                name="fname"
                className="form-input"
                id="fname"
                ref={fname}
                required
                placeholder="First Name"
              />
              <label htmlFor="fname">First Name</label>
            </div>

            <div className="form-group">
              <input
                name="lname"
                className="form-input"
                id="lname"
                ref={lname}
                required
                placeholder="Last Name"
              />
              <label htmlFor="lname">Last Name</label>
            </div>

            <div className="form-group">
              <input
                type="password"
                name="password"
                className="form-input"
                id="password"
                ref={password}
                required
                placeholder="Password"
              />
              <label htmlFor="password">Password</label>
            </div>

            <button className="signup-btn">Create Account</button>
          </form>

          <div className="login-footer">
            Already have an account?{" "}
            <Link to="/login" className="login-link">
              Sign In
            </Link>
          </div>
        </div>
      </div>
    </div>
  );
};

export default Signup;
