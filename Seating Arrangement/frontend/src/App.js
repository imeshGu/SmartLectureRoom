import logo from './logo.svg';
import './App.css';
import "chartjs-adapter-date-fns";
import { BrowserRouter, Route, Routes } from "react-router-dom";
import Navbar from "./components/Navbar/index";
import Login from "./components/Login/Login";
import SignUp from "./components/SignUp/Signup";
import Home from './pages/Home/Home';
import TimeSeries from './pages/TimeSeries';

function App() {
  return (
    <BrowserRouter>
      <div className="App">
        <Navbar />
        <Routes>
            <Route path="/login" element={<Login />} />
            <Route path="/signup" element={<SignUp />} />
            <Route path="/" element={<Home/>} />  
            <Route path="/time_series" element={<TimeSeries/>} />   
        </Routes>

        <div></div>
      </div>
    </BrowserRouter>
  );
}

export default App;
