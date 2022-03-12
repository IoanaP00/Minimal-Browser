/* Popescu Ioana-Maria - 314CB */
#include "utils.h"

int main(int argc, char* argv[])
{
	/* Fisiere */
	FILE *in = fopen(argv[1],"r");
	FILE *out = fopen(argv[2], "w");

	/* Alocari structuri necesare */
	ListaTabs tabs = AlocCelula(), tab_curent = tabs;
	TCoada* h = AlocQ(sizeof(WebPage));
	TCoada* dl = AlocQ(sizeof(Resource));

	char* cmd = calloc(MAX_LINE, sizeof(char));
	int bandwidth = BW;

	while(!feof(in))
	{	
		fscanf(in, "%s\n", cmd);

		if(strcmp(cmd, "newtab") == 0)
		{
			tab_curent = newtab(tab_curent);
		}

		if(strcmp(cmd, "change_tab") == 0)
		{
			tab_curent = change(tabs, in);
		}

		if(strcmp(cmd, "print_open_tabs") == 0)
		{
			PrintTabs(tabs, out);
		}
		if(strcmp(cmd, "deltab") == 0)
		{
			tab_curent = deltab(tabs, tab_curent);
		}

		if(strcmp(cmd, "goto") == 0)
		{
			go_to(tab_curent, in, h);

			if(dl != NULL && dl->ic != NULL)
			avans_dl(dl, bandwidth, SEC);
		}

		if(strcmp(cmd, "back") == 0)
		{
			back(tab_curent, out);
		}

		if(strcmp(cmd, "forward") == 0)
		{
			forward(tab_curent, out);
		}

		if(strcmp(cmd, "history") == 0)
		{
			history(h, out);
		}

		if(strcmp(cmd, "del_history") == 0)
		{
			del_history(h, in);
		}

		if(strcmp(cmd, "list_dl") == 0)
		{
			list_dl(tab_curent, out);
		}

		if(strcmp(cmd, "download") == 0)
		{
			download(tab_curent, dl, in);
		}

		if(strcmp(cmd, "downloads") == 0)
		{
			downloads(dl, out);
		}

		if(strcmp(cmd, "set_band") == 0)
		{
			bandwidth = set_band(in);
		}

		if(strcmp(cmd, "wait") == 0)
		{
			wait(dl, bandwidth, in);
		}
	}
	fclose(in);
	fclose(out);
	free(cmd);
}