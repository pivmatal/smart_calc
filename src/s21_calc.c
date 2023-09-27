#include "s21_smartcalc.h"

double start(char expression[], char x[]) {
  int len = strlen(expression) + 1;
  char *tmp = (char *)malloc(len * sizeof(char));

  for (int i = 0; i < len; i++) {
    tmp[i] = expression[i];
  }

  char result[512] = {'\0'};
  double res = NAN;
  // printf("x = %s\n",x);

  // printf("expression = %s\n",expression);

  if (x[0] != '\0') {
    from_x_to_func(expression, x);
    // printf("from_x_to_func = %s\n",expression);
  }

  // printf("expression = %s\n",expression);
  transform_mass(expression);
  // printf("expression = %s\n",expression);
  parser(expression, result);

  // printf("pareser = %s\n",result);

  if (is_valid(result) == 1) {
    res = calculation(result);
    // printf("calculation\n");
  }
  // printf("res = %f\n",res);

  for (int i = 0; i < len; i++) {
    expression[i] = tmp[i];
  }

  free(tmp);
  return res;
}

double calculation(char expression[]) {
  stack_n *top = NULL;
  double num1 = 0;
  double num2 = 0;
  int j = 0;
  int grad = 0;
  double res = 0;
  // int err = 0;
  for (int i = 0; i < (int)strlen(expression); i++) {
    j = 0;
    if (is_digit(expression[i]) == 1) {
      char tmp_num[512] = {'\0'};
      while (is_digit(expression[i]) == 1 || expression[i] != ' ') {
        tmp_num[j++] = expression[i++];
      }
      tmp_num[j] = '\0';
      push_stack(tmp_num, &top);
    } else if (is_operator(expression[i]) == 1) {
      double result;
      num1 = atof(top->data);
      pop_stack(&top);
      if (unar_operation(expression[i]) == 0) {
        num2 = atof(top->data);
        pop_stack(&top);
      }
      switch (expression[i]) {
      case 's':
        result = sin(num1);
        break;
      case 'c':
        result = cos(num1);
        break;
      case 't':

        grad = num1 * 180 / 3.1415;
        grad = round(grad);

        if(fmod(grad,90)==0 && fmod(grad,180)!=0 ){
          result = NAN; 
        } else {
          result = tan(num1);
        }
        
 
        break;
      case 'p':
        result = asin(num1);
        break;
      case 'o':
        result = acos(num1);
        break;
      case 'u':
        result = atan(num1);
        break;
      case 'e':
        result = log(num1);
        break;
      case 'l':
        result = log10(num1);
        break;
      case '~':
        result = -num1;
        break;
      case '`':
        result = 0 + num1;
        break;
      case '+':
        result = num1 + num2;
        break;
      case '-':
        result = num2 - num1;
        break;
      case '*':
        result = num1 * num2;
        break;
      case '/':
        result = num2 / num1;
        break;
      case '^':
        result = pow(num2, num1);
        break;
      default:
        result = 0;
        break;
      }
      char text[512];
      sprintf(text, "%.7f", result);

      push_stack(text, &top);
    }
  }
  res = atof(top->data);
  pop_stack(&top);
  return res;
}

void from_x_to_func(char expression[], char x[]) {
  char tmp[512];
  int tmp_index = 0; // Индекс для временного массива tmp

  for (int i = 0; i < (int)strlen(expression); i++) {
    if (expression[i] == 'x') {
      int x_index = 0; // Индекс для массива x
      // Копируем символы из x в tmp
      while (x[x_index] != '\0') {
        tmp[tmp_index++] = x[x_index++];
      }
    } else {
      tmp[tmp_index++] = expression[i];
    }
  }

  // Завершаем временную строку нуль-символом
  tmp[tmp_index] = '\0';

  // Копируем данные из временной строки tmp обратно в expression
  strcpy(expression, tmp);
}
