#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <string.h>

int main()
{
    int fd;
    char *mapped_mem;
    size_t length = 4096; // Size of the mapping

    // Open file for reading and writing
    fd = open("testfile.txt", O_RDWR | O_CREAT, 0666);
    if (fd == -1)
    {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    // Extend the file size
    if (ftruncate(fd, length) == -1)
    {
        perror("Error setting file size");
        close(fd);
        exit(EXIT_FAILURE);
    }

    // Pause before mmap
    printf("Before executing mmap() - Press Enter to continue after checking /proc/self/maps...\n");
    getchar();

    // Map file to memory
    mapped_mem = mmap(NULL, length, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (mapped_mem == MAP_FAILED)
    {
        perror("Error with mmap");
        close(fd);
        exit(EXIT_FAILURE);
    }

    // Write to mapped memory
    strncpy(mapped_mem, "Hello, mmap!\n", length - 1);
    mapped_mem[length - 1] = '\0';

    // Pause after mmap
    printf("After executing mmap() - Press Enter to continue after checking /proc/self/maps...\n");
    getchar();

    // Unmap memory
    if (munmap(mapped_mem, length) == -1)
    {
        perror("Error with munmap");
        close(fd);
        exit(EXIT_FAILURE);
    }

    // Pause after munmap
    printf("After executing munmap() - Press Enter to continue after checking /proc/self/maps...\n");
    getchar();

    close(fd);
    return 0;
}
