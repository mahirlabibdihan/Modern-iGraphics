# Iterate all the .cpp files in examples directory and build them with build.bat script.

import os
import subprocess


def build_cpp_files():
    examples_dir = 'examples'
    build_script = 'build.bat'

    print(f'Building iMain.cpp...')
    subprocess.run([build_script, "iMain.cpp"], check=True,
                   stdout=subprocess.DEVNULL)

    # Iterate through all files in the examples directory
    for root, dirs, files in os.walk(examples_dir):
        for file in files:
            if file.endswith('.cpp'):
                cpp_file_path = os.path.join(root, file)
                print(f'Building {cpp_file_path}...')

                # Run the build script with the cpp file as an argument (suppress output)
                subprocess.run([build_script, cpp_file_path], check=True,
                               stdout=subprocess.DEVNULL)


if __name__ == '__main__':

    build_cpp_files()
    print("All .cpp files have been built successfully.")
