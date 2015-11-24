/*
Copyright (c) 2015 Christian Uhsat <christian@uhsat.de>

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/

#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <sys/time.h>

#ifdef _WIN32
#error "This won't work on Windows and I don't care, you're fucked anyway!"
#endif

#define EPOCH(tv) (((tv.tv_sec) * 1000) + ((tv.tv_usec) / 1000))
#define THRESHOLD 800

/*
inline long long get_time() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return EPOCH(tv);
}
*/

void reset() {
    system("stty echo cooked");
}

int main()
{
    int c;

    struct timeval tv;

    long long t1, t2;

    atexit(reset);
    system("stty -echo raw");

    gettimeofday(&tv, NULL);
    t1 = EPOCH(tv);

    while ((c = getchar()) != 13) {
        gettimeofday(&tv, NULL);

        if (isprint(c)) {
            putchar(c);
        }

        t2 = EPOCH(tv);

        fprintf(stderr, (t2 - t1) >= THRESHOLD ? "-" : ".");
        t1 = t2;
    };

    return(EXIT_SUCCESS);
}
