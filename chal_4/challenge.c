#include "challenge.h"

// Having global variables gets around the whole malloc issue
//   (even if it kills me a bit inside)
// Basically any variable created in a function will cease to be reliable outside of scope
// So if we want to test the BSTNodes students create, they need to persist outside functions
// Hence, they are global

// This also becomes necessary for the strings.
// If the students use a char[] in the struct:
//   The getter for that field would end up returning a local variable (structs pass by value)
//   To fix this the getter would this need to copy to an array parameter or something
// If the students use a char* in the struct:
//   They can't create something that persists outside the build_tree stack frame (no dynamic memory yet)
//   The fix is to statically allocate memory for the students with these global variable
// I'm forcing the second option (students are no longer defining the struct)
//  and turning this into a "hook this [expletive deleted] together" assignment.
// This has been a surprisingly obnoxious thing to design, I'm playing games once I'm done with this
// -蛇
//
// P.S. to students: once you've learned about stack frames and dynamic allocation,
//      come back and appreciate the horrors of why I've done this (that's the real "challenge").

struct BSTNode apple;
struct BSTNode banana;
struct BSTNode mango;
struct BSTNode nectarine;
struct BSTNode orange;
struct BSTNode peach;
struct BSTNode pear;

char apple_str[10];
char banana_str[10];
char mango_str[10];
char nectarine_str[10];
char orange_str[10];
char peach_str[10];
char pear_str[10];

// I'd've liked to have students just print to a file, but we haven't done file I/O yet
// I can't have a function that returns a char*, because we haven't done dynamic allocation yet.
// So students will fill this buffer for the "printing"

char print_buf[100];

// These getters are so I can test the tree
struct BSTNode get_apple(){return apple;}
struct BSTNode get_banana(){return banana;}
struct BSTNode get_mango(){return mango;}
struct BSTNode get_nectarine(){return nectarine;}
struct BSTNode get_orange(){return orange;}
struct BSTNode get_peach(){return peach;}
struct BSTNode get_pear(){return pear;}

struct BSTNode* get_apple_ptr(){return &apple;}
struct BSTNode* get_banana_ptr(){return &banana;}
struct BSTNode* get_mango_ptr(){return &mango;}
struct BSTNode* get_nectarine_ptr(){return &nectarine;}
struct BSTNode* get_orange_ptr(){return &orange;}
struct BSTNode* get_peach_ptr(){return &peach;}
struct BSTNode* get_pear_ptr(){return &pear;}

// Getter so I can test print preparation

char* get_print_buf(){return print_buf;}

// Struct field getters

struct BSTNode* get_left(struct BSTNode node){return node.left;}
struct BSTNode* get_right(struct BSTNode node){return node.right;}
char* get_name(struct BSTNode node){return node.name;}

// goal: resets the "print buffer"
void reset_print(){print_buf[0]='\0';}

// goal: piece together a tree like the one below
/*
              banana                    
             /      \                   
            /        \                  
           /          \                 
      apple            pear             
                      /                 
                     /                  
                    /                   
           nectarine                    
          /         \                   
         /           \                  
        /             \                 
   mango               orange           
                             \          
                              \         
                               \        
                                peach   
*/
void build_tree(){
  strcpy(apple_str, "apple");
  strcpy(banana_str, "banana");
  strcpy(mango_str, "mango");
  strcpy(nectarine_str, "nectarine");
  strcpy(orange_str, "orange");
  strcpy(peach_str, "peach");
  strcpy(pear_str, "pear");

  apple.name = &apple_str[0];
  banana.name = &banana_str[0];
  mango.name = &mango_str[0];
  nectarine.name = &nectarine_str[0];
  orange.name = &orange_str[0];
  peach.name = &peach_str[0];
  pear.name = &pear_str[0];

  banana.left = &apple;
  banana.right = &pear;
  pear.left = &nectarine;
  nectarine.left = &mango;
  nectarine.right = &orange;
  orange.right = &peach;
}

// goal: fill print_buf with a new-line-delineated in-order-traversal of the trees's nodes' names
// param node: the root of the tree to "print"
// assumptions:
//   parameter node does not have NULL as its name field
//   reset_print has been called directly before this
//   (feel free to guard against these issues though)
void prep_print(struct BSTNode node){  
  puts("prep");
  char *delim = "\n";
  if(node.left){
    prep_print(*get_left(node));
  }
  strcat(get_print_buf(), get_name(node));
  strcat(get_print_buf(), delim);
  if(node.right){
    prep_print(*get_right(node));  
  }
}
