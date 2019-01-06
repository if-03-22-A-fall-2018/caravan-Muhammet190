#include <stdio.h>
#include "pack_animal.h"
#include "general.h"
#include "caravan.h"
#include <stdlib.h>

struct Node{
  struct Node* nextNode;
  PackAnimal animal;
};
struct CaravanImplementation{
  struct Node* start;
  struct Node* end;
  int length;
  int speed;
  int load;
};

Caravan new_caravan()
{
    struct CaravanImplementation* list;
    list = (struct CaravanImplementation*) malloc(sizeof(struct CaravanImplementation));
    list->length = 0;
    list->start =0;
    list->end = 0;
    list->load = 0;
    return list;
}

int get_length(Caravan caravan)
{
  return caravan->length;
}

void delete_caravan(Caravan caravan)
{
  struct Node* current = caravan->start;

  while(current!= 0){
    struct Node* bam = current;
    current = current->nextNode;
    sfree(bam);
  }
    sfree(caravan);
}

void add_pack_animal(Caravan caravan, PackAnimal animal)
{
  if(animal == 0 || get_caravan(animal) == caravan)return;
  if(caravan == 0)return;
  if(get_caravan(animal) != 0)remove_pack_animal(get_caravan(animal),animal);
  add_to_caravan(animal, caravan);
  struct Node* newc = (struct Node*) malloc(sizeof(struct CaravanImplementation));
  newc->animal = animal;
  newc->nextNode = 0;

  if(caravan->start == 0){
    caravan->start = newc;
    caravan->end = newc;
  }
  else{
  caravan->end->nextNode = newc;
  caravan->end = newc;
}
  caravan->length ++;
}

void remove_pack_animal(Caravan caravan, PackAnimal animal)
{
  struct Node* current = caravan->start;
  struct Node* bam = current;
  if(caravan->start == 0 || animal ==0 || caravan == 0)return;
  if(current->animal == animal){
    remove_from_caravan(animal, caravan);
    caravan->start = current->nextNode;
    sfree(bam);
    caravan->length--;
    return;
  }
  while(current->nextNode != 0){
    bam = current->nextNode;
    if(current->nextNode->animal == animal){
      remove_from_caravan(animal, caravan);
      current->nextNode = current->nextNode->nextNode;
      sfree(bam);
      caravan->length--;
      if(current->nextNode == 0)caravan->end = current;
      return;
    }
    current = current->nextNode;
  }

}

int get_caravan_load(Caravan caravan)
{
  int a=0;
  struct Node* current = caravan->start;
  while(current!= 0){
    a += get_load(current->animal);
    current = current->nextNode;
  }
  return a;
}

void unload(Caravan caravan)
{
  struct Node* current = caravan->start;
  for (int i = 0; i < caravan->length; i++)
  {
    unload(current->animal);
    current = current->nextNode;
  }
}

int get_caravan_speed(Caravan caravan)
{
    int speed = INT32_MAX;
    struct Node* current = caravan->start;
    for (int i = 0; i < caravan->length; ++i)
    {
      speed = get_actual_speed(current->animal)<speed ? get_actual_speed(current->animal): speed;
      current = current->nextNode;
    }
    return speed;
}
void optimize_load(Caravan caravan)
{
    return;
}
