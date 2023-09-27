#include "s21_smartcalc.h"
// #include <math.h>
// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>

// struct node{
//     char *data;
//     struct node* link;
// };
// typedef struct node stack_n;

// // stack functions
// void push_stack(char x[], stack_n** top);
// void pop_stack(stack_n** top);
// void print_stack(stack_n** top);

// // polish functions
// int is_digit(char op);
// int is_operator(char op);
// int unar_operation(char op) ;
// int is_valid(char expression[]);
// int get_operator_priority(char op);
// void parser(char expression[], char result_mass[]);
// void transform_mass(char expression[]);

// // calc functions
// double calculation(char expression[]);
// double start(char expression[],char x[]);
// void from_x_to_func(char expression[], char x[]);

// void push_stack(char x[], stack_n **top) {
//   stack_n *new_node = (stack_n *)malloc(sizeof(stack_n));
//   new_node->data = (char *)malloc(strlen(x) * sizeof(char));
//   strcpy(new_node->data, x);
//   new_node->link = *top;
//   *top = new_node;
// }

// void pop_stack(stack_n **top) {
//   if (*top == NULL)
//     return;
//   stack_n *tmp = (*top)->link;
//   free((*top)->data);
//   free(*top);
//   *top = tmp;
// }

// void print_stack(stack_n **top) {
//   stack_n *tmp = *top;
//   while (tmp != NULL) {
//     printf("%s\n", tmp->data);
//     tmp = tmp->link;
//   }
// }

// int is_digit(char op) {
//   int flag = 0;
//   if (op == '0' || op == '1' || op == '2' || op == '3' || op == '4' ||
//       op == '5' || op == '6' || op == '7' || op == '8' || op == '9' ||
//       op == '.' || op == 'x') {
//     flag = 1;
//   }
//   return flag;
// }

// int is_operator(char op) {
//   int flag = 0;
//   if (op == '+' || op == '-' || op == '*' || op == '/' || op == '^' ||
//       op == '~' || op == '`' || op == 's' || op == 'c' || op == 't' ||
//       op == 'p' || op == 'o' || op == 'u' || op == 'e' || op == 'l' || op ==
//       '(') {
//     flag = 1;
//   }
//   return flag;
// }

// int unar_operation(char op) {
//   int flag = 0;
//   if (op == '~' || op == '`' || op == 's' || op == 'c' || op == 't' ||
//       op == 'p' || op == 'o' || op == 'u' || op == 'e' || op == 'l') {
//     flag = 1;
//   }
//   return flag;
// }

// int is_valid(char expression[]) {
//   int flag = 0;
//   // int j = 0;
//   int dot = 0;
//   for (int i = 0; i < (int)strlen(expression); i++) {
//     if (is_digit(expression[i]) == 1 || is_operator(expression[i]) == 1) {
//       flag = 1;
//     }

//     if (flag == 1) {
//       while (is_digit(expression[i]) == 1 || expression[i] != ' ') {
//         if (expression[i] == '.') {
//           if (is_digit(expression[i - 1]) == 0 ||
//               is_digit(expression[i + 1]) == 0) {
//             dot = 2;
//           }
//           dot++;
//         }

//         i++;
//       }
//       if (dot > 1) {
//         flag = 0;
//         break;
//       }
//       dot = 0;
//     }
//   }
//   // printf("flag = %d\n", flag);
//   return flag;
// }
// /*---------------------------
//     Приоритет:  +:   1    Отдельно: sin, cos, tan,
//                 -:   1              asin, acos, atan,
//                 *:   2              ln, log, '(', ')';
//                 /:   2
//                 mod: 2
//                 ^:   3
// ----------------------------*/

// int get_operator_priority(char op) {
//   int flag = 0;
//   if (op == '+' || op == '-') {
//     flag = 1;
//   } else if (op == '*' || op == '/') {
//     flag = 2;
//   } else if (op == '^') {
//     flag = 3;
//   } else if (op == 's' || op == 'c' || op == 't' || op == 'p' || op == 'o' ||
//              op == 'u' || op == 'e' || op == 'l') {
//     flag = 4;
//   } else if (op == '~' || op == '`') {
//     flag = 5;
//   } else {
//     flag = 0; // Для других символов, не являющихся операторами, возвращаем 0
//               // приоритет.
//   }
//   return flag;
// }

// void parser(char expression[], char result_mass[]) {
//   stack_n *top = NULL;
//   int result_index = 0;

//   for (int i = 0; i < (int)strlen(expression); i++) {
//     if (is_digit(expression[i]) == 1 || expression[i] == 'x') {
//       result_mass[result_index++] = expression[i];
//       if (is_digit(expression[i + 1]) == 0) {
//         result_mass[result_index++] = ' ';
//       }

//     } else if (expression[i] == '+' || expression[i] == '-' ||
//                expression[i] == '*' || expression[i] == '/' ||
//                expression[i] == '^' || expression[i] == '(' ||
//                expression[i] == ')' || expression[i] == '%' ||
//                expression[i] == 's' || expression[i] == 'c' ||
//                expression[i] == 't' || expression[i] == 'p' ||
//                expression[i] == 'o' || expression[i] == 'u' ||
//                expression[i] == 'e' || expression[i] == 'l' ||
//                expression[i] == '~' || expression[i] == '`') {

//       if (expression[i] == ')') {
//         while (top && top->data[0] != '(') {
//           result_mass[result_index++] = top->data[0];
//           result_mass[result_index++] = ' ';
//           pop_stack(&top);
//         }
//         if (top && top->data[0] == '(') {
//           pop_stack(&top);
//         }
//       } else {

//         while (top &&
//                get_operator_priority(top->data[0]) >=
//                    get_operator_priority(expression[i]) &&
//                expression[i] != '(') {
//           result_mass[result_index++] = top->data[0];
//           result_mass[result_index++] = ' ';
//           pop_stack(&top);
//         }
//         char operator_str[1] = {expression[i]};
//         push_stack(operator_str, &top);
//       }
//     }
//   }

//   while (top) {
//     result_mass[result_index++] = top->data[0];
//     result_mass[result_index++] = ' ';
//     pop_stack(&top);
//   }

//   result_mass[result_index] = '\0'; // Добавляем завершающий нулевой символ.
// }

// /*---------------------------
//     sin = s cos = c, tan = t,
//     asin = p, acos = o, atan = u,
//     ln = e, log = l, ;

// ----------------------------*/
// void transform_mass(
//     char expression[]) { // возможно переполнение. На тестах провериьт
//   int result_index = 0;

//   char tmp[512];
//   int k = 0;
//   int j = 0;
//   int flag = 0;
//   // printf("strlen %d\n",(int)strlen(expression));
//   for (k = 0, j = 0; j < (int)strlen(expression); j++) {
//     if (expression[j] != ' ') {
//       tmp[k++] = expression[j];
//     }
//   }

//   tmp[k] = '\0'; // Добавляем завершающий нулевой символ
//   strcpy(expression, tmp);

//   char result_mass[512];
//   for (int i = 0; i < (int)strlen(expression); i++) {
//     if (expression[i] == 'm' && expression[i + 1] == 'o' &&
//         expression[i + 2] == 'd') {
//       result_mass[result_index++] = '%';
//       i = i + 3;
//     } else if (expression[i] == 's' && expression[i + 1] == 'i' &&
//                expression[i + 2] == 'n') {
//       result_mass[result_index++] = 's'; // Заменяем "sin" на символ 's'
//       i = i + 3;
//     } else if (expression[i] == 'c' && expression[i + 1] == 'o' &&
//                expression[i + 2] == 's') {
//       result_mass[result_index++] = 'c'; // Заменяем
//       i = i + 3;
//     } else if (expression[i] == 't' && expression[i + 1] == 'a' &&
//                expression[i + 2] == 'n') {
//       result_mass[result_index++] = 't'; // Заменяем
//       i = i + 3;
//     } else if (expression[i] == 'l' && expression[i + 1] == 'o' &&
//                expression[i + 2] == 'g') {
//       result_mass[result_index++] = 'l'; // Заменяем
//       i = i + 3;
//     } else if (expression[i] == 'l' && expression[i + 1] == 'n') {
//       result_mass[result_index++] = 'e'; // Заменяем
//       i = i + 2;
//     } else if (expression[i] == 'a' && expression[i + 1] == 's' &&
//                expression[i + 2] == 'i' && expression[i + 3] == 'n') {
//       result_mass[result_index++] = 'p'; // Заменяем
//       i = i + 4;
//     } else if (expression[i] == 'a' && expression[i + 1] == 'c' &&
//                expression[i + 2] == 'o' && expression[i + 3] == 's') {
//       result_mass[result_index++] = 'o'; // Заменяем
//       i = i + 4;
//     } else if (expression[i] == 'a' && expression[i + 1] == 't' &&
//                expression[i + 2] == 'a' && expression[i + 3] == 'n') {
//       result_mass[result_index++] = 'u'; // Заменяем
//       i = i + 4;
//     } else if (expression[i] == '-' &&
//                (is_operator(expression[i - 1]) == 1 || (i - 1) < 0)) {
//       result_mass[result_index++] = '~'; // Заменяем
//       i = i + 1;
//     } else if (expression[i] == '+' &&
//                (is_operator(expression[i - 1]) == 1 || (i - 1) < 0)) {
//       result_mass[result_index++] = '`'; // Заменяем
//       i = i + 1;
//     }
//     result_mass[result_index++] = expression[i];
//   }
//   result_mass[result_index] = '\0';
//   strcpy(expression, result_mass);
// }

// // double starting(char expression[],char x[]){
// //   char result[512];
// //   double res = NAN;
// //   transform_mass(expression);
// //   parser(expression,result);
// //   if(x[0] != '\0'){
// //     from_x_to_func(result,x);
// //     printf("\n%s\n",result);
// //   }
// //   if(is_valid(result) == 1){
// //     res = calculation(result);
// //   }
// //   return res;
// // }

// double calculation(char expression[]) {
//   stack_n *top = NULL;
//   double num1 = 0;
//   double num2 = 0;
//   int j = 0;
//   double res = 0;
//   // int err = 0;
//   for (int i = 0; i < (int)strlen(expression); i++) {
//     j = 0;
//     if (is_digit(expression[i]) == 1) {
//       char tmp_num[512];
//       while (is_digit(expression[i]) == 1 || expression[i] != ' ') {
//         tmp_num[j++] = expression[i++];
//       }
//       tmp_num[j] = '\0';
//       push_stack(tmp_num, &top);
//     } else if (is_operator(expression[i]) == 1) {
//       double result;
//       num1 = atof(top->data);
//       pop_stack(&top);
//       if (unar_operation(expression[i]) == 0) {
//         num2 = atof(top->data);
//         pop_stack(&top);
//       }
//       switch (expression[i]) {
//       case 's':
//         result = sin(num1);
//         break;
//       case 'c':
//         result = cos(num1);
//         break;
//       case 't':
//         result = tan(num1);
//         break;
//       case 'p':
//         result = asin(num1);
//         break;
//       case 'o':
//         result = acos(num1);
//         break;
//       case 'u':
//         result = atan(num1);
//         break;
//       case 'e':
//         result = log(num1);
//         break;
//       case 'l':
//         result = log10(num1);
//         break;
//       case '~':
//         result = -num1;
//         break;
//       case '`':
//         result = 0 + num1;
//         break;
//       case '+':
//         result = num1 + num2;
//         break;
//       case '-':
//         result = num2 - num1;
//         break;
//       case '*':
//         result = num1 * num2;
//         break;
//       case '/':
//         result = num2 / num1;
//         break;
//       case '^':
//         result = pow(num2, num1);
//         break;
//       default:
//         result = 0;
//         break;
//       }
//       char text[512];
//       sprintf(text, "%.7f", result);

//       push_stack(text, &top);
//     }
//   }
//   res = atof(top->data);
//   pop_stack(&top);
//   return res;
// }

// void from_x_to_func(char expression[], char x[]) {
//   char tmp[512];
//   int tmp_index = 0; // Индекс для временного массива tmp

//   for (int i = 0; i < (int)strlen(expression); i++) {
//     if (expression[i] == 'x') {
//       int x_index = 0; // Индекс для массива x
//       // Копируем символы из x в tmp
//       while (x[x_index] != '\0') {
//         tmp[tmp_index++] = x[x_index++];
//         printf("TYT\n");

//       }
//     } else {
//       tmp[tmp_index++] = expression[i];
//     }
//   }

//   // Завершаем временную строку нуль-символом
//   tmp[tmp_index] = '\0';

//   // Копируем данные из временной строки tmp обратно в expression
//   strcpy(expression, tmp);
// }

// double start(char expression[],char x[]){
//   char result[512] = {'\0'};
//   double res = NAN;
//   printf("x = %s\n",x);

//   if(x[0] != '\0'){
//       from_x_to_func(expression,x);
//       printf("OK\n");
//   }

//   transform_mass(expression);
//   parser(expression,result);

//   printf("pareser = %s\n",result);

//   if(is_valid(result) == 1){
//     res = calculation(result);
//   }
//   printf("res = %f\n",res);
//   return res;

// }

int main() {
  char temp[128] = "tan(1.573)";
  char temp2[128];
  
  printf("%.25f",start(temp,temp2));
  

  return 0;
}