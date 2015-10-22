# Usages

./quick <fichier>
./quickSeuil <fichier> <seuil>
./quickRandomSeuil <fichier> <seuil>
./quickRandom <fichier>
./bubble <fichier>

Afin d'executer l'ensemble des tests il faut que les données fournises soient placées dans le dossier "data" et rouler le script "./benchmark.sh".

# Exemple

Générer une liste d'entier si on en a pas une sous la main:
```shell
shuf -i 1-100000 -n 10000 > data
```

```shell
./quickSeuil data 10
```

