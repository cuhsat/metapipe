/*
 * Copyright (c) 2015 Christian Uhsat <christian@uhsat.de>
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */

#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <getopt.h>
#include <sys/time.h>

#include "metapipe.h"

#define CR 13

/*
 * Output mode buffer limit
 */
typedef enum {
    MORSE = 1,
    ASCII = 6,
    BYTE  = 7
} buffer_limit;

/*
 * Reset terminal settings.
 */
void reset_tty() {
    system("stty echo cooked");
}

/*
 * Metapipe main.
 */
int main(int argc, char **argv)
{
    int opt, c, i=0, threshold=THRESHOLD;

    buffer_limit limit=ASCII;
    unsigned char buffer=0;

    long long ks1=0, ks2=0;
    struct timeval tv;

    // parse arguments
    while ((opt = getopt(argc, argv, "abmn:hv")) != -1) {
        switch (opt) {
            case 'a':
                limit = ASCII;
                break;

            case 'b':
                limit = BYTE;
                break;

            case 'm':
                limit = MORSE;
                break;

            case 'n':
                threshold = atoi(optarg);
                break;

            case 'v':
                printf("metapipe %s\n", VERSION);
                exit(EXIT_SUCCESS);

            default:
                fprintf(stderr, "Usage: %s [-abmhv] [-n MSECS]\n", argv[0]);
                exit(EXIT_FAILURE);
        }
    }

    // set terminal mode
    atexit(reset_tty);
    system("stty -echo raw");

    // take input till line break
    while (CR != (c = fgetc(stdin))) {
        gettimeofday(&tv, NULL);

        // calculate EPOCH
        ks2 = ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));

        // echo STDIN
        if (isprint(c))
            fputc(c, stdout);

        // ignore first keystroke
        if (ks1) {
            buffer |= (((ks2 - ks1) > threshold) << i++);

            // is buffer full
            if (i == limit) {

                // convert to char
                if (limit == MORSE)
                    buffer = 0x2E - buffer;

                // flush buffer to STDERR
                fputc(buffer, stderr);
                buffer = i = 0;
            }
        }

        ks1 = ks2;
    };

    return(EXIT_SUCCESS);
}
