// L DEVANSH CS21B2023

#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
    int fifoFileDescriptor;
    char *fifoPath = "/tmp/myfifo";  // Path to the FIFO

    // Creating the FIFO file with read and write permissions (0666)
    if (mkfifo(fifoPath, 0666) == -1) {
        perror("Error creating FIFO file");
        return 1;
    }

    int numberA;
    printf("Enter a number A: ");
    scanf("%d", &numberA);

    // Opening the FIFO file in write-only mode
    fifoFileDescriptor = open(fifoPath, O_WRONLY);
    if (fifoFileDescriptor == -1) {
        perror("Error opening FIFO for writing");
        return 1;
    }

    // Writing the numberA to the FIFO file
    int bytesWritten = write(fifoFileDescriptor, &numberA, sizeof(numberA));
    if (bytesWritten == -1) {
        perror("Error writing to FIFO");
        return 1;
    }
    printf("Written A = %d to FIFO file\n", numberA);

    // Closing the FIFO file
    close(fifoFileDescriptor);

    int onesComplementB;
    // Opening the FIFO file in read-only mode
    fifoFileDescriptor = open(fifoPath, O_RDONLY);
    if (fifoFileDescriptor == -1) {
        perror("Error opening FIFO for reading");
        return 1;
    }

    // Reading the ones complement (B1) from the FIFO file
    int bytesRead = read(fifoFileDescriptor, &onesComplementB, sizeof(onesComplementB));
    if (bytesRead == -1) {
        perror("Error reading from FIFO");
        return 1;
    }
    printf("Reading B1 (one's complement of A) from FIFO file\n");
    printf("B1 = %d\n", onesComplementB);

    // Closing the FIFO file
    close(fifoFileDescriptor);

    // Removing the FIFO file
    unlink(fifoPath);

    return 0;
}
