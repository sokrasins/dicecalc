import argparse

if __name__ == '__main__':

    parser = argparse.ArgumentParser()
    parser.add_argument('filename',
                        type=str,
                        help='file to convert')

    args = parser.parse_args()

    byte_array = []
    count = [0, 0]

    with open(args.filename, 'rb') as f:
        rand_bits = bytearray(f.read())
        print("Number of bits: %d" % (len(rand_bits)))

        idx = 0;
        new_byte = 0
        for bit in rand_bits[:8*int(len(rand_bits)/8)]:
            new_byte |= bit << idx
            idx += 1

            count[bit] += 1

            if idx >= 8:
                byte_array.append(new_byte)
                idx = 0
                new_byte = 0

        print("Number of bytes: %d" % (len(byte_array)))
        print("Zeroes:ones: %d:%d" % (count[0], count[1]))

        new_filename = 'bytes-' + args.filename
        with open(new_filename, 'wb') as f:
            f.write(bytearray(byte_array))



