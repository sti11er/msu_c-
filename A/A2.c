// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>

// #define M 80

// int 
// main(int argc, char *argv[]) {
//     FILE *f = fopen(argv[1], "r");
//     char str[M + 1];
//     fgets(str, M + 1, stdin);

//     size_t len = strlen(str);
//     if (str[len - 1] == '\n') {
//         str[len - 1] = '\0';
//     }

//     FILE *tmp = tmpfile();
//     char line[M + 1];
//     while (fgets(line, M + 1, f) != NULL) {
//         if (strstr(line, str) != NULL) {
//             fputs(line, tmp);
//         }
//     }

//     fclose(f); 
//     rewind(tmp);
//     f = fopen(argv[1], "w");
//     while (fgets(line, M + 1, tmp) != NULL) {
//         fputs(line, f);
//     }

//     fclose(f);
//     fclose(tmp);
//     return 0;
// }

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    FILE *file = fopen(argv[1], "r");
    char search[80];
    if (fgets(search, 80, stdin) == NULL) { return 0; };

    search[strcspn(search, "\n")] = '\0';

    FILE *temp = tmpfile();
    char line[80];
    while (fgets(line, 80, file) != NULL) {
        if (strstr(line, search) != NULL) {
            fputs(line, temp);
        }
    }

    fclose(file);

    file = fopen(argv[1], "w");
    rewind(temp);
    while (fgets(line, 80, temp) != NULL) {
        fputs(line, file);
    }

    fclose(file);
    fclose(temp);
    return 0;
}