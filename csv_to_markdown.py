import os
import sys
import csv

def convert_csv_to_markdown():
    """
    Converts all CSV files in the project's 'Content/DataTablesAsCSV' directory
    to Markdown tables in 'Documentation/DataTables'.
    This script is robust to the current working directory.
    """
    try:
        # The absolute path to the directory containing this script.
        script_dir = os.path.dirname(os.path.realpath(__file__))

        # Define absolute paths for source and destination directories.
        csv_dir = os.path.join(script_dir, 'Content', 'DataTablesAsCSV')
        md_dir = os.path.join(script_dir, 'Documentation', 'generated', 'DataTables')

        # Check if the source directory exists.
        if not os.path.exists(csv_dir):
            print(f"Error: Source directory not found at '{csv_dir}'. No CSV files to convert.")
            return

        # Ensure the output directory exists.
        if not os.path.exists(md_dir):
            print(f"Creating output directory at '{md_dir}'...")
            os.makedirs(md_dir)

        print(f"Scanning for CSV files in '{csv_dir}'...")
        csv_files = [f for f in os.listdir(csv_dir) if f.endswith('.csv')]

        if not csv_files:
            print("No CSV files found to convert.")
            return

        print(f"Found {len(csv_files)} CSV file(s). Starting conversion...")
        for filename in csv_files:
            csv_path = os.path.join(csv_dir, filename)
            md_filename = os.path.splitext(filename)[0] + '.md'
            md_path = os.path.join(md_dir, md_filename)

            with open(csv_path, 'r', encoding='utf-8') as f_csv:
                reader = csv.reader(f_csv)
                try:
                    header = next(reader)
                except StopIteration:
                    print(f"Skipping empty file: {filename}")
                    continue

                with open(md_path, 'w', encoding='utf-8') as f_md:
                    # Write header
                    f_md.write('| ' + ' | '.join(header) + ' |\n')
                    f_md.write('| ' + ' | '.join(['---'] * len(header)) + ' |\n')

                    # Write rows
                    for row in reader:
                        f_md.write('| ' + ' | '.join(row) + ' |\n')
            print(f"  -> Converted '{filename}' to '{md_filename}'")

        print("Markdown conversion complete. ✨")

    except Exception as e:
        print(f"An unexpected error occurred: {e}")
        # Exit with a non-zero code to indicate failure to build tools.
        sys.exit(1)

if __name__ == '__main__':
    convert_csv_to_markdown()