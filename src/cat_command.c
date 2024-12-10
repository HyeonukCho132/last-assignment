#include <fcntl.h>  // for open
#include <unistd.h> // for read, write, close
#include <stdio.h>  // for perror

#include "cat_command.h"


#define BUFFER_SIZE 1024

void my_cat(const char *filename) {
    int fd;
    char buffer[BUFFER_SIZE];
    ssize_t bytes_read;

    // 1. 파일 열기
    fd = open(filename, O_RDONLY); // 읽기 전용으로 파일 열기
    if (fd == -1) {
        perror("open");
        return;
    }

    // 2. 파일 읽기 및 출력
    while ((bytes_read = read(fd, buffer, BUFFER_SIZE)) > 0) {
        if (write(STDOUT_FILENO, buffer, bytes_read) != bytes_read) {
            perror("write");
            close(fd);
            return;
        }
    }

    if (bytes_read == -1) {
        perror("read");
    }

    // 3. 파일 닫기
    close(fd);
}
