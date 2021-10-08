import argparse
import matplotlib.pyplot as plt
import subprocess
import sys
import os

def log(log_file, text):
    print(text)
    log_file.write(text + '\n')

def call_test_command(log_file, cmd, stdin=None):
    if log_file is not None:
        log(log_file, 'COMMAND: ' + ' '.join(cmd) + '\n')

    process = subprocess.Popen(
        cmd,
        stdin=stdin,
        stdout=subprocess.PIPE,
        stderr=subprocess.STDOUT)

    std_out = ""
    for c in iter(lambda: process.stdout.read(1), b''):
        #sys.stdout.buffer.write(c)
        string_log = c.decode('utf-8')
        if log_file is not None:
            log_file.write(string_log)
        std_out += string_log

    #search_phrase = 'min(H_original, 8 X H_bitstring): '
    search_phrase = "h': "
    result_idx = std_out.find(search_phrase)

    return float(std_out[result_idx+len(search_phrase):].strip())

if __name__ == '__main__':

    parser = argparse.ArgumentParser()
    parser.add_argument('filename',
                        type=str,
                        help='binary file'
                        )
    parser.add_argument('--log', '-l',
                        action='store_true',
                        help='If specified, writes the output of the entropy assessment to files'
                        )
    args = parser.parse_args()

    log_filename = args.filename.replace('.bin', '')

    entropy_bytes = None
    with open(args.filename, 'rb') as entropy_file:
        entropy_bytes = entropy_file.read()

    if entropy_bytes is None:
        print("Invalid entropy file. Quitting...")
        sys.exit()

    num_bytes = len(entropy_bytes)
    num_runs = int(num_bytes/1000000)

    print("File %s has %d bytes. Running on %d blocks" % (
        args.filename,
        num_bytes,
        num_runs
    ))

    current_block = [0] * 1000000

    entropy = []

    for i in range(num_runs):
        if os.path.exists('temp.bin'):
            os.remove('temp.bin')

        with open('temp.bin', 'wb') as temp_bin:
            temp_bin.write(entropy_bytes[i*1000000:(i+1)*1000000])

        log_file = log_filename + ('-iter-%d-.txt' % (i))

        test_log = None
        if args.log:
            test_log = open(log_file, 'w')

        # SP800-90b Non-IID
        entropy_result = call_test_command(test_log,
                          ['./ea_non_iid',
                           '-c',
                           '-v',
                           'temp.bin']
                         )
        entropy.append(entropy_result)

        if test_log is not None:
            test_log.close()

        print("%d: %f" % (
            i,
            entropy_result
        ))

    print("Done!")

    plt.hist(entropy)
    plt.ylabel('Count')
    plt.xlabel('Min Entropy')
    plt.show()




