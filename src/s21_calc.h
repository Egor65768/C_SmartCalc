#ifndef S21_CALC_H
#define S21_CALC_H

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE_EXPRESSION 1024

typedef struct s21_calc {
  double value;
  int priority;
  int operation;
  struct s21_calc* next;
} STAC;

enum operation {
  number,
  openbracket,
  closebracket,
  calc_add,
  calc_sub,
  calc_mul,
  calc_div,
  calc_pow,
  calc_mod,
  uadd,
  umin,
  calc_cos,
  calc_sin,
  calc_tan,
  calc_acos,
  calc_asin,
  calc_atan,
  calc_sqrt,
  calc_ln,
  calc_log,
  calc_x
};

/*
ВАЛИДАЦИЯ
*/

// Основная функция валидации
int validashion(char* input_expression);

// Проверка правильности растановки мат. операторов и сокбок
int check_math_syntax(char* str, int char_position, int* bracket);

// Проверка на правильное использование функций
int validate_function_operator_name(char* str, int* char_position);

// Анализирует строку и проверяет наличие чисел, символа 'x' и других условий
int validate_expression_segment(char* str, int* i);

// Функцию проверяет наличие символа 'x' в строке
int check_for_x(char* buf);

// Функция проверяет правильность расположения в стеке
int validate_stack_conditions(STAC* stack_notation);

/*
ПАРСИНГ
*/
// Основная функция парсинга
int parsing(STAC** stac_notation, char* str, double resultat);

// Функции ищет число в строке и обрабатывает ошибки
double read_number_with_error_check(char* str, int* n, int* flag_error);

// Функции обрабатывает мат. операции и добавляет их в стек. При ошибке
// возвращает 1
int parse_and_push_function(STAC** stac_notation, int* n, char* str);

// Функция обрабатывает математические операторы и скобки
void parse_operator_and_brackets(STAC** stac_notation, char* str, int n,
                                 int* bracket, int* last_oper);

/*
ОПЕРАЦИИ СО СТЕКОМ
*/

// Функция создает новый элемент стека
STAC* create(double value, int priority, int operation);

// Функция отчищает переданный элемент, указатель на следующий элемент
void destroy(STAC* stac_notation);

// Функция добавляет элемент в конец стека
void push_back(STAC** stac_notation, double value, int priority, int operation);

// Функция добавляет элемент в начало стека
void push_front(STAC** stac_notation, double value, int priority,
                int operation);

// Функция добавляет элемент в стек с учетом позиции
void insert_into_stack_at_position(STAC** stac_notation, double value,
                                   int priority, int operation, int position);

// Функция удаляет элемент из стека по заданной позиции
STAC* remove_element_at_position(STAC* stac_notation, int n);

// Функция возвращает элемент стека по заданной позиции
STAC* get_element_at_position(STAC* stac_notation, int n);

/*
КАЛЬКУЛЯТОР
*/

// Основная функция калькулятора. Возвращает статус
int calculator(char* str, double* result);

// Функции выполняет расчет на основе строки и возвращает код ошибки
int calculate_from_expression(char* str, double* result);

// Функция преобразовывает инфиксную нотации в постфиксную нотацию
STAC* convert_to_postfix_notation(STAC* stac_notation);

// Функция вычисляет постфиксные выражения
double calculate_postfix_expression(STAC* stac_notation);

// Функция выполняет арифметические операции над элементами стека
STAC* calculate_binary_operation(STAC* stac_notation, int n);

// Функция вычисляет значения математических функций на основе стека
STAC* calculate_math_function_from_stack(STAC* stac_notation, int n);

typedef struct s21_credit {
  // всего месяцев кредита
  int num_mont;
  // текущий месяц
  int current_month;
  // полная сумма кредита
  double ful_sum;
  // годовой процент
  double persent_year;
  // месячный платеж
  double month_sum;
  // платеж по процентам в месяц
  double month_persent;
  // платеж по основному долгу
  double main_pay;
  // остаток
  double remains;
  // всего уплочено
  double all_pay;
  // тип кредита: 1 - аннунитетный 2-дифференцированный
  int type;
} CREDIT;

enum type_credit { annuity_loan = 1, deferred_loan = 2 };

typedef struct s21_deposit {
  // полная сумма
  double ful_sum;
  // всего месяцев
  int num_month;
  // годовой процент
  double persent_year;
  // ключевая ставка ЦБ
  double central_banck_percen;
  // налог
  double tax;
  // прибыль за все время
  double money;
  // прибыль за определенный промежуток
  double money_month;
  // годовая прибыль
  double money_year;
  // выплаты по вкладу
  double payments;
  // изменение баланса
  double delta;
  int type;
  // выплата каждый день - 1 каждую неделю - 2 каждый месяц -3
  // каждый год - 4 в конце срока 5
  int type_pay;
  // внесено или вынесено
  double add_or_sub;
} DEPOSIT;

enum type_deposit { pay = 1, capitalization = 2 };

enum type_deposit_pay {
  every_day = 1,
  every_week = 2,
  every_month = 3,
  every_year = 4,
  at_the_end_of_the_term = 5
};

// Функция рассчитывает параметры кредита
int s21_calculate_credit_payment(CREDIT* credit_stac);

// Функция выполняет операции начисления процентов на депозит и обновлением его
// состояния.
int s21_calculate_deposit_interest(DEPOSIT* s21_dep, int days_in_year,
                                   int day_in_last);

#endif