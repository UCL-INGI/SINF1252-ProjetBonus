#include <stdio.h>
#include <stdlib.h>
#include "student_code.h"

int has_key(Node root, int key)
{
	//On verifie si on est sur la clee recherchee
	if(root.key==key)
	{
        return 1;
	}
	//Si la clee recherchee est plus petite, on descend l'arbre par la gauche.
	else if(root.key>key)
	{
		if(root.left!=NULL)
		{
			return has_key(*(root.left),key);
		}
		return 0;
	}
	//Sinon la clee recherchee est plus grande, on descend l'arbre par la droite.
	else
	{
		if(root.right!=NULL)
		{
			return has_key(*(root.right),key);
		}
		return 0; 
	 }
}

int compare(Node root_a, Node root_b)
{
   if(root_a.value!=root_b.value||root_a.key!=root_b.key)
   {return 0;}
    
    
   //On vérifie si les deux Nodes de droite sont tous les deux NULL ou tous les deux remplis
   if((!root_a.right &&root_b.right)||(root_a.right &&!root_b.right))
   {return 0;}
  	 
   //Dans le cas où les Nodes de droite sont non-NULL, on vérifie s'ils présentent la même structure.
   if(root_a.right&&root_b.right)
   { if(!(compare(*(root_a.right),*(root_b.right))))
	   {
		   return 0;
		}
	}
	
	//On vérifie si les deux Nodes de gauche sont tous les deux NULL ou tous les deux remplis
   if((!root_a.left &&root_b.left)||(root_a.left &&!root_b.left))
   {return 0;}
  	 
   //Dans le cas où les Nodes de gauche sont non-NULL, on vérifie s'ils présentent la même structure.
   if(root_a.left&&root_b.left)
   { if(!(compare(*(root_a.left),*(root_b.left))))
	   {
		   return 0;
		}
	} 
   //Tout est ok
   return 1;
}
