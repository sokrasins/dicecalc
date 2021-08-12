import argparse
import subprocess
import sys

def log(log_file, text):
    print(text)
    log_file.write(text + '\n')

def print_test_heading(log_file, text):
    log(log_file, "*************************************")
    log(log_file, "*** Running " + text + "...")
    log(log_file, "*************************************")

def call_test_command(log_file, cmd, stdin=None):
    log(log_file, 'COMMAND: ' + ' '.join(cmd) + '\n')
    process = subprocess.Popen(
        cmd,
        stdin=stdin,
        stdout=subprocess.PIPE,
        stderr=subprocess.STDOUT)

    for c in iter(lambda: process.stdout.read(1), b''):
        sys.stdout.buffer.write(c)
        log_file.write(c.decode('utf-8'))


if __name__ == '__main__':

    parser = argparse.ArgumentParser()
    parser.add_argument('filename',
                        type=str,
                        help='binary file to be plotted')
    args = parser.parse_args()

    log_filename = args.filename.replace('.bin', '') + '-results.txt'
    test_log = open(log_filename, 'w')

    # ent
    print_test_heading(test_log, 'ent')
    call_test_command(test_log, ['ent', args.filename])

    # SP800-90b IID
    print_test_heading(test_log, 'SP800-90b IID')
    call_test_command(test_log, ['./ent-tests/ea_iid', '-v', args.filename])

    # SP800-90b Non-IID
    print_test_heading(test_log, 'SP800-90b Non-IID')
    call_test_command(test_log, ['./ent-tests/ea_non_iid', '-v', args.filename])

    # rngtest
    print_test_heading(test_log, 'rngtest')
    with open(args.filename) as f:
        call_test_command(test_log, ['rngtest'], stdin=f)

    # Reallyreallyrandom IID test
    print_test_heading(test_log, 'Reallyreallyrandom IID test')
    call_test_command(test_log, ['java', '-jar', './ent-tests/iid-tester.jar', args.filename, 'results.json'])

    test_log.close()
