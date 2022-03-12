/* Popescu Ioana-Maria - 314CB */
#include "utils.h"

WebPage* AlocaWP(char* url)														/* Aloca spatiu pt o structura WebPage */
{
	int n = 0;
	WebPage* aux = calloc(1, sizeof(WebPage));
	aux->resources = calloc(MAX_RESOURCES, sizeof(Resource));
	if(!aux)
		return NULL;

	strcpy(aux->url, url);

	Resource* r = (Resource*)calloc(MAX_RESOURCES, sizeof(Resource));
	r = get_page_resources(url, &n);
	int size = n * sizeof(Resource);

	aux->num_res = n;
	memcpy(aux->resources, r, size);

	return aux;
}

void go_to(ListaTabs L, FILE* in, TCoada* history)								/* Acceseaza pagina respectiva, adauga in istoric, asigura secunda de download*/
{
	char* url = calloc(1000, sizeof(char));
	fscanf(in, "%s\n", url);

	if(L->tabs->current_page != NULL)											/* Verificare daca e c_p goala */
	{
		Push(L->tabs->back_stack, L->tabs->current_page->url);					/* Se adauga ce era in c_p in stiva back */
	}
	else
	{
		Tab* tab = (Tab*)calloc(1, sizeof(Tab));								/*Se aloca spatiu pt tab nou, daca era c_p gol */
		tab = L->tabs;

		tab->current_page = (WebPage*)calloc(1, sizeof(WebPage));
		tab->back_stack = AlocSt(sizeof(WebPage));
		tab->forward_stack = AlocSt(sizeof(WebPage));
	}

	L->tabs->current_page = AlocaWP(url);										/* Se constuieste in c_p pagina web coresp url-ului citit */
	L->tabs->forward_stack->vf = NULL;
	WebPage* aux = calloc(1, sizeof(WebPage));
	aux = AlocaWP(url);
	IntrQ(history, aux);
}

void back(ListaTabs L, FILE* out)												/* Acceseaza pagina din back_stack */
{
	Tab* tab = L->tabs;

	if(tab->back_stack == NULL)
		fprintf(out, "can\'t go back, no pages in stack");

	else
	{
		Push(tab->forward_stack, tab->current_page);
		Pop(L->tabs->back_stack, tab->current_page);
	}
}

void forward(ListaTabs L, FILE* out)											/* Acceseaza pagina din forward_stack */
{
	Tab* tab = L->tabs;

	if(tab->forward_stack == NULL)
		fprintf(out, "can\'t go forward,no pages in stack");

	else
	{
		Push(tab->back_stack, tab->current_page);
		Pop(L->tabs->forward_stack, tab->current_page);
	}
}

void history(TCoada* history, FILE* out)										/* Afiseaza istoricul */
{
	void* aux = calloc(1, sizeof(WebPage));
	void* coada = AlocQ(sizeof(WebPage));
	while(ExtrQ(history, aux))
	{
		IntrQ(coada, aux);
		fprintf(out, "%s\n", ((WebPage*)aux)->url);
		aux = calloc(1, sizeof(WebPage));
	}

	while(ExtrQ(coada, aux))
	{
		IntrQ(history, aux);
		aux = calloc(1, sizeof(WebPage));
	}
}

void del_history(TCoada* h, FILE* in)											/* Sterge un nr de pagini din istoric */
{
	int val, i = 0;
	fscanf(in, "%d\n", &val);

	WebPage* aux = (WebPage*)calloc(1, sizeof(WebPage));
	if(!aux)
		return;

	if(val == 0)
	{
		h->ic = NULL;
		h->sc = NULL;
	}
	else
	{
		while(i < val)
		{
			ExtrQ(h, aux);
			i++;
		}
	}
}