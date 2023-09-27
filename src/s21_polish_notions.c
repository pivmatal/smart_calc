#include "s21_smartcalc.h"

int is_digit(char op) {
  int flag = 0;
  if (op == '0' || op == '1' || op == '2' || op == '3' || op == '4' ||
      op == '5' || op == '6' || op == '7' || op == '8' || op == '9' ||
      op == '.' || op == 'x') {
    flag = 1;
  }
  return flag;
}

int is_operator(char op) {
  int flag = 0;
  if (op == '+' || op == '-' || op == '*' || op == '/' || op == '^' ||
      op == '~' || op == '`' || op == 's' || op == 'c' || op == 't' ||
      op == 'p' || op == 'o' || op == 'u' || op == 'e' || op == 'l' ||
      op == '(') {
    flag = 1;
  }
  return flag;
}

int unar_operation(char op) {
  int flag = 0;
  if (op == '~' || op == '`' || op == 's' || op == 'c' || op == 't' ||
      op == 'p' || op == 'o' || op == 'u' || op == 'e' || op == 'l') {
    flag = 1;
  }
  return flag;
}

int is_valid(char expression[]) {
  int flag = 0;
  // int j = 0;
  int dot = 0;
  for (int i = 0; i < (int)strlen(expression); i++) {
    if (is_digit(expression[i]) == 1 || is_operator(expression[i]) == 1) {
      flag = 1;
    }

    if (flag == 1) {
      while (is_digit(expression[i]) == 1 || expression[i] != ' ') {
        if (expression[i] == '.') {
          if (is_digit(expression[i - 1]) == 0 ||
              is_digit(expression[i + 1]) == 0) {
            dot = 2;
          }
          dot++;
        }

        i++;
      }
      if (dot > 1) {
        flag = 0;
        break;
      }
      dot = 0;
    }
  }
  // printf("flag = %d\n", flag);
  return flag;
}
/*---------------------------
    Приоритет:  +:   1    Отдельно: sin, cos, tan,
                -:   1              asin, acos, atan,
                *:   2              ln, log, '(', ')';
                /:   2
                mod: 2
                ^:   3
----------------------------*/

int get_operator_priority(char op) {
  int flag = 0;
  if (op == '+' || op == '-') {
    flag = 1;
  } else if (op == '*' || op == '/') {
    flag = 2;
  } else if (op == '^') {
    flag = 3;
  } else if (op == 's' || op == 'c' || op == 't' || op == 'p' || op == 'o' ||
             op == 'u' || op == 'e' || op == 'l') {
    flag = 4;
  } else if (op == '~' || op == '`') {
    flag = 5;
  } else {
    flag = 0; // Для других символов, не являющихся операторами, возвращаем 0
              // приоритет.
  }
  return flag;
}

void parser(char expression[], char result_mass[]) {
  stack_n *top = NULL;
  int result_index = 0;

  for (int i = 0; i < (int)strlen(expression); i++) {
    if (is_digit(expression[i]) == 1 || expression[i] == 'x') {
      result_mass[result_index++] = expression[i];
      if (is_digit(expression[i + 1]) == 0) {
        result_mass[result_index++] = ' ';
      }

    } else if (expression[i] == '+' || expression[i] == '-' ||
               expression[i] == '*' || expression[i] == '/' ||
               expression[i] == '^' || expression[i] == '(' ||
               expression[i] == ')' || expression[i] == '%' ||
               expression[i] == 's' || expression[i] == 'c' ||
               expression[i] == 't' || expression[i] == 'p' ||
               expression[i] == 'o' || expression[i] == 'u' ||
               expression[i] == 'e' || expression[i] == 'l' ||
               expression[i] == '~' || expression[i] == '`') {

      if (expression[i] == ')') {
        while (top && top->data[0] != '(') {
          result_mass[result_index++] = top->data[0];
          result_mass[result_index++] = ' ';
          pop_stack(&top);
        }
        if (top && top->data[0] == '(') {
          pop_stack(&top);
        }
      } else {

        while (top &&
               get_operator_priority(top->data[0]) >=
                   get_operator_priority(expression[i]) &&
               expression[i] != '(') {
          result_mass[result_index++] = top->data[0];
          result_mass[result_index++] = ' ';
          pop_stack(&top);
        }
        char operator_str[1] = {expression[i]};
        push_stack(operator_str, &top);
      }
    }
  }

  while (top) {
    result_mass[result_index++] = top->data[0];
    result_mass[result_index++] = ' ';
    pop_stack(&top);
  }

  result_mass[result_index] = '\0'; // Добавляем завершающий нулевой символ.
}

/*---------------------------
    sin = s cos = c, tan = t,
    asin = p, acos = o, atan = u,
    ln = e, log = l, ;


----------------------------*/
void transform_mass(
    char expression[]) { // возможно переполнение. На тестах провериьт
  int result_index = 0;

  char tmp[512];
  int k = 0;
  int j = 0;
  // int flag = 0;
  for (k = 0, j = 0; j < (int)strlen(expression); j++) {
    if (expression[j] != ' ') {
      tmp[k++] = expression[j];
    }
  }

  tmp[k] = '\0'; // Добавляем завершающий нулевой символ
  strcpy(expression, tmp);

  char result_mass[512];
  for (int i = 0; i < (int)strlen(expression); i++) {
    if (expression[i] == 'm' && expression[i + 1] == 'o' &&
        expression[i + 2] == 'd') {
      result_mass[result_index++] = '%';
      i = i + 3;
    } else if (expression[i] == 's' && expression[i + 1] == 'i' &&
               expression[i + 2] == 'n') {
      result_mass[result_index++] = 's'; // Заменяем "sin" на символ 's'
      i = i + 3;
    } else if (expression[i] == 'c' && expression[i + 1] == 'o' &&
               expression[i + 2] == 's') {
      result_mass[result_index++] = 'c'; // Заменяем
      i = i + 3;
    } else if (expression[i] == 't' && expression[i + 1] == 'a' &&
               expression[i + 2] == 'n') {
      result_mass[result_index++] = 't'; // Заменяем
      i = i + 3;
    } else if (expression[i] == 'l' && expression[i + 1] == 'o' &&
               expression[i + 2] == 'g') {
      result_mass[result_index++] = 'l'; // Заменяем
      i = i + 3;
    } else if (expression[i] == 'l' && expression[i + 1] == 'n') {
      result_mass[result_index++] = 'e'; // Заменяем
      i = i + 2;
    } else if (expression[i] == 'a' && expression[i + 1] == 's' &&
               expression[i + 2] == 'i' && expression[i + 3] == 'n') {
      result_mass[result_index++] = 'p'; // Заменяем
      i = i + 4;
    } else if (expression[i] == 'a' && expression[i + 1] == 'c' &&
               expression[i + 2] == 'o' && expression[i + 3] == 's') {
      result_mass[result_index++] = 'o'; // Заменяем
      i = i + 4;
    } else if (expression[i] == 'a' && expression[i + 1] == 't' &&
               expression[i + 2] == 'a' && expression[i + 3] == 'n') {
      result_mass[result_index++] = 'u'; // Заменяем
      i = i + 4;
    } else if (expression[i] == '-' &&
               (is_operator(expression[i - 1]) == 1 || (i - 1) < 0)) {
      result_mass[result_index++] = '~'; // Заменяем
      i = i + 1;
    } else if (expression[i] == '+' &&
               (is_operator(expression[i - 1]) == 1 || (i - 1) < 0)) {
      result_mass[result_index++] = '`'; // Заменяем
      i = i + 1;
    }
    result_mass[result_index++] = expression[i];
  }
  result_mass[result_index] = '\0';
  strcpy(expression, result_mass);
}
