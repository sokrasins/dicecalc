from reader import Reader

num_bits = 0
sampfile = open("samples.bin", "wb")

def cb(msg):
    global num_bits
    global sampfile
    new_vals = []

    for i in range(0, len(msg), 2):
        new_vals.append(msg[i] | (msg[i+1] << 4))

    num_bits += (len(new_vals) * 8)
    sampfile.write(bytearray(new_vals))
    print("Received %d bits" % (num_bits))

with Reader(cb=cb):
    try:
        while True:
            pass
    except KeyboardInterrupt:
        pass

sampfile.close()
print("Port closed")

