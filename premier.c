#include <stdio.h>
#include <math.h>
#include <stdlib.h>


void fonc( int *tab);
void ouvrir(FILE **file, char *fichier,char *mode );
void ecrire( FILE **file,int *tab ); 
void changer(FILE **f1,FILE **f2,char t[][100]);

void fonc( int *tab)
{
	int i;
	int n=0;
	int c=0;
	int nb_div;
		
	do
	{
		nb_div=0;	
		for (i=1;i<=n ;i++)
		{
			if (n%i==0)
			{
				nb_div++;
			
			}
		
		}
		if (nb_div==2)
		{
			tab[c]=n;
			c++;
		
		}

		n++;
		
	}
	while (c<50);
}

void ouvrir(FILE **file, char *fichier,char *mode)
{
	*file= fopen(fichier,mode);
	if (*file==NULL)
	{
		printf("il y a une erreur\n");
		exit (1);
	}
}

void ecrire (FILE **file, int *tab)
{
	int i;
	for (i=0;i<50;i++)
	{
		fprintf (*file,"%d\n",tab[i]);
	}
	fclose(*file);
}


void changer( FILE **f1, FILE **f2, char t[50][100])
{
	int i;
	int j;
	int n=0;
	ouvrir(f1,"nb_premier.txt","r");
	for (i=0;i<50;i++)
	{
		fscanf(*f1,"%s",t[i]);
	}

	for (i=0;i<50;i++)
	{
		for (j=0;(t[i][j] != '\0');j++)
		{
			if ( t[i][j] == '5' )
			{
				t[i][j] = 'v';
				n++;
			}
		}
	}
	fclose(*f1);
	ouvrir(f2,"changement.txt","w");
	for (i=0;i<50;i++)
	{
		fprintf(*f2,"%s\n",t[i]);
	}
	fprintf(*f1,"Le nombre de caractere 'v' est:%d\n",n); 
	fclose(*f2);
}

int main ()
{

	int tab[50];
	FILE *fichier1;
	FILE *fichier2;
	char tableau[50][100];
	fonc(tab);
	ouvrir(&fichier1,"nb_premier.txt","w");
	ecrire(&fichier1,tab);
	changer(&fichier1,&fichier2,tableau);
	return (0);
}



