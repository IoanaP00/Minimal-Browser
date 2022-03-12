/* Popescu Ioana-Maria - 314CB */
#include "utils.h"

ListaTabs AlocCelula()															/* Aloca spatiu pt o celula de lista */
{
	ListaTabs aux = (ListaTabs)calloc(1, sizeof(CelLista));
	Tab* info = calloc(1, sizeof(Tab));

	if (aux)
	{
		if(info)
			aux->tabs = info;
		aux->urm = NULL;
	}
	
	return aux;
}

ListaTabs Adauga(ListaTabs* L, ListaTabs el)									/* Adauga la finalul listei */
{
	ListaTabs p = *L;
	if(*L == NULL)
		*L = el;
	else
	{
		while(p != NULL && p->urm != NULL)
		{
			p = p->urm;
		}
		p->urm = el;
	}
	p = p->urm;

	return p;
}

ListaTabs newtab(ListaTabs L)													/* Aloca celula + adauga la finalul listei */
{
	ListaTabs aux = AlocCelula();
	L = Adauga(&L, aux);
	return L;
}

ListaTabs deltab(ListaTabs L, ListaTabs p)										/* Sterge ultimul tab adaugat in lista */
{
	ListaTabs q = L;
	if(p->urm == NULL)
	{
		while(q->urm != p)
		{
			q = q->urm;
		}
		q->urm = NULL;
	 	p = q;
	}

	else
	{
		while(q->urm != NULL && q->urm->urm != NULL)
		{
			q = q->urm;
		}
		q->urm = NULL;
	}

	return p;
}

ListaTabs change(ListaTabs L, FILE *in)											/* Ajunge la tabul corespunzator */
{
	int val, i = 0;
	ListaTabs p = L;
	fscanf(in, "%d", &val);

	while(p != NULL && i < val)
	{
		p = p->urm;
		i++;
	}

	return p;
}

void PrintTabs(ListaTabs L, FILE* out)											/* Afiseaza url tuturor tab-urilor */
{
	int i = 0;

	while(L != NULL)
	{
		if(L->tabs->current_page == NULL)
		{
			fprintf(out, "(%d: empty)\n", i);
		}
		else
		{
			fprintf(out, "(%d: %s)\n", i, L->tabs->current_page->url);
		}

		L = L->urm;
		i++;
	}
}