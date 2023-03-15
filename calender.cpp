#include<stdio.h>
#include<string.h>
#include<time.h>
#define annee_bissextile(annee)((annee%4==0&&annee%100!=0)||annee%400==0)
#define TRUE 1
#define CH '-'
#define MAX_NO 91

void heure()
{
	int h,min,s,jour,mois,an;
	time_t now;
	time(&now);
	struct tm*local=localtime(&now);
	h=local->tm_hour;
	min=local->tm_min;
	s=local->tm_sec;
	printf("l'heure actuelle est:%02d:%02d:%02d\n",h,min,s);
}
void date()
{
	int h,min,s,jour,mois,an;
	time_t now;
	time(&now);
	printf("aujourd'hui est :%s\t",ctime(&now));
	printf("\n");
	struct tm*local=localtime(&now);
	jour=local->tm_mday;
	mois=local->tm_mon+1;
	an=local->tm_year+1900;
	printf("la date actuelle est :%02d/%02d/%02d\n",jour,mois,an);	
}
int premier_jour(int annee)
{
	
	int jour;
	jour=(((annee-1)*365)+((annee-1)/4)-((annee-1)/100)+((annee/400)+1))%7;
	return jour;
	
}

int getzeller(int mois,int annee){
	int jour=1,zmois,zannee,zeller;
	if(mois<3){
		zmois=mois+10;
	}else{
		zmois=mois-2;
	}
	if(zmois>10){
	   zannee=annee-1;	
	}else{
		zannee=annee;
	}
	zeller=(((13*zmois-1)/5)+jour+zannee%100+(zannee%100)/4-2*(zannee/100)+(zannee/400)+77)%7;
	return zeller;
}
void printfmessage(const char* message){
	int len=0;
	int pos=0;
	len=((70-strlen(message))/2);
	printf("\t\t\t\t");
	for(pos=0;pos<len;pos++){
		printf("\t");
	}
	printf("%s",message);
}


int getjour_mois(int mois_nombre,int annee){
	int mois_jour[]={31,28,31,30,31,30,31,31,30,31,30,31};
	mois_jour[mois_nombre-1]+=(annee_bissextile(annee)&&(mois_nombre==2));
	return (mois_jour[mois_nombre-1]);
}
void affichage_mois(){
	char *month[]={"JANVIER","FEVRIER","MARS","AVRIL","MAI","JUIN","JUILLET","AOUT","SEPTEMBRE","OCTOBRE","NOVEMBRE","DECEMBRE"};
	int k,j;
	 int jour,annee,mois;
	 	do{	
	printf("entrer votre annee:");
	scanf("%d",&annee);
	}while(annee<1582||annee>4902);
	do{
		printf("entrer votre mois:");
		scanf("%d",&mois);
	}while(mois<1||mois>12);
	 char buf[32]={0};
	 sprintf(buf,"%s%d\n\n","calendrier-",annee);
	 printfmessage(buf);
	int courant=getzeller(mois,annee);
	jour=getjour_mois(mois,annee);
	printfmessage(month[mois-1]);
	printf("\n");
	
	printf("\n\n \tsun\tmon\ttue\twed\tthu\tfri\tsat\n");
	for(k=0;k<courant;k++)
	{
		printf("\t");
	}
	for(j=1;j<=jour;j++){
		printf("\t%d",j);
		k++;
		if(k>6)
		{
			k=0;
			printf("\n");
		}
	}
}

int validateDate(int d, int m, int y )
{
    //vérifier la validité de l'année
    if ( y >= 1800 && y <= 2999) {
        //vérifier la validité du mois
        if( m >= 1 && m <= 12) {
            //vérifier la validité du jour
            if ( d >= 1 && d <= 31) {
                if ( ( d >= 1 && d <= 30) && ( m == 4 || m == 6 || m == 9 || m == 11) )
                    return 1; //date valide
                else if( ( d >= 1 && d <= 30) && ( m == 1 || m == 3 || m == 5 || m == 7 || m == 8 || m == 10 || m == 12) )
                    return 1; //date valide
                else if ( ( d >= 1 && d <= 28) && ( m == 2) )
                    return 1; //date valide
                else if ( d == 29 && m == 2 && ( ( y % 400 == 0) || ( y % 4 == 0 && y % 100 != 0) ) )
                    return 1; //date valide
                else
                    return 0; //jour invalide
            }
            else {
                return 0; //le jour n'est pas valide
            }
        }
        else {
           return 0; //mois n'est pas valide
        }
    }
    else{
       return 0; //l'année n'est pas valide
    }
}
// Cette fonction renverra le numéro de jour de la semaine de 0 à 6
int wd(int jour, int mois, int an )
{
    int wday = 0;
    wday = ( jour + ( (153 * ( mois + 12 * ( (14 - mois ) / 12) - 3) + 2) / 5)
               + (365 * ( an + 4800 - ( (14 - mois ) / 12) ) )
               + ( ( an + 4800 - ( (14 - mois ) / 12) ) / 4)
               - ( ( an + 4800 - ( (14 - mois ) / 12) ) / 100)
               + ( ( an + 4800 - ( (14 - mois ) / 12) ) / 400)
               - 32045)% 7;
    return wday;
}

int anniversaire( )
{
	int jour,mois,annee;
    int wDayNo = 0;
    char dayNames [ ] [12] = { "Lundi", "Mardi", "Mercredi", "Jeudi", "Vendredi", "Samedi", "dimanche" };

    //date d'entrée
    printf ("Date d'entrée ( JJ-MM-AAAA ): ");
    scanf ("%d-%d-%d", &jour, &mois, &annee );

    //la date de vérification est correcte ou non
    if ( validateDate ( jour, mois, annee ) == 1) {
        printf ("La date est correcte [% 02d /% 02d /% 02d ].\n", jour, mois, annee );
        //obtenir le numéro de semaine
        wDayNo = wd ( jour, mois,annee  );
        //imprimer le jour de la semaine selon wDayNo
        printf ("le jour de votre anniversaire est:% s\n", dayNames [ wDayNo ] );
    }
    else
        printf ("La date est correcte.\n");

    return 0;
}   

void calendrier()
{
	int annee,i,j,total_jours,jour_semaine,compteur_jour;
	int jour_mois[]={31,28,31,30,31,30,31,31,30,31,30,31};
	char *mois[]={"Janvier","Fevrier","Mars","Avril","Mai","Juin","Juillet","Aout","Septembre","Octobre","Novembre","Decembre"};
	
	printf("entrer l'annee de votre choix:");
	scanf("%d",&annee);
	if((annee%4==0&&annee%100!=0)||annee%400==0)
       {
       	  jour_mois[1]=29;
       	  printf("\nannee bissextile!!!");
	   }
	       	//affichage du premier jour de l'annee
        	jour_semaine=premier_jour(annee);
 //affichage du mois
 	for(i=0;i<12;i++)
        {
        	printf("\n\n~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~%s~*~*~*~*~*~*~*~*~*~*~*~*\n",mois[i]);
        	printf("\tSun\tMon\tTue\tWed\tThur\tFri\tSat\n"); 
        	
        	//calcul de la disposition des chiffres par rapport au mois
        	for(compteur_jour=1;compteur_jour<=jour_semaine;compteur_jour++)
        	{
        		printf("\t");
			}
			// affichage des jour
			total_jours=jour_mois[i];
			for(j=1;j<=total_jours;j++)
			{
				printf("\t%d",j);
				jour_semaine++;
				if(jour_semaine>6)
				{
					jour_semaine=0;
					printf("\n");
				}
				
			}
		}		
}

int main()
{
	int choix;
	char reponse='n';
	do{
		printf("\n\n*************** MENU *****************\n");
		printf(" 1-afficher l'heure locale\n");
		printf(" 2-afficher la  date actuelle\n");
		printf(" 3-trouver le jour de son anniversaire\n");
		printf(" 4-rechercher le mois d'une annee de votre choix \n");
		printf(" 5-afficher le calendrier d'une annee de votre choix\n");
		printf(" 6-quitter\n\n");
		printf("entrer votre choix:");
		scanf("%d",&choix);
		
		switch(choix)
		{
			case 1:heure();
			break;
			case 2:date();
			break;
			case 3:anniversaire();
			break;
			case 4:affichage_mois();
			break;
			case 5:calendrier();
			break;
			case 6:break;
			default:printf("choix non disponible");
		}
		printf("\n voulez vous rentrez au menu principal o/n ? :");
		scanf("%s",&reponse);
	}while(reponse=='o'||reponse=='O');	
}


























