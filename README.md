# Minimal-Browser

	Pentru rezolvarea problemei am folosit o lista de tab-uri deschise(tabs), tab-ul 
curent(tab_curent), o coada de istoric(h) si una de downloads(dl).

	Pentru cozi si stive am folosit structurile generice si funtiile de 
initializare si de introducere/eliminare de elemente din fiecare structura 
de la curs.

	Functii cerinta:

	-set_bandwidth: initializez un bandwidth(1024), pe care functia il modifica
	in functie de valoarea citita din fisier
	-newtab: ajunge la finalul listei de tab-uri si adauga o celula noua(de tip
	Tab), pe care o returneaza ca tab-ul curent
	-deltab: verifica daca ne aflam pe ultimul tab deschis. Daca e tab-ul final
	atunci tab-ul curent devine anteriorul si se sterge tab-ul final, daca nu,
	atunci doar elimina elementul de la finalul listei
	-change_tab: citeste tab-ul la care trebuie sa ajunga, apoi parcurge 
	celulele pana ajunge la valoarea respectiva, iar celula respectiva devine
	tab-ul curent
	-print_open_tabs: parcurge toata lista de tab-uri si, pentru fiecare celula,
	afiseaza pozitia in lista si url-ul respectiv paginii.

	-go_to: citeste url-ul la care trebuie sa ajunga pagina curenta din tab. 
	Daca exista o pagina curenta deja, aceasta va fi bagata in stiva de back, 
	altfel se va aloca spatiu pentru o noua structura de Tab. Stiva de forward 
	se goleste, iar pagina nou accesata se va adauga in coada de istoric.
	La apelarea functiei se va asigura avansul descarcarilor cu o secunda.
	-back: aduga in stiva de forward pagina curenta, iar pagina curenta se 
	scoate din stiva de back
	-forward: aduga in stiva de back pagina curenta, iar pagina curenta se 
	scoate din stiva de forward
	-history: extrage element cu element din coada de istoric, afiseaza pagina
	salvata in fiecare element si o introduce intr-o coada auxiliara. Se va 
	restitui coada de istoric din cea auxiliara.
	-del_history: citeste numarul de pagini de eliminat din istoric si extrage 
	din coada de istoric numarul respectiv. Daca valoarea este 0, se reseteaza 
	coada.

	-list_dl: acceseaza vectorul de resurse alocat prin functia data si afiseaza 
	fiecare resursa disponibila, alaturi de dimensiunea ei
	-downloads: acceseaza coada descarcarilor si afiseaza progresul(dimension - 
	currently_downloaded) pentru fiecare resusa in curs de descarcare
	-download: citeste resursa de pe pagina respectiva pe care trebuie sa o 
	adauge in coada descarcarilor
	-wait: citeste numarul de secunde si prin functia avans_dl adauga la 
	valoarea de currently_downloaded a fiecarui element din coada descarcarilor
	pana se atinge valoarea respectiva(nr secunde * val bandwidth), dar nu tine 
	cont de coada de prioritati, le extrage la rand din coada.
