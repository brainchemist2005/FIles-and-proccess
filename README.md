Redémarrage automatique en cas de panne
=======================================

## Dépendances

Ubuntu:

```
  apt-get install build-essential cmake
```

Fedora:

```
  yum gcc gcc-c++ automake glibc-devel cmake
```

Il est également recommandé d'utiliser un IDE, tel que QtCreator, pour programmer la solution.

Compilation manuelle:

```
cmake -S . -B build
cd build
make 
make test
```
