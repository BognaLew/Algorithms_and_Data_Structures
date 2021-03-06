## Project 2 - XOR linked list

The task is based on implement a bidirectional list. A classic bidirectional list stores successor and predecessor addresses in nodes, in our task the list stores only xor of these addresses in nodes. This saves approximately 50% of memory used by the list structure.

The terms list node and list element are used interchangeably and means the same.

During adding a new node to the list, we write the xor value of the predecessor and the successor to this node. If it is the first or the last node, as the xor of addresses, we write the address of the successor or the predecessor, respectively, because the address xor with 0 (we take zero as NULL) does not change the address value. From this it follows that we need to store a pointer to the first and last element of the list, which will allow us to browse the list in both directions. If we want to go to the next node in the assumed direction, we read its address as xor values stored in the current and previously visited node. As described earlier, at the boundary node this will be the direct address (since the value of a hypothetical nonexistent earlier node is 0).

In the case of deleting a node, updating the xor values of the deleted node's predecessor and successor is required. When deleting an boundary node, there is only one neighbor that needs to be updated.

The task requires that we have an additional pointer showing the current value used by the ACTUAL command described later. In this case, we also need to keep one of the neighbors (successor or predecessor, preferably both) of pointer showing the current value. Otherwise, we will not be able to restore their addresses (successor or predecessor of the current element). In this case, we must additionally store one of the neighbors (successor or predecessor, preferably both), otherwise we will not be able to restore their addresses. It would seem that this does not apply to the first and last node, but we are not able to conclude (without additional information) that the index to the current element just points to one of the boundary elements.

The list provides the following functionalities related to the following commands:

- ACTUAL - value of the currently pointed element. For an empty list it is NULL and after adding the first element to the list ACTUAL returns the value of that element as long as it is not moved by other operations.
- NEXT - prints the value of the ACTUAL successor setting it ACTUAL at the same time. If ACTUAL points to the last element of the queue, its successor will be the first element of the queue.
- PREV - prints the value of the predecessor ACTUAL setting it ACTUAL at the same time. If ACTUAL points to the first element of a queue, its predecessor will be the last element of the queue.
- ADD_BEG N - adding an element with value N to the beginning of the list.
- ADD_END N - adding an element with value N to the end of the list.
- ADD_ACT N - adding an element with the value of N as a predecessor of the currently selected element (ACTUAL).
- DEL_BEG - removes the first node from the list.
- DEL_END - removes the last node from the list.
- DEL_VAL N - removes from the list all nodes whose value is equal to N.
- DEL_ACT - removes from the list the node that ACTUAL points to, simultaneously setting ACTUAL to PREV. In the case of the PREV does not exist (ACTUAL was the first element of the list) ACTUAL shows the last element of the list.
- PRINT_FORWARD - prints the contents of the list from the first to the last element.
- PRINT_BACKWARD - prints the contents of the list from the last to the first element.

The behavior of the NEXT, PREV and DEL_ACT commands suggests action on a circular queue in which (except for an empty queue) there is always a successor and a predecessor for each node. When such a queue has only one element, the xor value of this node is 0. However, the implementation of the circular queue is not required and is not forbidden. Instead, it is possible to implement additional functionality of the NEXT and PREV commands. It will be run when an exceptional situation occurs, i.e. NEXT call when ACTUAL points to the last element of the queue, or PREV or DEL_ACT when ACTUAL points to the first element of a non-cyclic queue.

DEL_BEG, DEL_END, DEL_VAL, and DEL_ACT commands for an empty list do not remove anything. In each of these cases, removing the currently pointed element (ACTUAL command) should result in moving the currently pointed element pointer to the preceding element, and if it does not exist, to the last element of the list.

Standard C ++ Template Library (STL) cannot be used. Please remember to free memory when deleting list elements. Please also delete the entire list before exiting the program, freeing up all memory occupied by all its elements.

### Input

A number of commands that run specific functionalities in the list.

### Output

The results of the operation of the appropriate commands on the list with a certain state. Initially, the list is empty and its later status depends on the commands that are previously invoked. Some commands do not generate any output, e.g. (ADD_BEG, DEL_ACT) but affect the state of the list and other commands that display certain information, e.g. (ACTUAL, PRINT_FORWARD).

----------------------------------------------------------------------------------------------------------------------------------------------------

Zadanie polega na implementacji listy dwukierunkowej. Klasyczna lista dwukierunkowa przechowuje w w??z??ach adresy nast??pnika i poprzednika, w naszym zadaniu lista przechowuje w w??z??ach jedynie xor tych adres??w. Pozwala to na ok. 50 zaoszcz??dzenie pami??ci wykorzystywanej na przez struktur listy.

Okre??lenie w??ze?? i element listy u??ywane s?? zamiennie i oznaczaj?? to samo.

Dodaj??c nowy w??ze?? do listy zapisujemy w nim warto???? xor poprzednika i nast??pnika. Je??li jest to pierwszy albo ostatni w??ze?? jako xor adres??w wpisujemy odpowiednio adres nast??pnika albo poprzednika poniewa?? xor adresu z 0 (zero przyjmujemy jako warto???? NULL) nie zmienia adresu. Z tego wynika, ??e musimy przechowywa?? wska??nik na pierwszy oraz ostatni element listy, co pozwoli nam przegl??da?? list?? w obydwu kierunkach. Chc??c przej???? do kolejnego w??z??a w ustalonym kierunku jego adres odczytujemy jako xor warto??ci przechowywanych w aktualnym i wcze??niej odwiedzonym w????le. Jak opisano wcze??niej, w skrajnym w????le b??dzie to bezpo??redni adres (poniewa?? warto???? hipotetycznego, nieistniej??cego wcze??niejszego w??z??a jest r??wna 0).

W przypadku usuwania w??z??a nale??y zaktualizowa?? warto??ci xor poprzednika i nast??pnika usuwanego w??z??a. W przypadku usuwania skrajnego w??z??a istnieje tylko jeden s??siad wymagaj??cy aktualizacji.

Zadanie wymaga aby??my dysponowali dodatkowym wska??nikiem wskazuj??cym aktualn?? warto???? wykorzystywanym przez komend?? ACTUAL opisan?? p????niej. W tym przypadku musimy dodatkowo przechowywa?? jednego z s??siad??w (nast??pnika albo poprzednika, a najlepiej obydwu) wska??nika wskazuj??cego aktualn?? warto????. W przeciwnym przypadku nie b??dziemy w stanie odtworzy?? ich adres??w (nast??pnika albo poprzednika elementu aktualnego). Wydawa??o by si??, ??e nie dotyczy to pierwszego i ostatniego w??z??a ale nie jeste??my w stanie (bez dodatkowych informacji) wywnioskowa??, ??e wska??nik na element aktualny akurat wskazuje na jeden ze skrajnych element??w.

Lista udost??pnia nast??puj??ce funkcjonalno??ci powi??zane z nast??puj??cymi komendami:

- ACTUAL - warto???? aktualnie wskazywanego elementu. Dla pustej listy jest to NULL a po dodaniu pierwszego elementu do listy ACTUAL zwraca warto???? tego elementu tak d??ugo dop??ki nie zostanie przesuni??ty przez inne operacje.
- NEXT - drukuje warto???? nast??pnika ACTUAL jednocze??nie ustawiaj??c na niego ACTUAL. Je??li ACTUAL wskazuje na ostatni element kolejki jego nast??pnikiem b??dzie pierwszy element kolejki.
- PREV - drukuje warto???? poprzednika ACTUAL jednocze??nie ustawiaj??c na niego ACTUAL. Je??li ACTUAL wskazuje na pierwszy element kolejki jego poprzednikiem b??dzie ostatni element kolejki.
- ADD_BEG N - dodanie elementu z warto??ci?? N na pocz??tek listy.
- ADD_END N - dodanie elementu z warto??ci?? N na koniec listy.
- ADD_ACT N - dodanie elementu z warto??ci?? N jako poprzednika aktualnie wskazywanego elementu (ACTUAL).
- DEL_BEG - usuwa z listy pierwszy w??ze??.
- DEL_END - usuwa z listy ostatni w??ze??.
- DEL_VAL N ??? usuwa z listy wszystkie w??z??y kt??rych warto???? r??wna jest N.
- DEL_ACT - usuwa z listy w??ze?? na kt??ry wskazuje ACTUAL, jednocze??nie ustawiaj??c ACTUAL na PREV. W przypadku kiedy PREV nie istnieje (ACTUAL by?? pierwszym elementem listy) ACTUAL pokazuje na ostatni element listy.
- PRINT_FORWARD - drukuje zawarto???? listy od pierwszego do ostatniego elementu.
- PRINT_BACKWARD - drukuje zawarto???? listy od ostatniego do pierwszego elementu.

Zachowanie komend NEXT, PREV i DEL_ACT sygeruje dzia??anie na kolejce cyklicznej w kt??rej (z wyj??tkiem pustej kolejki) dla ka??dego w??z??a zawsze istnieje nast??pnik i poprzednik. Kiedy taka kolejka posada tylko jeden element warto???? xor tego w??z??a r??wna jest 0. Jednak??e implementacja cyklicznej kolejki nie jest nakazana i nie jest zakazana. Mo??ana w zamian zaimplementowa?? dodatkow?? funkcjonalno???? komend NEXT i PREV. B??dzie ona uruchamiana w momencie zaistnienia sytuacji wyj??tkowej czyli wywo??ania NEXT gdy ACTUAL wskazuje na ostatni element kolejki lub PREV b??d?? DEL_ACT gdy ACTUAL wskazuje na pierwszy element kolejki nie cyklicznej.

Komendy DEL_BEG, DEL_END, DEL_VAL i DEL_ACT w przypadku pustej listy nic nie usuwaj??. W ka??dym z tych przypadk??w usuni??cie aktualnie wskazywanego elementu (komenda ACTUAL) powinno owocowa?? przesuni??ciem wska??nika aktualnie wskazywanego elementu na poprzedzaj??cy go element a je??li taki nie istnieje na ostatni element listy.

Nie mo??na u??ywa?? standardowej biblioteki szablon??w C++ (STL). Prosz?? pami??ta?? o odzyskiwaniu pami??ci podczas usuwania element??w listy. Prosz?? r??wnie?? usun???? ca???? list?? przed zako??czeniem programu zwalniaj??c pami???? zajmowan?? przez wszystkie jej elementy.

### Wej??cie

Pewna liczba komend uruchamiaj??cych okre??lone funkcjonalno??ci na li??cie.

### Wyj??cie

Wyniki dzia??ania odpowiednich komend na li??cie charakteryzuj??cej si?? pewnym stanem. Pocz??tkowo lista jest pusta a p????niejszy jej stan zale??y od kolejno wywo??ywanych komend. Niekt??re komendy nie generuj?? ??adnego wyj??cia np. (ADD_BEG, DEL_ACT) ale maj?? wp??yw na stan listy i na kolejne komendy kt??re wy??wietlaj?? pewne informacje np. (ACTUAL, PRINT_FORWARD).
