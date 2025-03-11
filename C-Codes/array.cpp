#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ARRAY_SIZE 101007039 //Размер массива
int global_array[ARRAY_SIZE];  //Глобальный массив
int sec_global_array[ARRAY_SIZE]; //Массив для повторного заполнения

int main() {
    int *heap_array = (int *)malloc(ARRAY_SIZE * sizeof(int));
    if (heap_array == NULL) {
        printf("Memorize error detected\n");
        return 1;
    }
    clock_t start, end;
    double time_used;
    double sec_time_used;
    double th_time_used;

    //Замер времени заполнения глобального массива последовательными числами
    start = clock();
    for (int i = 0; i < ARRAY_SIZE; i++) {
        global_array[i] = i;
    }
    end = clock();
    time_used = ((double) (end - start))/CLOCKS_PER_SEC;
    printf("Global: %f sec\n", time_used);

    //Замер времени заполнения массива в куче
    start = clock();
    for (int i = 0; i < ARRAY_SIZE; i++) {
        heap_array[i] = i;
    }
    end = clock();
    time_used = ((double) (end - start))/CLOCKS_PER_SEC;
    printf("Dynamic: %f sec\n", time_used);
    free(heap_array);  // Освобождение памяти
    
    //Повторное заполнение массива четными числами
    start = clock();
    for(int i = 0; i < ARRAY_SIZE; ++i){
        global_array[i] = i*2;
    }
    end = clock();
    sec_time_used = ((double) (end - start))/CLOCKS_PER_SEC;
    printf("Repeated: %f sec\n", sec_time_used);

    //Заполним массив через пять шагов
    start = clock();
    int step = 5;
    for(int i = 0; i < ARRAY_SIZE; i += step){
        global_array[i] = i*3;
    }
    end = clock();
    th_time_used = ((double) (end - start))/CLOCKS_PER_SEC;
    printf("Five Time: %f sec\n", th_time_used);

    
}