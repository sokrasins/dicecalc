from collections import deque
import matplotlib.pyplot as plt
from tqdm import tqdm
import argparse

class EntropyChecker:

    MIN_DATA = 80000
    MAX_COUNT = 0x4000

    def __init__(self):
        self.total_bits = 0
        self.bit_hist = deque([], 16)
        self.prev_bit = False

        self.zeros = [0] * 0x10000
        self.ones = [0] * 0x10000

        self.num_sampled = 0

        self.current_prob = 1.0

        self.entropy_bits = 0

    def add_bit(self, bit):
        self.total_bits += 1
        self.bit_hist.append(self.prev_bit)
        self.prev_bit = bit

        hist = self._convert_bithist_to_num()

        cur_zeros = self.zeros[hist]
        cur_ones = self.ones[hist]
        total = cur_zeros + cur_ones

        if bit and (cur_ones != 0):
            self.current_prob *= cur_ones/total;
        elif (not bit) and (cur_zeros != 0):
            self.current_prob *= cur_zeros/total;

        while self.current_prob <= 0.5:
            self.current_prob *= 2.0;
            self.entropy_bits += 1

        if bit:
            self.ones[hist] += 1
            if self.ones[hist] == self.MAX_COUNT:
                self._scale_stats()
        else:
            self.zeros[hist] += 1
            if self.zeros[hist] == self.MAX_COUNT:
                self._scale_stats()

        self._scale_entropy()
        #self._scale_zero_one_counts()

    def _scale_entropy(self):
        if self.total_bits >= self.MIN_DATA:
            self.entropy_bits >>= 1
            self.total_bits >>= 1

    def _scale_zero_one_counts(self):
        #TODO
        pass

    def _scale_stats(self):
        self.zeros = list(map(
            lambda x : x >> 1,
            self.zeros
        ))

        self.ones = list(map(
            lambda x : x >> 1,
            self.ones
        ))

    def _convert_bithist_to_num(self):
        val = 0
        for i, bit in enumerate(self.bit_hist):
            val |= bit << (len(self.bit_hist) - i - 1)
        return val

    def get_entropy(self):
        return self.entropy_bits/self.total_bits

if __name__ == '__main__':

    parser = argparse.ArgumentParser()

    parser.add_argument('filename',
                        type=str,
                        help='input entropy bit file'
                        )

    parser.add_argument('--bits', '-b',
                        type=int,
                        default=0,
                        help='Number of bytes to take in (default: all)'
                        )

    parser.add_argument('--kernel', '-k',
                        type=int,
                        default=10000,
                        help='Number of bits between entropy sample'
                        )

    args = parser.parse_args()

    with open(args.filename, 'rb') as f:
        rand_bits = bytearray(f.read())
        if args.bits > 0:
            rand_bits = rand_bits[:args.bits]

        num_blocks = int(len(rand_bits) / args.kernel)

        ent_check = EntropyChecker()
        running_entropy = []

        fig = plt.figure()
        plt.ion()
        plt.show()

        for j in tqdm(range(num_blocks), desc='Calculate entropy'):
            base_idx = j * args.kernel
            for i in range(args.kernel):
                ent_check.add_bit(rand_bits[base_idx+i])

            entropy = ent_check.get_entropy()
            running_entropy.append(entropy)

            plt.cla()
            plt.plot(running_entropy)
            plt.pause(.001)






