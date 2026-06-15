#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Date
{
	int jour;
	int mois;
	int annee;
};

struct Etudiant 
{
	int numero;
	char nom[100];
	char prenom[100];
	struct Date date_nais;
	char adresse[100];
	char niveau[10];
};

void ouvrir ( FILE **f ,char *fichier, char *mode );
void supprimer_espaces(char *tab);
void recup ( struct Etudiant *e );
void ajoute ( FILE **f, struct Etudiant *e ,int *x);
void recup_data( FILE **f,struct Etudiant *etudiant, struct Etudiant *e,int *n);
void trier_nom ( FILE **f, struct Etudiant *e,int *n);
void trier_date ( FILE **f, struct Etudiant *e,int *n);
void trier_adresse ( FILE **f, struct Etudiant *e,int *n);
void recherche(FILE **f,struct Etudiant *e,int *n);
void supprimer (FILE **f,struct Etudiant *e,int *n);
void modifier(FILE **f,struct Etudiant *e,int *n);

void ouvrir ( FILE **f , char *fichier,char *mode )
{
	*f=fopen(fichier,mode);
	if ( *f == NULL )
	{
		printf ("Erreur de creation du fichier\n");
	}
}

void supprimer_espaces(char *tab)
{
	int i;
	int j=0;
	int debut=0 , fin=(strlen(tab) - 1);
	while ( tab[debut] == ' ' )
	{
		debut++;
	}
	while (fin > debut && (tab[fin] ==' ' || tab[fin] == '\r' || tab[fin] == '\n') )
	{
		fin--;
	}
	
	for (i=debut;i<=fin;i++)
	{
		tab[j++]=tab[i];
	}
	tab[j]='\0';
	
}

void recup ( struct Etudiant *e )
{
	printf("Entrer votre nom: ");
	scanf(" %[^\n]",e->nom);
	supprimer_espaces(e->nom);
	
	printf("Entrer prenom(s): ");
	scanf(" %[^\n]", e->prenom );
	supprimer_espaces(e->prenom);
	
	printf("Entrer votre date de naissance jj/mm/aaaa: ");
	scanf("%d/%d/%d",&e->date_nais.jour,&e->date_nais.mois,&e->date_nais.annee);
	//supprimer_espace(&e->date_nais.jour);
	//supprimer_espace(&e->date_nais.mois);
	//supprimer_espace(&e->date_nais.annee);
	
	printf("Entrer votre adresse: ");
	scanf(" %[^\n]",e->adresse);
	supprimer_espaces(e->adresse);
	
	printf("Entrer votre niveau: ");
	scanf(" %[^\n]",e->niveau);
	supprimer_espaces(e->niveau);

}


void choix_fichier( FILE **f,struct Etudiant *e,char *mode )
{
	if (strcmp(e->niveau,"L1") == 0 )
	{
		ouvrir(f,"L1.csv",mode);
	}
	else if (strcmp(e->niveau,"L2") == 0 )
	{
		ouvrir(f,"L2.csv",mode);
	}
	else if (strcmp(e->niveau,"L3") == 0 )
	{
		ouvrir(f,"L3.csv",mode);
	}
	else if (strcmp(e->niveau,"M1") == 0 )
	{
		ouvrir(f,"M1.csv",mode);
	}
	else if (strcmp(e->niveau,"M2") == 0 )
	{
		ouvrir(f,"M2.csv",mode);
	}
	else 
	{
		printf("Niveau invalide \nVeuillez reecrire le niveau (avec lettre majuscule)\n");
		exit; 
	}
}

/*void stocker_par_niveau( FILE **f,struct Etudiant *e)
{
	choix_fichier(*f);
	ajoute(*f,e);
}*/	


void recup_data( FILE **f,struct Etudiant *etudiant, struct Etudiant *e, int *n)
{

	choix_fichier(f,etudiant,"r");
	if (*f == NULL )
	{
		*n=0;
		return;
	}
	
	while(fscanf(*f,"%d,%[^,],%[^,],%d/%d/%d,%[^,],%s",&e[*n].numero,e[*n].nom,e[*n].prenom,&e[*n].date_nais.jour,&e[*n].date_nais.mois,&e[*n].date_nais.annee,e[*n].adresse,e[*n].niveau) == 8)
	{
		(*n)++;
		
	}
	
	fclose(*f);
	
	
}


void ajoute ( FILE **f,struct Etudiant *e,int *x )
{
	e->numero=(*x+1);
	fprintf(*f,"%d,%s,%s,%d/%d/%d,%s,%s\n",e->numero,e->nom,e->prenom,e->date_nais.jour,e->date_nais.mois,e->date_nais.annee,e->adresse,e->niveau);
	fclose(*f);
}


void ajoute_tab(FILE **f,struct Etudiant *e,int *n)
{
	int i;
	for (i=0;i<(*n);i++)
	{
		fprintf(*f,"%d,%s,%s,%d/%d/%d,%s,%s\n",e[i].numero,e[i].nom,e[i].prenom,e[i].date_nais.jour,e[i].date_nais.mois,e[i].date_nais.annee,e[i].adresse,e[i].niveau);
	}
}


void trier_nom( FILE **f, struct Etudiant *e,int *n)
{
	struct Etudiant temp;
	int i;
	int j;
	for (i=0;i<(*n-1);i++)
	{
		for(j=i+1;j<(*n);j++)
		{
			if ( strcmp( e[i].nom, e[j].nom) > 0 )
			{
				temp=e[i];
				e[i]=e[j];
				e[j]=temp;	
			}
		}
	}
	ouvrir(f,"trie_nom.csv","w");
	ajoute_tab(f,e,n);
	fclose(*f);

}
	
void trier_adresse( FILE **f, struct Etudiant *e, int *n)
{
	struct Etudiant temp;
	int i;
	int j;
	for (i=0;i<(*n-1);i++)
	{
		for (j=i+1;j<(*n);j++)
		{
			if (strcmp(e[i].adresse, e[j].adresse) > 0)
			{
				temp=e[i];
				e[i]=e[j];
				e[j]=temp;
			}
		}
	}
	ouvrir(f,"trie_adresse.csv","w");
	ajoute_tab(f,e,n);
	fclose(*f);

}

void trier_date_nais( FILE **f, struct Etudiant *e, int *n)
{
	int i;
	int j;
	struct Etudiant temp;
//	int d1,m1,a1;
//	int d2,m2,a2;
		
	
	for (i=0;i<(*n-1);i++)
	{
		for (j=i+1;j<(*n);j++)
		{
//			sscanf(e[i].date_nais,"%d/%d/%d",&d1,&m1,&a1);
//			sscanf(e[j].date_nais,"%d/%d/%d",&d2,&m2,&a2);

			if ( e[i].date_nais.annee < e[j].date_nais.annee )
			{
				temp=e[i];
				e[i]=e[j];
				e[j]=temp;
			}
			else if ( e[i].date_nais.annee == e[j].date_nais.annee && e[i].date_nais.mois < e[j].date_nais.mois )
			{
				temp=e[i];
				e[i]=e[j];
				e[j]=temp;
			}
			else if ( e[i].date_nais.annee == e[j].date_nais.annee && e[i].date_nais.mois == e[j].date_nais.mois && e[i].date_nais.jour < e[j].date_nais.jour )
			{
				temp=e[i];
				e[i]=e[j];
				e[j]=temp;
			}
		}
	}
	ouvrir(f,"trie_date.csv","w");
	ajoute_tab(f,e,n);
	fclose(*f);
}
/*
void stocker( FILE **f, struct Etudiant *e, char **t)
{
	ouvrir(*f,"L1.csv","w+");
	for (i=0;i<(*n);i++)
	{
		fprintf(*f, "%s %s %s %s %s ",e->nom,e->prenom,e->date_nais,e->adresse,e->niveau);
	}
	fclose (*f);
}
*/
void recherche(FILE **f,struct Etudiant *e,int *n)
{
	int i=0;
	int trouve=0;
	char info[100];
	char ligne[500];
	char fichier[5][100]={"L1.csv","L2.csv","L3.csv","M1.csv","M2.csv"};
	printf("Entrer une information de la personne a rechercher:\n");
	scanf(" %99[^\n]",info);
	supprimer_espaces(info);

	//ouvrir(f,"L1.csv","r");
	/*for (i=0;i<*n;i++)
	{
		if (strcmp (e[i].nom,info) == 0  || strcmp (e[i].prenom,info) == 0 || strcmp (e[i].date_nais,info) == 0 || strcmp (e[i].adresse,info) == 0)
		{
			printf ("%s,%s,%s,%s,%s \n",e[i].nom,e[i].prenom,e[i].date_nais,e[i].adresse,e[i].niveau);
			trouve=1;
		}

		
	}
		if (trouve == 0)
		{
			printf("Aucun etudiant trouve\n");
		}*/
	printf("Resulat(s):\n");
	for (i=0;i<5;i++)
	{
		ouvrir(f,fichier[i],"r");

	while (fgets(ligne,sizeof(ligne),*f) != NULL )
	{
		if (strstr(ligne,info) != NULL )
		{
			printf("%s",ligne);
			trouve = 1;
			i++;
		}
	}
	fclose(*f);
	}
	if ( trouve == 0)
	{
		printf("Aucun etudiant trouve\n");
	}
	fclose(*f);
}

void verifier_num(struct Etudiant *e,int numero,int *n)
{
	int trouve=0;
	for (i=0;i<(*n);i++)
	{
		if ( e[i].numero == numero )
		{
			trouve=1;
			break ;
		}
	}
	if ( trouve == 0 )
		
		{
			printf ("Aucun etudiant correspondant\n");
		}
}

void supprime(FILE **f,struct Etudiant *e,int *n)
{
	int pos;
	int i;
	struct Etudiant etudiant;
	
	printf("Entrer le numero de l etudiant a supprimer sur la liste:");
	scanf("%d",&pos);
	verifier_num(e,pos,n);
	
	for (i=(pos-1);i<(*n)-1;i++)
	{
		e[i]=e[i+1];
	}
	(*n)--;
	
	for (i=0;i<(*n);i++)
	{
		e[i].numero=i+1;
	}
	
	e[pos]=etudiant; 
	choix_fichier(f,etudiant,"w+");
	ajoute_tab(f,e,n);
	fclose(*f);
}
		
void modifier(FILE **f, struct Etudiant *e, int *n)
{
	int i;
	int trouve=0;
	int choix;
	int numero;
	struct Etudiant etudiant;
	printf("Entrer le numero de l etudiant :");
	scanf("%d",&numero);
	verifier_num(e,numero,n);
	printf("Quelle information voulez-vous modifier (choisissez un numero):");
	printf("1.nom\n 2.prenom\n 3.date de naissance\n 4.adresse\n 5.niveau");
	scanf("%d",&choix);

	if ( choix == 1 )
	{
		printf("Entrer le nouveau nom :");
		scanf("%s",e[numero].nom);
		supprimer_espaces(e[numero].nom);
	}
	else if ( choix == 2 )
	{
		printf("Entrer le nouveau prenom :");
		scanf("%s",e[numero].prenom);
		supprimer_espaces(e[numero].prenom);
	}
	else if ( choix == 3 )
	{
		printf("Enterr la nouvelle date de naissance :");
		scanf("%d/%d/%d",&e[numero].date_nais.jour,&e[numero].date_nais.mois,&e[numero].date_nais.annee);
		//supprimer_espaces(e[numero].date_nais.jour);
		//supprimer_espaces(e[numero].date_nais.mois);
		//supprimer_espaces(e[numero].date_nais.annee);
	}
	else if ( choix == 4 )
	{
		printf("Entrer la nouvelle adresse :");
		scanf("%s",e[numero].adresse);
		supprimer_espaces(e[numero].adresse);
	}
	else if ( choix == 5 )
	{
		printf("Entrer niveau :");
		scanf("%s",e[numero].niveau);
		supprimer_espaces(e[numero].niveau);
	}
	else 
	{
		printf ("Aucun choix correspondant\n");
	}
	
	e[numero]=etudiant;
	choix_fichier(f,etudiant,"w+");
	ajoute_tab(f,e,n);
	fclose(*f);
}

void fichier()
{
	char niveau;
	printf("Entrer le niveau:");
	scanf("%s",&niveau);
	//choix_fichier(f,niveau,"r");
	recup_data



int main ()
{
	FILE *file;
	int n=0;
//	int numero=0;
	struct Etudiant e;
//	struct Etudiant *etudiant=malloc(n*sizeof(struct Etudiant));
	static struct Etudiant etudiant[100];
	recup(&e);
//	choix_fichier(&file,&e,"w+");
	choix_fichier(&file,&e,"a");
	fclose(file);
	recup_data(&file,&e,etudiant,&n);
	choix_fichier(&file,&e,"a");
	ajoute(&file,&e,&n);
	//ouvrir(&file1,"L1.csv","a");
	//fclose(file1);
	//recup_data(&file1,etudiant,&n);
	//recup(&e);
	//ouvrir(&file1,"L1.csv","a");
	//ajoute(&file1,&e,&n);
	//trier_nom(&file2,etudiant,&n);
	//trier_adresse(&file3,etudiant,&n);
	//trier_date_nais(&file4,etudiant,&n);
	//recherche(&file1,etudiant,&n);
	//supprime(&file1,etudiant,&n);
	//modifier(&file,etudiant,&n);

	return (0);
}








