/* Popescu Ioana-Maria - 314CB */
#include "utils.h"

void* AlocCelQ(void* e)															/* Aloacare celula coada */
{
	ACel aux = (ACel)calloc(1, sizeof(TCel));
	if(!aux)
		return NULL;

	aux->info = e;

	return (void*)aux;
}

void* AlocQ(size_t e)															/* Alocare coada */
{
	AQ aux = (AQ)calloc(1, sizeof(TCoada));
	if(!aux)
		return NULL;

	DIMEQ(aux) = e;

	return (void*)aux;
}

int IntrQ(void *c, void *ae)													/* Adaugare elem coada */
{
	void* aux = AlocCelQ(ae);
	if(!aux) return 0;

	if(VIDAQ(c))
	{
		IC(c) = aux;
		SC(c) = aux;
	}

	else
	{
		SC(c)->urm = aux;
		SC(c) = SC(c)->urm;
	}

	return 1;
}

int ExtrQ(void *a, void *ae)													/* Extrage primul elem din coada*/
{
	ACel aux;
	if(IC(a) != NULL)
	{
		if(IC(a) == SC(a))
		{
			aux = IC(a);
			IC(a) = aux->urm;
			SC(a) = IC(a);
			memcpy(ae, aux->info, DIMEQ(a));

			return 1;
		}

		else
		{
			aux = IC(a);
			IC(a) = aux->urm;
			memcpy(ae, aux->info, DIMEQ(a));

			return 1;
		}
	}
	return 0;
}