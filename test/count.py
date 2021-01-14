num_ones = 0
num_zeros = 0

with open('samples.bin', 'rb') as f:
    try:
        while True:
            val = ord(f.read(1))

            for _ in range(0, 8):
                if (val & 1) % 2:
                    num_ones += 1
                else:
                    num_zeros += 1
                val = int(val / 2)
    except:
        pass

print(num_ones)
print(num_zeros)
