<h1 align="center">📊 CDataframe</h1>
<p align="center"><i>Un mini-tableur C à la sauce DataFrame — puissance, structure et fun en C pur !</i></p>

<p align="center">
  <img src="https://img.shields.io/badge/Language-C-blue?logo=c&logoColor=white" alt="C">
  <img src="https://img.shields.io/badge/Platform-Windows-lightgrey?logo=windows&logoColor=white" alt="Windows">
  <img src="https://img.shields.io/badge/Project-Etudiant-purple" alt="Projet étudiant">
  <img src="https://img.shields.io/badge/Version-1.0.1-success" alt="Version">
</p>

---

## 👥 Équipe projet

- 👤 Eden Elfassy  
- 👤 Bryan Tewouda  
- 👤 Adam Assayag  

---

## 🔗 Dépôt GitHub

📎 [Accéder au dépôt](https://github.com/eden2807/CDataframe-Eden-Adam-Bryan-PP)

📂 **Exécutable Windows** disponible ici :  
`/x64/Release/CDataframe.exe`

---

## 🚀 Fonctionnalités principales

> ⚙️ Manipulez des données structurées comme dans un DataFrame Python… mais en C !

✅ Création d’un CDataframe  
✅ Ajout/suppression de colonnes  
✅ Insertion de valeurs dans des cellules  
✅ Affichage partiel ou complet du tableau  
✅ Recherche de valeurs, renommage de colonnes, tri par colonnes  
✅ Génération de statistiques sur les valeurs (nombre d’occurrences, etc.)  
✅ Sauvegarde au format `.csv`

🆕 Version 2.0 (en cours) avec **fonctions anglicisées** et **structuration modulaire** (`#pragma region` pour séparer les versions).

---

## 🛠️ Installation (Windows + Visual Studio 2022)

1. 📥 Installer [Visual Studio 2022 Community](https://visualstudio.microsoft.com/fr/vs/community/)  
   ➕ Inclure **la charge de travail C++**

2. 🧲 Cloner le dépôt :  
   Menu **"Cloner un dépôt"** → URL :  

3. 📁 Choisir un dossier local et **cloner**

4. ▶️ Appuyer sur **F5** pour exécuter le projet

5. 📂 Pour rouvrir le projet : double-cliquer sur `CDataframe.sln`

---

## ⚠️ Réglages importants sous Visual Studio

### ✅ Corriger `scanf_s` :
1. Clic droit sur le projet → **Propriétés**  
2. Aller dans : `C/C++ > General > SDL checks` → **No (/GS-)**

### ✅ Corriger l’erreur `E1072` :
1. Aller dans : `C/C++ > Langage > Norme du langage C`  
2. Choisir : `Norme ISO C17 (/std:c17)` ✅  
_(La norme C11 fonctionne aussi)_

---

## 🧪 Démo express

🎬 **Tester rapidement en 3 étapes :**

1. Lancer le programme → Menu d'accueil
2. Taper `11` → Créer un CDataframe vide (donner un nom)
3. Taper `15` → Remplissage automatique avec colonnes et données

🎯 Ensuite :
- `21` → Afficher tout le Dataframe  
- `22` → Afficher les 10 premières lignes (`-1` colonnes, `10` lignes)  
- 🔍 Testez les options : trier, chercher, ajouter une colonne, renommer, sauvegarder…

❌ **Ne surtout pas lancer la commande `38`…**  
Vous êtes prévenus. 😈

---

## 💡 À propos du code

🔀 Les versions sont séparées :

```c
#pragma region CDataframe 1
// Fonctions version chap. 1 (français)
#pragma endregion

#pragma region CDataframe 2
// Fonctions version chap. 2+ (anglicisées)
#pragma endregion
