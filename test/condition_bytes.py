import sys
from tqdm import tqdm
import hashlib
import argparse

def reshape(data, bytes_per_hash):
    num_blocks = int(len(data)/bytes_per_hash)
    reshaped_data = [[0]*bytes_per_hash]*num_blocks

    for i in tqdm(range(num_blocks), desc="Reshaping bytes..."):
        reshaped_data[i] = data[i*bytes_per_hash:(i+1)*bytes_per_hash]

    return reshaped_data

def condition(data):

    hashed_data = [bytearray([0] * 32)] * len(data)
    with tqdm(total=len(data), desc="Hashing blocks...") as pbar:
        for i, block in enumerate(data):
            m = hashlib.sha256()
            m.update(block)
            #m.update(i.to_bytes(4, 'little'))
            result = m.digest()
            hashed_data[i] = result
            pbar.update(1)
    return hashed_data

if __name__ == '__main__':
    parser = argparse.ArgumentParser()

    parser.add_argument('filename',
                        type=str,
                        help='input entropy byte file')

    parser.add_argument('--bytes', '-b',
                        type=int,
                        default=32,
                        help='How many bytes per hash (default: 32)')

    args = parser.parse_args()

    if args.bytes < 32:
        print("ERROR: need at least 256 bits per hash. Quitting...")
        sys.exit()

    with open(args.filename, 'rb') as f:
        rand_bytes = bytearray(f.read())
        print("Imported data: %d bytes" % (len(rand_bytes)))

        reshaped_bytes = reshape(rand_bytes, args.bytes)
        conditioned_blocks = condition(reshaped_bytes)
        conditioned = b"".join(conditioned_blocks)

        print("Conditioned data: %d bytes" % (len(conditioned)))

        new_filename = 'conditioned-' + args.filename

        with open(new_filename, 'wb') as f2:
            f2.write(conditioned)

