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

   void ajouter_ligne_valeur(DATAFRAME1* dataframe, int nombre_de_ligne_de_valeurs, int valeur) {
    for (int i = 0; i < nombre_de_ligne_de_valeurs; ++i) {
        for (int j = 0; j < dataframe->taille; j++) {
            printf("Element [%d][%d] : ", i, j);
            scanf("%d", &dataframe[i * dataframe->taille + j]);
        }
    }
    printf("Dataframe rempli :\n");
    for (int i = 0; i < nombre_de_ligne_de_valeurs; i++) {
        for (int j = 0; j < dataframe->taille; j++) {
            printf("%d ", dataframe[i * dataframe->taille + j]);
        }
        printf("\n");
    }
}

void supprimer_ligne_de_valeur(DATAFRAME* dataframe, int ligne_a_supprimer, int nombre_de_ligne_de_valeurs) {
    if (ligne_a_supprimer < 0 || ligne_a_supprimer >= nombre_de_ligne_de_valeurs) {
        printf("Erreur : L'indice de ligne à supprimer est invalide.\n");
        return;
    }
    // Décalage des lignes vers le haut pour supprimer la ligne sélectionnée
    for (int i = ligne_a_supprimer; i < nombre_de_ligne_de_valeurs - 1; i++) {
        for (int j = 0; j < dataframe->taille; j++) {
            dataframe[i * dataframe->taille + j] = dataframe[(i + 1) * dataframe->taille + j];
        }
    }
}
