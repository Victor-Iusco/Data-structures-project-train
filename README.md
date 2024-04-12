BIBLIOGRAFIE (Surse utilizate)
{
    GeeksForGeeks (intrebari generice): https://www.geeksforgeeks.org
    StackOverFlow (intrebari generice): https://stackoverflow.com
    W3Schools (Informatii functii string , pointeri) : https://www.w3schools.com/c/index.php
    Github Copilot (completare anumite legaturi) : https://github.com/features/copilot
}

Punctaj obtinul pe computerul personal
{
    -= TEMA 1 SDA =-
Total: 83.0/100
Valgrind: 0/20
}

Programul ce este reprezentat de cele 3 fisiere Initializari.h(fisierul header) in care am introdus toate librariile si am introdus toate headerele de functii si structurile folosite pentru coada si lista dublu inlantuita, Functii.c in care am implementat efectiv toate functiile care sunt cerute in cerinta si fisierul main.c in care am implementat citirea si scrierea in fisiere alaturi de call-urile pentru comenzile care modifica lista si coada respectiv.

Fisierul Initializari.h:

    In acest fisier sunt introduse toate librariile si sunt declarate structurile si toate functiile folosite in program pentru a face citirea codului mult mai usoara. Structurile utilizate sunt Vagon(nodul listei dublu inlantuite), trenulet (lista efectiva) , comanda (nodul cozii) si coada_de_comenzi. Structurile Vagon si comanda contin campurile next/prev respectiv sus/jos pentru a putea fi parcurse in ambele directii iar structurile structurile trenulet si coada_de_comenzi contin adrese catre mekanik si santinela respectiv primul si ultimul element din coada.

Fisierul Functii.c:

    InitTTren:
        Functia aloca spatiul de lista ca mai apoi sa creeze 2 vagoane care sunt initial mekanicul cu valoarea "#" si santinela pe care eu am ales sa tina un caracter "~" iar dupa ce le creaza face legaturile dintre cele 2 asiguranduse ca lista creata este dublu inlantuita circular.

    InitComenzi:
        Acelasi principiu doar ca nu se creaza comenzi initiale si de aceea nu se fac nici legaturi.

    CreareVagon:
        Creaza un vagon fara nici o legatura cu niciun alt vagon care primeste ca parametru in char care va fi stocat in campul info al vagonului nou creat

    AdaugareComanda:
        Creaza o comanda noua care primeste ca parametru un char* care este copiat in campul info. Functia contine si o conditie pentru cand coada este goala si cazul general.

    MOVE_LEFT / MOVE_RIGHT:
        Functiile ce sunt discutate au scopul de a muta pozitia mecanicului cu un spatiu la stanga / dreapta cu mici exceptii. MOVE_RIGHT daca se afla pe ultimul vagon sa creeze altul cu caracterul #.

    Write:
        Schimba inscriptia mecanicului cu un char transmis ca parametru

    INSERT_RIGHT/_LEFT
        Creaza o casuta noua in stanga / dreapta si muta mecanicul pe noul vagon creat iar daca mecanicul se afla pe primul vagon de langa santinela printeaza ERROR si nu mai se creaza vagonul.

    CLEAR_CELL/_ALL:
        Functiile de clear sterg vagoane si repara legaturile. Functia de CLEAR_ALL sterge toate vagoanele de la dreapta la stanga pana raman 2 si introduce un "#" in campul info al ultimului vagon ramas langa santinela pentru a intoarce trenul la lista initiala.

    SEARCH/-_LEFT/-_RIGHT:
        Functiile search trec prin toate vagoanele care intra in conditiile impuse fiecaruia si alcatuiesc un un string cu toate caracterele. Folosind formula strstr se returneaza o pozitie pentru primul caracter din sirul cautat, si prin 3 formule matematice deduse se fac mutari in stanga / dreapta pana ajungi in vagonul cu primul caracter al sirului pentru SEARCH si in vagoanele cu ultimele caractere pentru SEARCH_LEFT /_RIGHT

    SHOW / SHOW_CURRENT :
        SHOW afiseara tot trenul fara santinela si pune || in jurul mecanicului, iar SHOW_CURENT afiseara doar mecanicu fara bari

    TRECI_LA_FUNCTIA_URMATOARE:
        O functie care o chem dupa fiecare executare de functie si trece la urmatoarea comanda din coada si o elibereaza pe cea executata micsorand coada.

main.c:
    In fisierul main se deschid fisierele de citire si de scriere, se initializeaza lista si coada si dupa se intra in loopul while care citeste toate liniile si le compara cu comanda citita, daca se citeste SHOW/SHOW_CURRENT/SWITCH/EXECUTE se executa instant functiile iar restul sunt adaugate la coada cu functia respectiva si sunt chemate de EXECUTE. Iar dupa ce se termina se inchid fisierele si se opreste programul

