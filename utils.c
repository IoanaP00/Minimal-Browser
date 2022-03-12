/* Popescu Ioana-Maria - 314CB */
#include "utils.h"

Resource* get_page_resources(const char *URL_Name, int *n)						/* Aloca vect resurese coresp paginii web */
{
	int i, j, name_len, url_name_len = strlen(URL_Name);

	unsigned int resource_nr = 0;
	u_int32_t size = 0;
	if(URL_Name == NULL)
	{
		return NULL;
	}

	for(i = 0; i < url_name_len; i++)
	{
		resource_nr += URL_Name[i];
	}

	resource_nr %= 13;
	Resource *result = (Resource *)calloc(resource_nr, sizeof(Resource));
	*n = resource_nr;
	for(i = 0; i < resource_nr; i++)
	{
		sprintf(result[i].name, "%s-(%d)", URL_Name, i);
		size = 0;
		name_len = strlen(result[i].name);

		for(j = 0; j < name_len; j++)
		{
			size += result[i].name[j];
		}
		/* Some randomness */
		size ^= size << 3;
		size += size >> 5;
		size ^= size << 4;
		size += size >> 17;
		size ^= size << 25;
		size += size >> 6;

		/* 100MB Maximum size */
		result[i].dimension = size % 104857601;
		result[i].currently_downloaded = 0;
	}

	return result;
}

void list_dl(ListaTabs L, FILE* out)											/* Afiseaza resursele descarcabile */
{
    if(L != NULL && L->tabs != NULL && L->tabs->current_page != NULL)
    {
        WebPage* pag = L->tabs->current_page;
        int i;

        for(i = 0; i < pag->num_res; i++)
        {
            char* nume = pag->resources[i].name;
            unsigned long dim = pag->resources[i].dimension;
            fprintf(out, "[%d - \"%s\" : %ld]\n", i, nume,  dim);
        }
    }
}

void download(ListaTabs L, TCoada* dl, FILE* in)                                /* Download resursa citita */
{
    int index;
    fscanf(in, "%d\n", &index);

    if(L != NULL && L->tabs != NULL && L->tabs->current_page != NULL)
    {
        WebPage* pag = L->tabs->current_page;
        Resource resource = pag->resources[index];
        Resource* aux = calloc(1, sizeof(Resource));
            if(!aux) return;
        memcpy(aux, &resource, sizeof(Resource));
        IntrQ(dl, aux);
    }
}

void downloads(TCoada* dl , FILE* out)                                          /* Afiseaza resursele din istoricul de download */
{
	void* coada = AlocQ(sizeof(Resource));
	Resource* aux = calloc(1, sizeof(Resource));

	while(ExtrQ(dl, aux))
	{
		int val = aux->dimension - aux->currently_downloaded;
		if(val == 0)
			fprintf(out, "[\"%s\" : completed]\n", aux->name);
		else
			fprintf(out, "[\"%s\" : %d/%ld]\n", aux->name, val, aux->dimension);
		IntrQ(coada, aux);
		aux = calloc(1, sizeof(Resource));
	}
	while(ExtrQ(coada, aux))
	{
		IntrQ(dl, aux);
		aux = calloc(1, sizeof(Resource));
	}
}

int set_band(FILE* in)															/* Seteaza bandwidth */
{
	int val;
	fscanf(in, "%d\n", &val);
	return val;
}

void avans_dl(TCoada* dl, int band, int sec)									/* Descarca valoarea respectiva din istoricul de download */
{
	int val = band * sec;
	Resource* aux = calloc(1, sizeof(Resource));
	void* coada = AlocQ(sizeof(Resource));
	void* complete = AlocQ(sizeof(Resource));

	while(val > 0)
	{
		if(ExtrQ(dl, aux));
		{
			int dl_left = aux->dimension - aux->currently_downloaded;

			if(dl_left > val)
			{
				aux->currently_downloaded = aux->currently_downloaded + val;
				IntrQ(coada, aux);
				aux = calloc(1, sizeof(Resource));

				while(ExtrQ(dl, aux))
				{
					IntrQ(coada, aux);
					aux = calloc(1, sizeof(Resource));
				}
				while(ExtrQ(coada, aux))
				{
					IntrQ(dl, aux);
					aux = calloc(1, sizeof(Resource));
				}
				val = -1;
			}

			else
			{
				val = val - dl_left;
				aux->currently_downloaded = aux->dimension;
				IntrQ(complete, aux);
				aux = calloc(1, sizeof(Resource));
			}
		}
	}
	while(ExtrQ(complete, aux))
	{
		IntrQ(dl, aux);
		aux = calloc(1, sizeof(Resource));
	}
}

void wait(TCoada* dl, int band, FILE* in)										/* Citeste timpul de asteptare si apeleaza trece_timpul */
{
	int sec;
	fscanf(in, "%d\n", &sec);

	avans_dl(dl, band, sec);
}