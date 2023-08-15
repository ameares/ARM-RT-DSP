import argparse
import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns

def parse_arguments():
    # Set up argument parser
    parser = argparse.ArgumentParser(description='Generate a plot from CSV data.')
    parser.add_argument('input_file', type=str, help='Path to the input CSV file.')
    parser.add_argument('output_file', type=str, help='Path to the output PNG file.')
    parser.add_argument('-v', '--verbose', action='store_true', help='Print verbose output.')
    return parser.parse_args()

def verbose_print(args, *aargs, **kwargs):
    # Define a function to print if verbose is set
    if args.verbose:
        print(*aargs, **kwargs)

def load_data(input_file):
    # Load the CSV file into a pandas DataFrame, using the first row as column names
    try:
        df = pd.read_csv(input_file)
    except Exception as e:
        print(f"Error loading data from {input_file}: {e}")
        return None
    return df

def plot_data(df, output_file):
    # Get the column names
    x_col = df.columns[0]
    y_cols = df.columns[1:]

    # Set seaborn style
    sns.set(style='whitegrid')

    # Create a new figure and axis
    fig, ax = plt.subplots()

    # Plot each y-axis series on the same plot, using the column names as the labels
    try:
        for y_col in y_cols:
            sns.lineplot(data=df, x=x_col, y=y_col, ax=ax, label=y_col)
    except Exception as e:
        print(f"Error plotting data: {e}")
        return

    # Add labels and title
    ax.set_xlabel(x_col)
    ax.set_title('Plot of CSV data')

    # Add a legend
    ax.legend()

    # Save the figure to the output file
    try:
        plt.savefig(output_file)
    except Exception as e:
        print(f"Error saving plot to {output_file}: {e}")

def main():
    args = parse_arguments()

    # print the arguments
    verbose_print(args, 'Input file: {}'.format(args.input_file))
    verbose_print(args, 'Output file: {}'.format(args.output_file))

    df = load_data(args.input_file)
    if df is not None:
        plot_data(df, args.output_file)

        # print the DataFrame
        verbose_print(args, df)

if __name__ == "__main__":
    main()
