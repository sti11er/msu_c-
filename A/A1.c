#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char* argv[]) {
    int fd = open(argv[1], O_RDWR);
    if (fd == -1) {
        return 1;
    }
    char byte;
    ssize_t t = read(fd, &byte, 1);
    if (t == 1) {
        byte ^= 0b00001010; 
        lseek(fd, 0, SEEK_SET);
        write(fd, &byte, 1);
    }
    close(fd);
    return 0;
}