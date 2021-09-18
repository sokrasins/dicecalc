import time
import argparse
import serial
from tqdm import tqdm

class EntropyCollector:

    BYTES_IN_MSG = 24
    BITS_PER_BYTE = 7
    UPDATE_INTERVAL = 0.5 

    def __init__(self, port, baud=921600):
       self.ser = serial.Serial()
       self.ser.baudrate = baud
       self.ser.port = port

    def open(self):
        self.ser.open()

    def collect(self, bits):
        bytes_to_collect = int(bits/self.BITS_PER_BYTE) + 1
        collected_bytes = 0

        entropy = bytearray([0] * (bytes_to_collect + self.BYTES_IN_MSG))

        for i in tqdm(range(int(bytes_to_collect/24)), desc="Collecting Samples..."):
            rx_msg = self.ser.read_until()[:-1]
            entropy[collected_bytes:collected_bytes+len(rx_msg)] = rx_msg 
            collected_bytes += len(rx_msg)

        entropy = entropy[:collected_bytes]
        compact_bytes = self._reshape_entropy_bytes(entropy)

        return bytearray(compact_bytes)

    def _reshape_entropy_bytes(self, samp):
        num_bits = len(samp) * 7

        bool_array = [0] * num_bits

        # Convert to bool array first
        idx = 0
        for byte in samp:
            for i in range(7):
                bool_array[idx] = byte & 1
                byte = byte >> 1
                idx += 1
        
        return bool_array
        

    def close(self):
        self.ser.close()


def get_args():
    parser = argparse.ArgumentParser()

    parser.add_argument('--port', '-p',
            help='Serial port to collect samples from'
    )

    parser.add_argument('--samples', '-s', default=10000000, type=int,
            help='Number of bit samples to collect (default: 10,000,000)'
    )

    return parser.parse_args()


if __name__ == '__main__':
    args = get_args()

    ec = EntropyCollector(args.port)
    ec.open()
    entropy = ec.collect(args.samples)
    ec.close()

    filename = time.strftime('entropy-%Y%m%d-%H%M%S.bin')
    with open(filename, 'wb') as f:
        f.write(entropy)

