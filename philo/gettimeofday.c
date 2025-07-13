#include <stdio.h>
#include <sys/time.h>
#include <time.h>

int main() {
    struct timeval tv;
    struct tm *time;
    char buffer[64];

    if (gettimeofday(&tv, NULL) == 0) {
        printf("Seconds: %ld\n", tv.tv_sec);
        printf("Microseconds: %ld\n", tv.tv_usec);
    } else {
        perror("gettimeofday");
    }

    time = localtime(&tv.tv_sec);
    strftime(buffer, sizeof(buffer), "%d, %m, %Y %H:%M:%M", time);

    printf("%s\n", );

    return 0;
}

