//Для каждого из N городов известно, в какие города можно попасть из данного за один рейс.
//Напечатать номера городов, в которые можно добраться из города A (с любым числом
//пересадок)

#include <stdio.h>
#include <stdbool.h>

void city_to(int n, int index, unsigned int *city, bool *city_out){
    // Находясь в "Чикаго" мы можем попасть в "Чикаго"
    // Поэтому помечаем исходный город, чтобы не вызывать его повторно
    city_out[index] = true;
    for (int i = n-1; i >= 0; i--){
        // Достаем младший бит, выполняя коньюнкцию с единицей
        // Так мы проверяем можем ли мы попасть в город i
        // Так же проверяем, проверяли ли мы этот город ранее
        // Если проверяли, делать это еще раз избыточно
        // (и чревато бесконечным циклом)
        if (city[index] & 1 && !city_out[i]){
            // Если выполняются предыдущие условия
            // Помечаем город i как город в который мы можем попасть
            city_out[i] = true;
            // Рекурсивно вызываем функцию и проверяем города
            // в которые мы можем попасть из i
            city_to(n, i, city, city_out);
        }
        // Выполняем битовый сдвиг вправо, чтобы проверить следующий путь
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

    // Индекс проверяемого города
    int city_index = 0;
    // Булев массив, в котором будет хранится
    // информация о городах в которые мы можем 
    // попасть из проверяемого города
    bool city_out[n];

    city_to(n, city_index, city, city_out);

    // Вывод полученных городов за исключением исходного
    for(int i = 0; i < n; i++)
        if (city_out[i] && i != city_index)
            printf("%d ", i);

    return 0;
}
