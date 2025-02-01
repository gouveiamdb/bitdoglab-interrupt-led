#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "hardware/clocks.h"
#include "ws2812.pio.h"  

// Definições gerais
#define WS2812_PIN 7
#define LED_RED_PIN 11
#define LED_GREEN_PIN 12
#define LED_BLUE_PIN 13
#define BUTTON_A_PIN 5
#define BUTTON_B_PIN 6
#define NUM_PIXELS 25
#define MATRIX_WIDTH 5
#define MATRIX_HEIGHT 5
#define DEBOUNCE_US 200000  // 200ms debounce

// Estados globais
static int current_number = 0;
static PIO pio = pio0;
static uint sm = 0;

// Cores
#define RED   0xFF0000
#define GREEN 0x00FF00
#define BLUE  0x0000FF
#define BLACK 0x000000

// Matriz de números 0-9 (5x5)
const uint8_t number_patterns[10][MATRIX_HEIGHT][MATRIX_WIDTH] = {
    // Número 0
    {
        {1, 1, 1, 1, 1},
        {1, 0, 0, 0, 1},
        {1, 0, 0, 0, 1},
        {1, 0, 0, 0, 1},
        {1, 1, 1, 1, 1}
    },
    // Número 1
    {
        {0, 1, 1, 1, 0},
        {0, 0, 1, 0, 0},
        {0, 0, 1, 0, 0},
        {0, 1, 1, 0, 0},
        {0, 0, 1, 0, 0}
    },
    // Número 2
    {
        {1, 1, 1, 1, 0},
        {0, 0, 1, 0, 0},
        {0, 1, 0, 0, 0},
        {0, 1, 0, 0, 1},
        {0, 1, 1, 0, 0}
    },
    // Número 3
    {
        {0, 1, 1, 1, 0},
        {1, 0, 0, 0, 1},
        {0, 1, 1, 0, 0},
        {1, 0, 0, 0, 1},
        {0, 1, 1, 1, 0}
    },
    // Número 4
    {
        {0, 0, 1, 0, 0},
        {0, 0, 1, 0, 0},
        {1, 1, 1, 1, 1},
        {0, 1, 1, 0, 0},
        {0, 0, 1, 0, 0}
    },
    // Número 5 
    {
        {1, 1, 1, 1, 1},
        {0, 0, 0, 0, 1},
        {1, 1, 1, 1, 1},
        {1, 0, 0, 0, 0},
        {1, 1, 1, 1, 1}
    },
    // Número 6
    {
        {1, 1, 1, 1, 0},
        {1, 0, 0, 0, 1},
        {1, 1, 1, 1, 1},
        {1, 0, 0, 0, 0},
        {1, 1, 1, 1, 1}
    },
    // Número 7
    {
        {0, 0, 0, 1, 0},
        {0, 0, 1, 0, 0},
        {0, 1, 0, 0, 0},
        {0, 0, 0, 0, 1},
        {1, 1, 1, 1, 1},
    },
    // Número 8
    {
        {0, 1, 1, 1, 0},
        {1, 0, 0, 0, 1},
        {0, 1, 1, 1, 0},
        {1, 0, 0, 0, 1},
        {0, 1, 1, 1, 0}
    },
    // Número 9
    {
        {1, 1, 1, 1, 1},
        {0, 0, 0, 0, 1},
        {1, 1, 1, 1, 1},
        {1, 0, 0, 0, 1},
        {1, 1, 1, 1, 1}
    }
};

// Função para inicializar o WS2812
void ws2812_init() {
    uint offset = pio_add_program(pio, &ws2812_program);
    ws2812_program_init(pio, sm, offset, WS2812_PIN, 800000, false);
}

// Função para enviar um pixel
void put_pixel(uint32_t pixel_grb) {
    pio_sm_put_blocking(pio, sm, pixel_grb << 8u);
}

// Função para converter RGB em GRB
uint32_t rgb_to_grb(uint8_t r, uint8_t g, uint8_t b) {
    return ((uint32_t)(g) << 16) | ((uint32_t)(r) << 8) | (uint32_t)(b);
}

// Função para exibir o número na matriz
void display_number(int number) {
    if (number < 0 || number > 9) return;

    for (int row = 0; row < MATRIX_HEIGHT; row++) {
        for (int col = 0; col < MATRIX_WIDTH; col++) {
            if (number_patterns[number][row][col]) {
                put_pixel(rgb_to_grb(255, 0, 0));  // Vermelho
            } else {
                put_pixel(0);  // Apagado
            }
        }
    }
}

// Função de callback para os botões
void button_callback(uint gpio, uint32_t events) {
    static absolute_time_t last_interrupt_time = {0};
    absolute_time_t current_time = get_absolute_time();

    if (absolute_time_diff_us(last_interrupt_time, current_time) < DEBOUNCE_US) {
        return;  // Ignora interrupções muito próximas
    }

    if (gpio == BUTTON_A_PIN) {
        current_number = (current_number + 1) % 10;
    } else if (gpio == BUTTON_B_PIN) {
        current_number = (current_number - 1 + 10) % 10;
    }

    display_number(current_number);
    last_interrupt_time = current_time;
}

int main() {
    stdio_init_all();

    // Inicializa os pinos do LED RGB
    gpio_init(LED_RED_PIN);
    gpio_set_dir(LED_RED_PIN, GPIO_OUT);
    gpio_init(LED_GREEN_PIN);
    gpio_set_dir(LED_GREEN_PIN, GPIO_OUT);
    gpio_init(LED_BLUE_PIN);
    gpio_set_dir(LED_BLUE_PIN, GPIO_OUT);

    // Inicializa os pinos dos botões
    gpio_init(BUTTON_A_PIN);
    gpio_init(BUTTON_B_PIN);
    gpio_set_dir(BUTTON_A_PIN, GPIO_IN);
    gpio_set_dir(BUTTON_B_PIN, GPIO_IN);
    gpio_pull_up(BUTTON_A_PIN);
    gpio_pull_up(BUTTON_B_PIN);

    // Configura as interrupções dos botões
    gpio_set_irq_enabled_with_callback(BUTTON_A_PIN, GPIO_IRQ_EDGE_FALL, true, &button_callback);
    gpio_set_irq_enabled(BUTTON_B_PIN, GPIO_IRQ_EDGE_FALL, true);

    // Inicializa WS2812
    ws2812_init();

    // Exibe o número inicial (0)
    display_number(0);

    // Loop principal
    while (true) {
        // Pisca o LED vermelho (5 Hz = 100ms ON, 100ms OFF)
        gpio_put(LED_RED_PIN, 1);
        sleep_ms(100);
        gpio_put(LED_RED_PIN, 0);
        sleep_ms(100);
    }

    return 0;
}