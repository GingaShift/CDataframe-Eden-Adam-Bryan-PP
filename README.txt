# CDataframe

- Noms et prénoms des membres de l'équipe projet :
 
   - Eden Elfassy
   - Bryan Tewouda
   - Adam Assayag


- Lien direct vers le dépôt Git de votre projet :
  
   https://github.com/eden2807/CDataframe-Eden-Adam-Bryan-PP


- Fonctionnalités principales de l'application :

   - Ajouter une colonne / créer une colonne
   
   - Inserer une valeur dans la colonne choisit 
   
   - Afficher une colonne 
   
   - renommer une colonne (+ comparateur de châine de caractère pour vérifier que 2 colonnes n'ont pas le même nom)
   
   - Création d'un CDataframe
   
   - possibilité d'obtenir le nombre de lignes présent dans un CDataframe
   
   - possibilité d'afficher l'ensemble des colonnes d'un CDataframe 
   

- Instructions d'exécution du code :

   1) Installer Visual Studio 2022 Community Edition avec, au minimum, la charge de travail C++

   2) Lancer Visual Studio et choisir "Cloner un dépôt"

   3) Dans la zone "Emplacement du dépôt", entrer l'adresse du projet suivante:
      https://github.com/eden2807/CDataframe-Eden-Adam-Bryan-PP

   4) Dans la zone "Chemin", choisir un dossier qui hebergera le projet localement

   5) Cliquer ensuite sur le bouton "Cloner"

   6) Lancer le projet en appuyant sur la touche F5

  
   void ajouterLigne(DATAFRAME *dataframe, int *valeurs) {
    /* On suppose que toutes les colonnes ont la même taille */
    if (dataframe->taille > 0 && dataframe->colonnes[0]->taille >= 0) {
        int nouvelle_taille = dataframe->colonnes[0]->taille + 1;

        /* Allouer de la mémoire pour la nouvelle ligne dans chaque colonne */
        for (int i = 0; i < dataframe->taille; i++) {
            dataframe->colonnes[i]->valeurs = realloc(dataframe->colonnes[i]->valeurs, nouvelle_taille * sizeof(int));
            if (dataframe->colonnes[i]->valeurs == NULL) {
                printf("Erreur : Échec de l'allocation de mémoire.\n");
                return 1;
            }
        }

        /* Copier les valeurs dans la nouvelle ligne */
        for (int i = 0; i < dataframe->taille; i++) {
            dataframe->colonnes[i]->valeurs[nouvelle_taille - 1] = valeurs[i];
        }

        /* Mettre à jour la taille de la colonne */
        for (int i = 0; i < dataframe->taille; i++) {
            dataframe->colonnes[i]->taille = nouvelle_taille;
        }
    } else {
        printf("Erreur : Le dataframe est vide ou mal initialisé.\n");
    }
}


void supprimerLigne(DATAFRAME *dataframe, int indiceLigne) {
    /* On suppose que toutes les colonnes ont la même taille */
    if (dataframe->taille > 0 && dataframe->colonnes[0]->taille > 0) {
        int nouvelle_taille = dataframe->colonnes[0]->taille - 1;

        /* Supprimer la ligne de chaque colonne */
        for (int i = 0; i < dataframe->taille; i++) {
            for (int j = indiceLigne; j < nouvelle_taille; j++) {
                dataframe->colonnes[i]->valeurs[j] = dataframe->colonnes[i]->valeurs[j + 1];
            }
        }

        /* Mettre à jour la taille de la colonne */
        for (int i = 0; i < dataframe->taille; i++) {
            dataframe->colonnes[i]->taille = nouvelle_taille;
        }
    } else {
        printf("Erreur : Le dataframe est vide ou mal initialisé.\n");
    }
}

int nombreDeLignes(DATAFRAME *dataframe) {
    /* On suppose que toutes les colonnes ont la même taille */
    if (dataframe->taille > 0 && dataframe->colonnes[0]->taille > 0) {
        return dataframe->colonnes[0]->taille;
    } else {
        return 0;
    }
}
