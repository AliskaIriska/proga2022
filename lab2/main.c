/* / Подключение библиотек
#include "xtimer.h"
#include "timex.h"
#include "periph/gpio.h"

// Обработчик прерывания по нажатию кнопки
void btn_handler(void *arg)
{
  if (gpio_read(GPIO_PIN(A,0))>0){}
  // Прием аргументов, передаваемых из главного потока.
  (void)arg;
  // Переключение состояния пина PC8
  gpio_toggle(GPIO_PIN(PORT_C, 8));
}


int main(void)
{
  // Инициализация пина PA0, к которому подключена кнопка, как источника прерывания.
  // GPIO_RISING - прерывание срабатывает по фронту
  // btn_handler - имя функции обработчика прерывания
  // NULL - ничего не передаем в аргументах
  gpio_init_int(GPIO_PIN(PORT_A, 0), GPIO_IN, GPIO_RISING, btn_handler, NULL);
  // Инициализация пина PC8 на выход
  gpio_init(GPIO_PIN(PORT_C, 8), GPIO_OUT);

  while(1){}
  return 0;
}
*/

// Подключение библиотек
#include "xtimer.h"
#include "timex.h"
#include "periph/gpio.h"

//Количество микросекунд, прошедших с последнего вызова обработчика
uint32_t timer = 0;


// Обработчик прерывания по нажатию кнопки
void btn_handler1(void *arg) //задание 1
{
  // Прием аргументов, передаваемых из главного потока.
  (void)arg;
  if ((xtimer_usec_from_ticks(xtimer_now()) - timer) > 100000){ 
    // Переключение состояния пина PC8
    gpio_toggle(GPIO_PIN(PORT_C, 8));
    //Обновляем время последнего вызова обработчика
    timer = xtimer_usec_from_ticks(xtimer_now());
  }
}


void btn_handler2(void *arg){ //задание 2

  if (gpio_read(GPIO_PIN(PORT_A,0)) > 0){ //фронт
    (void)arg;
    if ((xtimer_usec_from_ticks(xtimer_now()) - timer) > 100000){ 
    // Переключение состояния пина PC8
      gpio_set(GPIO_PIN(PORT_C, 8));
    //Обновляем время последнего вызова обработчика
    timer = xtimer_usec_from_ticks(xtimer_now());
    }
  }
  else { //спад
    (void)arg;
    gpio_clear(GPIO_PIN(PORT_C, 8));
  }
}


int main(void)
{
  // Инициализация пина PA0, к которому подключена кнопка, как источника прерывания.
  // GPIO_RISING - прерывание срабатывает по фронту
  // btn_handler - имя функции обработчика прерывания
  // NULL - ничего не передаем в аргументах
  gpio_init_int(GPIO_PIN(PORT_A, 0), GPIO_IN, GPIO_RISING, btn_handler1, NULL); //задание 1
  gpio_init_int(GPIO_PIN(PORT_A, 0), GPIO_IN, GPIO_BOTH, btn_handler2, NULL); //задание 2
  // Инициализация пина PC8 на выход
  gpio_init(GPIO_PIN(PORT_C, 8), GPIO_OUT);

  while(1){}
  return 0;
}
