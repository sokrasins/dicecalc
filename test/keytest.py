from reader import Reader

def cb(msg):
    key = msg[0]
    state = ""

    if msg[1] == 0:
        state = "DOWN"
    else:
        state = "UP"

    print("key %d %s" % (
        key,
        state
    ))

with Reader(cb=cb) as rd:
    rd.block_while_reading()

print("done")
