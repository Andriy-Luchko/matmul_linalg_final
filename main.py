import pandas as pd
import matplotlib.pyplot as plt


# Function to load and visualize the data
def visualize_data():
    # Load the CSV file into a DataFrame
    data = pd.read_csv("data/times.csv")

    # Print the first few rows of the data to ensure it's loaded correctly
    print(data.head())

    # Plot the data: Matrix Size vs Time Taken
    plt.figure(figsize=(10, 6))
    plt.plot(
        data["size"],
        data["time_seconds"],
        marker="o",
        linestyle="-",
        color="b",
        label="Time (seconds)",
    )

    # Set plot title and labels
    plt.title("Matrix Multiplication Time vs Size")
    plt.xlabel("Matrix Size (2^N)")
    plt.ylabel("Time (seconds)")

    # Add a grid for better readability
    plt.grid(True, which="both", ls="--", linewidth=0.5)

    # Show the legend
    plt.legend()

    # Show the plot
    plt.tight_layout()
    plt.show()


if __name__ == "__main__":
    visualize_data()
