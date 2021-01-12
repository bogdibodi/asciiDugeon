# **asciiDungeon**

## 1 Descriere generală:
 asciiDungeon este un joc roguelike 2D ce presupune parcurgerea unui nivel generat întamplător, unde jucătorul este nevoit să îsî folosească echipamentul găsit ca să învingă monștrii ce îi ies in cale. 
 Aspectul este unul foarte simplist, elementele jocului mai puțin pereții și podeaua sunt reprezentate de simboluri de la tastatură. (Ex: un orc arată ca un 'o' de culoarea verde)

## 2 Funcționalitate:
### 2.1 Despre cum se joacă
 Mișcarea se controleaza după săgețile de la tastarură sau numpad. Inventarul se deschide cu 'i' si scările se coboară cu 's'.
### 2.2 Despre structura jocului
 Inițial asciiDungeon a fost conceput in C. Dupa o serie de dificultăți legate de organizarea programului și de faptul că un proiect de acest gen necesită multe obiecte care lucrează împreuna am decis să folosesc C++. Tranziția nu a fost dificilă avand in vedere ca librariile (libtcod și SDL2) au rămas compatibile. Structura jocului nu este foarte complexă, componentele principale sunt:
- Engine   
- Map
- Persistent
- Gui
- Actor
  - Destructible
  - AI
    - PlayerAI
    - MonsterAI
  - Attacker
  - Pickable
    - Healer
    - LightningBolt
  - Container
  
#### Actor:

![actor_diagram](https://user-images.githubusercontent.com/23166665/104172787-79d14d00-540d-11eb-9e60-3c96775846d8.png)


Clasa Actor se ocupa cu implementarea jucătorului si a inamicilor. Pentru a ține cont de poziția jucătorului coordonatele acestuia sunt reținute si in Engine.
Actor conține de asemnea pointeri catre obiecte de tip Destructible, AI si Attacker (inițializate NULL) pentru a selecta mai usor funcționalitățile necesare.
Spre exemplu, un "orc" este un actor ce folosește toate cele trei implementări in timp ce un obiect (care va fi adăugat în curănd) obișnuit cum ar fi o sabie de  pe podea nu trebuie să se miște sau să atace.

