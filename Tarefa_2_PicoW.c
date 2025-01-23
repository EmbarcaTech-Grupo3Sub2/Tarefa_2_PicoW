#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "matriz_leds.h"
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
//funcao modelo para fazer as animações na matriz de leds
void modelo_animacao(PIO pio, uint sm){
    //organização dos frames
    Matriz_leds_config frame1 = {
    //       Coluna 0          Coluna 1          Coluna 2          Coluna 3          Coluna 4
    //R    G    B       R    G    B       R    G    B       R    G    B       R    G    B
    {{0.0, 0.0, 1.0}, {1.0, 0.0, 0.0}, {0.0, 1.0, 0.0}, {0.0, 0.0, 1.0}, {1.0, 0.0, 0.0}}, // Linha 0
    {{0.0, 1.0, 0.0}, {1.0, 0.0, 0.0}, {0.0, 0.0, 1.0}, {0.0, 1.0, 0.0}, {1.0, 0.0, 0.0}}, // Linha 1
    {{0.0, 0.0, 1.0}, {1.0, 0.0, 0.0}, {0.0, 1.0, 0.0}, {0.0, 0.0, 1.0}, {0.0, 1.0, 0.0}}, // Linha 2
    {{0.0, 0.0, 1.0}, {1.0, 0.0, 0.0}, {0.0, 0.0, 1.0}, {0.0, 0.0, 1.0}, {1.0, 0.0, 0.0}}, // Linha 3
    {{0.0, 1.0, 0.0}, {1.0, 0.0, 0.0}, {0.0, 0.0, 1.0}, {0.0, 1.0, 0.0}, {1.0, 0.0, 0.0}}};// Linha 4

    Matriz_leds_config frame2 = {
        //       Coluna 0          Coluna 1          Coluna 2          Coluna 3          Coluna 4
        //R    G    B       R    G    B       R    G    B       R    G    B       R    G    B
        {{0.5, 0.2, 0.8}, {0.9, 0.1, 0.3}, {0.1, 0.8, 0.4}, {0.3, 0.7, 0.2}, {0.6, 0.4, 0.9}}, // Linha 0
        {{0.7, 0.3, 0.1}, {0.5, 0.6, 0.2}, {0.4, 0.2, 0.9}, {0.1, 0.3, 0.8}, {0.9, 0.5, 0.1}}, // Linha 1
        {{0.2, 0.4, 0.6}, {0.8, 0.2, 0.7}, {0.3, 0.9, 0.1}, {0.6, 0.1, 0.5}, {0.7, 0.3, 0.2}}, // Linha 2
        {{0.4, 0.1, 0.3}, {0.7, 0.6, 0.8}, {0.2, 0.5, 0.4}, {0.8, 0.3, 0.7}, {0.5, 0.9, 0.1}}, // Linha 3
        {{0.3, 0.8, 0.5}, {0.2, 0.7, 0.4}, {0.9, 0.1, 0.6}, {0.5, 0.2, 0.3}, {0.1, 0.4, 0.7}}  // Linha 4
        };

    Matriz_leds_config off = {
    //       Coluna 0          Coluna 1          Coluna 2          Coluna 3          Coluna 4
    //R    G    B       R    G    B       R    G    B       R    G    B       R    G    B
    {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}, // Linha 0
    {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}, // Linha 1
    {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}, // Linha 2
    {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}, // Linha 3
    {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}  // Linha 4
};

    //iteração dos frames
    for(int i = 0; i<5; i++){
        imprimir_desenho(frame1, pio, sm);
        sleep_ms(100);
        imprimir_desenho(frame2, pio, sm);
        sleep_ms(100);
    }
    imprimir_desenho(off, pio, sm);
    
}

//função responsável por adicionar ação a cada tecla
void action(char key, PIO pio, uint sm) {
    switch (key) {
        case '1':
            /* code for key 1 */
            break;
        case '2':
            /* code for key 2 */
            break;
        case '3':
            /* code for key 3 */
            break;
        case 'A':
            desligaTodos(pio,sm);
            break;
        case '4':
            /* code for key 4 */
            break;
        case '5':
            /* code for key 5 */
            break;
        case '6':
            /* code for key 6 */
            break;
        case 'B':
            putBlue(pio, sm);
            break;
        case '7':
            /* code for key 7 */
            break;
        case '8':
            /* code for key 8 */
            break;
        case '9':
            /* code for key 9 */
            break;
        case 'C':
            putRed80(pio, sm);
            break;
        case '*':
            modelo_animacao(pio, sm);
            break;
        case '0':
            /* code for key 0 */
            break;
        case '#':
            putWhite20(pio,sm);
            break;
        case 'D':
            putGreen50(pio, sm);
            break;
        default:
            /* code for unknown key */
            break;
    }
}

void desligaTodos(PIO pio, uint sm){
    Matriz_leds_config off = {
    //       Coluna 0          Coluna 1          Coluna 2          Coluna 3          Coluna 4
    //R    G    B       R    G    B       R    G    B       R    G    B       R    G    B
    {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}, // Linha 0
    {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}, // Linha 1
    {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}, // Linha 2
    {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}, // Linha 3
    {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}  // Linha 4
    };
    imprimir_desenho(off, pio, sm);
}

void putBlue(PIO pio, uint sm){
    Matriz_leds_config blue = {
    //       Coluna 0          Coluna 1          Coluna 2          Coluna 3          Coluna 4
    //R    G    B       R    G    B       R    G    B       R    G    B       R    G    B
    {{0.0, 0.0, 1.0}, {0.0, 0.0, 1.0}, {0.0, 0.0, 1.0}, {0.0, 0.0, 1.0}, {0.0, 0.0, 1.0}}, // Linha 0
    {{0.0, 0.0, 1.0}, {0.0, 0.0, 1.0}, {0.0, 0.0, 1.0}, {0.0, 0.0, 1.0}, {0.0, 0.0, 1.0}}, // Linha 1
    {{0.0, 0.0, 1.0}, {0.0, 0.0, 1.0}, {0.0, 0.0, 1.0}, {0.0, 0.0, 1.0}, {0.0, 0.0, 1.0}}, // Linha 2
    {{0.0, 0.0, 1.0}, {0.0, 0.0, 1.0}, {0.0, 0.0, 1.0}, {0.0, 0.0, 1.0}, {0.0, 0.0, 1.0}}, // Linha 3
    {{0.0, 0.0, 1.0}, {0.0, 0.0, 1.0}, {0.0, 0.0, 1.0}, {0.0, 0.0, 1.0}, {0.0, 0.0, 1.0}}  // Linha 4
    };
    imprimir_desenho(blue, pio, sm);
}

void putRed80(PIO pio, uint sm){
    Matriz_leds_config red = {
    //       Coluna 0          Coluna 1          Coluna 2          Coluna 3          Coluna 4
    //R    G    B       R    G    B       R    G    B       R    G    B       R    G    B
    {{0.8, 0.0, 0.0}, {0.8, 0.0, 0.0}, {0.8, 0.0, 0.0}, {0.8, 0.0, 0.0}, {0.8, 0.0, 0.0}}, // Linha 0
    {{0.8, 0.0, 0.0}, {0.8, 0.0, 0.0}, {0.8, 0.0, 0.0}, {0.8, 0.0, 0.0}, {0.8, 0.0, 0.0}}, // Linha 1
    {{0.8, 0.0, 0.0}, {0.8, 0.0, 0.0}, {0.8, 0.0, 0.0}, {0.8, 0.0, 0.0}, {0.8, 0.0, 0.0}}, // Linha 2
    {{0.8, 0.0, 0.0}, {0.8, 0.0, 0.0}, {0.8, 0.0, 0.0}, {0.8, 0.0, 0.0}, {0.8, 0.0, 0.0}}, // Linha 3
    {{0.8, 0.0, 0.0}, {0.8, 0.0, 0.0}, {0.8, 0.0, 0.0}, {0.8, 0.0, 0.0}, {0.8, 0.0, 0.0}}  // Linha 4
    };
    imprimir_desenho(red, pio, sm);
}

void putGreen50(PIO pio, uint sm){
    Matriz_leds_config green = { 
    //       Coluna 0          Coluna 1          Coluna 2          Coluna 3          Coluna 4
    //R    G    B       R    G    B       R    G    B       R    G    B       R    G    B
    {{0.0, 0.5, 0.0}, {0.0, 0.5, 0.0}, {0.0, 0.5, 0.0}, {0.0, 0.5, 0.0}, {0.0, 0.5, 0.0}}, // Linha 0
    {{0.0, 0.5, 0.0}, {0.0, 0.5, 0.0}, {0.0, 0.5, 0.0}, {0.0, 0.5, 0.0}, {0.0, 0.5, 0.0}}, // Linha 1
    {{0.0, 0.5, 0.0}, {0.0, 0.5, 0.0}, {0.0, 0.5, 0.0}, {0.0, 0.5, 0.0}, {0.0, 0.5, 0.0}}, // Linha 2
    {{0.0, 0.5, 0.0}, {0.0, 0.5, 0.0}, {0.0, 0.5, 0.0}, {0.0, 0.5, 0.0}, {0.0, 0.5, 0.0}}, // Linha 3
    {{0.0, 0.5, 0.0}, {0.0, 0.5, 0.0}, {0.0, 0.5, 0.0}, {0.0, 0.5, 0.0}, {0.0, 0.5, 0.0}}  // Linha 4
    };
    imprimir_desenho(green, pio, sm);
}

void putWhite20(PIO pio, uint sm){
    Matriz_leds_config white = { 
    //       Coluna 0          Coluna 1          Coluna 2          Coluna 3          Coluna 4
    //R    G    B       R    G    B       R    G    B       R    G    B       R    G    B
    {{0.2, 0.2, 0.2}, {0.2, 0.2, 0.2}, {0.2, 0.2, 0.2}, {0.2, 0.2, 0.2}, {0.2, 0.2, 0.2}}, // Linha 0
    {{0.2, 0.2, 0.2}, {0.2, 0.2, 0.2}, {0.2, 0.2, 0.2}, {0.2, 0.2, 0.2}, {0.2, 0.2, 0.2}}, // Linha 1
    {{0.2, 0.2, 0.2}, {0.2, 0.2, 0.2}, {0.2, 0.2, 0.2}, {0.2, 0.2, 0.2}, {0.2, 0.2, 0.2}}, // Linha 2
    {{0.2, 0.2, 0.2}, {0.2, 0.2, 0.2}, {0.2, 0.2, 0.2}, {0.2, 0.2, 0.2}, {0.2, 0.2, 0.2}}, // Linha 3
    {{0.2, 0.2, 0.2}, {0.2, 0.2, 0.2}, {0.2, 0.2, 0.2}, {0.2, 0.2, 0.2}, {0.2, 0.2, 0.2}}  // Linha 4
    };
    imprimir_desenho(white, pio, sm);
}

int main()
{
    //inicialização da matriz de leds;
    PIO pio = pio0;
    uint sm = configurar_matriz(pio);

    stdio_init_all();
    setup_pins();

    while (true)
    {
        action(get_key(), pio, sm);
    }

    return 0;
} 