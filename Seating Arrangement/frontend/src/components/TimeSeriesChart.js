import React, { useRef, useEffect } from "react";
import { Chart } from "chart.js";
import { registerables } from "chart.js";

Chart.register(...registerables);

const TimeSeriesChart = ({ data }) => {
  const chartRef = useRef(null);
  const canvasRef = useRef(null);

  useEffect(() => {
    if (canvasRef && canvasRef.current) {
      if (chartRef.current) chartRef.current.destroy();

      const chartInstance = new Chart(canvasRef.current, {
        type: "line",
        data: {
          labels: data.dates,
          datasets: [
            {
              label: "Temperature (°C)",
              data: data.temperatures,
              borderColor: "#007BFF",
              pointBackgroundColor: "#007BFF",
              pointBorderColor: "#fff",
              pointBorderWidth: 1,
              pointRadius: 4,
              pointHoverRadius: 5,
              backgroundColor: function (context) {
                const chart = context.chart;
                const { ctx, chartArea } = chart;

                if (!chartArea) {
                  return null;
                }

                const gradient = ctx.createLinearGradient(
                  0,
                  chartArea.bottom,
                  0,
                  chartArea.top
                );
                gradient.addColorStop(0, "rgba(0, 123, 255, 0.1)");
                gradient.addColorStop(1, "rgba(0, 123, 255, 0.5)");

                return gradient;
              },
              fill: "origin",
            },
          ],
        },
        options: {
          plugins: {
            legend: {
              display: true,
              labels: {
                color: "#333",
                font: {
                  size: 14,
                },
              },
            },
            title: {
              display: true,
              text: "Temperature Over Time",
              color: "#333",
              font: {
                size: 20,
              },
              padding: {
                top: 10,
                bottom: 30,
              },
            },
          },
          scales: {
            x: {
              type: "time",
              time: {
                unit: "day",
                parser: "yyyy-MM-dd",
              },
              title: {
                display: true,
                text: "Date",
                color: "#333",
                font: {
                  size: 16,
                },
              },
              grid: {
                color: "rgba(0,0,0,0.1)",
                borderColor: "rgba(0,0,0,0.2)",
              },
              ticks: {
                color: "#333",
              },
            },
            y: {
              beginAtZero: true,
              title: {
                display: true,
                text: "Temperature (°C)",
                color: "#333",
                font: {
                  size: 16,
                },
              },
              grid: {
                color: "rgba(0,0,0,0.1)",
                borderColor: "rgba(0,0,0,0.2)",
              },
              ticks: {
                color: "#333",
              },
            },
          },
        },
      });

      chartRef.current = chartInstance;
    }

    return () => {
      if (chartRef.current) {
        chartRef.current.destroy();
      }
    };
  }, [data]);

  return <canvas ref={canvasRef} />;
};

export default TimeSeriesChart;
