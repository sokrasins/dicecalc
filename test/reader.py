import sys
import threading
from serial import Serial
from serial.tools import list_ports

class Reader:

    class ReadThread(threading.Thread):

        def __init__(self, ser, eol, rx_cb):
            super().__init__()
            self.ser = ser
            self.eol = eol
            self.rx_cb = rx_cb
            self._running = True

        # Call to halt serial read
        def terminate(self):
            self._running = False

        # Continuously read until told to halt
        def run(self):
            while self._running:
                self._read_from_port()

        # Read a single line
        def _read_from_port(self):
            new_line = self.ser.read_until(self.eol)
            if new_line:
                new_line = new_line[:-2]
                self.rx_cb(new_line)


    def __init__(self, cb=None):
        eol = b'\xff\xff'
        rx_cb = cb if cb is not None else self._default_cb

        # Find any valid connected devices
        ports = self._list_valid_ports()
        if not ports:
            print("No valid devices connected. Exiting...")
            sys.exit()

        # Set up serial port. Choose the first valid device.
        self.ser = None
        self.ser = Serial(ports[0].device, 115200)
        self.ser.flushInput()
        self.ser.flushOutput()

        # Star thread to auto-read 
        self.thread = Reader.ReadThread(self.ser, eol, rx_cb)
        self.thread.start()

    # Return a list of all devices with the specified VID and PID
    def _list_valid_ports(self, vid=0x0483, pid=0x374B):
        result = []
        for port in list_ports.comports():
            if port.vid == vid and port.pid == pid:
                result.append(port)
        return result

    def close(self):
        self.thread.terminate()
        self.thread.join()
        self.ser.close()

    # Default callback when data is received and application doesn't provide
    # its own callback. Logs the data.
    def _default_cb(self, msg):
        print(msg.decode('utf-8', errors='backslashreplace'))

    # Make this "with-able"
    def __enter__(self):
        return self

    def __exit__(self, exc_type, exc_val, exc_tb):
        self.close()

    def block_while_reading(self):
        try:
            while True:
                pass
        except KeyboardInterrupt:
            pass

if __name__ == '__main__':
    with Reader():
        try:
            while True:
                pass
        except KeyboardInterrupt:
            pass

    print("Port closed")
