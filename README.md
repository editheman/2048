# 2048 in C

## Durata implementării: aproximativ 4 zile de lucru.

## Explicarea jocului:

În cadrul funcției principale, gestionăm mai multe aspecte ale jocului. În primul rând, avem o funcție dedicată afișării timpului și punctajului în fereastra jocului. Aceasta actualizează valorile și reînnoiește informațiile necesare într-o singură apelare.

Apoi, efectuăm verificări pentru a determina dacă autopilotul poate folosi tastele săgeți (stânga, dreapta, sus sau jos) ca inputuri valide. Aceste verificări sunt esențiale pentru buna funcționare a autopilotului.

Modificările generate de funcția engine_joc sunt afișate pe ecran, aplicând o colorare distinctivă pentru fiecare celulă din matrice. Astfel, se facilitează alegerea unei celule neocupate. De asemenea, valorile 2 sau 4 sunt generate în spațiile disponibile, conform unui algoritm specific.

În continuare, verificăm diverse condiții, precum pierderea jocului, atingerea punctajului maxim sau câștigarea jocului. Evaluarea acestor situații este esențială pentru a asigura o experiență de joc coerentă și captivantă.

Următoarea etapă constă în evaluarea inputului primit și comunicarea programului în privința direcției mișcărilor. Se verifică dacă inputul este valid, iar dacă este, se generează un număr pe tabla de joc, folosind o verificare similară cu cea din funcția testare_matrice.

Un joc nou începe prin inițializarea culorilor necesare pentru elementele jocului și utilizarea unei matrice pentru a salva valorile celulelor afișate. Fereastra pentru joc, date și legendă este alocată pentru a oferi o structură clară și organizată.

Matricea este salvată într-un fișier pentru a putea fi reluată ulterior, iar momentul ultimei apăsări de taste este reținut, oferind funcționalitate autopilotului. Mesajele afișate variază în funcție de stadiul jocului, iar în cazul încheierii acestuia, utilizatorul este restricționat la inputul tastelor "Q".

Funcția de resume funcționează similar cu cea de joc nou, cu excepția faptului că nu inițializează tabla de joc. Se fac inițializările necesare pentru fereastra de meniu, stabilind culorile și centrand opțiunile pentru un aspect plăcut și ordonat.

Opțiunile sunt selectate în funcție de tasta apăsată. În cazul opțiunii Quit, ne asigurăm că fișierul de salvare este eliberat, evitând persistența datelor. Pentru opțiunea Resume, citim matricea anterioară jucată, verificând existența ei în fișier, după care accesăm funcția de joc nou.

În final, inițializăm ecranul folosind ncurses și gestionăm inputul de la tastatură, asigurându-ne că acesta nu este afișat în terminal. Putem accesa inputul caracter cu caracter sau intra în fereastra de meniu, continuând astfel interacțiunea cu jocul. Închidem fereastra deschisă anterior pentru a menține un flux ordonat al acțiunilor.