import sys
import serial

def write_port(device_name, command):
    buf = bytearray(255)
    try:
        # Open serial port
        ser = serial.Serial(device_name, 9600, timeout=1)
        
        # Write command to serial port
        ser.write(command.encode())
        # time.sleep(20)
        # Read response from serial port
        m = ser.readinto(buf)
        ser.close()
        
        return buf[:m].decode()
    except serial.SerialException as e:
        sys.stderr.write(f"Error: {e}\n")
        sys.exit(1)

def usage():
    print("serial_drive <device> <command>")
    print("serial_drive /dev/ttyS0 [C|I|A|G|S|V]")

def main():
    if len(sys.argv) != 3:
        usage()
        sys.exit(1)
    
    device_name = sys.argv[1]
    command = sys.argv[2]
    response = write_port(device_name, command)
    print(response)

if __name__ == "__main__":
    # main()
    con_path = "/dev/ttyUSB0"
    write_port(con_path, "V")
    write_port(con_path, "C")
