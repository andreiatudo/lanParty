# Concluzie

***In urma realizarii acestui proiect, mi-am dat seama ca nu stiu sa imi organizez timpul atat de bine pe cat credeam si ca mereu dupa un malloc trb sa pun si free ca sa nu am probleme mai tarziu. A fost o experienta placuta si mi-ar placea sa avem mai multe proiecte de genul.***

# Main

In main am deschis fisierele dupa care am verificat daca s-au deschis corespunzator
Am citit valorile task-urilor pentru a stii ce task-uri facem si pe care nu
Am citit numarul de echipe
Pentru fiecare task am pus un if de verificare

## Task 1

Am citit toate echipele cu functia adaugare intr-un for

## Task 2

Am calculat cea mai mare putere a lui 2 mai mica sau egala decat numarul nostru de echipe
Am calculat punctajele echipelor si am sters echipele cu punctaj minim

Am afisat lista

## Task 3

Am creat coada si am pus echipele in ea
Am format stivele de castigatori si invinsi
Daca numarul de echipe ramas era 8 am creat o lista cu ultimele 8 echipe ramase
Am sters lista de invinsi
Am pus in coada echipele castigatoare

## Task 4

Am creat arborele bst si apoi l-am afisat in inordine

## Task 5

Am creat arborele avl cu ajutorul arborelui bst
Am folosit o functie pentru a afisa nodurile de pe al doilea nivel, luate de la radacina la frunza(**adica adancimea, nu inaltimea lor**)

# Fisierul lanPartyLib.c

## player_read

Citeste un jucator

## adaugare_player

Adauga jucatorul la echipa

## adaugare

Creeaza intreaga echipa, citind numarul de jucatori din fisier, sterge acel numar, ramanand cu numele echipei

## afisare

Afiseaza lista si sterge spatiul de la echipele din fisier care au acel spatiu

## eliminare

Sterge echipa cu punctajul minim

## team_points

Calculeaza numarul de puncte

## total_points_function

Atribuie numarul de puncte, echipei

## stergere

Cauta punctajul minim si sterge echipa cu acel punctaj

## Copy

Copiaza o echipa, intr-o alta echipa, printr-o copie profunda

## afisare_queue

Afiseaza numele echipelor din coada exact cum cere cerinta
Acel fprintf pune in partea stanga a 33 de spatii numele primei echipe, pune o liniuta si apoi numele celei de a doua echipe in partea dreapta

## createStacks

Aceasta functie creeaza stivele de castigatori si invinsi

## corectare_punctaje

La un moment dat am observat ca nu primeam tot punctajul pentru anumite teste. Am verificat punctajele echipelor si nu corespundeau cu cele din fisierele cu rezultate, si am creat aceasta functie 

## afisare_stack

Aceasta functie afiseaza caracter cu caracter numele echipei si apoi punctajul
Am ales aceasta abordare cu afisarea, deoarece cea de mai sus nu se potrivea exact in acest caz si am decis sa mai incerc si o alta idee

## creare_lista

Aceasta functie creeaza lista cu cele mai bune 8 echipe

## Pentru crearea bst-ului si avl-ului am folosit doar functiile din curs(pentru queue si stack si mai tot programul am folosit functii din curs)

## inorder_selection

Aceasta functie imi ia nodurile in ordinea corecta din bst si le pune in avl

## print_nodes

O functie recursiva care afiseaza toate nodurile de pe nivelul dat, in cazul nostru, al doilea. Aceasta functie tine minte nivelul pe care ne aflam si daca aceasta variabila este egala cu nivelul pe care il dorim, afiseaza numele echipei. Cauta in subarborele drept si apoi stang. In aceasta ordine, deoarece asa este fisierul cu rezultate

## Apoi urmeaza mai multe functii pentru eliberarea memoriei

# Fisierul lanPartyLib.h

In acest fisier se afla bibliotecile si declararea tuturor structurilor si subprogramelor