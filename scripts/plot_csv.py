import argparse
import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns

# Set up argument parser
parser = argparse.ArgumentParser(description='Generate a plot from CSV data.')
parser.add_argument('input_file', type=str, help='Path to the input CSV file.')
parser.add_argument('output_file', type=str, help='Path to the output PNG file.')
parser.add_argument('-v', '--verbose', action='store_true', help='Print verbose output.')

args = parser.parse_args()

# Define a function to print if verbose is set
def verbose_print(*aargs, **kwargs):
    if args.verbose:
        print(*aargs, **kwargs)

# print the arguments
verbose_print('Input file: {}'.format(args.input_file))
verbose_print('Output file: {}'.format(args.output_file))

# Load the CSV file into a pandas DataFrame, using the first row as column names
df = pd.read_csv(args.input_file)

# Get the column names
x_col = df.columns[0]
y_cols = df.columns[1:]

# Set seaborn style
sns.set(style='whitegrid')

# Create a new figure and axis
fig, ax = plt.subplots()

# Plot each y-axis series on the same plot, using the column names as the labels
for y_col in y_cols:
    sns.lineplot(data=df, x=x_col, y=y_col, ax=ax, label=y_col)

# Add labels and title
ax.set_xlabel(x_col)
ax.set_ylabel('Value')
ax.set_title('Plot of CSV data')

# Add a legend
ax.legend()

# Save the figure to the output file
plt.savefig(args.output_file)

# print the DataFrame
verbose_print(df)
