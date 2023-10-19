import pandas as pd
import random

# Number of records
n_records = 100

# List to hold the generated data
data = []

for i in range(n_records):
    record = {
        "Length of Room (m)": random.uniform(15, 30),
        "Width of Room (m)": random.uniform(10, 20),
        "Width of Video Wall (m)": random.uniform(3, 6),
        "Height of Video Wall (m)": random.uniform(2, 4),
        "Width of Seat (m)": random.uniform(0.45, 0.65),
        "Depth of Seat (m)": random.uniform(0.55, 0.75),
        "Preferred Viewing Angle (degrees)": random.uniform(25, 40),
        "Preferred Distance (m)": random.uniform(4, 7),
        "Seating Configuration": random.choice(["Rows", "Clusters", "Rows with Tables"])
    }
    data.append(record)

# Convert the list of dictionaries to a DataFrame
df = pd.DataFrame(data)

# Save the dataframe to a CSV file, if you wish
# df.to_csv('seating_data.csv', index=False)

# Display the DataFrame
print(df.head())