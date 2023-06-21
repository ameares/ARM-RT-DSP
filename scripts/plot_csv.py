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

# Load the CSV file into a pandas DataFrame
df = pd.read_csv(args.input_file)

# Set seaborn style
sns.set(style='whitegrid')

# Create a new figure and axis
fig, ax = plt.subplots()

# Plot the data
sns.lineplot(data=df, x='input_value', y='output_value', ax=ax)

# Add labels and title
ax.set_xlabel('Input value')
ax.set_ylabel('Output value')
ax.set_title('Input vs Output values')

# Add a legend
# ax.legend()

# Save the figure to the output file
plt.savefig(args.output_file)

# print the DataFrame
verbose_print(df)
