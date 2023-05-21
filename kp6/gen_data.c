#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char latin[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZFM";
#define LATIN_SIZE ((int)(sizeof(latin) - 1))
char digits[] = "123456789";
#define DIGITS_SIZE ((int)(sizeof(digits) - 1))
#define SUBJ_SIZE 20

#define FNAME_SIZE 32
#define NAME_MAX_SIZE 23
#define BUF_SIZE (4 * 1024 * 1024)

char buf[BUF_SIZE] = { '\0' };
static unsigned int g_seed = 0;

static inline void fast_srand(int seed)
{
    g_seed = seed;
}

static inline int fast_rand()
{
    g_seed = (214013 * g_seed + 2531011);
    return (g_seed >> 16) & 0x7FFF;
}

int main(int argc, char *argv[])
{
    int qty = 10;// * 1000 * 1000;
    if (argc >= 2) {
        qty = atoi(argv[1]);
    }
    
    char fname[FNAME_SIZE] = "_input.txt";
    if (argc >= 3) {
        strncat(argv[2], fname, FNAME_SIZE - 1);
    }
    
    FILE *f = fopen(fname, "wb");
    if (!f) {
        fprintf(stderr, "Error: can't open file '%s'.\n", fname);
        return 1;
    }
    
    fast_srand(0);

    register int buf_pos = 0;
    for (int i = 0; i < qty; ++i) {
        char subj[SUBJ_SIZE] = { '\0' };
        int subj_size = fast_rand() % 20 + 1;
        for (register int j = 0; j < subj_size; ++j) {
            subj[j] = latin[fast_rand() % LATIN_SIZE];
        }

        char gender = latin[LATIN_SIZE + fast_rand() % 2 - 2];
        int number = fast_rand() % 11 + 1;
        char letter1 = latin[fast_rand() % 15 + 26];
        char letter2 = latin[fast_rand() % 15 + 26];
        char letter3 = latin[fast_rand() % 25];

        char seq1[21] = { '\0' };
        int seq1_size = fast_rand() % 20;
        for (register int j = 0; j < seq1_size; ++j) {
            seq1[j] = latin[fast_rand() % LATIN_SIZE];
        }

        char seq2[19] = { '\0' };
        int seq2_size = fast_rand() % 19;
        for (register int j = 0; j < seq2_size; ++j) {
            seq2[j] = latin[fast_rand() % LATIN_SIZE];
        }
        buf_pos += sprintf(buf + buf_pos, "%-20s %c%c\t%c\t%d\t%c\te%-20s\t%-18s\n", subj, letter1, letter2, gender, number, letter3, seq1, seq2);

        if (buf_pos >= BUF_SIZE - 64) {
            fwrite(buf, sizeof(buf[0]), buf_pos, f);
            buf_pos = 0;
        }
    }

    if (buf_pos > 0) {
        fwrite(buf, sizeof(buf[0]), buf_pos, f);
    }
    
    fclose(f);
    
    return 0;
}