#include <curses.h>
#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void timpul(WINDOW *data_si_legenda_win, int punctaj) {
  // functie in care afisam timpul in fereasta
  // jocului dar in care avem si punctajul,
  // pentru a apela o singura functi pentru
  // a regenera ambele valori
  time_t timp;
  time(&timp);
  char *timp_sir = ctime(&timp);
  char timp_de_afisat[30];
  strcpy(timp_de_afisat, timp_sir);
  wattron(data_si_legenda_win, COLOR_PAIR(13));
  mvwprintw(data_si_legenda_win, 0, 0, "Timp si data : %s", timp_de_afisat);
  wattroff(data_si_legenda_win, COLOR_PAIR(13));
  wattron(data_si_legenda_win, COLOR_PAIR(16) | A_BOLD);
  mvwprintw(data_si_legenda_win, 9, 25, "Punctaj : %d", punctaj);
  wattroff(data_si_legenda_win, COLOR_PAIR(16) | A_BOLD);
  refresh();
  wrefresh(data_si_legenda_win);
}

int decizie_key_left(int matrice[4][4]) {
  // verificam daca autopilotul poate folosi tasta stanga
  // ca input valid
  int i, j, e_bun = 0;
  for (i = 0; i < 4; i++)
    for (j = 1; j < 4; j++)
      if ((matrice[i][j - 1] == matrice[i][j] && matrice[i][j] != 0) ||
          (matrice[i][j] != 0 && matrice[i][j - 1] == 0 && j >= 1))
        e_bun = 1;
  return e_bun;
}

int decizie_key_right(int matrice[4][4]) {
  // verificam daca autopilotul poate folosi tasta dreapta
  // ca input valid
  int i, j, e_bun = 0;
  for (i = 0; i < 4; i++)
    for (j = 2; j >= 0; j--)
      if ((matrice[i][j] == matrice[i][j + 1] && matrice[i][j + 1] != 0) ||
          (matrice[i][j] != 0 && matrice[i][j + 1] == 0 && j <= 2))
        e_bun = 1;
  return e_bun;
}

int decizie_key_up(int matrice[4][4]) {
  // verificam daca autopilotul poate folosi tasta sus
  // ca input valid
  int i, j, e_bun = 0;
  for (i = 0; i < 4; i++)
    for (j = 1; j < 4; j++)
      if ((matrice[j - 1][i] == matrice[j][i] && matrice[j][i] != 0) ||
          (matrice[j][i] != 0 && matrice[j - 1][i] == 0 && j >= 1))
        e_bun = 1;
  return e_bun;
}

int decizie_key_down(int matrice[4][4]) {
  // verificam daca autopilotul poate folosi tasta jos
  // ca input valid
  int i, j, e_bun = 0;
  for (i = 0; i < 4; i++)
    for (j = 2; j >= 0; j--)
      if ((matrice[j][i] == matrice[j + 1][i] && matrice[j + 1][i] != 0) ||
          (matrice[j][i] != 0 && matrice[j + 1][i] == 0 && j <= 2))
        e_bun = 1;
  return e_bun;
}

void update_matrice(int y_initial, int x_initial, WINDOW *vector_de_ecrane[],
                    WINDOW *gamewin, int matrice[4][4]) {
  // afisam pe ecram modificarile create in functia de engine_joc
  // pe ecram si coloram fiecare celula astfel incat sa fie distinctiva
  int i, j, k = 0, y, x;
  getmaxyx(vector_de_ecrane[0], y, x);
  for (i = 0; i < 4; i++) {
    for (j = 0; j < 4; j++) {
      wbkgd(vector_de_ecrane[k], COLOR_PAIR(12));
      if (matrice[i][j] != 0) {
        switch (matrice[i][j]) {
          case 2:
            wbkgd(vector_de_ecrane[k], COLOR_PAIR(1));
            break;
          case 4:
            wbkgd(vector_de_ecrane[k], COLOR_PAIR(2));
            break;
          case 8:
            wbkgd(vector_de_ecrane[k], COLOR_PAIR(3));
            break;
          case 16:
            wbkgd(vector_de_ecrane[k], COLOR_PAIR(4));
            break;
          case 32:
            wbkgd(vector_de_ecrane[k], COLOR_PAIR(5));
            break;
          case 64:
            wbkgd(vector_de_ecrane[k], COLOR_PAIR(6));
            break;
          case 128:
            wbkgd(vector_de_ecrane[k], COLOR_PAIR(7));
            break;
          case 256:
            wbkgd(vector_de_ecrane[k], COLOR_PAIR(8));
            break;
          case 512:
            wbkgd(vector_de_ecrane[k], COLOR_PAIR(9));
            break;
          case 1024:
            wbkgd(vector_de_ecrane[k], COLOR_PAIR(10));
            break;
          case 2048:
            wbkgd(vector_de_ecrane[k], COLOR_PAIR(11));
            break;
          default:
            break;
        }
        mvwprintw(vector_de_ecrane[k], (y / 2) - 1, x / 2, "      ");
        mvwprintw(vector_de_ecrane[k], (y / 2) - 1, x / 2, "%d", matrice[i][j]);
      }
      wrefresh(vector_de_ecrane[k]);
      wrefresh(gamewin);
      k++;
    }
  }
}

void generare_random(int matrice[4][4]) {
  // generam random valori pentru coordonatele
  // din matrice pentru a alege o casura neocupata,
  // si generam restul lui 2 pentru a gera astfel una din valorile
  // 2 sau 4, algoritmul de a ajjunge la 2,4 fiind vizibil mai jos
  int nr_random, pozitie_1, pozitie_2;
  srand(time(NULL));
  nr_random = (rand() % 2) + 1;
  pozitie_1 = rand() % 4;
  pozitie_2 = rand() % 4;
  while (matrice[pozitie_1][pozitie_2]) {
    pozitie_1 = rand() % 4;
    pozitie_2 = rand() % 4;
  }
  matrice[pozitie_1][pozitie_2] = nr_random * 2;
}

int testare_matrice(int matrice[4][4]) {
  // verificam daca am pierdut jocul, daca am ajuns la punctaj
  // maxim/castigator sau daca acestea nu s au indeplinit,
  // verificam daca mai avem miscari posibile la indemana
  int i, j, miscare_valabila = 0;
  int exit = 0, exista_0 = 0;
  for (i = 0; i < 4; i++) {
    for (j = 0; j < 4; j++) {
      if (matrice[i][j] == 0) exista_0 = 1;
      if (matrice[i][j] == 2048) exit = 1;
      if ((matrice[i][j] == matrice[i][j + 1] && j + 1 <= 3) ||
          (matrice[i][j] == matrice[i + 1][j] && i + 1 <= 3))
        miscare_valabila = 1;
    }
  }
  if (exit == 1) return 1;
  if (exista_0 == 0 && miscare_valabila == 0) return -1;
  return 0;
}

int engine_joc(int matrice[4][4], int c, int *punctaj) {
  // verificam, ce input am primit, si in functie de acesta,
  // ii comunicam programului in ce directie trebuiesc facute miscarile
  // (axa si directia axei)
  int i, j, k, miscare_valabila = 0;
  int exit = 0, exista_0 = 0;
  if (c == KEY_LEFT)
    for (i = 0; i < 4; i++) {
      for (j = 1; j < 4; j++) {
        k = j;
        while (matrice[i][k] != 0 && matrice[i][k - 1] == 0 && k >= 1) {
          matrice[i][k - 1] = matrice[i][k];
          matrice[i][k] = 0;
          k--;
          miscare_valabila = 1;
        }
      }
      for (j = 1; j < 4; j++) {
        if (matrice[i][j - 1] == matrice[i][j] && matrice[i][j] != 0) {
          matrice[i][j - 1] *= 2;
          *punctaj += matrice[i][j - 1];
          matrice[i][j] = 0;
          miscare_valabila = 1;
        }
      }
      for (j = 1; j < 4; j++) {
        k = j;
        while (matrice[i][k] != 0 && matrice[i][k - 1] == 0 && k >= 1) {
          matrice[i][k - 1] = matrice[i][k];
          matrice[i][k] = 0;
          k--;
        }
      }
    }
  if (c == KEY_RIGHT)
    for (i = 0; i < 4; i++) {
      for (j = 2; j >= 0; j--) {
        k = j;
        while (matrice[i][k] != 0 && matrice[i][k + 1] == 0 && k <= 2) {
          matrice[i][k + 1] = matrice[i][k];
          matrice[i][k] = 0;
          k++;
          miscare_valabila = 1;
        }
      }
      for (j = 2; j >= 0; j--) {
        if (matrice[i][j] == matrice[i][j + 1] && matrice[i][j + 1] != 0) {
          matrice[i][j + 1] *= 2;
          *punctaj += matrice[i][j + 1];
          matrice[i][j] = 0;
          miscare_valabila = 1;
        }
      }
      for (j = 2; j >= 0; j--) {
        k = j;
        while (matrice[i][k] != 0 && matrice[i][k + 1] == 0 && k <= 2) {
          matrice[i][k + 1] = matrice[i][k];
          matrice[i][k] = 0;
          k++;
        }
      }
    }
  if (c == KEY_UP)
    for (i = 0; i < 4; i++) {
      for (j = 1; j < 4; j++) {
        k = j;
        while (matrice[k][i] != 0 && matrice[k - 1][i] == 0 && k >= 1) {
          matrice[k - 1][i] = matrice[k][i];
          matrice[k][i] = 0;
          k--;
          miscare_valabila = 1;
        }
      }
      for (j = 1; j < 4; j++) {
        if (matrice[j - 1][i] == matrice[j][i] && matrice[j][i] != 0) {
          matrice[j - 1][i] *= 2;
          *punctaj += matrice[j - 1][i];
          matrice[j][i] = 0;
          miscare_valabila = 1;
        }
      }
      for (j = 1; j < 4; j++) {
        k = j;
        while (matrice[k][i] != 0 && matrice[k - 1][i] == 0 && k >= 1) {
          matrice[k - 1][i] = matrice[k][i];
          matrice[k][i] = 0;
          k--;
        }
      }
    }
  if (c == KEY_DOWN)
    for (i = 0; i < 4; i++) {
      for (j = 2; j >= 0; j--) {
        k = j;
        while (matrice[k][i] != 0 && matrice[k + 1][i] == 0 && k <= 2) {
          matrice[k + 1][i] = matrice[k][i];
          matrice[k][i] = 0;
          k++;
          miscare_valabila = 1;
        }
      }
      for (j = 2; j >= 0; j--) {
        if (matrice[j][i] == matrice[j + 1][i] && matrice[j + 1][i] != 0) {
          matrice[j + 1][i] *= 2;
          *punctaj += matrice[j + 1][i];
          matrice[j][i] = 0;
          miscare_valabila = 1;
        }
      }
      for (j = 1; j < 4; j++) {
        k = j;
        while (matrice[k][i] != 0 && matrice[k + 1][i] == 0 && k <= 2) {
          matrice[k + 1][i] = matrice[k][i];
          matrice[k][i] = 0;
          k++;
        }
      }
    }
  // daca am dar input o miscare valabila, generam in tabla un numar
  if (miscare_valabila == 1) generare_random(matrice);
  //   refacem o verificare ca in functia testare_matrice
  for (i = 0; i < 4; i++) {
    for (j = 0; j < 4; j++) {
      if (matrice[i][j] == 0) exista_0 = 1;
      if (matrice[i][j] == 2048) exit = 1;
    }
  }
  for (i = 0; i < 4; i++) {
    for (j = 0; j < 4; j++) {
      if ((matrice[i][j] == matrice[i][j + 1] && j + 1 <= 3) ||
          (matrice[i][j] == matrice[i + 1][j] && i + 1 <= 3))
        miscare_valabila = 1;
    }
  }
  if (exit == 1) return 1;
  if (exista_0 == 0 && miscare_valabila == 0) return -1;
  miscare_valabila = 0;
  return 0;
}

void joc_nou() {
  // incepem un joc nou
  // initializam toate culorile necesare pentru colorarea
  // tuturor elementelor ce le vom folosi pe parcurs
  clear();
  //   folosim o matrice in care salvam valorile celulelor
  // 	ce care le vom afisa
  int matrice[4][4] = {0};
  int y_final, x_final, y_initial, x_initial;
  int punctaj = 0;
  int y, x, c;
  int i, j, k = 0;
  getmaxyx(stdscr, y_final, x_final);
  getbegyx(stdscr, y_initial, x_initial);
  start_color();
  init_pair(1, COLOR_YELLOW, COLOR_RED);
  init_pair(2, COLOR_BLACK, COLOR_GREEN);
  init_pair(3, COLOR_RED, COLOR_YELLOW);
  init_pair(4, COLOR_BLACK, COLOR_BLUE);
  init_pair(5, COLOR_BLACK, COLOR_MAGENTA);
  init_pair(6, COLOR_WHITE, COLOR_CYAN);
  init_pair(7, COLOR_WHITE, COLOR_BLACK);
  init_pair(8, COLOR_RED, COLOR_YELLOW);
  init_pair(9, COLOR_RED, COLOR_BLUE);
  init_pair(10, COLOR_RED, COLOR_MAGENTA);
  init_pair(11, COLOR_RED, COLOR_BLACK);
  init_pair(12, COLOR_WHITE, COLOR_WHITE);
  init_pair(13, COLOR_WHITE, COLOR_BLUE);
  init_pair(14, COLOR_BLACK, COLOR_YELLOW);
  init_pair(15, COLOR_WHITE, COLOR_WHITE);
  init_pair(16, COLOR_WHITE, COLOR_RED);
  //   initializam fereastra jocului mare
  // si fereastra datelor si legendei
  WINDOW *gamewin = newwin(y_final, x_final, y_initial, x_initial);
  WINDOW *data_si_legenda_win = newwin(10, 40, y_initial + 2, x_initial + 2);
  //   functia sare peste inputul userului daca acesta este inexistent
  // pentru a ma ajuta sa mentin constant timpul curent in fereastra
  nodelay(data_si_legenda_win, TRUE);
  nodelay(gamewin, TRUE);
  keypad(gamewin, true);
  keypad(data_si_legenda_win, true);
  wattron(gamewin, COLOR_PAIR(14));
  box(gamewin, 64, 64);
  wattroff(gamewin, COLOR_PAIR(14));
  refresh();
  wrefresh(gamewin);
  timpul(data_si_legenda_win, punctaj);
  wrefresh(gamewin);
  wattron(data_si_legenda_win, COLOR_PAIR(13));
  mvwprintw(data_si_legenda_win, 2, 0,
            "Legenda:\nLEFT ARRW - move left\nRIGHT ARRW - move right\nDOWN "
            "ARRW - move down\nUP ARRW - move up\n'q' - QUIT TO MENU");
  wattroff(data_si_legenda_win, COLOR_PAIR(13));
  refresh();
  wrefresh(data_si_legenda_win);
  wrefresh(gamewin);
  //   folosim 16 ferestre ce reprezinta matricea noastra pentru a da jocului
  // un aspect placut
  // initializez tabla de joc pe care vor fi generate ulterior valorile
  WINDOW *vector_de_ecrane[16];
  for (i = y_initial + 11; i < y_initial + 27; i = i + 5) {
    for (j = x_initial + 55; j < x_initial + 86; j = j + 10) {
      vector_de_ecrane[k] = newwin(4, 8, i, j);
      keypad(vector_de_ecrane[k], true);
      k++;
    }
  }
  k = 0;
  for (i = 0; i < 16; i++) {
    wbkgd(vector_de_ecrane[k], COLOR_PAIR(15));
    wrefresh(vector_de_ecrane[k]);
    wrefresh(gamewin);
    napms(10);
    k++;
  }
  //   generam numerele de inceput
  generare_random(matrice);
  generare_random(matrice);

  getmaxyx(vector_de_ecrane[0], y, x);
  k = 0;
  for (i = 0; i < 4; i++) {
    for (j = 0; j < 4; j++) {
      wbkgd(vector_de_ecrane[k], COLOR_PAIR(15));
      if (matrice[i][j] != 0) {
        if (matrice[i][j] == 2)
          wbkgd(vector_de_ecrane[k], COLOR_PAIR(1));
        else
          wbkgd(vector_de_ecrane[k], COLOR_PAIR(2));
        mvwprintw(vector_de_ecrane[k], (y / 2) - 1, x / 2, "%d", matrice[i][j]);
      }
      wrefresh(vector_de_ecrane[k]);
      wrefresh(gamewin);
      k++;
    }
  }
  keypad(gamewin, true);
  time_t timp1, timp2 = time(NULL);
  while (1) {
    timp1 = time(NULL);
    c = wgetch(gamewin);
    if (difftime(timp1, timp2) > 10 && timp2 != -2) {
      if (decizie_key_left(matrice))
        c = KEY_LEFT;
      else {
        if (decizie_key_right(matrice))
          c = KEY_RIGHT;
        else {
          if (decizie_key_up(matrice))
            c = KEY_UP;
          else {
            if (decizie_key_down(matrice)) c = KEY_DOWN;
          }
        }
      }
    }
    timpul(data_si_legenda_win, punctaj);
    wrefresh(gamewin);
    if (c == 'q') {
      // salvez in fisier matricea pentru a ma putea intoarce la ea
      FILE *pointer_fisier = fopen("matrice.txt", "w");
      for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
          fprintf(pointer_fisier, "%d ", matrice[i][j]);
        }
        fprintf(pointer_fisier, "\n");
      }
      fprintf(pointer_fisier, "%d", punctaj);
      fclose(pointer_fisier);
      break;
    }
    if (c == KEY_UP || c == KEY_DOWN || c == KEY_LEFT || c == KEY_RIGHT) {
      // salvez momentul in care s a apasat ultima data o tasta de catre
      // user pentru a da functionalitate autopilotului
      timp2 = time(NULL);
      engine_joc(matrice, c, &punctaj);
      update_matrice(y_initial, x_initial, vector_de_ecrane, gamewin, matrice);
      //   afisez mesaje aferente momentului in care se afla userul
      if (testare_matrice(matrice) == 1) {
        wattron(gamewin, COLOR_PAIR(2) | A_BOLD);
        mvwprintw(gamewin, y_initial + 32, x_initial + 66, "WINNER!");
        wattroff(gamewin, COLOR_PAIR(2) | A_BOLD);
        break;
      } else {
        if (testare_matrice(matrice) == -1) {
          wattron(gamewin, COLOR_PAIR(1) | A_BOLD);
          mvwprintw(gamewin, y_initial + 32, x_initial + 69, "GAME LOST!");
          wattroff(gamewin, COLOR_PAIR(1) | A_BOLD);
          break;
        }
      }
      timpul(data_si_legenda_win, punctaj);
    }
  }
  //   dca jocul s a terminat, folosesc bucla
  //  pentru a inregistra ca input doar tasta q, alta
  // optiune ne fiind valabila
  if (c == KEY_UP || c == KEY_DOWN || c == KEY_LEFT || c == KEY_RIGHT) {
    while (1) {
      c = wgetch(gamewin);
      timpul(data_si_legenda_win, punctaj);
      wrefresh(gamewin);

      if (c == 'q') {
        FILE *pointer_fisier = fopen("matrice.txt", "w");
        for (i = 0; i < 4; i++) {
          for (j = 0; j < 4; j++) {
            fprintf(pointer_fisier, "%d ", matrice[i][j]);
          }
          fprintf(pointer_fisier, "\n");
        }
        fprintf(pointer_fisier, "%d", punctaj);
        fclose(pointer_fisier);

        break;
      }
    }
  }
  //   rescriu in fisier matricea pentru a o putea
  // reaccesa ulterior
  FILE *pointer_fisier = fopen("matrice.txt", "w");
  for (i = 0; i < 4; i++) {
    for (j = 0; j < 4; j++) {
      fprintf(pointer_fisier, "%d ", matrice[i][j]);
    }
    fprintf(pointer_fisier, "\n");
  }
  fprintf(pointer_fisier, "%d", punctaj);
  fclose(pointer_fisier);

  delwin(gamewin);
  clear();
}

void resume() {
  // functia resume, functioneaza exact ca si
  // functia joc_nou, doar ca nu initializeaza
  // tabla de joc
  clear();
  int y_final, x_final, y_initial, x_initial;
  int matrice[4][4] = {0};
  int punctaj = 0;
  int k = 0, c;
  int i, j;
  time_t timp1, timp2 = -2;
  FILE *pointer_fisier = fopen("matrice.txt", "r");
  for (i = 0; i < 4; i++) {
    for (j = 0; j < 4; j++) {
      fscanf(pointer_fisier, "%d", &matrice[i][j]);
    }
  }
  fscanf(pointer_fisier, "%d", &punctaj);
  fclose(pointer_fisier);
  getmaxyx(stdscr, y_final, x_final);
  getbegyx(stdscr, y_initial, x_initial);
  start_color();
  init_pair(1, COLOR_YELLOW, COLOR_RED);
  init_pair(2, COLOR_BLACK, COLOR_GREEN);
  init_pair(3, COLOR_RED, COLOR_YELLOW);
  init_pair(4, COLOR_BLACK, COLOR_BLUE);
  init_pair(5, COLOR_BLACK, COLOR_MAGENTA);
  init_pair(6, COLOR_WHITE, COLOR_CYAN);
  init_pair(7, COLOR_WHITE, COLOR_BLACK);
  init_pair(8, COLOR_RED, COLOR_YELLOW);
  init_pair(9, COLOR_RED, COLOR_BLUE);
  init_pair(10, COLOR_RED, COLOR_MAGENTA);
  init_pair(11, COLOR_RED, COLOR_BLACK);
  init_pair(12, COLOR_WHITE, COLOR_WHITE);
  init_pair(13, COLOR_WHITE, COLOR_BLUE);
  init_pair(14, COLOR_BLACK, COLOR_YELLOW);
  init_pair(15, COLOR_WHITE, COLOR_WHITE);
  init_pair(16, COLOR_WHITE, COLOR_RED);
  WINDOW *gamewin = newwin(y_final, x_final, y_initial, x_initial);
  WINDOW *data_si_legenda_win = newwin(10, 40, y_initial + 2, x_initial + 2);
  nodelay(data_si_legenda_win, TRUE);
  nodelay(gamewin, TRUE);
  keypad(gamewin, true);
  keypad(data_si_legenda_win, true);
  wattron(gamewin, COLOR_PAIR(14));
  box(gamewin, 64, 64);
  wattroff(gamewin, COLOR_PAIR(14));
  refresh();
  wrefresh(gamewin);
  timpul(data_si_legenda_win, punctaj);
  wrefresh(gamewin);
  wattron(data_si_legenda_win, COLOR_PAIR(13));
  mvwprintw(data_si_legenda_win, 2, 0,
            "Legenda:\nLEFT ARRW - move left\nRIGHT ARRW - move right\nDOWN "
            "ARRW - move down\nUP ARRW - move up\n'q' - QUIT TO MENU");
  wattroff(data_si_legenda_win, COLOR_PAIR(13));
  refresh();
  wrefresh(data_si_legenda_win);
  wrefresh(gamewin);
  WINDOW *vector_de_ecrane[16];
  for (i = y_initial + 11; i < y_initial + 27; i = i + 5) {
    for (j = x_initial + 55; j < x_initial + 86; j = j + 10) {
      vector_de_ecrane[k] = newwin(4, 8, i, j);
      keypad(vector_de_ecrane[k], true);
      k++;
    }
  }
  update_matrice(y_initial, x_initial, vector_de_ecrane, gamewin, matrice);
  wrefresh(gamewin);
  keypad(gamewin, true);
  if (testare_matrice(matrice) == 1) {
    wattron(gamewin, COLOR_PAIR(2) | A_BOLD);
    mvwprintw(gamewin, y_initial + 32, x_initial + 66, "WINNER!");
    wattroff(gamewin, COLOR_PAIR(2) | A_BOLD);
  } else {
    if (testare_matrice(matrice) == -1) {
      wattron(gamewin, COLOR_PAIR(1) | A_BOLD);
      mvwprintw(gamewin, y_initial + 32, x_initial + 69, "GAME LOST!");
      wattroff(gamewin, COLOR_PAIR(1) | A_BOLD);
    }
  }
  while (1) {
    timp1 = time(NULL);
    c = wgetch(gamewin);
    if (difftime(timp1, timp2) > 3 && timp2 != -2) {
      if (decizie_key_left(matrice))
        c = KEY_LEFT;
      else {
        if (decizie_key_right(matrice))
          c = KEY_RIGHT;
        else {
          if (decizie_key_up(matrice))
            c = KEY_UP;
          else {
            if (decizie_key_down(matrice)) c = KEY_DOWN;
          }
        }
      }
    }
    timpul(data_si_legenda_win, punctaj);
    wrefresh(gamewin);
    if (c == 'q') {
      FILE *pointer_fisier = fopen("matrice.txt", "w");
      for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
          fprintf(pointer_fisier, "%d ", matrice[i][j]);
        }
        fprintf(pointer_fisier, "\n");
      }
      fprintf(pointer_fisier, "%d", punctaj);
      fclose(pointer_fisier);
      break;
    }
    if (c == KEY_UP || c == KEY_DOWN || c == KEY_LEFT || c == KEY_RIGHT) {
      timp2 = time(NULL);
      engine_joc(matrice, c, &punctaj);
      update_matrice(y_initial, x_initial, vector_de_ecrane, gamewin, matrice);
      if (testare_matrice(matrice) == 1) {
        wattron(gamewin, COLOR_PAIR(2) | A_BOLD);
        mvwprintw(gamewin, y_initial + 32, x_initial + 66, "WINNER!");
        wattroff(gamewin, COLOR_PAIR(2) | A_BOLD);
        break;
      } else {
        if (testare_matrice(matrice) == -1) {
          wattron(gamewin, COLOR_PAIR(1) | A_BOLD);
          mvwprintw(gamewin, y_initial + 32, x_initial + 69, "GAME LOST!");
          wattroff(gamewin, COLOR_PAIR(1) | A_BOLD);
          break;
        }
      }
      timpul(data_si_legenda_win, punctaj);
    }
  }
  if (c == KEY_UP || c == KEY_DOWN || c == KEY_LEFT || c == KEY_RIGHT) {
    while (1) {
      c = wgetch(gamewin);
      timpul(data_si_legenda_win, punctaj);
      wrefresh(gamewin);

      if (c == 'q') {
        FILE *pointer_fisier = fopen("matrice.txt", "w");
        for (i = 0; i < 4; i++) {
          for (j = 0; j < 4; j++) {
            fprintf(pointer_fisier, "%d ", matrice[i][j]);
          }
          fprintf(pointer_fisier, "\n");
        }
        fprintf(pointer_fisier, "%d", punctaj);
        fclose(pointer_fisier);
        break;
      }
    }
  }
  FILE *pointer_fisier_2 = fopen("matrice.txt", "w");
  for (i = 0; i < 4; i++) {
    for (j = 0; j < 4; j++) {
      fprintf(pointer_fisier_2, "%d ", matrice[i][j]);
    }
    fprintf(pointer_fisier_2, "\n");
  }
  fprintf(pointer_fisier, "%d", punctaj);
  fclose(pointer_fisier_2);
  delwin(gamewin);
  clear();
}
void meniu() {
  // initializez fereastra meniunui in care colorez fundalul
  // ecranului standard pentru a iesi in evidenta box ul si
  //  fereastra creata pentru optiunile de meniu
  int y_final, x_final, i;
  char alegeri_de_meniu[3][20] = {"New Game", "Resume", "Quit"};
  int ales;
  int numar;
  int selectat = 0;
  getmaxyx(stdscr, y_final, x_final);
  start_color();
  init_pair(1, COLOR_YELLOW, COLOR_RED);
  init_pair(2, COLOR_RED, COLOR_RED);
  init_pair(3, COLOR_CYAN, COLOR_CYAN);
  init_pair(4, COLOR_WHITE, COLOR_BLACK);
  init_pair(5, COLOR_BLACK, COLOR_WHITE);
  init_color(COLOR_CYAN, 300, 300, 300);
  WINDOW *menuwin = newwin(10, 20, y_final / 2 - 5, (x_final) / 2 - 10);
  bkgd(COLOR_PAIR(3));
  refresh();
  wbkgd(menuwin, COLOR_PAIR(4));
  wrefresh(menuwin);
  wattron(menuwin, COLOR_PAIR(2));
  box(menuwin, 0, 0);
  wattroff(menuwin, COLOR_PAIR(2));
  refresh();
  wrefresh(menuwin);
  keypad(menuwin, true);
  curs_set(0);
  while (1) {
    for (i = 0; i < 3; i++) {
      wattron(menuwin, COLOR_PAIR(5));
      //   daca suntem cu selectia pe o anumita optiune, ii schimbam culoarea
      // pentru a iesi in evidenta
      if (i == selectat) wattron(menuwin, A_BOLD | COLOR_PAIR(1));
      //   centrz optiunile de meniu ca sa fie in mijlocul ferestrei create
      // si la dau coluri de fundal initiale;
      mvwprintw(menuwin, (10 - 3) / 2 + i,
                (20 - strlen(alegeri_de_meniu[i])) / 2, alegeri_de_meniu[i]);
      wattroff(menuwin, A_BOLD | COLOR_PAIR(1));
      wattroff(menuwin, COLOR_PAIR(5));
    }
    ales = wgetch(menuwin);
    // decid pe ce optiune ma aflu verificand ce tasta am apasat
    switch (ales) {
      case KEY_UP:
        if (selectat == 0)
          selectat = 2;
        else
          selectat--;
        break;
      case KEY_DOWN:
        if (selectat == 2)
          selectat = 0;
        else
          selectat++;
        break;
      default:
        break;
    }
    // daca se apasa enter
    if (ales == 10) {
      if (selectat == 2) {
        // pentru optiunea de quit, am grija sa eliberez fisierul in
        // care salvez pentru al opri sa nu fie persistent, ulterior
        // folosind acest lucru pentru a face butonul de resume
        // accesibil doar daca am dat new game dupa pornirea jocului
        system("clear");
        FILE *pointer_fisier = fopen("matrice.txt", "w");
        fprintf(pointer_fisier, "%d", -1);
        fclose(pointer_fisier);
        clear();
        break;
      } else {
        if (selectat == 1) {
          // daca apasam resume, citim matricea antecedent jucata
          FILE *pointer_fisier = fopen("matrice.txt", "r");
          fscanf(pointer_fisier, "%d", &numar);
          fclose(pointer_fisier);
          //   verificam daca in fisier exista o matrice jucata
          // anterior, sau pe scurt daca abia am pornit jocul
          if (numar != -1) {
            resume();
          }
          delwin(menuwin);
          meniu();
          clear();

          break;
        } else {
          // accesam new game
          if (selectat == 0) {
            delwin(menuwin);
            joc_nou();
            meniu();
            clear();
            break;
          }
        }
      }
    }
  }
  init_color(COLOR_BLACK, 0, 0, 0);
  bkgd(0);
}

int main() {
  // initializez ecranul in libraria ncurses
  initscr();
  // nu afisez in terminal inputul de la tastatura
  noecho();
  // pot sa accesez imputul caracter cu caracter pentru functiile getch sau
  // wgetch
  cbreak();
  // intru in fereasta de meniu de unde continua intreb jocul
  meniu();
  // inchid fereastra deschisa anterior
  endwin();
  return 0;
}
