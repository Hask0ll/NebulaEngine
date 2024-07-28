# Nebula

Bienvenue sur Nebula, un moteur de jeu 3D custom.

## Prérequis
Pour commencer à utiliser Nebula, assurez-vous d'avoir installé:

- Visual Studio 2022 ou supérieur
- CMake 3.15 ou supérieur
- Git pour cloner le dépôt

## Installation
### Étape 1: Cloner le dépôt
Ouvrez un terminal et clonez le dépôt avec la commande suivante:

```
git clone (https://github.com/Hask0ll/NebulaEngine.git)
cd NebulaEngine
```
### Avec Bash

#### Etape 2: Installer les dépendances avec vcpkg
Assurez-vous d'avoir *vcpkg* installé et intégré à votre environnement de développement. Exécutez ensuite:

```
vcpkg install
```

Cela installera toutes les dépendances nécessaires pour Nebula.

#### Étape 3: Construire avec CMake
Générez les fichiers de projet pour *Visual* *Studio* en exécutant:

```
cmake -S . -B build -DCMAKE_TOOLCHAIN_FILE=[vcpkg root]/scripts/buildsystems/vcpkg.cmake
cmake --build build
```

### Avec Visual Studio

#### Étape 2: Construire avec CMake
Générez les fichiers de projet pour *Visual* *Studio* en appuyant sur le bouton : **Générer**

### Étape 4: Lancer Nebula
Après la construction, vous pouvez lancer le moteur de jeu en ouvrant le projet dans Visual Studio et en démarrant le projet.

## Documentation
Pour plus d'informations sur l'utilisation et le développement avec Nebula, veuillez consulter la documentation disponible dans le dossier docs en utilisant doxygen.
```
doxygen NebulaDoc
```

Une fois la documentation généré lancer **Index.html** depuis l'explorateur de fichier.

## Licence
Nebula est distribué sous la licence **Apache-2.0 license**. Voir le fichier LICENSE pour plus d'informations.

By Haskoll (J'ai menti c'est ChatGPT).
