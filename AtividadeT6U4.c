// Inclusão de bibliotecas
#include <stdlib.h>
#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "hardware/gpio.h"
#include "hardware/clocks.h"
#include "inc/ssd1306.h"
#include "inc/font.h"
#include "AtividadeT6U4.pio.h"

// MATRIZ DE LEDs
// Definição de variáveis
#define LED_PIN 7
#define NUM_PIXELS 25
uint valor_led;
PIO pio = pio0;
uint sm;

// FUNÇÃO PARA DEFINIÇÃO DE INTENSIDADE DE CORES NOS LEDs
uint matrix_rgb(float r, float g, float b)
{
  unsigned char R, G, B;
  R = r * 255;
  G = g * 255;
  B = b * 255;
  return (G << 24) | (R << 16) | (B << 8);
}

// Função para converter a posição do matriz para uma posição do vetor.
int getid(int x, int y)
{
  // Se a linha for par (0, 2, 4), percorremos da esquerda para a direita.
  // Se a linha for ímpar (1, 3), percorremos da direita para a esquerda.
  if (y % 2 == 0)
  {
    return 24 - (y * 5 + x); // Linha par (esquerda para direita).
  }
  else
  {
    return 24 - (y * 5 + (4 - x)); // Linha ímpar (direita para esquerda).
  }
}

// FUNÇÃO DESENHO P/ MATRIZ DE LEDS
void desenho_pio(double *desenho, uint32_t valor_led, PIO pio, uint sm, double r, double g, double b)
{

  for (int16_t i = 0; i < NUM_PIXELS; i++)
  {
    valor_led = matrix_rgb(desenho[i] * r, desenho[i] * g, desenho[i] * b);
    pio_sm_put_blocking(pio, sm, valor_led);
  };
}

// SPRITES
double apagar_leds[25] = {0.0, 0.0, 0.0, 0.0, 0.0, // Apagar LEDs
                          0.0, 0.0, 0.0, 0.0, 0.0,
                          0.0, 0.0, 0.0, 0.0, 0.0,
                          0.0, 0.0, 0.0, 0.0, 0.0,
                          0.0, 0.0, 0.0, 0.0, 0.0};

double numero_1[25] =    {0.0, 0.0, 1.0, 0.0, 0.0, // Algarismo 1
                          0.0, 0.0, 1.0, 0.0, 0.0,
                          0.0, 0.0, 1.0, 0.0, 0.0,
                          0.0, 1.0, 1.0, 0.0, 0.0,
                          0.0, 0.0, 1.0, 0.0, 0.0};

double numero_2[25] =    {1.0, 1.0, 1.0, 1.0, 1.0, // Algarismo 2
                          1.0, 0.0, 0.0, 0.0, 0.0,
                          1.0, 1.0, 1.0, 1.0, 1.0,
                          0.0, 0.0, 0.0, 0.0, 1.0,
                          1.0, 1.0, 1.0, 1.0, 1.0};

double numero_3[25] =    {1.0, 1.0, 1.0, 1.0, 1.0, // Algarismo 3
                          0.0, 0.0, 0.0, 0.0, 1.0,
                          1.0, 1.0, 1.0, 0.0, 0.0,
                          0.0, 0.0, 0.0, 0.0, 1.0,
                          1.0, 1.0, 1.0, 1.0, 1.0};

double numero_4[25] =    {1.0, 0.0, 0.0, 0.0, 0.0, // Algarismo 4
                          0.0, 0.0, 0.0, 0.0, 1.0,
                          1.0, 1.0, 1.0, 1.0, 1.0,
                          1.0, 0.0, 0.0, 0.0, 1.0,
                          1.0, 0.0, 0.0, 0.0, 1.0};

double numero_5[25] =    {1.0, 1.0, 1.0, 1.0, 1.0, // Algarismo 5
                          0.0, 0.0, 0.0, 0.0, 1.0,
                          1.0, 1.0, 1.0, 1.0, 1.0,
                          1.0, 0.0, 0.0, 0.0, 0.0,
                          1.0, 1.0, 1.0, 1.0, 1.0};

double numero_6[25] =    {1.0, 1.0, 1.0, 1.0, 1.0, // Algarismo 6
                          1.0, 0.0, 0.0, 0.0, 1.0,
                          1.0, 1.0, 1.0, 1.0, 1.0,
                          1.0, 0.0, 0.0, 0.0, 0.0,
                          1.0, 1.0, 1.0, 1.0, 1.0};

double numero_7[25] =    {0.0, 0.0, 0.0, 0.0, 1.0, // Algarismo 7
                          0.0, 1.0, 0.0, 0.0, 0.0,
                          0.0, 0.0, 1.0, 0.0, 0.0,
                          0.0, 0.0, 0.0, 1.0, 0.0,
                          1.0, 1.0, 1.0, 1.0, 1.0};

double numero_8[25] =    {1.0, 1.0, 1.0, 1.0, 1.0, // Algarismo 8
                          1.0, 0.0, 0.0, 0.0, 1.0,
                          1.0, 1.0, 1.0, 1.0, 1.0,
                          1.0, 0.0, 0.0, 0.0, 1.0,
                          1.0, 1.0, 1.0, 1.0, 1.0};

double numero_9[25] =    {1.0, 1.0, 1.0, 1.0, 1.0, // Algarismo 9
                          0.0, 0.0, 0.0, 0.0, 1.0,
                          1.0, 1.0, 1.0, 1.0, 1.0,
                          1.0, 0.0, 0.0, 0.0, 1.0,
                          1.0, 1.0, 1.0, 1.0, 1.0};

double numero_0[25] =    {1.0, 1.0, 1.0, 1.0, 1.0, // Algarismo 0
                          1.0, 0.0, 0.0, 0.0, 1.0,
                          1.0, 0.0, 0.0, 0.0, 1.0,
                          1.0, 0.0, 0.0, 0.0, 1.0,
                          1.0, 1.0, 1.0, 1.0, 1.0};

double *sprites[10] = {numero_0, numero_1, numero_2, numero_3, numero_4, numero_5, numero_6, numero_7, numero_8, numero_9};

//I2C
#define I2C_PORT i2c1
#define I2C_SDA 14
#define I2C_SCL 15
#define endereco 0x3C
ssd1306_t ssd;

// Display OLED
void char_display (char caractere, bool cor){
  ssd1306_fill(&ssd, !cor); // Limpa o display
  ssd1306_rect(&ssd, 3, 3, 122, 58, cor, !cor); // Desenha um retângulo
  cor = !cor;
  ssd1306_draw_char(&ssd, caractere, 64, 32); // Desenha o caractere enviado
  ssd1306_send_data(&ssd); // Atualiza o display
}

// Botões e LEDs RGB
// Definição de variáveis
#define BUTTON_A 5
#define BUTTON_B 6
#define LED_GREEN 11
#define LED_BLUE 12

// Função de interrupção
void irq_button(uint gpio_button, uint32_t events)
{
    if(!gpio_get(gpio_button)){ //Leitura do botão
      if(gpio_button == BUTTON_A){
        gpio_put(LED_GREEN, !gpio_get(LED_GREEN)); // Altera o estado do LED Verde
        printf("Alterando estado do LED Verde\n"); // Mensagem de depuração
        ssd1306_fill(&ssd, false); // Limpa o display
        ssd1306_draw_string(&ssd, "LED VERDE", 15, 48); // Desenha uma string
        ssd1306_send_data(&ssd); // Atualiza o display
      }
      else if(gpio_button == BUTTON_B){
        gpio_put(LED_BLUE, !gpio_get(LED_BLUE)); // Altera o estado do LED Azul
        printf("Alterando estado do LED Azul\n"); // Mensagem de depuração
        ssd1306_fill(&ssd, false); // Limpa o display
        ssd1306_draw_string(&ssd, "LED AZUL", 15, 48); // Desenha uma string
        ssd1306_send_data(&ssd); // Atualiza o display
    }
  }
}

// Função de configuração
void setup(){

//I2C
  i2c_init(I2C_PORT, 400 * 1000);

  gpio_set_function(I2C_SDA, GPIO_FUNC_I2C); // Set the GPIO pin function to I2C
  gpio_set_function(I2C_SCL, GPIO_FUNC_I2C); // Set the GPIO pin function to I2C
  gpio_pull_up(I2C_SDA); // Pull up the data line
  gpio_pull_up(I2C_SCL); // Pull up the clock line
  ssd1306_init(&ssd, WIDTH, HEIGHT, false, endereco, I2C_PORT); // Inicializa o display
  ssd1306_config(&ssd); // Configura o display
  ssd1306_send_data(&ssd); // Envia os dados para o display

  // Limpa o display. O display inicia com todos os pixels apagados.
  ssd1306_fill(&ssd, false);
  ssd1306_send_data(&ssd);

// PIO
  printf("iniciando a transmissão PIO");
  bool frequenciaClock;
  frequenciaClock = set_sys_clock_khz(128000, false);
  uint offset = pio_add_program(pio, &pio_matrix_program);
  sm = pio_claim_unused_sm(pio, true);
  pio_matrix_program_init(pio, sm, offset, LED_PIN);

// Botões e LEDs RGB
  gpio_init(BUTTON_A);
  gpio_set_dir(BUTTON_A, GPIO_IN);
  gpio_pull_up(BUTTON_A);
  gpio_set_irq_enabled_with_callback(BUTTON_A, GPIO_IRQ_EDGE_FALL, true, &irq_button);

  gpio_init(BUTTON_B);
  gpio_set_dir(BUTTON_B, GPIO_IN);
  gpio_pull_up(BUTTON_B);
  gpio_set_irq_enabled_with_callback(BUTTON_B, GPIO_IRQ_EDGE_FALL, true, &irq_button);

  gpio_init(LED_GREEN);
  gpio_set_dir(LED_GREEN, GPIO_OUT);
  gpio_put(LED_GREEN, 0);

  gpio_init(LED_BLUE);
  gpio_set_dir(LED_BLUE, GPIO_OUT);
  gpio_put(LED_BLUE, 0);

  gpio_init(LED_PIN);
  gpio_set_dir(LED_PIN, GPIO_OUT);
}

// Função principal
int main()
{
  stdio_init_all(); // Inicializa a comunicação serial
  setup(); // Configuração inicial

  bool cor = true;

  // Loop principal
  while (true)
  {
    cor = !cor;
    char caractere = getchar(); // Recebe um caractere
    if (caractere >= '0' && caractere <= '9') // Verifica se o caractere é um número
    {
      desenho_pio(sprites[caractere - '0'], valor_led, pio, sm, 1.0, 1.0, 1.0);
    }
    else
    {
      desenho_pio(apagar_leds, valor_led, pio, sm, 0.0, 0.0, 0.0);
    }
    char_display(caractere, cor); // Envia o caractere para o display
    sleep_ms(1000); // Aguarda 1 segundo
  }
}