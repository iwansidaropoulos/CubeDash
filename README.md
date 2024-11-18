# CubeDash

CubeDash est un projet de jeu d'arcade où le joueur contrôle un cube devant éviter un environnement dessiné.

## CMake

Le projet CubeDash utilise **CMake** pour la gestion de la compilation multiplateforme, permettant de le construire facilement sous **Windows**, **Linux**, et **macOS**.

### Compilation et Configuration Cross-Platform

Pour compiler CubeDash sur différentes plateformes, assurez-vous d'avoir les dépendances nécessaires (SFML, OpenCV, Freetype) et modifiez le fichier `CMakeLists.txt` :
   - Pour **macOS**, les bibliothèques SFML doivent être liées via `.dylib`.
   - Pour **Windows**, utilisez les `.dll` (lignes déjà commentées dans le fichier).
   - Pour **Linux**, utilisez les `.so` (également commentées).

Décommentez la section correspondant à votre plateforme et commentez les autres.