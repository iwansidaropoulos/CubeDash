# CubeDash

CubeDash est un projet de jeu d'arcade où le joueur contrôle un cube devant éviter un environnement dessiné.

## CMake

Le projet CubeDash utilise **CMake** pour la gestion de la compilation multiplateforme, permettant de le construire facilement sous **Windows**, **Linux**, et **macOS**.

### Compilation et Configuration Cross-Platform

Pour compiler CubeDash sur différentes plateformes, assurez-vous d'avoir les dépendances nécessaires (SFML, OpenCV, Freetype) et suivez les étapes ci-dessous :

1. **Modification de `CMakeLists.txt`** :
   - **macOS** : Les bibliothèques SFML doivent être liées via `.dylib` (sections déjà actives dans `CMakeLists.txt`).
   - **Windows** : Décommentez les lignes utilisant les `.dll` dans `CMakeLists.txt` et commentez les autres.
   - **Linux** : Décommentez les lignes utilisant les `.so` dans `CMakeLists.txt` et commentez les autres.

2. **Ajout des bibliothèques nécessaires** :
   - **Téléchargement des fichiers SFML** : 
     - Les fichiers SFML requis pour chaque plateforme peuvent être téléchargés depuis [le site officiel de SFML](https://www.sfml-dev.org/download-fr.php).
   - **Windows** :
     - Copiez les fichiers `.dll` nécessaires dans le dossier `dependencies/lib`.
   - **Linux** :
     - Copiez les fichiers `.so` nécessaires dans `dependencies/lib`.

Avec ces étapes, CubeDash sera correctement configuré pour votre plateforme.
