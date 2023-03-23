#include "./s21_smart_calc.h"

#define SIZE 10
#define BUFFER_SIZE 256
#define GTK_HAVE_FREE_ALL_MEMORY 1

typedef struct {
  GtkWidget *draw;
  GtkWidget *window;
  GtkWidget *grid;
  GtkWidget *button[33];

  GtkWidget *box;
  GtkWidget *box_x;
  GtkWidget *box_Ox1;
  GtkWidget *box_Ox2;
  GtkWidget *box_Oy1;
  GtkWidget *box_Oy2;

  char x_buffer[BUFFER_SIZE];
  char Ox1_buffer[BUFFER_SIZE];
  char Ox2_buffer[BUFFER_SIZE];
  char Oy1_buffer[BUFFER_SIZE];
  char Oy2_buffer[BUFFER_SIZE];
  char output_buffer[BUFFER_SIZE];
  char graph_buffer[BUFFER_SIZE];

  gdouble Ox1;
  gdouble Ox2;
  gdouble Oy1;
  gdouble Oy2;
  gdouble x;
} boxes_and_data;


gdouble s21_get_point(gfloat x, boxes_and_data *data) {
  char str[BUFFER_SIZE];
  gdouble result = s21_get_answer(str, data->graph_buffer, x);
  return result;
}

static gboolean on_draw(GtkWidget *widget, cairo_t *cr, gpointer user_data) {
  boxes_and_data *data = user_data;
  gdouble x1 = data->Ox1;
  gdouble x2 = data->Ox2;
  gdouble y1 = data->Oy1;
  gdouble y2 = data->Oy2;
  if (!(x1 != x1) && x2 > x1 && y2 > y1) {
    gdouble dx = 1.0, dy = 1.0; /* Pixels between each point (step)*/
    gdouble clip_x1 = 0.0;
    gdouble clip_x2 = 0.0;
    gdouble clip_y1 = 0.0;
    gdouble clip_y2 = 0.0;
    cairo_set_font_size(cr, 10);
    cairo_set_source_rgb(cr, 1.0, 1.0, 1.0); // Set white color
    cairo_paint(cr); // Paint white whole area
    cairo_clip_extents(cr, &clip_x1, &clip_y1, &clip_x2, &clip_y2); // Get clips (x1 - left, x2 - right, y1 - top, y2 - bottom)
    clip_x1 = clip_x1 + 40;
    clip_y2 = clip_y2 - 24;
    gdouble step_x = (x2 - x1) / ((clip_x2 - clip_x1) / dx); // recalculated steps according Ox and Oy
    gdouble step_y = (y2 - y1) / ((clip_y2 - clip_y1) / dy);
    s21_print_mesh(cr, clip_x1, clip_x2, clip_y1, clip_y2, x1, x2, y1, y2, dx, dy, step_x, step_y);

    cairo_set_line_width(cr, dx * 2);
    cairo_set_source_rgb(cr, 0.2, 0.2, 1.0);

    gdouble y = 0.0 / 0.0;
    step_x /= 100;
    step_y /= 100;
    dx /= 100;
    dy /= 100;
    if (strlen(data->graph_buffer) > 0) {
      gdouble i;
      gdouble k;
      for (i = clip_x1, k = x1; i < clip_x2; i += dx, k += step_x) {
        gdouble x = i;
        gdouble prev_y = y;
        y = clip_y2 - ((s21_get_point(k, data) - y1) / step_y * dy);
        if (y != y) {
          cairo_move_to(cr, x, clip_y1);
        } else {
          if (y > clip_y2) {
            y = clip_y2;
          } else if (y < clip_y1) {
            y = clip_y1 - 1;
          }
          if (prev_y != prev_y || prev_y == clip_y2 || prev_y < clip_y1) {
            cairo_move_to(cr, x, y);
          }
          cairo_line_to(cr, x, y);
        }
      }
      cairo_stroke(cr);
    }
    cairo_set_source_rgb(cr, 0.0, 0.0, 0.0);
    cairo_set_line_width(cr, 2);
    cairo_move_to(cr, clip_x1, clip_y2);
    cairo_line_to(cr, clip_x2, clip_y2);
    cairo_stroke(cr);
  }
  return FALSE;
}

void s21_print_mesh(cairo_t *cr, gdouble clip_x1, gdouble clip_x2,
                    gdouble clip_y1, gdouble clip_y2, gdouble x1,
                    gdouble x2, gdouble y1, gdouble y2,
                    gdouble dx, gdouble dy, gdouble step_x, gdouble step_y) {
  gdouble mesh_step_x;
  gdouble mesh_step_y;
  s21_get_steps(&mesh_step_x, &mesh_step_y, x2 - x1, y2 - y1);
  int zero_x_printed;
  int zero_y_printed;
  s21_print_zero_lines(cr, x1, x2, y1, y2, clip_x1, clip_x2,
                       clip_y1, clip_y2, dx, dy, step_x, step_y, &zero_x_printed, &zero_y_printed);

  gdouble start;
  if (zero_x_printed) {
    start = clip_x1 - (x1 / step_x * dx);
    while (start > clip_x1) {
      start -= ((mesh_step_x / step_x) * dx);
    }
  } else {
    start = fmod(x1, mesh_step_x);
    if (x1 < 0.0) {
      start += mesh_step_x;
    }
    start = clip_x1 - start / step_x * dy;
  }
  cairo_set_line_width(cr, dx / 2);
  s21_print_verticals(cr, start, clip_x1, clip_x2, clip_y1, clip_y2, mesh_step_x / step_x * dx);
  cairo_set_line_width(cr, dx / 8);
  mesh_step_x = mesh_step_x / 10.0;
  s21_print_verticals(cr, start, clip_x1, clip_x2, clip_y1, clip_y2, mesh_step_x / step_x * dx);
  if (zero_y_printed) {
    start = clip_y1 + (y2 / step_y * dy);
    while (start > clip_y1) {
      start -= ((mesh_step_y / step_y) * dy);
    }
  } else {
    start = fmod(y2, mesh_step_y);
    if (y2 > 0.0) {
      start = mesh_step_y - start;
    }
    start = clip_y1 - start / step_y * dy;
  }
  cairo_set_line_width(cr, dx / 2);
  s21_print_horizontals(cr, start, clip_x1, clip_x2, clip_y1, clip_y2, mesh_step_y / step_y * dy);
  cairo_set_line_width(cr, dx / 8);
  mesh_step_y = mesh_step_y / 10.0;
  s21_print_horizontals(cr, start, clip_x1, clip_x2, clip_y1, clip_y2, mesh_step_y / step_y * dy);

  cairo_set_line_width(cr, dx * 2);
  cairo_set_source_rgb(cr, 0.0, 0.0, 0.0);
  cairo_move_to(cr, clip_x1 - 24, clip_y2 + 4);
  cairo_show_text(cr, g_strdup_printf("%.1lf", y1));
  cairo_move_to(cr, clip_x1 - 10, clip_y2 + 12);
  cairo_show_text(cr, g_strdup_printf("%.1lf", x1));

  cairo_set_source_rgb(cr, 0.0, 0.0, 0.0);
  cairo_move_to(cr, clip_x1, clip_y2);
  cairo_line_to(cr, clip_x2, clip_y2);
  cairo_move_to(cr, clip_x1, clip_y2);
  cairo_line_to(cr, clip_x1, clip_y1);
  cairo_stroke(cr);
}

void s21_print_verticals(cairo_t *cr, gdouble start, gdouble clip_x1,
                         gdouble clip_x2, gdouble clip_y1, gdouble clip_y2,
                         gdouble pixels_step) {
  for (gdouble i = start; i < clip_x2; i += pixels_step) {
    cairo_move_to(cr, i, clip_y1);
    if (i > clip_x1) {
      cairo_line_to(cr, i, clip_y2);
    }
  }
  cairo_stroke(cr);
}

void s21_print_horizontals(cairo_t *cr, gdouble start, gdouble clip_x1,
                           gdouble clip_x2, gdouble clip_y1, gdouble clip_y2,
                           gdouble pixels_step) {
  for (gdouble i = start; i < clip_y2; i += pixels_step) {
    cairo_move_to(cr, clip_x1, i);
    if (i < clip_y2) {
      cairo_line_to(cr, clip_x2, i);
    }
  }
  cairo_stroke(cr);
}

void s21_print_zero_lines(cairo_t *cr, gdouble x1, gdouble x2,
                          gdouble y1, gdouble y2, gdouble clip_x1,
                          gdouble clip_x2, gdouble clip_y1, gdouble clip_y2,
                          gdouble dx, gdouble dy, gdouble step_x,
                          gdouble step_y, int *zero_x_printed, int *zero_y_printed) {
  cairo_set_source_rgb(cr, 0.2, 0.2, 0.6);
  *zero_x_printed = 0;
  *zero_y_printed = 0;
  if (x1 * x2 <= 0) {
    *zero_x_printed = 1;
    gdouble dist_x = x1 * (-1.0) / step_x * dx;
    cairo_move_to(cr, clip_x1 + dist_x, clip_y2);
    cairo_line_to(cr, clip_x1 + dist_x, clip_y1);
  }
  if (y1 * y2 <= 0) {
    *zero_y_printed = 1;
    gdouble dist_y = y1 * (-1.0) / step_y * dy;
    cairo_move_to(cr, clip_x1, clip_y2 - dist_y);
    cairo_line_to(cr, clip_x2, clip_y2 - dist_y);
  }
  cairo_stroke(cr);
}

void s21_get_steps(gdouble *mesh_step_x, gdouble *mesh_step_y, gdouble x_dim_len, gdouble y_dim_len) {
  *mesh_step_x = 500000.0;
  *mesh_step_y = 500000.0;
  while (*mesh_step_x * 2.0 >= x_dim_len) {
    s21_set_lower_step(mesh_step_x);
  }
  while (*mesh_step_y * 2.0 >= y_dim_len) {
    s21_set_lower_step(mesh_step_y);
  }
//  int steps_count_x = round(x_dim_len / *mesh_step_x);
//  int steps_count_y = round(y_dim_len / *mesh_step_y);
//  if (steps_count_x > steps_count_y) {
//    s21_set_lower_step(mesh_step_y);
//  } else if (steps_count_x < steps_count_y) {
//    s21_set_lower_step(mesh_step_x);
//  }
}

void s21_set_lower_step(gdouble *mesh_step) {
  gdouble temp = *mesh_step;
  while (temp > 10.0) {
    temp /= 10;
  }
  while (temp < 1) {
    temp *= 10;
  }
  if (fmod(temp, 10.0) == 5.0) {
    *mesh_step = *mesh_step / 5.0 * 2.0;
  } else {
    *mesh_step /= 2.0;
  }
}

static void calculate(GtkButton *button, gpointer data) {
  boxes_and_data *widget = data;
  const gchar *text = gtk_button_get_label(button);
  gchar text_1[10] = {0};
  strcpy(text_1, text);
  if (strcmp("=", text) == 0) {
    char str[BUFFER_SIZE] = {0};
    const gchar *x_str = gtk_entry_get_text(GTK_ENTRY(widget->box_x));
    strcpy(widget->x_buffer, x_str);
    if (s21_is_double(widget->x_buffer)) {
      widget->x = s21_str_to_double(widget->x_buffer);
    }
    s21_get_postfix(widget->output_buffer, str);
    s21_get_answer(str, str, widget->x);
    gtk_entry_set_text(GTK_ENTRY(widget->box), "");
    gtk_entry_set_text(GTK_ENTRY(widget->box), str);
    memset(widget->output_buffer, 0, strlen(widget->output_buffer));
    memset(widget->x_buffer, 0, strlen(widget->x_buffer));
    widget->x = 0.0 / 0.0;
  } else if (!strcmp("C", text)) {
    gtk_entry_set_text(GTK_ENTRY(widget->box), "");
    memset(widget->output_buffer, 0, strlen(widget->output_buffer));
  } else if (!strcmp("<--", text)) {
    s21_backspase(widget->output_buffer);
    gtk_entry_set_text(GTK_ENTRY(widget->box), widget->output_buffer);
  } else if (!strcmp("GRAPH", text)) {
    if(s21_is_function(widget->output_buffer)) {
      s21_zero_buffer(widget->graph_buffer);
      s21_get_postfix(widget->output_buffer, widget->graph_buffer);
      const gchar *str = gtk_entry_get_text(GTK_ENTRY(widget->box_Ox1));
      strcpy(widget->Ox1_buffer, str);
      str = gtk_entry_get_text(GTK_ENTRY(widget->box_Ox2));
      strcpy(widget->Ox2_buffer, str);
      str = gtk_entry_get_text(GTK_ENTRY(widget->box_Oy1));
      strcpy(widget->Oy1_buffer, str);
      str = gtk_entry_get_text(GTK_ENTRY(widget->box_Oy2));
      strcpy(widget->Oy2_buffer, str);
      if (s21_is_double(widget->Ox1_buffer) && s21_is_double(widget->Ox2_buffer) &&
          s21_is_double(widget->Oy1_buffer) && s21_is_double(widget->Oy2_buffer)) {
        widget->Ox1 = s21_str_to_double(widget->Ox1_buffer);
        widget->Ox2 = s21_str_to_double(widget->Ox2_buffer);
        widget->Oy1 = s21_str_to_double(widget->Oy1_buffer);
        widget->Oy2 = s21_str_to_double(widget->Oy2_buffer);
        if (widget->Oy2 > widget->Oy1 && widget->Ox2 > widget->Ox1) {
          gtk_widget_queue_draw(widget->draw);
        }
      }
    }
  } else {
    if (!strcmp("sin", text) || !strcmp("cos", text) || !strcmp("tan", text) ||
        !strcmp("asin", text) || !strcmp("acos", text) || !strcmp("atan", text) ||
        !strcmp("sqrt", text) || !strcmp("ln", text) || !strcmp("log", text)) {
      s21_check_for_func(text_1, widget->output_buffer);
    } else if (!strcmp(" / ", text) || !strcmp(" * ", text) || !strcmp(" mod ", text) ||
        !strcmp(" + ", text) || !strcmp(" - ", text) || !strcmp("^", text)) {
      s21_check_input_str(text_1, widget->output_buffer);
    } else if (!strcmp(")", text)) {
      s21_check_closed_br(text_1, widget->output_buffer);
    } else if (!strcmp(".", text)) {
      s21_check_for_point(text_1, widget->output_buffer);
    } else if (!strcmp("x", text) || IS_DIGIT(text[strlen(text) - 1])) {
      s21_check_for_x(text_1, widget->output_buffer);
      if (IS_DIGIT(text[0])) {
        s21_check_for_zero(text_1, widget->output_buffer);
      }
    } else if (!strcmp("(", text)) {
      s21_check_for_open_br(text_1, widget->output_buffer);
    }
    strncat(widget->output_buffer, text_1, strlen(text_1));
    gtk_entry_set_text(GTK_ENTRY(widget->box), widget->output_buffer);
  }
}

void s21_check_for_zero(char *text, char *output_buffer) {
  int last = strlen(output_buffer) - 1;
  if (output_buffer[last] == '0') {
    if (!(last > 0 && (IS_DIGIT(output_buffer[last - 1]) || output_buffer[last - 1] == '.'))) {
      output_buffer[last] = text[0];
      text[0] = 0;
    }
  }
}

int s21_is_function(char *str) {
  int result = 0;
  while(*str) {
    if (*str == 'x') {
      result = 1;
    }
    str++;
  }
  return result;
}

void s21_backspase(char *output_buffer) {
  int last = strlen(output_buffer) - 1;
  if (last > -1) {
    char last_ch = output_buffer[last];
    memset(&output_buffer[last], 0, 1);
    last--;
    if (last_ch == '(') {
      while (last > -1 && output_buffer[last] > 96 && output_buffer[last] < 123) {
        memset(&output_buffer[last], 0, 1);
        last--;
      }
    } else if (last_ch == ' ') {
      while (output_buffer[last] != ' ') {
        memset(&output_buffer[last], 0, 1);
        last--;
      }
      memset(&output_buffer[last], 0, 1);
    }
  }
}

int s21_get_postfix(char *str, char *dst) {
  s21_stack operators;
  s21_stack_init(&operators);
  int error_code = s21_to_postfix(str, &operators, dst);
  return error_code;
}

double s21_get_answer(char *result_str, char *postfix, double x) {
  double result = 0.0 / 0.0;
  s21_stack operands;
  s21_stack_init(&operands);
  int error_code = s21_calculate_postfix(postfix, &operands, x);
  if (!error_code || !strlen(postfix)) {
    result = operands.array[0].operand;
    sprintf(result_str, "%.7lf", operands.array[0].operand);
  } else if (error_code == 1) {
    sprintf(result_str, "Wrong expression");
  } else if (error_code == 2) {
    sprintf(result_str, "Calc error");
  } else if (error_code == 3) {
    sprintf(result_str, "Wrong x value");
  }
  return result;
}

void s21_check_for_func(char *text, char *output_buffer) {
  int buffer_len = strlen(output_buffer);

  if (buffer_len) {
    if (output_buffer[buffer_len - 1] == '.' || output_buffer[buffer_len - 1] == 'x'
        || IS_DIGIT(output_buffer[buffer_len - 1]) || output_buffer[buffer_len - 1] == ')') {
      int shift = output_buffer[buffer_len - 1] == '.' ? 4 : 3;
      int text_len = strlen(text);
      while (text_len > 0) {
        text[text_len + shift - 1] = text[text_len - 1];
        text_len--;
      }
      text[shift - 1] = ' ';
      text[shift - 2] = '*';
      text[shift - 3] = ' ';
      if (shift == 4) {
        text[0] = '0';
      }
    }
  }
  text[strlen(text)] = '(';
}

void s21_check_for_open_br(char *text, char *output_buffer) {
  int buffer_len = strlen(output_buffer);
  if (buffer_len) {
    char ch = output_buffer[buffer_len - 1];
    s21_put_mul_operator(text, ch);
  }
}

void s21_check_for_x(char *text, char *output_buffer) {
  int buffer_len = strlen(output_buffer);
  if (buffer_len) {
    char ch = output_buffer[buffer_len - 1];
    s21_put_mul_operator(text, ch);
  }
}

void s21_put_mul_operator(char *text, char last) {
  if (last == 'x' || last == ')' ||
      (IS_DIGIT(last) && (text[0] == '(' || text[0] == 'x'))) {
    text[3] = text[0];
    text[0] = ' ';
    text[1] = '*';
    text[2] = ' ';
  } else if (last == '.' && !IS_DIGIT(text[0])) {
    text[4] = text[0];
    text[0] = '0';
    text[1] = ' ';
    text[2] = '*';
    text[3] = ' ';
  }
}

void s21_check_for_point(char *text, char *output_buffer) {
  int buffer_len = strlen(output_buffer);
  if (!buffer_len || output_buffer[buffer_len - 1] == ' ' || output_buffer[buffer_len - 1] == '(' ||
      output_buffer[buffer_len - 1] == '-' || output_buffer[buffer_len - 1] == '^') {
    text[0] = '0';
    text[1] = '.';
  } else {
    if (output_buffer[buffer_len - 1] != 'x') {
      while (buffer_len > 0 && IS_DIGIT(output_buffer[buffer_len - 1])) {
        buffer_len--;
      }
      if (buffer_len > 0 && output_buffer[buffer_len - 1] == '.') {
        s21_zero_text(text);
      } else if (output_buffer[buffer_len - 1] == ')') {
        text[0] = ' ';
        text[1] = '*';
        text[2] = ' ';
        text[3] = '0';
        text[4] = '.';
      }
    } else {
      s21_zero_text(text);
    }
  }
}

int s21_check_input_str(char *text, char *output_buffer) {
  char ch = text[1];
  int is_unary = 0;
  int error_code = 0;
  if (ch == '-') {
    is_unary = s21_check_for_unary(text, output_buffer);
  }
  if (!is_unary) {
    error_code = s21_simple_check_buff_for_operator(text, output_buffer);
  }
  return error_code;

}

int s21_check_for_unary(char *text, char *output_buffer) {
  int is_unary = 0;
  int buffer_len = strlen(output_buffer);
  if (buffer_len == 0 || output_buffer[buffer_len - 1] == '(') {
    text[0] = text[1];
    text[1] = 0;
    text[2] = 0;
    is_unary = 1;
  } else if (output_buffer[buffer_len - 1] == ' ' ||
            IS_OPERATOR(output_buffer[buffer_len - 1])) {
    text[0] = '(';
    text[2] = 0;
    is_unary = 1;
  }
  return is_unary;
}

void s21_check_closed_br(char *text, char *output_buffer) {
  int counter = 0;
  for (int i = 0; output_buffer[i]; i++) {
    if (output_buffer[i] == '(' || output_buffer[i] == ')') {
      counter = output_buffer[i] == '(' ? counter + 1 : counter - 1;
    }
  }
  if (counter <= 0) {
    s21_zero_text(text);
  }
}

int s21_simple_check_buff_for_operator(char *text, char *output_buffer) {
  int buffer_len = strlen(output_buffer);
  int error_code = 0;
  if (buffer_len == 0 || (!IS_DIGIT(output_buffer[buffer_len - 1]) &&
      output_buffer[buffer_len - 1] != ')' && output_buffer[buffer_len - 1] != 'x' &&
      output_buffer[buffer_len - 1] != '.')) {
    error_code = 1;
    s21_zero_text(text);
  } else if (output_buffer[buffer_len - 1] == '.') {
    int text_len = strlen(text);
    while (text_len > 0) {
      text[text_len] = text[text_len - 1];
      text_len--;
    }
    text[0] = '0';
  }
  return error_code;
}

void s21_zero_buffer(char *str) {
  for (int i = 0; i < BUFFER_SIZE; i++) {
    str[i] = 0;
  }
}

void s21_zero_text(char *text) {
  int i = strlen(text) - 1;
  while (i >= 0) {
    text[i] = 0;
    i--;
  }
}

static gboolean quit(gpointer user_data) {
  boxes_and_data *widget = user_data;
//  gtk_widget_destroy(GTK_WIDGET(widget->button[0]));
//  gtk_widget_destroy(GTK_WIDGET(widget->draw));
//  gtk_widget_destroy(GTK_WIDGET(widget->button[0]));
//  gtk_widget_destroy(GTK_WIDGET(widget->button[1]));
//  gtk_widget_destroy(GTK_WIDGET(widget->button[2]));
//  gtk_widget_destroy(GTK_WIDGET(widget->button[3]));
//  gtk_widget_destroy(GTK_WIDGET(widget->button[4]));
//  gtk_widget_destroy(GTK_WIDGET(widget->button[5]));
//  gtk_widget_destroy(GTK_WIDGET(widget->button[6]));
//  gtk_widget_destroy(GTK_WIDGET(widget->button[7]));
//  gtk_widget_destroy(GTK_WIDGET(widget->button[8]));
//  gtk_widget_destroy(GTK_WIDGET(widget->button[9]));
//  gtk_widget_destroy(GTK_WIDGET(widget->button[10]));
//  gtk_widget_destroy(GTK_WIDGET(widget->button[11]));
//  gtk_widget_destroy(GTK_WIDGET(widget->button[12]));
//  gtk_widget_destroy(GTK_WIDGET(widget->button[13]));
//  gtk_widget_destroy(GTK_WIDGET(widget->button[14]));
//  gtk_widget_destroy(GTK_WIDGET(widget->button[15]));
//  gtk_widget_destroy(GTK_WIDGET(widget->button[16]));
//  gtk_widget_destroy(GTK_WIDGET(widget->button[17]));
//  gtk_widget_destroy(GTK_WIDGET(widget->button[18]));
//  gtk_widget_destroy(GTK_WIDGET(widget->button[19]));
//  gtk_widget_destroy(GTK_WIDGET(widget->button[20]));
//  gtk_widget_destroy(GTK_WIDGET(widget->button[21]));
//  gtk_widget_destroy(GTK_WIDGET(widget->button[22]));
//  gtk_widget_destroy(GTK_WIDGET(widget->button[23]));
//  gtk_widget_destroy(GTK_WIDGET(widget->button[24]));
//  gtk_widget_destroy(GTK_WIDGET(widget->button[25]));
//  gtk_widget_destroy(GTK_WIDGET(widget->button[26]));
//  gtk_widget_destroy(GTK_WIDGET(widget->button[27]));
//  gtk_widget_destroy(GTK_WIDGET(widget->button[28]));
//  gtk_widget_destroy(GTK_WIDGET(widget->button[29]));
//  gtk_widget_destroy(GTK_WIDGET(widget->button[30]));
//  gtk_widget_destroy(GTK_WIDGET(widget->button[31]));
//  gtk_widget_destroy(GTK_WIDGET(widget->button[32]));
//  gtk_widget_destroy(GTK_WIDGET(widget->grid));
//  gtk_widget_destroy(GTK_WIDGET(widget->box));
//  gtk_widget_destroy(GTK_WIDGET(widget->box_x));
//  gtk_widget_destroy(GTK_WIDGET(widget->box_Ox1));
//  gtk_widget_destroy(GTK_WIDGET(widget->box_Ox2));
//  gtk_widget_destroy(GTK_WIDGET(widget->box_Oy1));
//  gtk_widget_destroy(GTK_WIDGET(widget->box_Oy2));
//  gtk_widget_destroy(GTK_WIDGET(widget->window));
  return FALSE;
}

static void activate(GtkApplication *app, gpointer user_data) {
  boxes_and_data *widget = user_data;
  widget->window = GTK_WIDGET(gtk_application_window_new(app));
  gtk_window_set_position(GTK_WINDOW(widget->window), GTK_WIN_POS_CENTER);
  gtk_window_set_title(GTK_WINDOW(widget->window), "KURKULATOR");
  gtk_window_set_default_size(GTK_WINDOW(widget->window), 470, 470);
  gtk_container_set_border_width(GTK_CONTAINER(widget->window), 10);

  widget->grid = gtk_grid_new();
  gtk_container_add(GTK_CONTAINER(widget->window), widget->grid);

  widget->box = gtk_entry_new();
  gtk_editable_set_editable(GTK_EDITABLE(widget->box), FALSE);
  gtk_entry_set_alignment(GTK_ENTRY(widget->box), 1.0);

  widget->box_x = gtk_entry_new();
  gtk_editable_set_editable(GTK_EDITABLE(widget->box_x), TRUE);
  gtk_entry_set_alignment(GTK_ENTRY(widget->box_x), 1.0);

  widget->box_Ox1 = gtk_entry_new();
  gtk_entry_set_text(GTK_ENTRY(widget->box_Ox1), "-10");
  gtk_editable_set_editable(GTK_EDITABLE(widget->box_Ox1), TRUE);
  gtk_entry_set_alignment(GTK_ENTRY(widget->box_Ox1), 1.0);

  widget->box_Ox2 = gtk_entry_new();
  gtk_entry_set_text(GTK_ENTRY(widget->box_Ox2), "10");
  gtk_editable_set_editable(GTK_EDITABLE(widget->box_Ox2), TRUE);
  gtk_entry_set_alignment(GTK_ENTRY(widget->box_Ox2), 1.0);

  widget->box_Oy1 = gtk_entry_new();
  gtk_entry_set_text(GTK_ENTRY(widget->box_Oy1), "-10");
  gtk_editable_set_editable(GTK_EDITABLE(widget->box_Oy1), TRUE);
  gtk_entry_set_alignment(GTK_ENTRY(widget->box_Oy1), 1.0);

  widget->box_Oy2 = gtk_entry_new();
  gtk_entry_set_text(GTK_ENTRY(widget->box_Oy2), "10");
  gtk_editable_set_editable(GTK_EDITABLE(widget->box_Oy2), TRUE);
  gtk_entry_set_alignment(GTK_ENTRY(widget->box_Oy2), 1.0);

  widget->draw = gtk_drawing_area_new();
  gtk_widget_set_size_request(widget->draw, 500, 500);
  g_signal_connect(widget->draw, "draw", G_CALLBACK(on_draw), widget);

  GtkWidget *space = gtk_label_new(NULL);
  gtk_grid_attach(GTK_GRID(widget->grid), space, 0, 7, 14, 1);
  GtkWidget *space2 = gtk_label_new(NULL);
  gtk_grid_attach(GTK_GRID(widget->grid), space2, 0, 11, 14, 1);


  GtkWidget *label = gtk_label_new("Ox");
  gtk_grid_attach(GTK_GRID(widget->grid), label, 6, 8, 1, 1);
  GtkWidget *label1 = gtk_label_new("...");
  gtk_grid_attach(GTK_GRID(widget->grid), label1, 10, 8, 1, 1);
  GtkWidget *label2 = gtk_label_new("Oy");
  gtk_grid_attach(GTK_GRID(widget->grid), label2, 6, 9, 1, 1);
  GtkWidget *label3 = gtk_label_new("...");
  gtk_grid_attach(GTK_GRID(widget->grid), label3, 10, 9, 1, 1);
  GtkWidget *label4 = gtk_label_new("         -1000000    ...    1000000");
  gtk_grid_attach(GTK_GRID(widget->grid), label4, 6, 10, 8, 1);


  widget->button[0] = gtk_button_new_with_label("0");
  widget->button[1] = gtk_button_new_with_label("1");
  widget->button[2] = gtk_button_new_with_label("2");
  widget->button[3] = gtk_button_new_with_label("3");
  widget->button[4] = gtk_button_new_with_label("4");
  widget->button[5] = gtk_button_new_with_label("5");
  widget->button[6] = gtk_button_new_with_label("6");
  widget->button[7] = gtk_button_new_with_label("7");
  widget->button[8] = gtk_button_new_with_label("8");
  widget->button[9] = gtk_button_new_with_label("9");
  widget->button[10] = gtk_button_new_with_label(".");
  widget->button[11] = gtk_button_new_with_label(" + ");
  widget->button[12] = gtk_button_new_with_label(" - ");
  widget->button[13] = gtk_button_new_with_label(" * ");
  widget->button[14] = gtk_button_new_with_label(" / ");
  widget->button[15] = gtk_button_new_with_label("C");
  widget->button[16] = gtk_button_new_with_label("=");
  widget->button[17] = gtk_button_new_with_label("<--");
  widget->button[18] = gtk_button_new_with_label("sin");
  widget->button[19] = gtk_button_new_with_label("cos");
  widget->button[20] = gtk_button_new_with_label("tan");
  widget->button[21] = gtk_button_new_with_label("acos");
  widget->button[22] = gtk_button_new_with_label("asin");
  widget->button[23] = gtk_button_new_with_label("atan");
  widget->button[24] = gtk_button_new_with_label("ln");
  widget->button[25] = gtk_button_new_with_label("sqrt");
  widget->button[26] = gtk_button_new_with_label("log");
  widget->button[27] = gtk_button_new_with_label(" mod ");
  widget->button[28] = gtk_button_new_with_label("^");
  widget->button[29] = gtk_button_new_with_label("(");
  widget->button[30] = gtk_button_new_with_label(")");
  widget->button[31] = gtk_button_new_with_label("x");
  widget->button[32] = gtk_button_new_with_label("GRAPH");

  gtk_grid_attach(GTK_GRID(widget->grid), widget->box, 0, 0, 14, 1);

  gtk_grid_attach(GTK_GRID(widget->grid), widget->button[18], 0, 1, 3, 1);
  gtk_grid_attach(GTK_GRID(widget->grid), widget->button[22], 3, 1, 3, 1);
  gtk_grid_attach(GTK_GRID(widget->grid), widget->button[15], 6, 1, 4, 1);
  gtk_grid_attach(GTK_GRID(widget->grid), widget->button[17], 10, 1, 4, 1);

  gtk_grid_attach(GTK_GRID(widget->grid), widget->button[19], 0, 2, 3, 1);
  gtk_grid_attach(GTK_GRID(widget->grid), widget->button[21], 3, 2, 3, 1);
  gtk_grid_attach(GTK_GRID(widget->grid), widget->button[29], 6, 2, 2, 1);
  gtk_grid_attach(GTK_GRID(widget->grid), widget->button[30], 8, 2, 2, 1);
  gtk_grid_attach(GTK_GRID(widget->grid), widget->button[28], 10, 2, 2, 1);
  gtk_grid_attach(GTK_GRID(widget->grid), widget->button[14], 12, 2, 2, 1);

  gtk_grid_attach(GTK_GRID(widget->grid), widget->button[20], 0, 3, 3, 1);
  gtk_grid_attach(GTK_GRID(widget->grid), widget->button[23], 3, 3, 3, 1);
  gtk_grid_attach(GTK_GRID(widget->grid), widget->button[7], 6, 3, 2, 1);
  gtk_grid_attach(GTK_GRID(widget->grid), widget->button[8], 8, 3, 2, 1);
  gtk_grid_attach(GTK_GRID(widget->grid), widget->button[9], 10, 3, 2, 1);
  gtk_grid_attach(GTK_GRID(widget->grid), widget->button[13], 12, 3, 2, 1);

  gtk_grid_attach(GTK_GRID(widget->grid), widget->button[24], 0, 4, 3, 1);
  gtk_grid_attach(GTK_GRID(widget->grid), widget->button[26], 3, 4, 3, 1);
  gtk_grid_attach(GTK_GRID(widget->grid), widget->button[4], 6, 4, 2, 1);
  gtk_grid_attach(GTK_GRID(widget->grid), widget->button[5], 8, 4, 2, 1);
  gtk_grid_attach(GTK_GRID(widget->grid), widget->button[6], 10, 4, 2, 1);
  gtk_grid_attach(GTK_GRID(widget->grid), widget->button[12], 12, 4, 2, 1);

  gtk_grid_attach(GTK_GRID(widget->grid), widget->button[25], 0, 5, 3, 1);
  gtk_grid_attach(GTK_GRID(widget->grid), widget->button[27], 3, 5, 3, 1);
  gtk_grid_attach(GTK_GRID(widget->grid), widget->button[1], 6, 5, 2, 1);
  gtk_grid_attach(GTK_GRID(widget->grid), widget->button[2], 8, 5, 2, 1);
  gtk_grid_attach(GTK_GRID(widget->grid), widget->button[3], 10, 5, 2, 1);
  gtk_grid_attach(GTK_GRID(widget->grid), widget->button[11], 12, 5, 2, 1);

  gtk_grid_attach(GTK_GRID(widget->grid), widget->button[31], 6, 6, 2, 1);
  gtk_grid_attach(GTK_GRID(widget->grid), widget->button[0], 8, 6, 2, 1);
  gtk_grid_attach(GTK_GRID(widget->grid), widget->button[10], 10, 6, 2, 1);
  gtk_grid_attach(GTK_GRID(widget->grid), widget->button[16], 12, 6, 2, 1);

  gtk_grid_attach(GTK_GRID(widget->grid), widget->box_x, 0, 6, 6, 1);

  gtk_grid_attach(GTK_GRID(widget->grid), widget->button[32], 0, 8, 3, 2);

  gtk_grid_attach(GTK_GRID(widget->grid), widget->box_Ox1, 7, 8, 3, 1);
  gtk_grid_attach(GTK_GRID(widget->grid), widget->box_Ox2, 11, 8, 3, 1);
  gtk_grid_attach(GTK_GRID(widget->grid), widget->box_Oy1, 7, 9, 3, 1);
  gtk_grid_attach(GTK_GRID(widget->grid), widget->box_Oy2, 11, 9, 3, 1);

  gtk_grid_attach(GTK_GRID(widget->grid), widget->draw, 0, 12, 14, 14);

  g_signal_connect(widget->button[0], "clicked", G_CALLBACK(calculate), widget);
  g_signal_connect(widget->button[1], "clicked", G_CALLBACK(calculate), widget);
  g_signal_connect(widget->button[2], "clicked", G_CALLBACK(calculate), widget);
  g_signal_connect(widget->button[3], "clicked", G_CALLBACK(calculate), widget);
  g_signal_connect(widget->button[4], "clicked", G_CALLBACK(calculate), widget);
  g_signal_connect(widget->button[5], "clicked", G_CALLBACK(calculate), widget);
  g_signal_connect(widget->button[6], "clicked", G_CALLBACK(calculate), widget);
  g_signal_connect(widget->button[7], "clicked", G_CALLBACK(calculate), widget);
  g_signal_connect(widget->button[8], "clicked", G_CALLBACK(calculate), widget);
  g_signal_connect(widget->button[9], "clicked", G_CALLBACK(calculate), widget);
  g_signal_connect(widget->button[10], "clicked", G_CALLBACK(calculate), widget);
  g_signal_connect(widget->button[11], "clicked", G_CALLBACK(calculate), widget);
  g_signal_connect(widget->button[12], "clicked", G_CALLBACK(calculate), widget);
  g_signal_connect(widget->button[13], "clicked", G_CALLBACK(calculate), widget);
  g_signal_connect(widget->button[14], "clicked", G_CALLBACK(calculate), widget);
  g_signal_connect(widget->button[15], "clicked", G_CALLBACK(calculate), widget);
  g_signal_connect(widget->button[16], "clicked", G_CALLBACK(calculate), widget);
  g_signal_connect(widget->button[17], "clicked", G_CALLBACK(calculate), widget);
  g_signal_connect(widget->button[18], "clicked", G_CALLBACK(calculate), widget);
  g_signal_connect(widget->button[19], "clicked", G_CALLBACK(calculate), widget);
  g_signal_connect(widget->button[20], "clicked", G_CALLBACK(calculate), widget);
  g_signal_connect(widget->button[21], "clicked", G_CALLBACK(calculate), widget);
  g_signal_connect(widget->button[22], "clicked", G_CALLBACK(calculate), widget);
  g_signal_connect(widget->button[23], "clicked", G_CALLBACK(calculate), widget);
  g_signal_connect(widget->button[24], "clicked", G_CALLBACK(calculate), widget);
  g_signal_connect(widget->button[25], "clicked", G_CALLBACK(calculate), widget);
  g_signal_connect(widget->button[26], "clicked", G_CALLBACK(calculate), widget);
  g_signal_connect(widget->button[27], "clicked", G_CALLBACK(calculate), widget);
  g_signal_connect(widget->button[28], "clicked", G_CALLBACK(calculate), widget);
  g_signal_connect(widget->button[29], "clicked", G_CALLBACK(calculate), widget);
  g_signal_connect(widget->button[30], "clicked", G_CALLBACK(calculate), widget);
  g_signal_connect(widget->button[31], "clicked", G_CALLBACK(calculate), widget);
  g_signal_connect(widget->button[32], "clicked", G_CALLBACK(calculate), widget);

//  g_signal_connect_after(widget->window, "destroy", G_CALLBACK(quit), widget);

  gtk_widget_show_all(widget->window);
}

int main(int argc, char **argv) {
  GtkApplication *app;

  boxes_and_data data;
  s21_zero_buffer(data.x_buffer);
  s21_zero_buffer(data.Ox1_buffer);
  s21_zero_buffer(data.Ox2_buffer);
  s21_zero_buffer(data.Oy1_buffer);
  s21_zero_buffer(data.Oy2_buffer);
  s21_zero_buffer(data.output_buffer);
  s21_zero_buffer(data.graph_buffer);
  strcpy(data.Ox1_buffer, "-10");
  strcpy(data.Ox2_buffer, "10");
  strcpy(data.Oy1_buffer, "-10");
  strcpy(data.Oy2_buffer, "10");
  data.Ox1 = -10.0;
  data.Ox2 = 10.0;
  data.Oy1 = -10.0;
  data.Oy2 = 10.0;
  data.x = 0.0 / 0.0;

//  gtk_init(&argc, &argv);

  app = gtk_application_new(NULL, G_APPLICATION_FLAGS_NONE);
  g_signal_connect(app, "activate", G_CALLBACK(activate), &data);
  printf("%lf\n", pow(-0.5, -0.5));
  int status = g_application_run(G_APPLICATION(app), argc, argv);

  g_object_unref(app);

  return 0;
}
