#include <stdio.h>
#include <string.h>
#include <windows.h>

char* write_port(char *device_name, char *command, char *buf) {
    HANDLE hSerial;
    DCB dcbSerialParams = {0};
    COMMTIMEOUTS timeouts = {0};
    DWORD dwBytesWritten, dwBytesRead;

    hSerial = CreateFile(device_name, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

    if (hSerial == INVALID_HANDLE_VALUE) {
        fprintf(stderr, "Unable to open %s\n", device_name);
        return NULL;
    }

    dcbSerialParams.DCBlength = sizeof(dcbSerialParams);

    if (!GetCommState(hSerial, &dcbSerialParams)) {
        fprintf(stderr, "Error getting serial port state\n");
        CloseHandle(hSerial);
        return NULL;
    }

    dcbSerialParams.BaudRate = CBR_9600;
    dcbSerialParams.ByteSize = 8;
    dcbSerialParams.StopBits = ONESTOPBIT;
    dcbSerialParams.Parity = NOPARITY;

    if (!SetCommState(hSerial, &dcbSerialParams)) {
        fprintf(stderr, "Error setting serial port state\n");
        CloseHandle(hSerial);
        return NULL;
    }

    timeouts.ReadIntervalTimeout = 50;
    timeouts.ReadTotalTimeoutConstant = 50;
    timeouts.ReadTotalTimeoutMultiplier = 10;
    timeouts.WriteTotalTimeoutConstant = 50;
    timeouts.WriteTotalTimeoutMultiplier = 10;

    if (!SetCommTimeouts(hSerial, &timeouts)) {
        fprintf(stderr, "Error setting timeouts\n");
        CloseHandle(hSerial);
        return NULL;
    }

    if (!WriteFile(hSerial, command, 1, &dwBytesWritten, NULL)) {
        fprintf(stderr, "WriteFile failed!\n");
        CloseHandle(hSerial);
        return NULL;
    }

    if (!ReadFile(hSerial, buf, 255, &dwBytesRead, NULL)) {
        fprintf(stderr, "ReadFile failed!\n");
        CloseHandle(hSerial);
        return NULL;
    }

    buf[dwBytesRead] = '\0';

    CloseHandle(hSerial);

    return buf;
}

void usage() {
    printf("serial_drive <device> <command>\n");
    printf("serial_drive COM1 [C|I|A|G|S|V]\n");

    printf("V: Signup or version(sometimes required as first command)");
    printf("C: Reset or Calibrate unit");
    printf("I: Input disc from bin to drive");
    printf("A: Accept disc from drive to output bin");
    printf("G: Get disc from drive and hold in picker(required before R and sometimes A)");
    printf("R: Move disc from picker to Reject bin");
    printf("S: Status of mechanism Trial and Error");
    printf("B: 'G'rab from Printer");
    printf("H: If 'G'rabbing, put in CD Tray");
    printf("P: Same as G");
    printf("K: Input stack -> Printer,");
    printf("If currently 'G'rabbing,");
    printf("it will move that to the input queue,");
    printf("drop it, and then move it to the printer.");
    printf("D: Down");
    printf("U: Up");
    printf("L: Load Printer");
    printf("M: Drop");
    printf("N: Get from Printer");
    printf("Q: Accept from Printer");
    printf("T: Test(input -> cd_tray, cd_tray -> accept_bin)");
    printf("W: some type of 3 number status");


int main(int argc, char *argv[]) {
    char buf[255];

    if (argc != 3) {
        usage();
        return 1;
    }

    if (write_port(argv[1], argv[2], buf) != NULL) {
        printf("%s\n", buf);
        return 0;
    }

    return 1;
}
