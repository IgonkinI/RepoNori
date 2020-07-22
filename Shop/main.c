#include <pthread.h>
#include <time.h>
#include <unistd.h>

#include "stdio.h"
#include "stdlib.h"

#define SHOP_COUNTS 5
#define BYERS 3
#define BYER_PURPOSE 10000
#define LOADERS 1
#define LOADER_POWER 500
#define MIN_VALUE 9800
#define MAX_VALUE 10200

// Структура, в которой мы храним номер покупателя и указатель на массив
// магазинов
struct PARAM {
  int a;
  int *ptr;
};

pthread_mutex_t mutex;

// Действия покупателя. Номер покупателя и указатель на магазин получаем из
// param.
void *byer_act(void *ptr_to_shop) {
  struct PARAM *param = (struct PARAM *)ptr_to_shop;
  int *ptr = param->ptr;
  int *shops = ptr;
  int byer = param->a;

  // Делаем разброс в кошельках клиентов +-200
  int count = MIN_VALUE + rand() % (MAX_VALUE - MIN_VALUE);
  int buff;
  printf("\nByer %d:\tInitial value: %d", byer, count);

  while (count > 0) {
    pthread_mutex_lock(&mutex);

    buff = 0 + rand() % 5;
    if (count >= shops[buff]) {
      count = count - shops[buff];
      printf("\nByer %d:\tI am going to shop N: %d\t\tIn shop: %d Me: %d", byer,
             buff, shops[buff], count);
      shops[buff] = 0;

    } else {
      shops[buff] = shops[buff] - count;
      count = 0;
      printf("\nByer %d:\tI am going to shop N: %d\tIn shop: %d Me: %d", byer,
             buff, shops[buff], count);
    }
    pthread_mutex_unlock(&mutex);
    sleep(2);

    if (count == 0) {
      printf("\nByer %d:\t I have done. I am going home!\n", byer);
      return 0;
    }
  }
}

// Это работник магазина. Он один, но это исправляется.
// Количество работы вычисляется как: (МАКСИМАЛЬНОЕ ЗНАЧЕНИЕ / ОБЩЕЕ ЧИСЛО
// ПОКУПАТЕЛЕЙ)/ МАКСИМАЛЬНУЮ ГРУЗОПОДЪЕМНОСТЬ РАБОТНИКА

void *loader_act(void *ptr_to_shop) {
  int *shops = (int *)ptr_to_shop;
  int buff;
  int i = 0;
  while (i <= (MAX_VALUE * BYERS) / LOADER_POWER) {
    pthread_mutex_lock(&mutex);
    buff = 0 + rand() % 5;
    shops[buff] = shops[buff] + 500;
    printf("\nWorker: In the shop %d were %d products. Now = %d", buff,
           shops[buff] - 500, shops[buff]);
    pthread_mutex_unlock(&mutex);

    sleep(1);
    i++;
  }

  printf("\nWorker: Job has done. I go to home!\n");
  return 0;
}

int main(int argc, char const *argv[]) {
  pthread_mutex_init(&mutex, NULL);
  srand(time(NULL));
  pthread_t pthread_ID_BYER[BYERS];
  pthread_t pthread_ID_LOADER[LOADERS];
  int shops[SHOP_COUNTS];
  int buff;

  // Массив структур нужен для того, чтобы мы могли выводить номер каждого
  // покупателя.
  struct PARAM param[BYERS];
  // Изначальное значение количества продуктов в магазине вычисляется случайным
  // образом в пределах от 0 до 500
  for (int i = 0; i < SHOP_COUNTS; i++) {
    shops[i] = 0 + rand() % 500;
  }

  // Создаем потоки покупателей
  printf("\nCreating byers!\n");
  for (int i = 0; i < BYERS; i++) {
    param[i].a = i;
    param[i].ptr = &shops[0];
    pthread_create(&pthread_ID_BYER[i], NULL, byer_act, &param[i]);
  }
  // Создаем потоки грузчиков
  for (int i = 0; i < LOADERS; i++) {
    pthread_create(&pthread_ID_LOADER[i], NULL, loader_act, &shops[0]);
  }

  // Ждем окончания потоков покупателей
  for (int i = 0; i < BYERS; i++) {
    pthread_join(pthread_ID_BYER[i], NULL);
  }
  // Ждем окончания потоков грузчиков
  for (int i = 0; i < LOADERS; i++) {
    pthread_join(pthread_ID_LOADER[i], NULL);
  }

  pthread_mutex_destroy(&mutex);
  return 0;
}
