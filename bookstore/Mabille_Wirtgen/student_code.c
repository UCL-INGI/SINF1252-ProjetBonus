//===-- student_code.c ----------------------------------------------------===//
//
//       Module servant à l'implémentation d'une structure de données
//       gérant une libriairie d'auteurs avec leur livres
//
// Authors : MABILLE Florent && WIRTGEN Thomas
// Version : 03/04/2016
//
//===----------------------------------------------------------------------===//

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../student_code.h"

cellAuteur *existe(cellAuteur *librairie, char *strAuteur)
{
  if(strAuteur == NULL) return NULL;  // commentez cette ligne pour faire échouer test_existe_parmametreIncorrect
  cellAuteur *current = librairie;
  while(current != NULL)
  {
    if(strcmp(strAuteur, current->auteur) == 0) return current;
    current = current->next;
  }
  return NULL;
}

int compteOuvrage(cellAuteur *librairie, char *strAuteur)
{
  cellAuteur *author = existe(librairie, strAuteur);
  if(author == NULL) return 0; //commentez cette ligne pour faire échouer test_compteOuvrage_auteurNotInside
  cellLivre *books = author->Livres;

  int countBook = 0;
  while(books != NULL)
  {
    countBook++;  //commentez cette ligne pour faire échouer test_compteOuvrage
    books = books->suiv;
  }
  return countBook;
}

int check_present(cellAuteur *librairie, char *strAuteur, char *strTitre)//regarde si un livre est déjà présent dans la collection d'un auteur
{
  cellAuteur *author = existe(librairie, strAuteur);
  if(author == NULL) return -1; // auteur pas présent mais jamais utilisé normalement
  cellLivre *crt = author->Livres;
  while(crt != NULL)
  {
    if(strcmp(crt->titre, strTitre) == 0)
    {
      return 1;
    }
    crt = crt->suiv;
  }
  return 0;
}

void add(cellAuteur *librairie, char *strAuteur, char *strTitre)
{
  //----------------
  if(check_present(librairie,strAuteur,strTitre) == 1)//livre déjà présent
  {
    printf("Livre déjà présent dans la collection");
    return;
  }
  //----------------
  // commentez tout le bloc "if" pour faire échouez add_le_meme_livre
  // (i.e. ce qui ce trouve entre les deux lignes de tirets)

  cellAuteur *author = existe(librairie, strAuteur);
  if(author == NULL) // si aucun auteur n'a été trouvé
  {
    printf("Error, \"%s\" not found...\n", strAuteur);
    return;
  }

    cellLivre *newLivre = (cellLivre *) malloc(sizeof(cellLivre));
    if(newLivre == NULL)
    {
      printf("Error malloc while creating newBook\n");
      return;
    }
    newLivre->titre = strTitre;
    newLivre->suiv = author->Livres;
    author->Livres = newLivre;
    return;
}

void suppressionLivres(cellLivre *books)//supression des livres
{
  while(books != NULL)
  {
    cellLivre *toRemove = books;
    books = books->suiv;
    free(toRemove);
  }
  return;
}

void supprimer(cellAuteur **librairie, char *strAuteur)
{
  if(*librairie == NULL) return;//si la librairie est déjà vide, ne rien faire.

  cellAuteur *current = *librairie;
  cellAuteur *next = current->next;
  //------------
  if(strcmp(current->auteur, strAuteur) == 0) //si c'est le premier
  {
    *librairie = next;
    suppressionLivres(current->Livres);  //commetez cette ligne pour faire échouer test_supprimer_auteur
    free(current);
    return;
  }
  //------------
  // commentez toutes les lignes se trouvant entres les tirets pour faire échouer
  // test_suppression_premier_auteur
  while(next != NULL)
  {
    if(strcmp(next->auteur, strAuteur) == 0)//autre cas
    {
      current->next = next->next;
      suppressionLivres(next->Livres);  //commetez cette ligne pour faire échouer test_supprimer_auteur
      free(next);
      return;
    }
    current = current->next;
    next = current->next;
  }
}
/*void affiche(cellAuteur *librairie)//affiche la liste des auteurs
{
  cellAuteur *current = librairie;
  while(current != NULL)
  {
    printf("%s\n", current->auteur);
    current = current->next;
  }
  return;
}*/
