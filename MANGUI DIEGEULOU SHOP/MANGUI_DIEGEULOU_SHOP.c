//BIBLIOTHEQUES
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<windows.h>
#include<time.h>


//CONSTANTTES
#define CLS system("cls");
#define PAUSE system("pause");
#define VIDER fflush(stdin);


// LES STRUCTURES DU PROJET
typedef struct{
    int j,m,a;
}Date;


typedef struct{
    int id,nbr_Element,liste;
    char libelle[30];
}CATEGORIE;


typedef struct{
    int prix,qteStock,liste;
    char designation[30],code[10];
    char categorie[30];
    char dateAjout[20];
}ARTICLE;


typedef struct{
    int id,etat,supAdmin,nbreElement;
    char nom[30],prenom[30],tel[20],fonct[20],bloque[20];
    char login[20],mdp[20];
}USERS;


typedef struct{
    int id,nbreElement;
    char numero[20];
    ARTICLE tabproduits;
    int montants;
    USERS infoUsers;
}VENTE;




//DECLARATION DES VAIABLES SUPER GLOBALES
USERS Users,Session;
VENTE  vente;
ARTICLE article;
CATEGORIE categori;
Date date;
int cpt_user=0,cpt_cat=0,finMontant=0,nbPro=0;

/////////////////**********************************************************************************//////////////////

// LES FONCTIONS

//la fonction gotoxy pour la manipulation du curseur qui recoit deux   parametre ,elle place le curseur  a la position x et y

void gotoxy(int i , int j)
{
    HANDLE h=GetStdHandle(STD_OUTPUT_HANDLE);
    COORD c;

    c.X=i;
    c.Y=j;
    SetConsoleCursorPosition(h,c);
}

void color(int col)
{
    HANDLE h=GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(h,(WORD)col);
}

/////////////////**********************************************************************************//////////////////

// LES FONCTIONS POUR SE CONNECTER
void connexion(){
    puts("\n\n\n\n\n\n\n \t\t\t\t BIENVENUE DANS MANGUI DIEGEULOU SHOP !!!\n\n\n");

    PAUSE
    //VERIFICATION
    FILE *fichuser = NULL;
    char login[30],mdp[30],okLogin[20],verife[20];
    int trouve=0;

  //////////////////MA PAGE DE CONNECTION////////////////////////////////

     do{
            CLS
            printf("\n\t\t\t\t-------------------------------------------------------------");
            printf("\n\t\t\t\t--------------- PAGE DE CONNEXION ---------------------------");
            printf("\n\t\t\t\t-------------------------------------------------------------");
            printf("\n\t\t\t\t-------------------------------------------------------------");
            printf("\n\t\t\t\t---- LOGIN :                                              ---");
            printf("\n\t\t\t\t-------------------------------------------------------------");
            printf("\n\t\t\t\t-------------------------------------------------------------");
            printf("\n\t\t\t\t--- MOT DE PASSE :                                       ---");
            printf("\n\t\t\t\t------------------------------------------------------------");
            printf("\n\t\t\t\t------------------------------------------------------------");
            printf("\n\t\t\t\t---------                                      -------------");
            printf("\n\t\t\t\t-------------------------------------------------------------");
            printf("\n\t\t\t\t-------------------------------------------------------------");

      //les deux gotoxy pour l'emplacement du curseur
    gotoxy(45,5);
    gets(login);
    gotoxy(52,8);
   gets(mdp);
   //METTRES LES INFORMATIONS DANS UN FICHIER
    fichuser = fopen("USERS","rb");
    if(fichuser){
        while(fread(&Users,sizeof(Users),1,fichuser),!feof(fichuser)){
            if(strcasecmp(Users.login,login)==0 && strcasecmp(Users.mdp,mdp)==0){

                strcpy(Session.nom,Users.nom);
                strcpy(Session.prenom,Users.prenom);
                strcpy(Session.tel,Users.tel);
                strcpy(Session.mdp,Users.mdp);
                strcpy(Session.login,Users.login);
                trouve=1;
                if(Users.etat == 0){
                    nouveau_mdp();
                }
                PAUSE
                menuPrincipal();
            }
        }
        if (trouve==0)
        {
            gotoxy(75,11);
            printf("LOGIN OU MOT DE PASSE INCORRECT");
            gotoxy(72,14);
            PAUSE
        }
    }fclose(fichuser);
}while(trouve!=1);

}





//////////////////////////////NOUVEAU MOT DE PASSE /////////////////////////////////////////////////////////////////



void nouveau_mdp(){
   FILE *fichuser = NULL;
   char mdp[20],confirme[20];
   fichuser = fopen("USERS","r+b");
   if(fichuser){
                    while(fread(&Users,sizeof(Users),1,fichuser),!feof(fichuser)){
                        if(strcasecmp(Users.login,Session.login)==0&&strcasecmp(Users.mdp,Session.mdp)==0){
                            break;
                        }
                    }
                    CLS
                    gotoxy(65,8);
                    printf("\n\t\t\t\t---------------------------------------------------------------------------------------------------------------------");
                    printf("\n\t\t\t\t---------------------------------------------------------------------------------------------------------------------");
                    printf("\n\t\t\t\t------- FELICITION VOUS AVEZ PUIS VOUS CONNECTER %s %s VEILLIEZ CHANGE VOTRE MOT DE PASSE SVP           ---",Session.prenom,Session.nom);
                    printf("\n\t\t\t\t---------------------------------------------------------------------------------------------------------------------");
                    printf("\n\t\t\t\t---------------------------------------------------------------------------------------------------------------------");
                                                            gotoxy(72,25);
                    PAUSE
                    do{
                            CLS
            printf("\n\t\t\t\t\t\t\t\t------------------------------------------------------------");
            printf("\n\t\t\t\t\t\t\t\t------------------ PAGE DE CONNEXION -----------------------");
            printf("\n\t\t\t\t\t\t\t\t------------------------------------------------------------");
            printf("\n\t\t\t\t\t\t\t\t------------------------------------------------------------");
            printf("\n\t\t\t\t\t\t\t\t--- NOUVEAU MOT DE PASSE :                               ---");
            printf("\n\t\t\t\t\t\t\t\t------------------------------------------------------------");
            printf("\n\t\t\t\t\t\t\t\t------------------------------------------------------------");
            printf("\n\t\t\t\t\t\t\t\t--- CONFIRMATION :                                       ---");
            printf("\n\t\t\t\t\t\t\t\t------------------------------------------------------------");
            printf("\n\t\t\t\t\t\t\t\t---                                                    -----");
            printf("\n\t\t\t\t\t\t\t\t------------------------------------------------------------");
            printf("\n\t\t\t\t\t\t\t\t------------------------------------------------------------");
                     gotoxy(91,5);
                    gets(mdp);
                    gotoxy(83,8);
                    gets(confirme);
                    if(strcasecmp(Session.mdp,mdp)==0){
                            gotoxy(70,10);
                        printf("LE MOT DE PASSE DOIT ETRE DIFFERENT DU PRECEDENT.");
                             gotoxy(94,16);
                        PAUSE
                    }else if(strcasecmp(mdp,confirme)!=0){
                              gotoxy(85,10);
                        printf("CONFIRMATION INCORRECT");
                              gotoxy(60,16);
                        PAUSE
                    }

                    }while(strcasecmp(Session.mdp,mdp)==0||strcasecmp(mdp,confirme)!=0);

                    //fseek: Cette fonction permet d'effectuer la position du pointeur de fichier.
                    fseek(fichuser,-1l*sizeof(Users),SEEK_CUR);
                    strcpy(Users.mdp,mdp);
                     Users.etat = 1;
                     fwrite(&Users,sizeof(Users),1,fichuser);
                     gotoxy(60,16);
                     printf("MOT DE PASSE MODIFIER AVEC SUCCES");
                     gotoxy(60,19);
                                   PAUSE
   }fclose(fichuser);
                       menuPrincipal();
}

/*--------------------------------------------------AJOUTSUER----------------------------------------*/




void ajoutUser(){
    CLS
    FILE *fichuser = NULL;
    char nom[20],prenom[20],tmplg[20];
    int taille = 0,trouve = 0,i,trouv = 0,choix;

     do{
            VIDER
            PAUSE
            CLS
             trouve = 0;
             puts("ENTRER LE NOM:");
             gets(nom);
             taille = strlen(nom);
         if(taille<4){
                 printf("\nLE NOM DOIT AVOIR AU MOINS 4 CARACTERES ALPHABETIQUES.\n");
                 trouve = 2;
          }else{

              for(i=0;i<taille;i++){
                  if(nom[i]>='a'&&nom[i]<='z'){

                     if(nom[i]!=toupper(nom[i])){
                        trouve = 1;
                      }
                   }
              }
                 if(trouve==1){
                    printf("\nLE NOM DOIT ETRE TOUT EN MAJUSCULE\n");
                  }
          }
    }while(trouve != 0);

    do{
            VIDER
        trouve = 0;
        puts("ENTRER LE PRENOM:");
        gets(prenom);
        taille = strlen(prenom);
        if(taille<3){
             printf("\nLE PRENOM DOIT AVOIR AU MOINS 3 CARACTERES ALPHABETIQUES.\n");
             trouve = 2;
        }else{

             for(i=0;i<taille;i++){
               if(prenom[i]>='a'&&prenom[i]<='z'){
                   if(prenom[0]!=toupper(prenom[0])){
                        trouve = 1;
                     }
                 }
              }
                  if(trouve==1){
                      printf("\nLE PREMIER CARACTERE DU PRENOM DOIT ETRE EN MAJUSCULE\n");
                    }
           }
    }while(trouve != 0);
//fichier lecture en mode binaire
	fichuser = fopen("USERS","rb");
	if(fichuser){
            while(fread(&Users,sizeof(Users),1,fichuser),!feof(fichuser)){
                if(strcasecmp(Users.nom,nom)==0&&strcasecmp(Users.prenom,prenom)==0){
                    trouv = 1;
                    break;
                }
            }
	}fclose(fichuser);

	if(trouv == 0){
    //fichier ajouter en mode binaire
         fichuser = fopen("USERS","ab");
	     if(fichuser){
           VIDER
            Users.nbreElement++;
            Users.id = Users.nbreElement;
            strcpy(Users.nom,nom);
            strcpy(Users.prenom,prenom);
            puts("Entrer le Telephone:");
            gets(Users.tel);
            do{
                    VIDER
               printf("\n-------------FONCTION---------\n");
               printf("\n1 ..........UTILISATEUR ADMIN\n");
               printf("2 ..........UTILISATEUR SIMPLE\n");
               printf("choix :");
               scanf("%d",&choix);
               switch(choix){
                   case 1:{
                       strcpy(Users.fonct,"ADMIN");
                       break;
                   }
                   case 2:{
                       strcpy(Users.fonct,"UTILISATEUR");
                       break;
                   }
                   default:{
                       printf("\nCHOIX INVALIDE\n");
                   }
               }
               }while(choix!=1&&choix!=2);
            sprintf(tmplg,"%c%c%c%c%c",Users.nom[0],Users.nom[1],Users.nom[2],Users.nom[3],Users.prenom[0]);
            strcpy(Users.mdp,"passer123");
            strcpy(Users.login,tmplg);
            cpt_user ++;
            Users.etat = 0;
            strcpy(Users.bloque,"OPENED");
		    fwrite(&Users,sizeof(Users),1,fichuser);
	     }fclose(fichuser);

	}else{
	    printf("\nCet utilisateur existe deja dans le systeme\n");
	}
}


/*--------------------------------------LIST USER------------------------------------------------------*/


void listUsers(){
    CLS
    FILE *fichuser = NULL;
	fichuser = fopen("USERS","rb");
	if(fichuser){

		while(fread(&Users,sizeof(Users),1,fichuser),!feof(fichuser)){
                    printf("\n------------------------------------------------------------------------------------------------------------------------------------------------\n");
				printf("\tID\t|\tNOM\t|\tPRENOM\t|\tTELEPHONE\t|\tLOGIN\t|\tFONCTION\t|\tETAT\t|\n%9d%20s%17s%19s%20s%20s%20s\n",Users.id,Users.nom,Users.prenom,Users.tel,Users.login,Users.fonct,Users.bloque);
                    printf("------------------------------------------------------------------------------------------------------------------------------------------------\n");
		}
	}
	fclose(fichuser);
}

/*------------------------------------AJOUT CATEGORIES--------------------------------------*/
void ajoutCategorie(){
    CLS
    FILE *fichcat = NULL;
    int trouve =0;
    char cat[20];
    VIDER
      puts("Entrer  le libelle");
      gets(cat);
	fichcat = fopen("CATEGORIES","rb");
	if(fichcat){
       while(fread(&categori,sizeof(categori),1,fichcat),!feof(fichcat)){
           if(strcasecmp(categori.libelle,cat)==0){
            trouve = 1;
            break;
           }
       }
    } fclose(fichcat);
     if(trouve == 0){
       fichcat = fopen("CATEGORIES","ab");
     if(fichcat){
        VIDER
        strcpy(categori.libelle,cat);
        categori.nbr_Element++;
        categori.id = categori.nbr_Element;
        categori.liste = 1;
        fwrite(&categori,sizeof(categori),1,fichcat);
     }fclose(fichcat);

     }else{
         printf("\ncette categorie existe deja\n");
     }
}

/*--------------------------------------------LISTER LES CATEGORIES-----------------------------------*/


void listCategories(){
    CLS
    FILE *fichcat = NULL;
	fichcat = fopen("CATEGORIES","rb");
	if(fichcat){
		while(fread(&categori,sizeof(categori),1,fichcat),!feof(fichcat)){
                printf("\n****************************************************\n");
		        printf("ID : %d\t\tLIBELLE : %s",categori.id,categori.libelle);
                printf("\n****************************************************\n");
		}
	}
	fclose(fichcat);
}

/*-----------------------------------------AJOUTER ARTICLE----------------------------------*/

void ajoutArticle(){
    CLS
    FILE *fichcat = NULL;
    FILE *fichpro = NULL;

    char tmpCat[20];
    char tmpPro[20],temps[20],code[20];
    int trouve = 0,verifie = 0,trv = 0;
    int choix;
    do{
         VIDER
         CLS
       printf("\n1 .............. METTRE A JOUR UN PRODUIT\n");
       printf("\n2 .............. AJOUTER UN NOUVEAU PRODUIT\n");
       printf("choix : ");
       scanf("%d",&choix);
       if(choix == 2){
            printf("\n-------------- NOUVEAU PRODUIT --------------\n");
            VIDER
    printf("entrer la categorie du produit:");
    gets(tmpCat);
    fichcat = fopen("CATEGORIES","rb");
    if(fichcat){
    while(fread(&categori,sizeof(categori),1,fichcat),!feof(fichcat)){
		    if(strcasecmp(categori.libelle,tmpCat)==0){
                verifie = 1;
                break;
		    }
         }
              if(verifie == 1){
                puts("entrer la designation du produit:");
                  gets(tmpPro);
                  fichpro = fopen("PRODUITS","rb");
                  if(fichpro){
                    while(fread(&article,sizeof(article),1,fichpro),!feof(fichpro)){
                      if(strcasecmp(article.designation,tmpPro)==0){
                          trv = 1;
                          break;
                      }
                    }
                  }fclose(fichpro);

                  if(trv == 0){
                      fichpro = fopen("PRODUITS","ab");
                      if(fichpro){
                      strcpy(temps,__DATE__);
                      strcpy(article.dateAjout,temps);
                      strcpy(article.designation,tmpPro);
                      puts("Entrer le prix: ");
                      scanf("%d",&article.prix);
                      puts("Entrer la quantite;");
                      scanf("%d",&article.qteStock);
                      strcpy(article.categorie,tmpCat);
                      sprintf(article.code,"%c%c%c-%c%c%c",article.designation[0],article.designation[1],article.designation[2],article.categorie[0],article.categorie[1],article.categorie[2]);
                      fwrite(&article,sizeof(article),1,fichpro);
                  }fclose(fichpro);
                }else{
                    printf("\nCe produit existe deja\n");
                }
              }else{
                  printf("\ncette categorie nexiste pas\n");
              }
		    }fclose(fichcat);
       }else if(choix == 1){
                    VIDER
                  puts("Entrer le code du produit:");
                  gets(code);
                  fichpro = fopen("PRODUITS","r+b");
                  if(fichpro){
                    while(fread(&article,sizeof(article),1,fichpro),!feof(fichpro)){
                      if(strcasecmp(article.code,code)==0){
                            printf("NOM DU PRODUIT : %s \n",article.designation);
                          trv = 1;
                          fseek(fichpro,-1l*sizeof(article),SEEK_CUR);
                          puts("entrer le nouveau prix du produit: ");
                          scanf("%d",&article.prix);
                          puts("entrer la nouvelle quantite:");
                          scanf("%d",&article.qteStock);
                          fwrite(&article,sizeof(article),1,fichpro);
                           printf("\nCE PRODUIT A ETE MIS A JOUR AVEC SUCCES\n");
                          break;
                      }
                    }
                  }fclose(fichpro);
                  if(trv ==0){
                    printf("\n LE CODE DU PRODUIT INCORRECT !!!!\n");
                  }

                }else{
                    printf("\nCHOIX INVALIDE\n");
                }
                VIDER
        }while(choix!=1&&choix!=2);
}

/*---------------------------------------LISTER LES PRODUITS------------------------------------------*/

void listProduits(){
    CLS
    FILE *fichpro = NULL;
    fichpro = fopen("PRODUITS","rb");
    if(fichpro){
        while(fread(&article,sizeof(article),1,fichpro),!feof(fichpro)){
                printf("\n\t**************************************************************************************************************************************\n");
		        printf("\tCODE: %s |\tDESIGNATION: %s |\tPRIX: %d |\tQUANTITE: %d |\tCATEGORIE: %s |\tDATE D'AJOUT: %s |",article.code,article.designation,article.prix,article.qteStock,article.categorie,article.dateAjout);
                printf("\n\t**************************************************************************************************************************************\n\n");
		}
    }fclose(fichpro);
}



/*---------------------------ETAT JOURNALIER-----------------------------------*/
void etatJournalier(){
    CLS
    char genere[50];
    FILE* F;
    F = fopen("etat.txt","a");
    fprintf(F,"MONTANT JOURNALIER : %d \tNOMBRE TOTAL DE PRODUITS VENDUS : %d",finMontant,nbPro);
    fclose(F);

//genere l'etat du jour
    system("start etat.txt");
}

/*---------------------------------------------EFFECTUER UNE VENT---------------------------------------*/
void Vente(){
   CLS
    FILE *fichpro = NULL;
   char tmp[30],numero[100],dt[20],ts[20],facture[100],genere[100];
   char code[20],rep,rep1;
   int qt,i,somme,Som,nb,N = 0;
   FILE* Fich,*F;

        vente.nbreElement++;
        vente.id = vente.nbreElement;
        strcpy(dt,__DATE__);//dte du jour
        strcpy(ts,__TIME__);//le temps
        sprintf(facture,"RECU_%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c_%d_%s.txt",dt[0],dt[1],dt[2],dt[4],dt[5],dt[7],dt[8],dt[9],dt[10],ts[0],ts[1],ts[3],ts[4],ts[6],ts[7],vente.id,Session.login);
        printf("\n%s\n",facture);
        sprintf(numero,"%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c_%d",dt[0],dt[1],dt[2],dt[4],dt[5],dt[7],dt[8],dt[9],dt[10],ts[0],ts[1],ts[3],ts[4],ts[6],ts[7],vente.id);
        printf("\n%s\n",numero);
        Fich = fopen(facture,"a");
                    fprintf(Fich,"\n----------------------------- INFOS UTILISATEURS CONNECTE ---------------------------------\n\n");
                    fprintf(Fich,"\nNOM :  %s\tPRENOM : %s\tTELEPHONE : %s\n",Session.nom,Session.prenom,Session.tel);
                    fprintf(Fich,"\n-----------------------------------------------------------------------------------------------\n\n");
                    fprintf(Fich,"\n------------------------------ LISTE DES PRODUITS ----------------------------------------\n\n");

    do{
     puts("Entrer le code du produit :");
     gets(code);
     VIDER
     fichpro = fopen("PRODUITS","r+b");
     if(fichpro){
        while(fread(&article,sizeof(article),1,fichpro),!feof(fichpro)){
            if(strcasecmp(article.code,code)==0){
                puts("Entrer la quatite a vendre :");
                scanf("%d",&qt);
                 VIDER
                if(article.qteStock==0){
                    printf("\nProduits en rupture de stock\n");
                    break;
                }else
                if(article.qteStock<qt){
                        somme = 0;
                        nb = 0;
                    printf("\nIL RESTE  %d %s EN STOCK...VOULEZ VOUS PRENDRE CETTE QUANTITE ?[O/N]\n");
                    scanf("%c",&rep);
                    if(rep=='n'||rep=='N'){
                        break;
                    }
                    somme = article.prix*qt; // somme = montant par unité
                    Som = Som + somme;  // Som montant total des produits
                    nb = qt;  // nb = qté du produit sélectionné
                    N = N + nb; // N = qte total des produits

                    fprintf(Fich,"CODE: %s  LIBELLE: %s  CATEGORIE: %s  PRIX: %d  QUANTITE: %d  DATE AJOUT: %s\n\n",article.code,article.designation,article.categorie,article.prix,qt,article.dateAjout);
                    fseek(fichpro,-1l*sizeof(article),SEEK_CUR);
                    article.qteStock = article.qteStock - qt;
                    fwrite(&article,sizeof(article),1,fichpro);
                    break;


                } else{
                         somme = 0;
                         nb = 0;
                    somme = article.prix*qt;
                    Som = Som + somme;
                    nb = qt;
                    N = N + nb;
                    fprintf(Fich,"CODE: %s  LIBELLE: %s  CATEGORIE: %s  PRIX: %d  QUANTITE: %d  DATE AJOUT: %s\n\n",article.code,article.designation,article.categorie,article.prix,qt,article.dateAjout);
                    fseek(fichpro,-1l*sizeof(article),SEEK_CUR);
                    article.qteStock = article.qteStock - qt;
                    fwrite(&article,sizeof(article),1,fichpro);
                    break;

                }
            }
        }

     }fclose(fichpro);

     puts("VOULEZ VOUS AJOUTER UN AUTRE PRODUIT ? [O/N]");
     scanf("%c",&rep1);
     if(rep1=='n' || rep1=='N'){
        break;
     }
      VIDER
    }while(rep1!='n' || rep1!='N');

     fprintf(Fich,"\n\n----------------------------------------------------------------------------------------------\n\n");
     fprintf(Fich,"MONTANT TOTAL = %d\tNOMBRE PRODUITS : %d",Som,N);
     finMontant = finMontant + Som;
     nbPro = nbPro + N;
    fclose(Fich);

    sprintf(genere,"start %s",facture);
    system(genere);

}



/*-----------------------------------BLOQUE DEBLOQUER USER----------------------------------------------------*/
void bloque_debloque_users(){
    CLS
    int choix,id,tv;
    FILE *fichuser = NULL;
    do{
            VIDER
            CLS
            printf("\n******* UPDATE USERS *********\n");
            printf("\n1 ......... BLOQUER\n");
            printf("\n2 ......... DEBLOQUER\n");
            printf("choix :");
            scanf("%d",&choix);
        if(choix == 1){
            tv =0;
           printf("entrer son ID: ");
           scanf("%d",&id);
           fichuser = fopen("USERS","r+b");
	       if(fichuser){
             while(fread(&Users,sizeof(Users),1,fichuser),!feof(fichuser)){
                if(Users.id==id){
                        tv = 1;
                        if(Users.supAdmin ==0){
                                printf("NOM : %s\t\t PRENOM : %s\n",Users.nom,Users.prenom);
                            if(strcasecmp(Users.bloque,"CLOSED")!=0){
                            fseek(fichuser,-1l*sizeof(Users),SEEK_CUR);
                            strcpy(Users.bloque,"CLOSED");
                            fwrite(&Users,sizeof(Users),1,fichuser);
                            printf("\nUTILISATEUR BLOQUER AVEC SUCCES...\n");
                            break;
                            }else{
                                printf("\nUsers deja bloquer\n");
                                break;
                            }
                         }else{
                             printf("\nc'est le super admin\n");
                             break;
                         }
                         break;
                  }
               }
               if(tv == 0){
                printf("\nCET IDENTIFIANT N'EXISTE PAS ...\n");
               }
	       } fclose(fichuser);

        }else if(choix == 2){
            tv=0;
            printf("entrer son ID: ");
           scanf("%d",&id);
           fichuser = fopen("USERS","r+b");
	       if(fichuser){
             while(fread(&Users,sizeof(Users),1,fichuser),!feof(fichuser)){
                if(Users.id==id){
                        tv = 1;
                        if(Users.supAdmin ==0){
                            printf("NOM : %s\t\t PRENOM : %s\n",Users.nom,Users.prenom);
                            if(strcasecmp(Users.bloque,"OPENED")!=0){
                            fseek(fichuser,-1l*sizeof(Users),SEEK_CUR);
                            strcpy(Users.bloque,"OPENED");
                            fwrite(&Users,sizeof(Users),1,fichuser);
                            printf("\nUTILISATEUR DEBLOQUER AVEC SUCCES...\n");
                            break;
                            }else{
                                printf("\nUsers deja debloquer\n");
                                break;
                            }
                         }else{
                             printf("\nc'est le super admin\n");
                             break;
                         }
                  }
               }
               if(tv == 0){
                printf("\nCET IDENTIFIANT N'EXISTE PAS ...\n");
               }
	       } fclose(fichuser);
        }else{
            printf("\nCHOIX INVALIDE\n");
        }

    }while(choix!=1&&choix!=2);
}



//-----------------------------------------------------MENU PRINCIPALE---------------------------------------------------------------------------

//fonction MENU PRINCIPAL

void menuPrincipal(){



   // system("pause");
    system("cls");

    puts("\n\n\n");


                printf("\t\t\t      §              §   § § § § § §  §           §  § § § § § §  §       §  § \n");system("color 0c");_sleep(25);
                printf("\t\t\t      § §          § §   §         §  § §         §  §            §       §  § \n");system("color 0f");_sleep(25);
                printf("\t\t\t      §   §      §   §   §         §  §   §       §  §            §       §  § \n");system("color 0c");_sleep(25);
                printf("\t\t\t      §     §  §     §   § § § § § §  §     §     §  §   § § § §  §       §  § \n");system("color 0f");_sleep(25);
                printf("\t\t\t      §       §      §   §         §  §       §   §  §         §  §       §  § \n");system("color 0c");_sleep(25);
                printf("\t\t\t      §              §   §         §  §         § §  §         §  §       §  § \n");system("color 0c");_sleep(25);
                printf("\t\t\t      §              §   §         §  §           §  § § § § § §  § § § § §  § \n");system("color 0c");_sleep(25);



    puts("\n\n\n\n\n\n\n");
                            printf("\t\t\t    §          §   §  § § § § § §   § § § § § § §  §           §  §             § § § § § §  §         §\n");system("color 0c");_sleep(25);
                            printf("\t\t\t    §  §       §   §  §             §              §           §  §             §         §  §         §\n");system("color 0c");_sleep(25);
                            printf("\t\t\t    §    §     §   §  §             §              §           §  §             §         §  §         §\n");system("color 0c");_sleep(25);
                            printf("\t\t\t    §      §   §   §  § § § § § §   §              §           §  §             §         §  §         §\n");system("color 0c");_sleep(25);
                            printf("\t\t\t    §     §    §   §  §             §     § § § §  §           §  §             §         §  §         §\n");system("color 0c");_sleep(25);
                            printf("\t\t\t    §  §       §   §  §             §           §  §           §  §             §         §  §         §\n");system("color 0c");_sleep(25);
                            printf("\t\t\t    § §        §   §  §             §           §  §           §  §             §         §  §         §\n");system("color 0c");_sleep(25);
                            printf("\t\t\t    §          §   §  § § § § § §   § § § § § § §  § § § § § § §  § § § § § §   § § § § § §  § § § § § §\n");system("color 0c");_sleep(25);



    puts("\n\n\n\n\n\n\n");




                        printf("\t\t\t  § § § § § §   §         §    § § § § § § §   § § § § §\n");system("color 0c");_sleep(25);
                        printf("\t\t\t  §             §         §    §           §   §       §\n");system("color 0c");_sleep(25);
                        printf("\t\t\t  §             §         §    §           §   §       §\n");system("color 0c");_sleep(25);
                        printf("\t\t\t  §             §         §    §           §   § § § § §\n");system("color 0c");_sleep(25);
                        printf("\t\t\t  § § § § § §   § § § § § §    §           §   §        \n");system("color 0c");_sleep(25);
                        printf("\t\t\t            §   §         §    §           §   §        \n");system("color 0c");_sleep(25);
                        printf("\t\t\t            §   §         §    §           §   §        \n");system("color 0c");_sleep(25);
                        printf("\t\t\t            §   §         §    §           §   §        \n");system("color 0c");_sleep(25);
                        printf("\t\t\t  § § § § § §   §         §    § § § § § § §   §        \n");system("color 0c");_sleep(25);




    system("color 0d");_sleep(10);
    system("color 0c");_sleep(10);
    system("color 0d");_sleep(10);
    system("color 0c");_sleep(10);
    system("color 0d");_sleep(10);
    system("color 0c");_sleep(10);
    system("cls");
    //_sleep(10);




puts("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");






    printf("\t\t\t\t\t\t   §§§§§§§§ §  §§§§§§  §     §  §        §  §§§§§§  §     §  §    §  §§§§§§    \n");system("color 0c");_sleep(25);
    printf("\t\t\t\t\t\t   §     §  §  §       § §   §   §      §   §       § §   §  §    §  §         \n");system("color 0f");_sleep(25);
    printf("\t\t\t\t\t\t   §§§§§§   §  §§§§    §  §  §    §    §    §§§§    §  §  §  §    §  §§§§      \n");system("color 0c");_sleep(25);
    printf("\t\t\t\t\t\t   §     §  §  §       §   § §     §  §     §       §   § §  §    § §         \n");system("color 0f");_sleep(25);
    printf("\t\t\t\t\t\t   §§§§§§§  §  §§§§§§  §     §      §§      §§§§§§  §     §  §§§§§§  §§§§§§    \n");system("color 0c");_sleep(25);



    system("color 0d");_sleep(10);
    system("color 0c");_sleep(10);
    system("color 0d");_sleep(10);
    system("color 0c");_sleep(10);
    system("color 0d");_sleep(10);
    system("color 0c");_sleep(10);
    system("cls");


    //_sleep(10);

puts("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");



       puts("\n\n\n");


                printf("\t\t\t      §              §   § § § § § §  §           §  § § § § § §  §       §  § \n");system("color 0c");_sleep(25);
                printf("\t\t\t      § §          § §   §         §  § §         §  §            §       §  § \n");system("color 0f");_sleep(25);
                printf("\t\t\t      §   §      §   §   §         §  §   §       §  §            §       §  § \n");system("color 0c");_sleep(25);
                printf("\t\t\t      §     §  §     §   § § § § § §  §     §     §  §   § § § §  §       §  § \n");system("color 0f");_sleep(25);
                printf("\t\t\t      §       §      §   §         §  §       §   §  §         §  §       §  § \n");system("color 0c");_sleep(25);
                printf("\t\t\t      §              §   §         §  §         § §  §         §  §       §  § \n");system("color 0c");_sleep(25);
                printf("\t\t\t      §              §   §         §  §           §  § § § § § §  § § § § §  § \n");system("color 0c");_sleep(25);



    puts("\n\n\n\n\n\n\n");
                            printf("\t\t\t    §          §   §  § § § § § §   § § § § § § §  §           §  §             § § § § § §  §         §\n");system("color 0c");_sleep(25);
                            printf("\t\t\t    §  §       §   §  §             §              §           §  §             §         §  §         §\n");system("color 0c");_sleep(25);
                            printf("\t\t\t    §    §     §   §  §             §              §           §  §             §         §  §         §\n");system("color 0c");_sleep(25);
                            printf("\t\t\t    §      §   §   §  § § § § § §   §              §           §  §             §         §  §         §\n");system("color 0c");_sleep(25);
                            printf("\t\t\t    §     §    §   §  §             §     § § § §  §           §  §             §         §  §         §\n");system("color 0c");_sleep(25);
                            printf("\t\t\t    §  §       §   §  §             §           §  §           §  §             §         §  §         §\n");system("color 0c");_sleep(25);
                            printf("\t\t\t    § §        §   §  §             §           §  §           §  §             §         §  §         §\n");system("color 0c");_sleep(25);
                            printf("\t\t\t    §          §   §  § § § § § §   § § § § § § §  § § § § § § §  § § § § § §   § § § § § §  § § § § § §\n");system("color 0c");_sleep(25);



    puts("\n\n\n\n\n\n\n");




                        printf("\t\t\t  § § § § § §   §         §    § § § § § § §   § § § § §\n");system("color 0c");_sleep(25);
                        printf("\t\t\t  §             §         §    §           §   §       §\n");system("color 0c");_sleep(25);
                        printf("\t\t\t  §             §         §    §           §   §       §\n");system("color 0c");_sleep(25);
                        printf("\t\t\t  §             §         §    §           §   § § § § §\n");system("color 0c");_sleep(25);
                        printf("\t\t\t  § § § § § §   § § § § § §    §           §   §        \n");system("color 0c");_sleep(25);
                        printf("\t\t\t            §   §         §    §           §   §        \n");system("color 0c");_sleep(25);
                        printf("\t\t\t            §   §         §    §           §   §        \n");system("color 0c");_sleep(25);
                        printf("\t\t\t            §   §         §    §           §   §        \n");system("color 0c");_sleep(25);
                        printf("\t\t\t  § § § § § §   §         §    § § § § § § §   §        \n");system("color 0c");_sleep(25);



        system("color 5f");_sleep(100);


printf("\n\n");
    system("pause");


    system("mode con LINES=39 COLS=170");
    int choix;
    char temps[20];
    printf("\n\n\t\t\t\t\t\t\tBIENVENU(E) %s %s\n",Session.prenom,Session.nom);
    PAUSE
    do{
        CLS
    printf("\n\n\n\n\n\t\t\t\t\t\t\tUTILISATEUR CONNECTE(E) : %s %s\n",Session.prenom,Session.nom);
    printf("\n\t\t\t\t\t\t\t%s %s",__TIME__,__DATE__);

            printf("\n\n\n\n");
            printf("\n\n\n\n\t\t\t\t\t\t\t____________________________________________________________");
            printf("\n\t\t\t\t\t\t\t------------------------ MENU PRINCIPAL --------------------");
            printf("\n\t\t\t\t\t\t\t-----------------------------------------------------------");
            printf("\n\t\t\t\t\t\t\t____________________________________________________________");
            printf("\n\t\t\t\t\t\t\t----   1---------- Ajouter un utilisateur               ----");
            printf("\n\t\t\t\t\t\t\t____________________________________________________________");
            printf("\n\t\t\t\t\t\t\t----   2---------- Lister des utilisateur               ----");
            printf("\n\t\t\t\t\t\t\t------------------------------------------------------------");
            printf("\n\t\t\t\t\t\t\t---   3---------- Ajouter une categorie                ----");
            printf("\n\t\t\t\t\t\t\t------------------------------------------------------------");
            printf("\n\t\t\t\t\t\t\t----   4---------- Lister les categories                ----");
            printf("\n\t\t\t\t\t\t\t------------------------------------------------------------");
            printf("\n\t\t\t\t\t\t\t----   5---------- Ajouter un produit                   ----");
            printf("\n\t\t\t\t\t\t\t------------------------------------------------------------");
            printf("\n\t\t\t\t\t\t\t----   6---------- Lister les produits                  ----");
            printf("\n\t\t\t\t\t\t\t------------------------------------------------------------");
            printf("\n\t\t\t\t\t\t\t----   7---------- Imprimer  l'etat du jour             ----");
            printf("\n\t\t\t\t\t\t\t------------------------------------------------------------");
            printf("\n\t\t\t\t\t\t\t----   8---------- Effectuer une vente                  ----");
            printf("\n\t\t\t\t\t\t\t------------------------------------------------------------");
            printf("\n\t\t\t\t\t\t\t----   9---------- Deconnecter                          ----");
            printf("\n\t\t\t\t\t\t\t------------------------------------------------------------");
            printf("\n\t\t\t\t\t\t\t----   10---------- Fermer le programme                 ----");
            printf("\n\t\t\t\t\t\t\t------------------------------------------------------------");
            printf("\n\t\t\t\t\t\t\t----   11---------- Bloquer ou Debloquer un user        ----");
            printf("\n\t\t\t\t\t\t\t------------------------------------------------------------");
            printf("\n\t\t\t\t\t\t\t------------------------------------------------------------");
            printf("\n\t\t\t\t\t\t\t------------------------------------------------------------");
            printf("\n\t\t\t\t\t\t\t----   Faites votre chsoix:");
            scanf("%d",&choix);
            printf("\n\t\t\t\t\t\t\t");


    switch(choix){
    case 1 :
        ajoutUser(); PAUSE
        break;
    case 2:
        listUsers(); PAUSE
        break;
    case 3:
        ajoutCategorie(); PAUSE
        break;
    case 4:
        listCategories(); PAUSE
        break;
    case 5:
        ajoutArticle(); PAUSE
        break;
    case 6:
        listProduits(); PAUSE
        break;
    case 7:
        etatJournalier(); PAUSE
        break;
    case 8:
        PAUSE
        VIDER
        Vente();
        break;
    case 9:
        PAUSE
        VIDER
        CLS
        connexion();
        break;
    case 10:
        return 0;
        break;
    case 11:
        bloque_debloque_users(); PAUSE
        break;
        default : {
             printf("choix invalide");
        }
    }
}while(1);
}





















































//-----------------------------------------------------------------------------------------------------///////

    // LES METHODES OU FONCTIONS

main(){
    ajoutUser();
    connexion();
    //menuPrincipal();


}

