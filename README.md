# **asciiDungeon**

## 1 Descriere generală:
 asciiDungeon este un joc roguelike 2D ce presupune parcurgerea unui nivel generat întamplător, unde jucătorul este nevoit să îsî folosească echipamentul găsit ca să învingă monștrii ce îi ies in cale. 
 Aspectul este unul foarte simplist, elementele jocului mai puțin pereții și podeaua sunt reprezentate de simboluri de la tastatură. (Ex: un orc arată ca un 'o' de culoarea verde)

## 2 Funcționalitate:
### 2.1 Despre cum se joacă
 Mișcarea se realizează folosind săgețile de la tastatură, (Acest lucru o să fie înlocuit cu butoanele de pe numpad pentru a creea posibilitatea jucătorului de a se deplasa și pe diagonală, urmează sa fie adăugate si comenzi pentru a accesa inventarul) 
### 2.2 Despre structura jocului
 Inițial asciiDungeon a fost conceput in C. Dupa o serie de dificultăți legate de organizarea programului și de faptul că un proiect de acest gen necesită multe obiecte care lucrează împreuna am decis să folosesc C++. Tranziția nu a fost dificilă avand in vedere ca librariile (libtcod și SDL2) au rămas compatibile. Structura jocului nu este foarte complexă, componentele principale sunt:
- Engine
- Map
- Actor
  - Destructible
  - AI
  - Attacker
- BspListener

#### Engine:
După cum spune și numele, aceasta este motorul jocului. Prin Engine se apeleaza functiile update() si render(). Tot ce se intamplă în program ajunge intr-un final aici pentru a concretiza schimbările făcute in timpul jocului (mișcare, moartea unui inamic sau a jucătorului).
#### Map:

#### Actor:

#### BspListener:


## 3 Probleme cunoscute:
 Pentru a rezolva un bug în care inamicii atacau jucătorul de la orice distanță căt timp erau in cămpul vizual am implementat o soluție în care inamicul are voie sa attace doar atunci cand jucătorul este lănga acesta. Acest lucru a scos la iveala o nouă problemă în care aceștia nu iși urmăresc ținta niciodată ci aleg să stea pe loc indefinitiv. În urma unor teste am observat că in anumite situații acestia aleg sa urmărească jucătorul dar încă nu cunosc condițiile declanșatoare.
