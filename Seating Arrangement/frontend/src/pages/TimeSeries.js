import React from "react";
import TimeSeriesChart from "../components/TimeSeriesChart";

const TimeSeries = () => {

  const data = {
    dates: [
      "2023-10-01",
      "2023-10-02",
      "2023-10-03",
      "2023-10-04",
      "2023-10-05",
    ],
    temperatures: [20, 21, 19, 23, 22],
  };

  return (
    <div style={{margin:"110px 50px 50px 50px", textAlign:'center'}}>
      <h1 style={{margin:"0px 0px 30px 0px"}}>Time Series Visualization</h1>
      <TimeSeriesChart data={data} />
    </div>
  );
};

export default TimeSeries;
