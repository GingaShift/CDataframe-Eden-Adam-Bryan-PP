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


- Reglages à effectuer impérativement pour pouvoir tester le code sous Visual Studio 2022:

   1) Remplacer scanf_s par scanf:

      1.1) Ouvrez votre projet dans Visual Studio 2022.

      1.2) Cliquez avec le bouton droit sur votre projet dans l'Explorateur de solutions.

      1.3) Sélectionnez "Propriétés" dans le menu contextuel.

      1.4) Dans les propriétés du projet, accédez à "Configuration Properties" > "C/C++" > "General".

      1.5) Dans la section "Use of Specific Functions", définissez "Security Development Lifecycle (SDL) checks" sur "No (/GS-)".

      1.6) Cliquez sur "Appliquer" puis sur "OK" pour enregistrer les modifications.

   2) Correction de l'erreur E1072 "une déclaration ne peut pas avoir d'étiquette":

      Modifier la norme ISO retenu pour le langage C dans les paramètres de projet de Visual Studio.
      Dans la barre de menu, choisir Projet -> Propriétés du projet -> Propriétés de configuration -> C/C++ ->
      Langage -> Norme du langage C.
   
      Choisir "Norme ISO C17 (2018) (/std:c17)".

      Notes:
        Par défaut c'est "Valeur par défaut (MSVC hérité)" qui est utilisé.
        La "Norme ISO C11 (/std:c11)" fonctionne aussi... 
      
                                                 =======
    DATAFRAME v.2:

       Toutes les fonctions seront anglicisées afin de les differencier facilement de celles du chap 1, entierement en français.

       Pour chaque fichier .h et .c du projet, les lignes de codes concernant chap 1 et chap 2 sont délimitées par des balises
       nommées comme suit: 

           #pragma region CDataframe 1

               ...Code CDataframe1 du chap 1

           #pragma endregion Fin CDataframe 1

           #pragma region CDataframe 2

               ...Code CDataframe2 du chap 2 et suivant

           #pragma endregion Fin CDataframe 2

                                                =======
     