# Dépôt du projet bonus SINF1252

### Introduction 

Pour ce projet bonus, vous êtes invités à sélectionner un exercice parmi ceux proposés dans le fichier exercices.md. Vous devrez alors réaliser des tests unitaires à l'aide de CUnit pour cet exercice. Le but est que ces tests soient assez complets pour qu'ils puissent être intégrés à INGInious et permettent de vérifier si la solution d'un étudiant à cet exercice est correct ou non. Si les tests fournis par l'étudiant sont corrects et assez exhaustifs au vu de l'exercice choisi, celui-ci peut gagner 1 point bonus pour le cours SINF1252.

Le mode opératoire est le suivant :
* Choisissez un exercice qui n'est pas encore réservé dans le fichier exercices.md. Soumettez alors un Pull-Request (PR) pour indiquer que vous réservez cet exercice. Modifiez la mention « *RESERVATION* : <1 personne> » par « *RESERVATION* : Prénom Nom Noma » de l'exercice. Á partir du moment où vous réservez un exercice, vous vous engagez à le réaliser. Si après un temps raisonnable aucune preuve de travail de votre part n'a été montrée, la réservation peut être annulée au profit de quelqu'un d'autre.
* Écrivez des tests unitaires à l'aide de CUnit pour l'exercice. Vous êtes invités à être le plus exhaustif possible dans vos tests unitaires. En outre, des idées de tests à réaliser vous sont imposés. Ceux-ci sont généralement des tests plus compliqués qui nécessitent de mettre en œuvre des pratiques avancées. Leur réalisation est également indispensable pour l'obtention du point bonus.
* Proposez également une solution à l'exercice qui passe tous vos tests unitaires. Votre solution comprendra également des lignes de code commentées qui une fois décommentées feront échouer un de vos tests. Vos tests doivent vérifier votre solution, mais votre solution doit également pouvoir vérifier vos tests !
* Soumettez alors un PR sur ce dépôt dans le dossier de l'exercice avec les fichiers que vous avez écrits. Une discussion commencera autour de ce PR où votre soumission sera analysée et jugée, si celle-ci est pertinente votre PR sera mergé au dépôt, sinon vous serez invités à effectuer des modifications à votre code et resoumettre un nouveau PR.

### Structure d'une soumission

Chaque exercice possède a un dossier associé dans le dépôt. Les fichiers relatifs à l'exercice que vous avez choisi devront être insérés dans ce dossier. Le dossier aura toujours au moins la structure suivante :

* `tests.c` : Le code reprenant les tests.
* `student_code.c` : Votre résolution de l'exercice.
* `student_code.h` : Le fichier header de `student_code.c`. Celui-ci est normalement déjà fourni et vous n'êtes pas censé le modifier.

Vous pouvez également adjoindre d'autres fichiers, comme un Makefile, ou par exemple un fichier réécrivant certaines fonctions de la librairie standard grâce au mécanisme `LD_PRELOAD`. 

N'hésitez pas à regarder la structure des dossiers mini-projet-string et calloc2, ces deux exercices font office d'exemple.

### Écriture des tests

Les tests unitaires doivent être écrits à l'aide du framework CUnit. Nous insistons que vous soyez vigilants aux points suivants :

* Un test unitaire (donc une fonction) ne doit vérifier *qu'un seul aspect* du programme. Ainsi si vous souhaitez tester un cas général, puis un cas limite d'une fonction codée par l'utilisateur, ne faites pas un seul test avec 2 assertions (l'une vérifiant le cas général, l'autre le cas limite), mais bien 2 tests différents, un pour chaque cas.
* Au-dessus de chaque test doit être inséré un commentaire avec une annotation spécifique. Cette annotation contiendra le message d'erreur qui sera renvoyé par INGInious lorsque le test concerné échouera. La structure de l'annotation est la suivante : `@nom_fonction_a_tester:nom_test => [Message d'erreur]`. N'hésitez pas à rédiger des messages d'erreur complets. Par exemple :
```
// @strlen:test_strlen1 => [Lorsque strlen est appelé avec comme argument la chaine \"foo bar\", strlen ne renvoie pas le bon nombre de caractères.]
void test_strlen1(void) {
    char *testString = "foo bar";

    //un test unitaire peut contenir plusieurs assertions
    //ici on s'assure que la fonction strlen renvoie bien le bon nombre de caractères présents dans testString
    CU_ASSERT_EQUAL(strlen(testString), 7); 
}
```
* Faites bien attention à libérer les ressources allouées sur la heap, même si ces ressources ont été allouées par le code de l'étudiant. 

### Techniques avancées de test

Il se peut que certains exercices nécessitent l'utilisation de techniques avancées de test. Nous en expliquons ici trois :

**L'interception de segfault** : Il se peut que le code de l'étudiant segfault. INGInious interceptera toujours un segfault et l'indiquera à l'étudiant à l'aide d'un message générique (du style "Votre code a produit un segfault."). Cela dit, ce message d'erreur n'est pas très utile car il n'indique pas forcément quelle partie du code a produit le segfault et pourquoi. Si dans un de vos tests vous testez un cas limite qui peut amener à un segfault, interceptez-le à l'aide des fonctions `signal`, `siglongjmp` et `sigsetjmp` afin de pouvoir indiquer un message d'erreur plus précis à l'utilisateur (par ex. "Votre code a segfault parce que votre fonction ne gère pas NULL comme argument."). 2 exemples d'utilisation de ces fonctions sont disponibles dans calloc2 et mini-projet-string.

**Vérification d'un dépassement mémoire (buffer overflow)** : Il est intéressant de vérifier si l'utilisateur n'accède pas à de la mémoire à laquelle il n'est pas censé accéder. La technique utilisée fait appel à l'utilisation de la fonction `mmap` qui permet d'allouer un bloc de la mémoire et de modifier les droits d'accès à ce bloc. L'idée de base est de réserver 2 blocs mémoires (appelés pages). Il est possible d'attribuer des droits spécifiques à chaque page, vous pouvez autoriser les droits d'écriture et de lecture au premier bloc et ne donner aucun droit d'accès au second. 

Si la fonction de l'étudiant prend comme argument une chaîne de caractères, inscrivez la chaîne à la fin de la première page. Si le code de l'étudiant fait un dépassement de mémoire vers la droite (autrement dit s'il va plus loin que le caractère de terminaison \0 situé à la fin de la première page), il accédera à une adresse mémoire de la seconde page qui est réservée. Cela entrainera un segfault que vous devrez intercepter, et vous pourrez alors renvoyer un message d'erreur approprié à INGInious. Un exemple d'implémentation est reprise dans le test `test_strcasecmp4` de mini-projet-string.

**Modification d'une fonction de la librairie standard** : Il est possible à l'aide du mécanisme de `LD_PRELOAD` de modifier certaines fonctions comme `malloc` ou `free`. Par exemple, une idée serait de forcer `malloc` à échouer dans un test unitaire afin de vérifier si l'étudiant gère bien le cas où `malloc` renvoie `NULL`. On réécrit une fonction `malloc` qui pourra appeler la fonction `malloc` originale, mais en y ajoutant certains mécanismes. Cette fonction devra être écrite dans un fichier séparé, puis compilée séparement dans une librairie partagée, nommée par exemple `mymalloc.so` (extension .so pour _shared object_). En exécutant les tests de la sorte : `LD_PRELOAD=./mymalloc.so ./tests`, lorsque l'exécutable `tests` fera appel à `malloc`, c'est le `malloc` de `mymalloc.so` qui sera utilisé. La fonction `malloc` que vous avez implémentée devra faire appel à la fonction `malloc` originale grâce à un mécanisme de chargement de symboles. 

N'hésitez pas à regarde l'exemple calloc2 qui utilise cette technique et explique en détail dans les commentaires comment elle fonctionne. Si vous êtes amenés à écrire un test utilisant cette technique, basez-vous sur le code de calloc2 et modifiez-le. Utilisez et modifiez notamment le Makefile fourni car il utilise des options spécifiques nécessaires au bon fonctionnement de la compilation de la librairie partagée et de l'interaction de celle-ci avec l'exécutable de tests.
