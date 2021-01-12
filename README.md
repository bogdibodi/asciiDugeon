# **asciiDungeon**

## 1 Descriere generală:
 asciiDungeon este un joc roguelike 2D ce presupune parcurgerea unui nivel generat întamplător, unde jucătorul este nevoit să îsî folosească echipamentul găsit ca să învingă monștrii ce îi ies in cale. 
 Aspectul este unul foarte simplist, elementele jocului mai puțin pereții și podeaua sunt reprezentate de simboluri de la tastatură. (Ex: un orc arată ca un 'o' de culoarea verde)

## 2 Funcționalitate:
### 2.1 Despre cum se joacă
 Mișcarea se controleaza după săgețile de la tastarură sau numpad. Inventarul se deschide cu 'i' si scările se coboară cu 's'. Pentru a lua un obiect de pe jos se apasă 'g'.
### 2.2 Despre structura jocului
 Inițial asciiDungeon a fost conceput in C. Dupa o serie de dificultăți legate de organizarea programului și de faptul că un proiect de acest gen necesită multe obiecte care lucrează împreuna am decis să folosesc C++. Tranziția nu a fost dificilă avand in vedere ca librariile (libtcod și SDL2) au rămas compatibile. Structura jocului este:
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
  
#### Engine:
Aceasta conține fluxul jocului. În main.cpp sunt apelate engine.update() și engine.render() atât timp căt fereastra jocului este deschisă. 
engine.update():
 Folosind o enumerație pentru flag-uri (STARTUP, IDLE, NEW_TURN) funcția update pornește jocul sau iterează o tură noua.
engine.render():
 Aici se apelează mai departe funcțiile care desenează nivelul, actorii si interfața jucătorului.

#### Map
Pentru a creea un nivel harta este împărțită in jumătate succesiv păna cand se ajunge la o marime minimă setată (ROOM_MIN_SIZE) și se creeaza coridoare intre camere. Pe urmă se apelează addMonster(), si addItem() pentru popularea acestuia cu inamici, poțiuni sau vrăji. 

#### Persistent
Această clasă este folosita pentru a reține progresul jocului în cazul in care jucătorul se oprește inainte să moară. Pentru fiecare clasă din diagramă au fost create funcțiile save() si load(). Toată informația este salvată intr-un .zip folosind o implementare oferită de libtcod.

![persistent_diag](https://user-images.githubusercontent.com/23166665/104303507-d5b1d980-54d2-11eb-8236-b69933a044dc.png)

#### Gui
Este componenta responsabilă de generarea pentru combat log, inventar, bara de xp, bara de viața și afișează numele unui actor atunci cand jucătorul îl selecteaza folosind mouse-ul.

#### Actor:
Clasa Actor se ocupa cu implementarea jucătorului si a inamicilor. Pentru a ține cont de poziția jucătorului coordonatele acestuia sunt reținute si in Engine.
Actor conține de asemnea pointeri catre obiecte de tip Destructible, AI, Attacker, Pickable si Container (inițializate NULL) pentru a selecta mai usor funcționalitățile necesare.
Spre exemplu, un "orc" este un actor ce folosește toate cele trei implementări in timp ce o poțiune  nu trebuie să se miște sau să atace dar trebuie sa aplice un efect in momentul în care este folosită.

![diagrama_actor](https://user-images.githubusercontent.com/23166665/104309194-75bf3100-54da-11eb-9e0f-f38edbb64618.png)




