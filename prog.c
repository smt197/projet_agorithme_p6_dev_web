#include <stdio.h>
#include <stdlib.h> 
#include "bib.h"
#include <string.h>
#include <unistd.h>
#include <termios.h>
#include <time.h>
#define TAILLE_MAX 100
char loginSaisi[TAILLE_MAX];
char mdpSaisi[TAILLE_MAX];
#ifdef _WIN32
#include <conio.h> 
#else 
#include <termios.h> 
#include <unistd.h> 
#endif
int getch() 
{
    struct termios oldt, newt;
    int ch;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return ch;
}

int afficheMenuAdmin() 
{
    int choix;
    do {
        printf("\n");
        printf("        MENU Admin       \n");
        printf("-------------------------------------\n");
        printf(" 1. GESTION DES ETUDIANTS           \n");
        printf(" 2. Generation de fichiers      \n");
        printf(" 3. MARQUER LES PRESENCES           \n");
        printf(" 4. ENVOYER UN MESSAGE              \n");
        printf(" 5. QUITTER                         \n");
        printf("\n");
        printf("Votre choix : ");
        scanf("%d", &choix);
        if (!(choix >= 1 && choix <= 5)) {
            printf("Choix invalide. Veuillez choisir entre 1 et 5.\n");
        }
    } while (!(choix >= 1 && choix <= 5));

    return choix;
}

int afficheMenuApprenant()
{
    int choix;
    do {
        printf("\n");
        printf("------------------------------------\n");
        printf("        MENU Apprenant             \n");
        printf("1. MARQUER MA PRESENCE             \n");
        printf(" 2. NOMBRE DE MINUTES D'ABSENCES    \n");
        printf(" 3. MES MESSAGES                    \n");
        printf("4. QUITTER                         \n");                                                              
        printf("------------------------------------\n");
        printf("\n");
        printf("Votre choix : ");
        scanf("%d", &choix);
        if (!(choix >= 1 && choix <= 4)) {
            printf("Choix invalide. Veuillez choisir entre 1 et 5.\n");
        }
    } while (!(choix >= 1 && choix <= 4));
    return choix;
}

int sousMenuAdmin()
{
    int a;
    do
    {
        printf("\n");
        printf("1-GENERER L'ENSEMBLE DES PRESENCES\n");
        printf("2-GENERER LES PRESENCES PAR DATE\n");
        printf("choix:");
        scanf("%d",&a);
        if(!(a==1 || a==2))
        {
            puts("choix invalide reessayez");
        }
    }while(!(a==1 || a==2));
    printf("\033[0m");
    return a;
    
}

int sousMenuMessage()
{
    int b;
    do
    {
        printf("\n");
        printf("1-Envoyer messages a tous les apprenants\n");
        printf("2-Message par classe\n");
        printf("3-Message individuel\n");
        printf("choix:");
        scanf("%d",&b);
        if(!(b==1 || b==2 || b==3))
        {
            puts("choix invalide reessayez");
        }
    }while(!(b==1 || b==2 || b==3));
    return b;
    
}



int verifierLoginMdp(const char* Fichier, const char* loginSaisi, const char* mdpSaisi)
{
    char ligne[TAILLE_MAX];
    char loginFichier[TAILLE_MAX];
    char mdpFichier[TAILLE_MAX];
    char* token;

    int verification = 0; 


    FILE* infoApprenant = fopen(Fichier, "r");
    if (infoApprenant == NULL) {
        printf("Erreur lors de l'ouverture du fichier.\n");
        return 0; 
    }

    while (fgets(ligne, TAILLE_MAX, infoApprenant) != NULL) 
    {
        token = strtok(ligne, " ");
        if (token != NULL) 
        {
            strcpy(loginFichier, token);

            token = strtok(NULL, "\n");
            if (token != NULL) 
            {
                strcpy(mdpFichier, token);

                if (strcmp(loginSaisi, loginFichier) == 0 && strcmp(mdpSaisi, mdpFichier) == 0) {
                    fclose(infoApprenant);
                    return 1; 
                }
            }
        }
    }

    fclose(infoApprenant);
    return 0; 
}

int authentification() {
    
    
    int c;

    do {
        printf("Login: ");
        fgets(loginSaisi, TAILLE_MAX, stdin);
        loginSaisi[strcspn(loginSaisi, "\n")] = '\0'; 
        if (strlen(loginSaisi) == 0) {
            printf("Le login est obligatoire. Veuillez saisir un login.\n");
        }
    } while (strlen(loginSaisi) == 0);

    printf("Mot de passe: ");

    int i = 0;
    char b;
    while (i < TAILLE_MAX - 1 && (b = getch()) != '\n') {
        putchar('*'); 
        mdpSaisi[i++] = b;
    }
    mdpSaisi[i] = '\0'; 

    printf("\n");

    if(verifierLoginMdp("connexAdmin.txt", loginSaisi, mdpSaisi)) 
    {
        c=1;
        return c;
    } else if(verifierLoginMdp("connexApprenant.txt", loginSaisi, mdpSaisi)) 
    {
        c=2;
        return c;
    } else 
    {
        puts("Login ou mot de passe invalide.");
        return 0;
    }
}

void obtenirNomPrenom(int id, char *nom, char *prenom) 
{
    FILE *fichier = fopen("listeEtudiants.txt", "r");
    if (fichier == NULL) {
        printf("Erreur lors de l'ouverture du fichier de liste des étudiants.\n");
        return;
    }

    int idFichier;
    while (fscanf(fichier, "%d %s %s", &idFichier, prenom, nom) == 3) {
        if (idFichier == id) {
            fclose(fichier);
            return; 
        }
    }

    fclose(fichier);
    nom[0] = '\0'; 
    prenom[0] = '\0';
}

void marquerPresenceAdmin() {
    char choix[TAILLE_MAX];
    char codeVerification[TAILLE_MAX];

    do {
        printf("Entrez votre code (ou 'q' pour quitter) : ");
        scanf("%s", choix);

        if (strncmp(choix, "q", 1) == 0) {

            printf("Mot de passe: ");
            fgets(codeVerification, TAILLE_MAX, stdin);
            int i = 0;
            char cr;
            while (i < TAILLE_MAX - 1 && (cr = getch()) != '\n') {
                putchar('*');
                codeVerification[i++] = cr;
            }
            codeVerification[i] = '\0';
            printf("\n");
            if (verifierLoginMdp("connexAdmin.txt", loginSaisi, codeVerification)) {
                break;
            } else {
                printf("Mot de passe incorrect. Veuillez réessayer.\n");
                continue;
            }
        }

        int id = atoi(choix);

        char nom[TAILLE_MAX];
        char prenom[TAILLE_MAX];
        obtenirNomPrenom(id, nom, prenom);

        if (nom[0] == '\0' || prenom[0] == '\0') {
            printf("L'etudiant n'existe pas.\n");
        } else {
            FILE *fichierPresence = fopen("liste_presence.txt", "r");
            if (fichierPresence == NULL) {
                printf("Erreur lors de l'ouverture du fichier de présence.\n");
                return;
            }

            char date[20];
            time_t maintenant = time(NULL);
            struct tm *tm_maintenant = localtime(&maintenant);
            strftime(date, sizeof(date), "%Y-%m-%d %H:%M:%S", tm_maintenant);

            int dejaPresent = 0;
            char ligne[TAILLE_MAX];
            while (fgets(ligne, sizeof(ligne), fichierPresence) != NULL) 
            {
                int idFichier;
                char dateFichier[20];
                sscanf(ligne, "%d %*s %*s %s", &idFichier, dateFichier);
                if (idFichier == id && strncmp(date, dateFichier, 10) == 0) {
                    dejaPresent = 1;
                    break;
                }
            }
            fclose(fichierPresence);

            if (dejaPresent) {
                printf("L'étudiant est déjà marqué présent.\n");
            } else {
                fichierPresence = fopen("liste_presence.txt", "a");
                if (fichierPresence == NULL) {
                    printf("Erreur lors de l'ouverture du fichier de présence.\n");
                    return;
                }

                fprintf(fichierPresence, "%d %s %s %s\n", id, prenom, nom, date);
                printf("Presence marquée pour %s %s à %s.\n", prenom, nom, date);

                fclose(fichierPresence);
            }
        }

    } while (1);
}


void marquerPresenceApprenant()
{
    char choix[TAILLE_MAX]; 
    char codeVerification[TAILLE_MAX];
    char nom[TAILLE_MAX];
    char prenom[TAILLE_MAX];
    int mdp=atoi(mdpSaisi); 
    obtenirNomPrenom(mdp, nom, prenom);

        if (nom[0] == '\0' || prenom[0] == '\0') 
        {
            printf("L'etudiant n'existe pas.\n");
        } else {
            FILE *fichierPresence = fopen("liste_presence.txt", "r");
            if (fichierPresence == NULL) {
                printf("Erreur lors de l'ouverture du fichier de présence.\n");
                return;
            }

            char date[20];
            time_t maintenant = time(NULL);
            struct tm *tm_maintenant = localtime(&maintenant);
            strftime(date, sizeof(date), "%Y-%m-%d %H:%M:%S", tm_maintenant);

            int dejaPresent = 0;
            char ligne[TAILLE_MAX];
            while (fgets(ligne, sizeof(ligne), fichierPresence) != NULL) 
            {
                int idFichier;
                char dateFichier[20];
                sscanf(ligne, "%d %*s %*s %s", &idFichier, dateFichier);
                if (idFichier == mdp&& strncmp(date, dateFichier, 10) == 0) {
                    dejaPresent = 1;
                    break;
                }
            }
            fclose(fichierPresence);

            if (dejaPresent) {
                printf("Vous etes déjà marqué présent.\n");
            } else {
                fichierPresence = fopen("liste_presence.txt", "a");
                if (fichierPresence == NULL) {
                    printf("Erreur lors de l'ouverture du fichier de présence.\n");
                    return;
                }

                fprintf(fichierPresence, "%d %s %s %s\n", mdp, prenom, nom, date);
                printf("Presence marquée pour %s %s à %s.\n", prenom, nom, date);

                fclose(fichierPresence);
            }
        }
}

char continuer()
{
    char con;
    
    printf("voulez vous vous reconnecter? o ou n:");
    scanf(" %c",&con);

    
    return con;
}

void genererFichierPresences()
{
    FILE *fichierPresence = fopen("liste_presence.txt", "r");
    if (fichierPresence == NULL) {
        printf("Erreur lors de l'ouverture du fichier de présence.\n");
        return;
    }

    Presence presences[TAILLE_MAX];
    int nombrePresences = 0;

    char ligne[TAILLE_MAX];

    while (fgets(ligne, sizeof(ligne), fichierPresence) != NULL) {
        int code;
        char prenom[TAILLE_MAX];
        char nom[TAILLE_MAX];
        char date[TAILLE_MAX];

        if (sscanf(ligne, "%d %s %s %s", &code, prenom, nom, date) != 4) {
            continue;
        }

        presences[nombrePresences].code = code;
        strcpy(presences[nombrePresences].prenom, prenom);
        strcpy(presences[nombrePresences].nom, nom);
        strcpy(presences[nombrePresences].date, date);

        // Chercher la classe de l'étudiant dans listeEtudiants.txt
        FILE *fichierEtudiants = fopen("listeEtudiants.txt", "r");
        if (fichierEtudiants == NULL) {
            printf("Erreur lors de l'ouverture du fichier des étudiants.\n");
            return;
        }

        char classe[TAILLE_MAX];
        while (fgets(ligne, sizeof(ligne), fichierEtudiants) != NULL) {
            int codeEtudiant;
            char prenomEtudiant[TAILLE_MAX];
            char nomEtudiant[TAILLE_MAX];
            char classeEtudiant[TAILLE_MAX];

            if (sscanf(ligne, "%d %s %s %s", &codeEtudiant, prenomEtudiant, nomEtudiant, classeEtudiant) != 4) {
                continue;
            }

            if (code == codeEtudiant) {
                strcpy(presences[nombrePresences].classe, classeEtudiant);
                break;
            }
        }

        fclose(fichierEtudiants);

        nombrePresences++;
    }

    fclose(fichierPresence);

    FILE *fichierSortie = fopen("totalPresence.txt", "w");
    if (fichierSortie == NULL) {
        printf("Erreur lors de la création du fichier de sortie.\n");
        return;
    }

    char datePrecedente[TAILLE_MAX] = "";

    for (int i = 0; i < nombrePresences; i++) {
        if (strcmp(presences[i].date, datePrecedente) != 0) {
            if (strcmp(datePrecedente, "") != 0) {
                fprintf(fichierSortie, "-------------------------------------------------------------+\n");
                fprintf(fichierSortie, "\n");
            }
            fprintf(fichierSortie, "Date: %s\n", presences[i].date);
            fprintf(fichierSortie, "-------------------------------------------------------------\n");
            fprintf(fichierSortie, "| Code  | Nom              | Prénom           | Classe           |\n");
            fprintf(fichierSortie, "-------------------------------------------------------------\n");
            strcpy(datePrecedente, presences[i].date);
        }

        fprintf(fichierSortie, "| %-5d | %-16s | %-16s | %-16s |\n",
                presences[i].code, presences[i].nom, presences[i].prenom, presences[i].classe);
    }

    fprintf(fichierSortie, "-------------------------------------------------------------\n");

    fclose(fichierSortie);

    printf("Le fichier totalPresencetxt a été généré avec succès.\n");
}


int validerFormatDate(const char *date) {
    
    if (strlen(date) != 10 || date[4] != '-' || date[7] != '-') {
        return 0;
    }

    for (int i = 0; i < 10; i++) {
        if (i != 4 && i != 7 && (date[i] < '0' || date[i] > '9')) {
            return 0;
        }
    }

    int jour, mois, annee;
    if (sscanf(date, "%d-%d-%d", &annee, &mois, &jour) != 3) {
        return 0;
    }

    if (annee < 1000 || annee > 9999 || mois < 1 || mois > 12 || jour < 1 || jour > 31) {
        return 0;
    }

    time_t maintenant = time(NULL);
    struct tm *tm_maintenant = localtime(&maintenant);
    if (annee > tm_maintenant->tm_year + 1900 ||
        (annee == tm_maintenant->tm_year + 1900 && mois > tm_maintenant->tm_mon + 1) ||
        (annee == tm_maintenant->tm_year + 1900 && mois == tm_maintenant->tm_mon + 1 && jour > tm_maintenant->tm_mday)) {
        return 2; 
    }


    return 1;
}


void listePresencesParDate() 
{
    int verification;
    char dateRecherchee[20];
    printf("Entrez une date (AAAA-MM-JJ) : ");
    scanf("%s", dateRecherchee);
    verification = validerFormatDate(dateRecherchee);

    if (verification == 1)
    {
        FILE *fichierPresence = fopen("liste_presence.txt", "r");
        if (fichierPresence == NULL)
        {
            printf("Erreur lors de l'ouverture du fichier de présence.\n");
            return;
        }

        char nomFichier[100];
        sprintf(nomFichier, "Liste des présences pour la date %s.txt", dateRecherchee);
        FILE *fichierSortie = fopen(nomFichier, "w");
        if (fichierSortie == NULL)
        {
            printf("Erreur lors de la création du fichier de sortie.\n");
            fclose(fichierPresence);
            return;
        }

        fprintf(fichierSortie, "Liste des présences pour la date %s :\n", dateRecherchee);
        fprintf(fichierSortie, "-------------------------------------------------------------\n");
        fprintf(fichierSortie, "| Code  | Nom              | Prénom           | Classe           |\n");
        fprintf(fichierSortie, "-------------------------------------------------------------\n");

        char ligne[TAILLE_MAX];
        while (fgets(ligne, sizeof(ligne), fichierPresence) != NULL)
        {
            char date[TAILLE_MAX];
            sscanf(ligne, "%*d %*s %*s %s", date);
            if (strcmp(date, dateRecherchee) == 0)
            {
                int code;
                char nom[TAILLE_MAX];
                char prenom[TAILLE_MAX];
                sscanf(ligne, "%d %s %s", &code, prenom, nom);

                FILE *fichierEtudiants = fopen("listeEtudiants.txt", "r");
                if (fichierEtudiants == NULL)
                {
                    printf("Erreur lors de l'ouverture du fichier des étudiants.\n");
                    fclose(fichierPresence);
                    fclose(fichierSortie);
                    return;
                }

                char classe[TAILLE_MAX];
                while (fgets(ligne, sizeof(ligne), fichierEtudiants) != NULL)
                {
                    int codeEtudiant;
                    char prenomEtudiant[TAILLE_MAX];
                    char nomEtudiant[TAILLE_MAX];
                    char classeEtudiant[TAILLE_MAX];

                    if (sscanf(ligne, "%d %s %s %s", &codeEtudiant, prenomEtudiant, nomEtudiant, classeEtudiant) != 4)
                    {
                        continue;
                    }

                    if (code == codeEtudiant)
                    {
                        strcpy(classe, classeEtudiant);
                        break;
                    }
                }

                fclose(fichierEtudiants);

                fprintf(fichierSortie, "| %-5d | %-16s | %-16s | %-16s |\n", code, nom, prenom, classe);
            }
        }

        fprintf(fichierSortie, "-------------------------------------------------------------\n");

        fclose(fichierPresence);
        fclose(fichierSortie);

        printf("Le fichier %s a été généré avec succès!!.\n", nomFichier);
    }
    else if (verification == 2)
    {
        puts("Erreur : la date n'est pas encore arrivée XX");
    }
    else
    {
        puts("Erreur : format de date invalide");
    }
}

/// Gestion des messages //////

void envoyerMessageApprenants(const char *auteur) {
    char message[TAILLE_MAX];

    printf("Entrez votre message(max %d caractères):\n", TAILLE_MAX);
    getchar(); // Pour consommer le caractère '\n' restant après la saisie de l'authentification
    fgets(message, TAILLE_MAX, stdin);
    message[strcspn(message, "\n")] = '\0'; // Pour supprimer le '\n' ajouté par fgets

    FILE *fichierMessage = fopen("messageApprenants.txt", "a");
    if (fichierMessage == NULL) {
        printf("Erreur lors de l'ouverture du fichier de message.\n");
        return;
    }

    time_t maintenant = time(NULL);
    struct tm *tm_maintenant = localtime(&maintenant);
    fprintf(fichierMessage, "[%d-%02d-%02d %02d:%02d:%02d] %s : %s\n", tm_maintenant->tm_year + 1900, tm_maintenant->tm_mon + 1,
            tm_maintenant->tm_mday, tm_maintenant->tm_hour, tm_maintenant->tm_min, tm_maintenant->tm_sec, auteur, message);
    fclose(fichierMessage);

    printf("Message envoyé avec succès à tous les apprenants.\n");
}

// Pour afficher les messages des apprenants
void lireMessageApprenants() {
    FILE *fichierMessage = fopen("messageApprenants.txt", "r");
    if (fichierMessage == NULL) {
        printf("Aucun message disponible pour le moment.\n");
        return;
    }

    char ligne[TAILLE_MAX];
    int nbMessages = 0;

    printf("Nombre de messages: %d\n", nbMessages);
    while (fgets(ligne, TAILLE_MAX, fichierMessage) != NULL) {
        nbMessages++;
        printf("%s", ligne);
    }


    fclose(fichierMessage);
}

/// ----------Message par classe-------------- ///

// Fonction pour saisir un message et la classe des destinataires
Message saisirMessage() {
    Message message;
    printf("Entrez le message à envoyer : ");
    scanf("%s", message.message);
    printf("Entrez la classe des destinataires : ");
    scanf("%s", message.classe);
    return message;
}
// Fonction pour rechercher les apprenants dans la classe spécifiée et leur envoyer le message
void envoyerMessage(Message message) {
    FILE *fichierEtudiants = fopen("listeClasse.txt", "r");
    if (fichierEtudiants == NULL) {
        printf("Erreur lors de l'ouverture du fichier des étudiants.\n");
        return;
    }

    char ligne[TAILLE_MAX];
    while (fgets(ligne, sizeof(ligne), fichierEtudiants) != NULL) {
        char classeEtudiant[TAILLE_MAX];
        char prenom[TAILLE_MAX];
        char nom[TAILLE_MAX];
        int code;
        if (sscanf(ligne, "%d %s %s %s", &code, prenom, nom, classeEtudiant) != 4) {
            continue;
        }
        if (strcmp(classeEtudiant, message.classe) == 0) {
            // Ici vous pouvez envoyer le message à l'étudiant
            printf("Message envoyé à %s %s de la classe %s : %s\n", prenom, nom, classeEtudiant, message.message);
        }
    }

    fclose(fichierEtudiants);
}

// Fonction pour envoyer un message aux apprenants de chaque classe
void envoyerMessageAuxApprenants() {
    Message message = saisirMessage();
    envoyerMessage(message);
}


void gestionMenu()
{
    int choix;
    int sousMenuChoix;
    char c;
    do
   {
        sousMenuChoix=authentification();
        if(sousMenuChoix==2)
        {
            do
            {
                choix=afficheMenuApprenant();
                if(choix==1)
                {
                    marquerPresenceApprenant();
                }
                if (choix==3)
                {
                    lireMessageApprenants();
                }
                
            }while(choix!=4);
            
        }
        else if(sousMenuChoix==1)
        {
            do
            {
                choix=afficheMenuAdmin();
                if(choix==3)
                {
                    marquerPresenceAdmin();
                }
                if(choix==2)
                {
                    int p;
                    p=sousMenuAdmin();
                    if(p==1)
                    {
                        genererFichierPresences();
                    }
                    else
                    {
                        listePresencesParDate(); 
                    }
                }
                if (choix==4)
                {
                    char auteur;
                    int q = sousMenuMessage();
                    if (q==1)
                    {
                        envoyerMessageApprenants(&auteur);
                    }
                    else{
                        envoyerMessageAuxApprenants();
                        break;
                    }
                    
                    
                }
                
            }while(choix!=5);
            
        }
    c=continuer();
    }while(c!='n');
}




