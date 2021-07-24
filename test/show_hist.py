import matplotlib.pyplot as plt
import argparse

if __name__ == '__main__':

    parser = argparse.ArgumentParser()
    parser.add_argument('filename',
                        type=str,
                        help='binary file to be plotted')

    args = parser.parse_args()

    with open(args.filename, 'rb') as f:
        rand_bytes = bytearray(f.read())
        plt.hist(rand_bytes, bins=range(0, 256))
        plt.show()
