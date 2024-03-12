#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define MAX_NUMBERS 300

int numbers[MAX_NUMBERS];
int num_count = 0;
int target_digit;
int max_difference = 0;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void* read_numbers(void* arg) {
    FILE* file = fopen("/tmp/test-file", "r");
    if (file == NULL) {
        perror("Nu s-a putut deschide fisierul");
        pthread_exit(NULL);
    }

    int number;
    while (fscanf(file, "%d", &number) != EOF) {
        pthread_mutex_lock(&mutex);

        if (num_count >= MAX_NUMBERS) {
            printf("Numarul maxim de numere a fost atins. Se renunta la citire.\n");
            pthread_mutex_unlock(&mutex);
            break;
        }

        numbers[num_count++] = number;
        pthread_mutex_unlock(&mutex);
    }

    fclose(file);
    pthread_exit(NULL);
}

void* process_numbers(void* arg) {
    int i;
    for (i = 0; i < num_count - 1; i++) {
        if (numbers[i] % 10 == target_digit && numbers[i + 1] % 10 == target_digit) {
            int difference = abs(numbers[i] - numbers[i + 1]);

            pthread_mutex_lock(&mutex);
            if (difference > max_difference) {
                max_difference = difference;
            }
            pthread_mutex_unlock(&mutex);
        }
    }

    pthread_exit(NULL);
}

int main() {
    int n;
    printf("Introduceti o cifra (0-9): ");
    scanf("%d", &target_digit);

    printf("Introduceti un numar (30000, 60000, 90000): ");
    scanf("%d", &n);

    pthread_t read_thread, process_thread[n];
    pthread_create(&read_thread, NULL, read_numbers, NULL);

    int i;
    for (i = 0; i < n; i++) {
        pthread_create(&process_thread[i], NULL, process_numbers, NULL);
    }

    pthread_join(read_thread, NULL);

    for (i = 0; i < n; i++) {
        pthread_join(process_thread[i], NULL);
    }

    printf("Numerele citite: ");
    for (i = 0; i < num_count; i++) {
        printf("%d ", numbers[i]);
    }
    printf("\nDiferenta maxima absoluta: %d\n", max_difference);

    return 0;
}
