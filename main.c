#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct Book {
    char surname[20];
    char name[20];
    char patronymic[20];
    int number;
} Book;

void swap(Book *arr, int l, int r) {
    if (l != r) {
        struct Book tmp;
        strcpy(tmp.surname, arr[l].surname);
        strcpy(tmp.name, arr[l].name);
        strcpy(tmp.patronymic, arr[l].patronymic);
        tmp.number = arr[l].number;

        strcpy(arr[l].surname, arr[r].surname);
        strcpy(arr[l].name, arr[r].name);
        strcpy(arr[l].patronymic, arr[r].patronymic);
        arr[l].number = arr[r].number;

        strcpy(arr[r].surname, tmp.surname);
        strcpy(arr[r].name, tmp.name);
        strcpy(arr[r].patronymic, tmp.patronymic);
        arr[r].number = tmp.number;
    }
}

int compare(Book *arr, int l, int r) {
    int cmp;
    cmp = strcmp(arr[l].surname, arr[r].surname);
    if (cmp) return cmp;

    cmp = strcmp((const char *) arr[l].name, arr[r].name);
    if (cmp) return cmp;

    cmp = strcmp(arr[l].patronymic, arr[r].patronymic);
    if (cmp) return cmp;

    return arr[l].number - arr[r].number;
}

int partition(Book *arr, int l, int h) {

    int i = (l - 1);

    for (int j = l; j <= h - 1; j++) {
        if (compare(arr, j, h) < 0) {
            i++;
            swap(arr, i, j);
        }
    }

    swap (arr, i + 1 , h);

    return (i + 1);
}


void my_qsort(void *arr, int l, int h) {
    if (l < h) {
        int pi = partition(arr, l, h);
        my_qsort(arr, l, pi - 1);
        my_qsort(arr, pi + 1, h);
    }
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Quantity of arguments is incorrect!\nargument 1: lab2\nargument 2: <name of input file>\nargument 3: <name of output file>");
        return 1;
    }

    if ((argv[1] == NULL) || (argv[2] == NULL)) {
        printf("Problem with name of files!");
        return 1;
    }

    FILE *fin = fopen(argv[1], "r");

    if (fin == NULL) {
        printf("Can't open input file");
        return 1;
    }

    int length = 10000000;
    Book *arr;
    if (!(arr = (Book *) malloc(length * sizeof(Book)))) {
        printf("Can't allocate memory!");
        return 1;
    }

    int i = 0;
    struct Book book;
    while (fscanf(fin, "%s%s%s%d", book.surname, book.name, book.patronymic, &book.number) != EOF) {
        arr[i] = book;
        i++;
        struct Book book;
    }

    fclose(fin);

    my_qsort(arr, 0, i - 1);

    FILE *fout = fopen(argv[2], "w");

    if (fout == NULL) {
        printf("Can't open output file");
        return 3;
    }

    for (int j = 0; j < i; j++) {
        fprintf(fout, "%s %s %s %i\n", arr[j].surname, arr[j].name, arr[j].patronymic, arr[j].number);
    }

    free(arr);
    fclose(fout);
    return 0;
}
