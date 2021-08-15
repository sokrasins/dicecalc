"""
Demonstrates how to stream using a callback to read stream, which is useful
for streaming in external clock stream mode.
"""

from datetime import datetime
import matplotlib.pyplot as plt
import sys
import threading
import time
import traceback
import argparse

from labjack import ljm


# Class to hold our stream information
class StreamInfo:
    def __init__(self):
        self.handle = 0
        self.scanRate = 0
        self.scansPerRead = 0
        self.streamLengthMS = 0
        self.numberOfReadsToPerform = 0
        self.done = False

        self.numAddresses = 0
        self.aScanList = 0
        self.aScanListNames = 0

        self.aDataSize = 0
        self.aData = None

        self.streamRead = 0
        self.totSkip = 0
        self.totScans = 0

        self.bin_residue = []
        self.byte_samps = []


printLock = threading.Lock()
def printWithLock(string):
    global printLock
    with printLock:
        print(string)


# Function to pass to the callback function. This needs have one
# parameter/argument, which will be the handle.
def myStreamReadCallback(arg):
    global si

    if si.handle != arg:
        printWithLock("myStreamReadCallback - Unexpected argument: %d" % (arg))
        return

    # Check if stream is done so that we don't output the print statement below.
    if si.done:
        return

    string = "\niteration: %3d\n" % si.streamRead
    si.streamRead += 1

    try:
        # Read data from the stream
        ret = ljm.eStreamRead(si.handle)
        si.aData = ret[0]
        deviceScanBacklog = ret[1]
        ljmScanBackLog = ret[2]

        if len(si.aData) < 8:
            return

        # Collapse the data into bytes
        bin_samps = si.bin_residue + list(map(lambda x : int(x) >> 4 & 1, si.aData))
        si.bin_residue = []

        last_full_byte = 8 * int(len(bin_samps) / 8)
        si.bin_residue = bin_samps[last_full_byte:]
        si.byte_samps += reduce_bin_to_byte(bin_samps[:last_full_byte])

        scans = len(si.aData) / si.numAddresses
        si.totScans += scans

        # Count the skipped samples which are indicated by -9999 values. Missed
        # samples occur after a device's stream buffer overflows and are
        # reported after auto-recover mode ends.
        curSkip = si.aData.count(-9999.0)
        si.totSkip += curSkip
        percent_done = 100 * float(si.streamRead) / float(si.numberOfReadsToPerform)

        string = "  Percent done: %0.2f Total bytes: %d" % (percent_done, len(si.byte_samps))
        string += "  Scans Skipped = %0.0f, Scan Backlogs: Device = %i, LJM = %i" % \
                (curSkip/si.numAddresses, deviceScanBacklog, ljmScanBackLog)
        printWithLock(string)

    # If LJM has called this callback, the data is valid, but LJM_eStreamRead
    # may return LJME_STREAM_NOT_RUNNING if another thread (such as the Python
    # main thread) has stopped stream.
    except ljm.LJMError as err:
        if err.errorCode == ljm.errorcodes.STREAM_NOT_RUNNING:
            printWithLock("eStreamRead returned LJME_STREAM_NOT_RUNNING.")
        else:
            printWithLock(err)


def reduce_bin_to_byte(bin_list):
    bin_chunks = [bin_list[i:i+8] for i in range(0, len(bin_list), 8)]

    byte_array = []
    for chunk in bin_chunks:
        byte_val = 0
        for place, bin_val in enumerate(chunk):
            byte_val += bin_val << (7-place)
        byte_array.append(byte_val)

    return byte_array


# Create the global StreamInfo class which is used to pass information between
# the callback and main code.
si = StreamInfo()


if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument('--samples', '-s', type=int, default=100000000,
                        help='Total boolean samples to collect (default: 100,000,000)')
    parser.add_argument('--rate', '-r', type=int, default=20000,
                        help='Sample rate in Hz (default: 20,000)')
    parser.add_argument('--plot', '-p', action='count', default=0,
                        help='Plot histogram as samples are collected')
    args = parser.parse_args()

    if args.rate > 40000 or args.rate < 0:
        print("ERROR: Invalid sample rate, max is 40 kSa/sec and must be positive. Exiting...")
        sys.exit()

    param_log = "Input Params:"
    param_log += "\n  samples: %d" % (args.samples)
    param_log += "\n  rate: %d" % (args.rate)
    print(param_log)

    # Open first found T4 LabJack
    handle = ljm.openS("T4", "ANY", "ANY")  # Any device, Any connection, Any identifier

    info = ljm.getHandleInfo(handle)
    print("Opened a LabJack with Device type: %i, Connection type: %i,\n"
          "Serial number: %i, IP address: %s, Port: %i,\nMax bytes per MB: %i" %
          (info[0], info[1], info[2], ljm.numberToIP(info[3]), info[4], info[5]))

    deviceType = info[0]

    # Disable scaling of scream to analog range
    ljm.writeLibraryConfigS("LJM_STREAM_AIN_BINARY", 1)


    # Stream Configuration
    si.aScanListNames = ["FIO_STATE"]
    si.numAddresses = len(si.aScanListNames)
    si.aScanList = ljm.namesToAddresses(si.numAddresses, si.aScanListNames)[0]
    si.scanRate = args.rate
    si.scansPerRead = int(si.scanRate / 2)

    si.numberOfReadsToPerform = int(args.samples / si.scansPerRead)
    si.done = False
    si.aDataSize = si.numAddresses * si.scansPerRead
    si.handle = handle

    try:
        # When streaming, negative channels and ranges can be configured for
        # individual analog inputs, but the stream has only one settling time
        # and resolution.

        # LabJack T4 configuration
        t0 = datetime.now()

        # Configure and start stream
        si.scanRate = ljm.eStreamStart(handle, si.scansPerRead, si.numAddresses, si.aScanList, si.scanRate)
        print("\nStream started with a scan rate of %0.0f Hz." % si.scanRate)

        # Set the callback function.
        ljm.setStreamCallback(handle, myStreamReadCallback)

        printWithLock("Stream running and callback set.")
        printWithLock("Waiting until eStreamRead has been called %d times."
            % si.numberOfReadsToPerform)

        if args.plot:
            fig = plt.figure()
            hist = plt.hist(si.byte_samps, bins=256)
            plt.ion()
            plt.show()

        while (si.streamRead < si.numberOfReadsToPerform):
            # While we're collecting data update the histogram
            if args.plot:
                plt.cla()
                plt.hist(si.byte_samps, bins=256)
                plt.title("%d Byte Samples" % (len(si.byte_samps)))
                plt.ylabel("Counts")
                plt.xlabel("Byte Values")
                plt.pause(.001)

            time.sleep(.1)

        t1 = datetime.now()

        printWithLock("\nStreaming done. %.3f milliseconds have elapsed since eStreamStart" %
              ((t1-t0).seconds*1000 + float((t1-t0).microseconds)/1000))

    except ljm.LJMError:
        ljme = sys.exc_info()[1]
        printWithLock(ljme)
    except Exception:
        e = sys.exc_info()[1]
        printWithLock(e)

    try:
        printWithLock("\nStop Stream")
        si.done = True
        ljm.eStreamStop(handle)
    except ljm.LJMError:
        ljme = sys.exc_info()[1]
        print(ljme)
    except Exception:
        e = sys.exc_info()[1]
        print(e)

    # Close handle
    ljm.close(handle)

    filename = time.strftime('%Y%m%d-%H%M%S.bin')
    filename = ('entropy-%dSaps-' % args.rate) + filename
    with open(filename, 'wb') as f:
        f.write(bytearray(si.byte_samps))

