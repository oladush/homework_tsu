#include <stdio.h>
#include <stdbool.h>

void city_to(int n, int index, unsigned int *city, bool *city_out){
    city_out[index] = true;
    for (int i = n-1; i >= 0; i--){
        // Достаем младший бит, выполняя коньюнкцию с единицей
        // И проверяем, не 
        if (city[index] & 1 && !city_out[i]){
            // 
            city_out[i] = true;
            city_to(n, i, city, city_out);
        }
        city[index] = city[index] >> 1;
    }
}


int main() {
////test 1
//    int n = 5;
//    unsigned int city[5] = {
//            0b00001,
//            0b00001,
//            0b00010,
//            0b00100,
//            0b11000
//    };


////test 2
//    int n = 5;
//    unsigned int city[5] = {
//            0b01000,
//            0b10110,
//            0b01010,
//            0b01100,
//            0b00000
//    };


//test 3
    int n = 7;
    // Массив из булевых векторов, хранящий информацию маршрутах
    unsigned int city[7] = {
             0b0000100,
             0b0000010,
             0b0001000,
             0b0010101,
             0b1001000,
             0b0100000,
             0b0001000
    };

    int city_index = 0;
    bool city_out[n];

    city_to(n, city_index, city, city_out);

    for(int i = 0; i < n; i++)
        if (city_out[i] && i != city_index)
            printf("%d ", i);

    return 0;
}
