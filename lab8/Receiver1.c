// L DEVANSH CS21B2023

#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
    int fd;
    char *fifoPath = "/tmp/myfifo";  // Path to the FIFO

    int A;
    // Open the FIFO file in read-only mode
    fd = open(fifoPath, O_RDONLY);
    if (fd == -1) {
        perror("Error opening FIFO for reading");
        return 1;
    }

    // Read the integer (A) from the FIFO file
    int bytesRead = read(fd, &A, sizeof(A));
    if (bytesRead == -1) {
        perror("Error reading from FIFO");
        return 1;
    }
    printf("Reading A from FIFO file\n");
    printf("A = %d\n", A);

    // Close the FIFO file
    close(fd);

    // Calculate the one's complement (B1)
    int binaryRepresentation[32];
    int i = 0;
    int tempA = A;
    while (tempA > 0) {
        binaryRepresentation[i] = tempA % 2;
        tempA = tempA / 2;
        i++;
    }
    int B1 = 0;
    int k = 1;
    for (int j = 0; j < i; j++) {
        if (binaryRepresentation[j] == 0) {
            binaryRepresentation[j] = 1;
        } else {
            binaryRepresentation[j] = 0;
        }
        B1 = B1 + binaryRepresentation[j] * k;
        k = k * 2;
    }

    // Open the FIFO file in write-only mode
    fd = open(fifoPath, O_WRONLY);
    if (fd == -1) {
        perror("Error opening FIFO for writing");
        return 1;
    }

    // Write the one's complement (B1) to the FIFO file
    int bytesWritten = write(fd, &B1, sizeof(B1));
    if (bytesWritten == -1) {
        perror("Error writing to FIFO");
        return 1;
    }
    printf("B1 is the one's complement of A\n");
    printf("Written B1 = %d to FIFO file\n", B1);

    // Close the FIFO file
    close(fd);

    return 0;
}
