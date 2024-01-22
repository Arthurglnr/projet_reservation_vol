#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_AGENTS 100
#define MAX_CLIENTS 100
#define MAX_VOLS 50
#define MAX_RESERVATIONS 200

typedef struct {
    int numero;
    char nom[50];
    char prenom[50];
    char login[50];
    char motDePasse[50];
    char adresse[100];
    char numeroTelephone[15];
} Client;

typedef struct {
    int numeroVol;
    char dateDepart[20];
    char destination[50];
    char lieuDepart[50];
    int placesClasseA;
    int placesClasseB;
    float prixClasseA;
    float prixClasseB;
    int annulation;
    int reservations[MAX_RESERVATIONS];
    int nbReservationsA;
    int nbReservationsB;
} Vol;

typedef struct {
    int numeroReservation;
    int placesClasseA;
    int placesClasseB;
    int numeroVol;
    int numeroClient;
    float montantTotal;
    float montantAcompte;
} Reservation;

typedef struct {
    char nom[50];
    char prenom[50];
    char login[50];
    char motDePasse[50];
} Agent;

void connexion();
void recherche();
void nouveauCompte();
void connexionCompte();
int verifierLoginUnique(const char *login);
void menuClient();
void menuAgent();
void voirTableauAgents();
void voirTableauClients();
void ajouterNouvelAgent();
void creerVol();
void modifierPrixVol();
void consulterNbReservationsVol();
void annulerVol();
void voirMontantReservationsVol();
void voirMontantReservationsDestination();
void voirTableauVols();
void voirTableauReservations();
void modifierMotDePasseClient();
void creerReservationVol();
void supprimerReservation();
void voirListeReservations();
void rechercherReservationParDestination();
void payerReservation();

Client clients[MAX_CLIENTS] = {
    {1, "GOELLNER", "Arthur", "Arthur51", "azerty", "26 chemin des fleurs", "09876"}};
Vol vols[MAX_VOLS] = {
    {1, "2024/1/22", "Paris", "Lyon", 10, 15, 30, 20, 0, 0, 0, 0}};
Reservation reservations[MAX_RESERVATIONS];
Agent agents[MAX_AGENTS] = {
    {"Admin", "Admin", "Admin", "Admin"}};
int nbClients = 1;
int nbAgents = 1;
int nbReservations = 0;
int nbVols = 1;
int numeroClientConnecte = 0;

int main() {
    int choix;

    while (choix != 3) {
        printf("Menu Principal\n");
        printf("1. Connexion\n");
        printf("2. Recherche de vols\n");
        printf("3. Quitter\n");
        printf("Entrez votre choix : ");
        scanf("%d", &choix);

        switch (choix) {
            case 1:
                connexion();
                break;
            case 2:
                recherche();
                break;
            case 3:
                printf("Au revoir!\n");
                return 0;
            default:
                printf("Choix invalide. Veuillez reessayer.\n");
        }
    }

    return 0;
}

void connexion() {
    printf("Fonction de connexion.\n");
    int choix;

    while (1) {
        printf("Menu Connexion\n");
        printf("1. Creer un nouveau compte\n");
        printf("2. Se connecter a un compte existant\n");
        printf("3. Retour au menu principal\n");
        printf("Entrez votre choix : ");
        scanf("%d", &choix);

        switch (choix) {
            case 1:
                nouveauCompte();
                break;
            case 2:
                connexionCompte();
                break;
            case 3:
                return;
            default:
                printf("Choix invalide. Veuillez reessayer.\n");
        }
    }
}

int verifierLoginUnique(const char *login) {
    for (int i = 0; i < nbClients; i++) {
        if (strcmp(login, clients[i].login) == 0) {
            return 0;
        }
    }

    for (int i = 0; i < nbAgents; i++) {
        if (strcmp(login, agents[i].login) == 0) {
            return 0;
        }
    }

    return 1;
}

void nouveauCompte() {
    Client nouveauClient;
    char login[50];

    printf("Creation d'un nouveau compte client\n");

    int dernierNumeroClient = 0;
    for (int i = 0; i < nbClients; i++) {
        if (clients[i].numero > dernierNumeroClient) {
            dernierNumeroClient = clients[i].numero;
        }
    }
    nouveauClient.numero = dernierNumeroClient + 1;

    printf("Nom : ");
    scanf("%s", nouveauClient.nom);
    printf("Prenom : ");
    scanf("%s", nouveauClient.prenom);

    do {
        printf("Login (doit etre unique) : ");
        scanf("%s", login);
        if (!verifierLoginUnique(login)) {
            printf("Le login existe deja. Veuillez en choisir un autre.\n");
        }
    } while (!verifierLoginUnique(login));

    strcpy(nouveauClient.login, login);

    printf("Mot de passe : ");
    scanf("%s", nouveauClient.motDePasse);
    printf("Adresse : ");
    getchar();
    fgets(nouveauClient.adresse, sizeof(nouveauClient.adresse), stdin);
    printf("Numero de telephone : ");
    scanf("%s", nouveauClient.numeroTelephone);

    clients[nbClients++] = nouveauClient;

    printf("Compte client cree avec succes!\n");
}

void connexionCompte() {
    char login[50];
    char motDePasse[50];
    int estClient = 0;
    int estAgent = 0;

    printf("Connexion a un compte\n");
    printf("Login : ");
    scanf("%s", login);
    printf("Mot de passe : ");
    scanf("%s", motDePasse);

    for (int i = 0; i < nbClients; i++) {
        if (strcmp(login, clients[i].login) == 0 && strcmp(motDePasse, clients[i].motDePasse) == 0) {
            estClient = 1;
            numeroClientConnecte = clients[i].numero;
            break;
        }
    }

    for (int i = 0; i < nbAgents; i++) {
        if (strcmp(login, agents[i].login) == 0 && strcmp(motDePasse, agents[i].motDePasse) == 0) {
            estAgent = 1;
            break;
        }
    }

    if (estClient) {
        printf("Connexion reussie en tant que client.\n");
        menuClient();
    } else if (estAgent) {
        printf("Connexion reussie en tant qu'agent.\n");
        menuAgent();
    } else {
        printf("Login ou mot de passe incorrect. Reessayez.\n");
        connexion();
    }
}

void menuAgent() {
    int choix;

    while (1) {
        printf("Menu Agent\n");
        printf("1. Voir le tableau des agents\n");
        printf("2. Voir le tableau des clients\n");
        printf("3. Ajouter un nouvel agent\n");
        printf("4. Creer un vol\n");
        printf("5. Modifier le prix d'un vol\n");
        printf("6. Consulter le nombre de reservations pour un vol\n");
        printf("7. Annuler un vol\n");
        printf("8. Voir le montant des reservations pour un vol donne\n");
        printf("9. Voir le montant des reservations pour une destination\n");
        printf("10. Voir le tableau des vols\n");
        printf("11. Voir le tableau des reservations\n");
        printf("12. Retour au menu principal\n");
        printf("Entrez votre choix : ");
        scanf("%d", &choix);

        switch (choix) {
            case 1:
                voirTableauAgents();
                break;
            case 2:
                voirTableauClients();
                break;
            case 3:
                ajouterNouvelAgent();
                break;
            case 4:
                creerVol();
                break;
            case 5:
                modifierPrixVol();
                break;
            case 6:
                consulterNbReservationsVol();
                break;
            case 7:
                annulerVol();
                break;
            case 8:
                voirMontantReservationsVol();
                break;
            case 9:
                voirMontantReservationsDestination();
                break;
            case 10:
                voirTableauVols();
                break;
            case 11:
                voirTableauReservations();
                break;
            case 12:
                return; 
            default:
                printf("Choix invalide. Veuillez reessayer.\n");
        }
    }
}

void voirTableauAgents() {
    printf("Tableau des Agents :\n");

    for (int i = 0; i < nbAgents; i++) {
        printf("Agent %d :\n", i + 1);
        printf("Nom : %s\n", agents[i].nom);
        printf("Prenom : %s\n", agents[i].prenom);
        printf("Login : %s\n", agents[i].login);
        printf("Mot de passe : %s\n", agents[i].motDePasse);
        printf("\n");
    }
}

void voirTableauClients() {
    printf("Tableau des Clients :\n");

    for (int i = 0; i < nbClients; i++) {
        printf("Client %d :\n", i + 1);
        printf("Nom : %s\n", clients[i].nom);
        printf("Prenom : %s\n", clients[i].prenom);
        printf("Login : %s\n", clients[i].login);
        printf("Mot de passe : %s\n", clients[i].motDePasse);
        printf("\n");
    }
}

void voirTableauReservations() {
    printf("Tableau des Reservations :\n");

    for (int i = 0; i < nbReservations; i++) {
        printf("Reservation %d :\n", i + 1);
        printf("Numero de la reservation : %d\n", reservations[i].numeroReservation);
        printf("Places en classe A : %d\n", reservations[i].placesClasseA);
        printf("Places en classe B : %d\n", reservations[i].placesClasseB);
        printf("Numero du client : %d\n", reservations[i].numeroClient);
        printf("Montant total : %f\n", reservations[i].montantTotal);
        printf("Montant de l'acompte : %f\n", reservations[i].montantAcompte);
        printf("\n");
    }
}

void voirTableauVols() {
    printf("Tableau des Vols :\n");

    for (int i = 0; i < nbVols; i++) {
        printf("Vol %d :\n", i + 1);
        printf("Numero du vol : %d\n", vols[i].numeroVol);
        printf("Date de depart : %s\n", vols[i].dateDepart);
        printf("Destination : %s\n", vols[i].destination);
        printf("Lieu de depart : %s\n", vols[i].lieuDepart);
        printf("Places en classe A : %d\n", vols[i].placesClasseA);
        printf("Places en classe B : %d\n", vols[i].placesClasseB);
        printf("Prix en classe A : %f\n", vols[i].prixClasseA);
        printf("Prix en classe B : %f\n", vols[i].prixClasseB);
        printf("Annulation : %d\n", vols[i].annulation);
        printf("Nombre de reservations en classe A : %d\n", vols[i].nbReservationsA);
        printf("Nombre de reservations en classe B : %d\n", vols[i].nbReservationsB);
        printf("\n");
    }
}

void menuClient() {
    int choix;

    while (1) {
        printf("Menu Client\n");
        printf("1. Recherche de vols\n");
        printf("2. Modifier le mot de passe\n");
        printf("3. Creer une reservation de vol\n");
        printf("4. Supprimer une reservation\n");
        printf("5. Voir la liste de mes reservations\n");
        printf("6. Rechercher une reservation par destination\n");
        printf("7. Payer une reservation\n");
        printf("8. Retour au menu principal\n");
        printf("Entrez votre choix : ");
        scanf("%d", &choix);

        switch (choix) {
            case 1:
                recherche();
                break;
            case 2:
                modifierMotDePasseClient();
                break;
            case 3:
                creerReservationVol();
                break;
            case 4:
                supprimerReservation();
                break;
            case 5:
                voirListeReservations();
                break;
            case 6:
                rechercherReservationParDestination();
                break;
            case 7:
                payerReservation();
                break;
            case 8:
                printf("Retour au menu principal.\n");
                numeroClientConnecte = 0;
                return;
            default:
                printf("Choix invalide. Veuillez reessayer.\n");
        }
    }
}

void recherche() {
    char dateRecherche[20];
    char destinationRecherche[50];
    char lieuDepartRecherche[50];

    printf("Recherche de vols\n");

    printf("Entrez la date de depart (ou appuyez sur Entree pour ignorer) : \n");
    fgets(dateRecherche, sizeof(dateRecherche), stdin);
    dateRecherche[strcspn(dateRecherche, "\n")] = '\0';
    getchar(); 

    printf("Entrez la destination (ou appuyez sur Entree pour ignorer) : \n");
    fgets(destinationRecherche, sizeof(destinationRecherche), stdin);
    destinationRecherche[strcspn(destinationRecherche, "\n")] = '\0'; 
    getchar();  

    printf("Entrez le lieu de depart (ou appuyez sur Entree pour ignorer) : \n");
    fgets(lieuDepartRecherche, sizeof(lieuDepartRecherche), stdin);
    lieuDepartRecherche[strcspn(lieuDepartRecherche, "\n")] = '\0';
    getchar(); 

    printf("Resultats de la recherche :\n");

    for (int i = 0; i < nbVols; i++) {
        Vol vol = vols[i];

        int correspondanceDate = (dateRecherche[0] == '\0') || (strcmp(dateRecherche, vol.dateDepart) == 0);
        int correspondanceDestination = (destinationRecherche[0] == '\0') || (strcmp(destinationRecherche, vol.destination) == 0);
        int correspondanceLieuDepart = (lieuDepartRecherche[0] == '\0') || (strcmp(lieuDepartRecherche, vol.lieuDepart) == 0);

        if (correspondanceDate && correspondanceDestination && correspondanceLieuDepart) {
            printf("Numero du vol : %d\n", vol.numeroVol);
            printf("Destination : %s\n", vol.destination);
            printf("Lieu de depart : %s\n", vol.lieuDepart);
            printf("Date de depart : %s\n", vol.dateDepart);
            printf("Prix en classe A : %f euros\n", vol.prixClasseA);
            printf("Prix en classe B : %f euros\n", vol.prixClasseB);
            printf("\n");
        }
    }
}

void ajouterNouvelAgent() {
    Agent nouvelAgent;
    char login[50];

    printf("Ajout d'un nouvel agent\n");

    printf("Nom : ");
    scanf("%s", nouvelAgent.nom);
    printf("Prenom : ");
    scanf("%s", nouvelAgent.prenom);

    do {
        printf("Login (doit etre unique) : ");
        scanf("%s", login);
        if (!verifierLoginUnique(login)) {
            printf("Le login existe deja. Veuillez en choisir un autre.\n");
        }
    } while (!verifierLoginUnique(login));

    strcpy(nouvelAgent.login, login);

    printf("Mot de passe : ");
    scanf("%s", nouvelAgent.motDePasse);

    agents[nbAgents++] = nouvelAgent;

    printf("Nouvel agent ajoute avec succes!\n");
}

void creerVol() {
    Vol nouveauVol;
    char destination[50];
    char lieuDepart[50];

    printf("Creation d'un nouveau vol\n");

    int dernierNumeroVol = 0;
    for (int i = 0; i < nbVols; i++) {
        if (vols[i].numeroVol > dernierNumeroVol) {
            dernierNumeroVol = vols[i].numeroVol;
        }
    }
    nouveauVol.numeroVol = dernierNumeroVol + 1;

    printf("Date de depart : ");
    scanf("%s", nouveauVol.dateDepart);

    printf("Destination : ");
    scanf("%s", destination);
    strcpy(nouveauVol.destination, destination);

    printf("Lieu de depart : ");
    scanf("%s", lieuDepart);
    strcpy(nouveauVol.lieuDepart, lieuDepart);

    printf("Nombre de places en classe A : ");
    scanf("%d", &nouveauVol.placesClasseA);

    printf("Nombre de places en classe B : ");
    scanf("%d", &nouveauVol.placesClasseB);

    printf("Prix en classe A : ");
    scanf("%f", &nouveauVol.prixClasseA);

    printf("Prix en classe B : ");
    scanf("%f", &nouveauVol.prixClasseB);

    nouveauVol.annulation = 0; 
    nouveauVol.nbReservationsA = 0; 
    nouveauVol.nbReservationsB = 0;

    vols[nbVols++] = nouveauVol;

    printf("Nouveau vol cree avec succes! Numero de vol : %d\n", nouveauVol.numeroVol);
}

void modifierPrixVol() {
    int numeroVol;
    int indexVol = -1;

    printf("Modification du prix d'un vol\n");

    printf("Numero de vol : ");
    scanf("%d", &numeroVol);

    for (int i = 0; i < nbVols; i++) {
        if (vols[i].numeroVol == numeroVol) {
            indexVol = i;
            break;
        }
    }

    if (indexVol == -1) {
        printf("Aucun vol correspondant trouve. Retour au menu Agent.\n");
        return;
    }

    if (vols[indexVol].annulation == 1) {
        printf("Ce vol est annule. Aucun prix a modifier.\n");
        return;
    }

    printf("Prix actuel en classe A : %f\n", vols[indexVol].prixClasseA);
    printf("Prix actuel en classe B : %f\n", vols[indexVol].prixClasseB);

    printf("Nouveau prix en classe A : ");
    scanf("%f", &vols[indexVol].prixClasseA);

    printf("Nouveau prix en classe B : ");
    scanf("%f", &vols[indexVol].prixClasseB);

    printf("Prix du vol (numero %d) modifie avec succes!\n", numeroVol);
}

void consulterNbReservationsVol() {
    int numeroVol;
    int indexVol = -1; 

    printf("Consultation du nombre de reservations pour un vol\n");

    printf("Numero de vol : ");
    scanf("%d", &numeroVol);

    for (int i = 0; i < nbVols; i++) {
        if (vols[i].numeroVol == numeroVol) {
            indexVol = i;
            break;
        }
    }

    if (indexVol == -1) {
        printf("Aucun vol correspondant trouve.\n");
    } else if (vols[indexVol].annulation == 1) {
        printf("Ce vol est annule. Aucune reservation a consulter.\n");
    } else {
        printf("Nombre de reservations en classe A pour ce vol : %d\n", vols[indexVol].nbReservationsA);
        printf("Nombre de reservations en classe B pour ce vol : %d\n", vols[indexVol].nbReservationsB);
    }
}

void annulerVol() {
    int numeroVol;
    int indexVol = -1; 

    printf("Annulation d'un vol\n");

    printf("Numero de vol : ");
    scanf("%d", &numeroVol);

    for (int i = 0; i < nbVols; i++) {
        if (vols[i].numeroVol == numeroVol) {
            indexVol = i;
            break;
        }
    }

    if (indexVol == -1) {
        printf("Aucun vol correspondant trouve. Retour au menu Agent.\n");
        return;
    }

    vols[indexVol].annulation = 1;

    printf("Le vol (numero %d) a ete annule avec succes!\n", numeroVol);
}

void voirMontantReservationsVol() {
    int numeroReservation;

    printf("Consultation du montant d'une reservation pour un vol\n");

    printf("Numero de reservation : ");
    scanf("%d", &numeroReservation);

    for (int i = 0; i < nbReservations; i++) {
        if (reservations[i].numeroReservation == numeroReservation) {
            int numeroClient = reservations[i].numeroClient;
            float montantTotal = reservations[i].montantTotal;

            for (int j = 0; j < nbClients; j++) {
                if (clients[j].numero == numeroClient) {
                    printf("Montant total de la reservation : %f\n", montantTotal);
                    printf("Cette reservation appartient a : %s %s\n", clients[j].prenom, clients[j].nom);
                    return;
                }
            }

            printf("Numero de client associe a la reservation non trouve. Retour au menu.\n");
            return;
        }
    }

    printf("Aucune reservation correspondante trouvee. Retour au menu.\n");
}

void voirMontantReservationsDestination() {


    char destinationRecherchee[50];
    float montantTotalDestination = 0.0;
    int destinationTrouvee = 0; 

    printf("Consultation du montant total des reservations pour une destination\n");

    printf("Entrez la destination recherchee : ");
    scanf("%s", destinationRecherchee);

    for (int i = 0; i < nbVols; i++) {
        if (strcmp(destinationRecherchee, vols[i].destination) == 0 && vols[i].annulation == 0) {
            destinationTrouvee = 1;

            for (int j = 0; j < vols[i].nbReservationsA + vols[i].nbReservationsB; j++) {
                int numeroReservation = vols[i].reservations[j];

                for (int k = 0; k < nbReservations; k++) {
                    if (reservations[k].numeroReservation == numeroReservation) {
                        montantTotalDestination += reservations[k].montantTotal;
                        break;
                    }
                }
            }
        }
    }

    if (!destinationTrouvee) {
        printf("Aucun vol avec la destination '%s' n'a ete trouve.\n", destinationRecherchee);
    } else if (montantTotalDestination == 0.0) {
        printf("La destination '%s' a comme montant total de 0euro.\n", destinationRecherchee);
    } else {
        printf("Montant total des reservations pour la destination '%s' : %f\n", destinationRecherchee, montantTotalDestination);
    }
}

void modifierMotDePasseClient() {
    char nouveauMotDePasse[50];

    printf("Modification du mot de passe\n");

    printf("Nouveau mot de passe : ");
    scanf("%s", nouveauMotDePasse);

    for (int i = 0; i < nbClients; i++) {
        if (clients[i].numero == numeroClientConnecte) {
            strcpy(clients[i].motDePasse, nouveauMotDePasse);
            printf("Mot de passe modifie avec succes!\n");
            return; 
        }
    }

    printf("Client introuvable. Mot de passe non modifie.\n");
}

void creerReservationVol() {
    int numeroVol;
    int placesClasseA;
    int placesClasseB;

    printf("Creation d'une nouvelle reservation de vol\n");

    printf("Numero du vol : ");
    scanf("%d", &numeroVol);

    int indexVol = -1;
    for (int i = 0; i < nbVols; i++) {
        if (vols[i].numeroVol == numeroVol) {
            indexVol = i;
            break;
        }
    }

    if (indexVol == -1) {
        printf("Vol introuvable. Reservation non creee.\n");
        return;
    }

    printf("Nombre de places en classe A : ");
    scanf("%d", &placesClasseA);

    printf("Nombre de places en classe B : ");
    scanf("%d", &placesClasseB);

    int placesDispoA = vols[indexVol].placesClasseA - vols[indexVol].nbReservationsA;
    int placesDispoB = vols[indexVol].placesClasseB - vols[indexVol].nbReservationsB;

    if (placesClasseA > placesDispoA || placesClasseB > placesDispoB) {
        printf("Nombre de places demandees indisponible. Reservation non creee.\n");
        return;
    }

    int dernierNumeroReservation = 0;
    for (int i = 0; i < nbReservations; i++) {
        if (reservations[i].numeroReservation > dernierNumeroReservation) {
            dernierNumeroReservation = reservations[i].numeroReservation;
        }
    }

    Reservation nouvelleReservation;
    nouvelleReservation.numeroReservation = dernierNumeroReservation + 1;
    nouvelleReservation.placesClasseA = placesClasseA;
    nouvelleReservation.placesClasseB = placesClasseB;
    nouvelleReservation.numeroVol = numeroVol;
    nouvelleReservation.numeroClient = numeroClientConnecte;

    float montantTotal = (placesClasseA * vols[indexVol].prixClasseA) + (placesClasseB * vols[indexVol].prixClasseB);
    nouvelleReservation.montantTotal = montantTotal;
    nouvelleReservation.montantAcompte = 0.0; 

    reservations[nbReservations++] = nouvelleReservation;

    vols[indexVol].nbReservationsA += placesClasseA;
    vols[indexVol].nbReservationsB += placesClasseB;

    printf("Reservation creee avec succes! Montant total a payer : %f euros\n", montantTotal);
}

void supprimerReservation() {
    int numeroReservation;

    printf("Suppression d'une reservation\n");

    printf("Numero de la reservation a supprimer : ");
    scanf("%d", &numeroReservation);

    int indexReservation = -1;
    for (int i = 0; i < nbReservations; i++) {
        if (reservations[i].numeroReservation == numeroReservation && reservations[i].numeroClient == numeroClientConnecte) {
            indexReservation = i;
            break;
        }
    }

    if (indexReservation == -1) {
        printf("Reservation introuvable ou non autorisee. Suppression non effectuee.\n");
        return;
    }

    int numeroVol = reservations[indexReservation].numeroVol;
    int placesClasseA = reservations[indexReservation].placesClasseA;
    int placesClasseB = reservations[indexReservation].placesClasseB;

    for (int i = 0; i < nbVols; i++) {
        if (vols[i].numeroVol == numeroVol) {
            vols[i].nbReservationsA -= placesClasseA;
            vols[i].nbReservationsB -= placesClasseB;
            break;
        }
    }

    for (int i = indexReservation; i < nbReservations - 1; i++) {
        reservations[i] = reservations[i + 1];
    }

    nbReservations--;

    printf("Reservation supprimee avec succes!\n");
}

void voirListeReservations() {
    printf("Liste de vos reservations :\n");

    for (int i = 0; i < nbReservations; i++) {
        if (reservations[i].numeroClient == numeroClientConnecte) {
            printf("Numero de reservation : %d\n", reservations[i].numeroReservation);
            printf("Places en classe A : %d\n", reservations[i].placesClasseA);
            printf("Places en classe B : %d\n", reservations[i].placesClasseB);
            printf("Numero de vol : %d\n", reservations[i].numeroVol);
            printf("Numero de client : %d\n", reservations[i].numeroClient);
            printf("Montant total : %f\n", reservations[i].montantTotal);
            printf("Montant de l'acompte : %f\n", reservations[i].montantAcompte);
            printf("\n");
        }
    }
}

void rechercherReservationParDestination() {
    char destinationRecherche[50];

    printf("Recherche de reservations par destination\n");
    printf("Destination : ");
    scanf("%s", destinationRecherche);

    printf("Reservations pour la destination '%s' :\n", destinationRecherche);

    for (int i = 0; i < nbReservations; i++) {
        int numeroVol = reservations[i].numeroVol;
        if (reservations[i].numeroClient == numeroClientConnecte) {
            if (strcmp(destinationRecherche, vols[numeroVol].destination) == 0) {
                printf("Numero de reservation : %d\n", reservations[i].numeroReservation);
                printf("Places en classe A : %d\n", reservations[i].placesClasseA);
                printf("Places en classe B : %d\n", reservations[i].placesClasseB);
                printf("Numero de vol : %d\n", numeroVol);
                printf("Numero de client : %d\n", reservations[i].numeroClient);
                printf("Montant total : %f\n", reservations[i].montantTotal);
                printf("Montant de l'acompte : %f\n", reservations[i].montantAcompte);
                printf("\n");
            }
        }
    }
}

void payerReservation() {
    int numeroReservation;
    float montantRestant;

    printf("Paiement d'une reservation\n");
    printf("Numero de reservation : ");
    scanf("%d", &numeroReservation);

    for (int i = 0; i < nbReservations; i++) {
        if (reservations[i].numeroReservation == numeroReservation && reservations[i].numeroClient == numeroClientConnecte) {
            montantRestant = reservations[i].montantTotal - reservations[i].montantAcompte;

            if (montantRestant == 0) {
                printf("Aucun paiement requis, la reservation est deja entierement payee.\n");
                return;
            }

            printf("Montant restant a payer : %f euros\n", montantRestant);

            float montantPaiement;
            do {
                printf("Montant a deposer (0 pour annuler) : ");
                scanf("%f", &montantPaiement);

                if (montantPaiement < 0) {
                    printf("Montant invalide, veuillez entrer un montant positif ou 0 pour annuler.\n");
                } else if (montantPaiement == 0) {
                    printf("Paiement annule.\n");
                    return;
                } else if (montantPaiement > montantRestant) {
                    printf("Montant trop eleve, veuillez entrer un montant inferieur ou egal a %f euros.\n", montantRestant);
                }
            } while (montantPaiement < 0 || montantPaiement > montantRestant);

            reservations[i].montantAcompte += montantPaiement;
            printf("Paiement de %f euros effectue avec succes.\n", montantPaiement);
            printf("Montant restant a payer : %f euros\n", montantRestant - montantPaiement);
            return;
        }
    }

    printf("Reservation introuvable ou non autorisee. Veuillez verifier le numero de reservation.\n");
}