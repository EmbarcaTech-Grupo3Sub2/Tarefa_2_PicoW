#include "pico/stdlib.h"
#include <stdio.h>


const uint col[4] = {19, 18, 17, 16};   // Definição dos pinos do teclado
const uint rw[4] = {26, 22, 21, 20};    // com as portas GPIO

char lastKey = ' ';                 // última tecla pressionada
const char keysFlatMap[16] = {
    '1', '2', '3', 'A',
    '4', '5', '6', 'B',             // Mapeamento das teclas do teclado
    '7', '8', '9', 'C',
    '*', '0', '#', 'D'};

void setup_pins()
{

    for (int i = 0; i < 4; i++)
    {
        gpio_init(rw[i]);
        gpio_set_dir(rw[i], GPIO_OUT);
        gpio_put(rw[i], 1);
                                            // Configuração dos pinos do teclado
        gpio_init(col[i]);
        gpio_set_dir(col[i], GPIO_IN);
        gpio_pull_up(col[i]);
    }
}

char get_key()
{
    char res = ' ';
    for (int r = 0; r < 4; r++)
    {
        gpio_put(rw[r], 0);     //  linha atual em estado baixo

        for (int c = 0; c < 4; c++)
        {
            sleep_ms(5);
            if (gpio_get(col[c]) == 0) 
            {
                gpio_put(rw[r], 1);     // linha atual em estado alto
                const char key = keysFlatMap[r * 4 + c];
                res = key;      // valor da tecla pressionada
            }
        }
        gpio_put(rw[r], 1); // Desativa a linha
    }
    if (res == ' ' || res != lastKey)
    {
        lastKey = res;
        if (res != ' ')
            printf("\nTecla pressionada: %c ", res);
        return res;
    }
    else
        return ' ';
}


int main()
{
    stdio_init_all();
    setup_pins();

    while (true)
    {
        get_key();
    }

    return 0;
} 