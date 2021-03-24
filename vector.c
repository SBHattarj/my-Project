#include <stdio.h>

//defining base of vector

typedef struct vBase {
  void *Value;  //vallue of the member of the vector
  char *type;   //variable to store type of the member
} vBase;

//defining vector

typedef struct vector {
  vBase *Base;  //Base of the vector where the elements will be stored
  int size;     //size of the vector
  int assignment;
} vector;

//defining macro to declare vector

#define decVector(x) vector x = {.Base = malloc(sizeof(vBase)), .size = 0, .assignment = "Undefined"}

//defining push to add a element to the end of a vector

void push(vector *a, void *b, char type[]) {
  int temp = a->size+1;  //assigning temp to the total size
  a->Base = realloc(a->Base, temp*sizeof(vBase)); //resizing the vector
  a->Base[a->size].Value = b;  //assigning b to the last element of the vector
  a->Base[a->size].type = type;  //changing type of the element
  a->size = temp;
}

//defining pushAll to add all the elements of a vector to the end of another vector

void pushAll(vector *a, vector b) {
  int temp = a->size+b.size;  //assigning temp to the total size
  a->Base = realloc(a->Base, temp*sizeof(vBase));  //resizing  vector
  for(int n = a->size; n < temp; ++n) {
    a->Base[n] = b.Base[n-a->size];  // assigning elements of b to a after the last assigned element
  }
  a->size = temp;  //changing size
}

//defining insert to add an element at a certain index

void insert(vector *a, void *b, int index, char type[]) {
  ++a->size;  //changing size of the vector
  a->Base = realloc(a->Base,a->size*sizeof(vBase)); //resizing vector
  vBase c = a->Base[index], d; //assigning  Base of index to c and initiating d
  a->Base[index].Value = b;  //changing value of index
  a->Base[index].type = type;  //changing type
  for(int n = index+1; n < a->size; ++n) {
    d = c;  //assigning  c to d
    c = a->Base[n];  //changing c
    a->Base[n] = d;  //changing element of vector to the previous element
  }
}

//defining insertAll to add elements of a vector to another vector

void insertAll(vector *a, vector b, int index) {
  vBase *c = malloc(a->size*sizeof(vBase));  //resizing c to a's size
  c = a->Base;  //copying into c
  a->size += b.size;  //increasing size
  a->Base = realloc(a->Base, a->size*sizeof(vBase)); //increasing size of the vector
  for(int n = 0; n < b.size; ++n) {
    a->Base[n+index] = b.Base[n]; //assigning elements of b to a
  }
  for(int n = index+b.size; n < a->size; ++n) {
    a->Base[n] = c[n-b.size];  //reassigning vallues of a to the end of a
  }
}

//defining pop to delete last element of a

void pop(vector *a) {
  --a->size;  //changing size
  vBase *b = malloc(a->size*sizeof(vBase)); //making a pointer with a size of a->size
  for(int n = 0; n < a->size; ++n) {
    b[n] = a->Base[n]; //copying values of a except the last value
  }
  a->Base = realloc(b, a->size*sizeof(vBase));  //assigning a with the elements of b
}

//defining delIndex to delete an element at the index position

void delIndex(vector *a, int index) {
  --a->size;  //changing size
  vBase *b = malloc(a->size*sizeof(vBase));  //making a pointer with the size of a->size 
  for(int n = 0; n < a->size; ++n) {
    if(n < index) {
      b[n] = a->Base[n];  //assigning elements of a with a index no. less than index
    }
    else {
      b[n] = a->Base[n+1];  //assigning elements of a with a index no. greater than index
    }
  }
  a->Base = realloc(b, a->size*sizeof(vBase));  //assigning a with the elements  of b
}

//defining delRange to delete multiple items from a vector

void delRange(vector *a, int index, int size) {
  a->size -= size;  //changing size
  vBase *b = malloc(a->size*sizeof(vBase));  //making a pointer of size a->size
  for(int n = 0; n < a->size; ++n) {
    if(n < index) {
      b[n] = a->Base[n];  //assigning vallues less than index
    }
    else {
      b[n] = a->Base[n+size];  //assigning vallues greater than index+size-1
    }
  }
  a->Base = realloc(b, a->size*sizeof(vBase));  //assigning a with elements of b
}

//defining clear to delete  all elements  of a vector

void clear(vector *a) {
  decVector(b);  //initiating new empty vector
  *a = b; //assigning a with a empty vector
}

//defining assgnments and their functions for vector:

//string:

//assignment

void assignStr(vector *a, char b[]) {
  clear(a);  //clearing a to change it's value totally
  a->size = strlen(b);  //changing a->size to the length of the string
  a->Base = malloc(a->size*sizeof(vBase));  //resizing  vector
  a->assignment = 1;  //changing assignment of the vector
  for(int n = 0; n < a->size; ++n) {
    a->Base[n].Value = b[n];  //assigning single characters of the string to the vector
    a->Base[n].type = "char";  //assingning type to char
  }
}

//defining append and appendstr to add string at the end

void append (vector *a, char b[]) {
  if(a->assignment != 1) {
    printf("Wrong Assignment \n Assignment is '%d' \n assignment must be 1", a->assignment);  //error message when one of them or both of them are not string
    return; //terminating function
  }
  decVector(c); //declaring new vector to assign value of b
  assignStr(&c, b);  //assigning value of b to c
  pushAll(a,c);  //adding c at the end of a
}

void appendstr(vector *a, vector b) {
  if((a->assignment != 1) && (b.assignment != 1)) {
    printf("Wrong Assignment \n Assignments are '%d' and '%d' \n both assignments must be 1", a->assignment, b.assignment);  //error message when one of them or both of them are not string
    return; //terminating function
  }
  pushAll(a, b);  //Adding b at the end of a
}

//defining add and addStr to add string at the given index

void add(vector *a, char b[], int index) {
  if(a->assignment != 1) {
    printf("Wrong Assignment \n Assignment is '%d' \n assignment must be 1", a->assignment);  //error message when one of them or both of them are not string
    return; //terminating function
  }
  decVector(c);  //declaring c to assign vallue of b
  assignStr(&c, b);  //assigning vallue of b to c
  insertAll(a, c, index);  //assigning vallue of c at the given index
}

void addStr(vector *a, vector b, int index) {
  if((a->assignment != 1) && (b.assignment != 1)) {
    printf("Wrong Assignment \n Assignments are '%d' and '%d' \n both assignments must be 1", a->assignment, b.assignment);  //error message when one of them or both of them are not string
    return; //terminating function
  }
  insertAll(a, b, index);  //assigning vallues of b to a
}

//defining find and findStr to find the first instance of the given string in the string

int find(vector a, char b[]) {
  if(a.assignment != 1) {
    printf("Wrong Assignment \n Assignment is '%d' \n both assignment must be 1", a.assignment);  //error message when one of them or both of them are not string
    return; //terminating function
  }
  int temp = strlen(b);  //assigning temp to length of b
  for(int n = 0; n < a.size-temp+1; ++n) {
    if((char)a.Base[n].Value == b[0]) {
      int match = 1;  //assigning match to be one aka true
      for(int m = 1; m < temp; ++m) {
        if(b[m] != (char)a.Base[n+m].Value) {
          match = 0;  //if the sequence of the characters in a does'nt match match = 0 aka false
          break;  //terminating loop
        }
      }
      if(match == 1) {
        return n;  //returning index of the string's first character
      }
    }
  }
  return -1;  //default value
}

int findStr(vector a, vector b) {
  if((a.assignment != 1) && (b.assignment != 1)) {
    printf("Wrong Assignment \n Assignments are '%d' and '%d' \n both assignments must be 1", a.assignment, b.assignment);  //error message when one of them or both of them are not string
    return; //terminating function
  }
  for(int n = 0; n < a.size-b.size; ++n) {
    if(a.Base[n].Value == b.Base[0].Value) {  
      int match = 1;  //assigning match to be one aka true
      for(int m = 1; m < b.size; ++m) {
        if(b.Base[m].Value != a.Base[n+m].Value) {
          match = 0;  //if the sequence of the characters in a does'nt match match = 0 aka false
          break;  //terminating loop
        }
      }
      if(match == 1) {
        return n;  //returning the index of the string
      }
    }
  }
  return -1;  //default value
}

//defining findAfterIndex and findAfterIndexStr to find the first instance of the given string in the string

int findAfterIndex(vector a, char b[], int index) {
  if(a.assignment != 1) {
    printf("Wrong Assignment \n Assignment is '%d', assignment must be 1", a.assignment);  //error message when one of them or both of them are not string
    return; //terminating function
  }
  int temp = strlen(b);  //assigning temp to length of b
  for(int n = index; n < a.size-temp+1; ++n) {
    if((char)a.Base[n].Value == b[0]) {
      int match = 1;  //assigning match to be one aka true
      for(int m = 1; m < temp; ++m) {
        if(b[m] != (char)a.Base[n+m].Value) {
          match = 0;  //if the sequence of the characters in a does'nt match match = 0 aka false
          break;  //terminating loop
        }
      }
      if(match == 1) {
        return n;  //returning index of the string's first character
      }
    }
  }
  return -1;  //default value
}

int findAfterIndexStr(vector a, vector b, int index) {
  if((a.assignment != 1) && (b.assignment != 1)) {
    printf("Wrong Assignment \n Assignments are '%d' and '%d' \n both assignments must be 1", a.assignment, b.assignment);  //error message when one of them or both of them are not string
    return; //terminating function
  }
  for(int n = index; n < a.size-b.size; ++n) {
    if(a.Base[n].Value == b.Base[0].Value) {  
      int match = 1;  //assigning match to be one aka true
      for(int m = 1; m < b.size; ++m) {
        if(b.Base[m].Value != a.Base[n+m].Value) {
          match = 0;  //if the sequence of the characters in a does'nt match match = 0 aka false
          break;  //terminating loop
        }
      }
      if(match == 1) {
        return n;  //returning the index of the string
      }
    }
  }
  return -1;  //default value
}

//defining del and delStr to delete first instance of the given string

void del(vector *a, char b[]) {
  if(a->assignment != 1) {
    printf("Wrong Assignment \n Assignment is '%d' \n assignment must be 1", a->assignment);  //error message when one of them or both of them are not string
    return; //terminating function
  }
  int temp = strlen(b);  //assigning temp to length of b
  for(int n = 0; n < a->size-temp+1; ++n) {
    if((char)a->Base[n].Value == b[0]) {
      int match = 1;  //assigning match to be one aka true
      for(int m = 1; m < temp; ++m) {
        if(b[m] != (char)a->Base[n+m].Value) {
          match = 0;  //if the sequence of the characters in a does'nt match match = 0 aka false
          break;  //terminating loop
        }
      }
      if(match == 1) {
        delRange(a, n, temp);  //if matched deletiing the part
        return;  //terminating function
      }
    }
  }
}

void delStr(vector *a, vector b) {
  if((a->assignment != 1) && (b.assignment != 1)) {
    printf("Wrong Assignment \n Assignments are '%d' and '%d' \n both assignments must be 1", a->assignment, b.assignment);  //error message when one of them or both of them are not string
    return; //terminating function
  }
  for(int n = 0; n < a->size-b.size; ++n) {
    if(a->Base[n].Value == b.Base[0].Value) {  
      int match = 1;  //assigning match to be one aka true
      for(int m = 1; m < b.size; ++m) {
        if(b.Base[m].Value != a->Base[n+m].Value) {
          match = 0;  //if the sequence of the characters in a does'nt match match = 0 aka false
          break;  //terminating loop
        }
      }
      if(match == 1) {
        delRange(a, n, b.size);  //if matched deletiing the part
        return;  //terminating function
      }
    }
  }
}

//defining delAfterIndex and delAfterIndexStr to delete the first instance of the given string after the given index

void delAfterIndex(vector *a, char b[], int index) {
  if(a->assignment != 1) {
    printf("Wrong Assignment \n Assignment is '%d' \n assignment must be 1", a->assignment);  //error message when one of them or both of them are not string
    return; //terminating function
  }
  int temp = strlen(b);  //assigning temp to length of b
  for(int n = index; n < a->size-temp+1; ++n) {
    if((char)a->Base[n].Value == b[0]) {
      int match = 1;  //assigning match to be one aka true
      for(int m = 1; m < temp; ++m) {
        if(b[m] != (char)a->Base[n+m].Value) {
          match = 0;  //if the sequence of the characters in a does'nt match match = 0 aka false
          break;  //terminating loop
        }
      }
      if(match == 1) {
        delRange(a, n, temp);  //if matched deletiing the part
        return;  //terminating function
      }
    }
  }
}

void delAfterIndexStr(vector *a, vector b, int index) {
  if((a->assignment != 1) && (b.assignment != 1)) {
    printf("Wrong Assignment \n Assignments are '%d' and '%d' \n both assignments must be 1", a->assignment, b.assignment);  //error message when one of them or both of them are not string
    return; //terminating function
  }
  for(int n = index; n < a->size-b.size; ++n) {
    if(a->Base[n].Value == b.Base[0].Value) {  
      int match = 1;  //assigning match to be one aka true
      for(int m = 1; m < b.size; ++m) {
        if(b.Base[m].Value != a->Base[n+m].Value) {
          match = 0;  //if the sequence of the characters in a does'nt match match = 0 aka false
          break;  //terminating loop
        }
      }
      if(match == 1) {
        delRange(a, n, b.size);  //if matched deletiing the part
        return;  //terminating function
      }
    }
  }
}

//defining delAll and delAllStr to delete all instances of the given string

void delAll(vector *a, char b[]) {
  if(a->assignment != 1) {
    printf("Wrong Assignment \n Assignment is '%d' \n assignment must be 1", a->assignment);  //error message when one of them or both of them are not string
    return; //terminating function
  }
  int temp = strlen(b);  //assigning temp to length of b
  for(int n = 0; n < a->size-temp; ++n) {
    if(a->Base[n].Value == b[0]) {  
      int match = 1;  //assigning match to be one aka true
      for(int m = 1; m < temp; ++m) {
        if(b[m] != a->Base[n+m].Value) {
          match = 0;  //if the sequence of the characters in a does'nt match match = 0 aka false
          break;  //terminating loop
        }
      }
      if(match == 1) {
        delRange(a, n, temp);  //if matched deletiing the part
      }
    }
  }
}

void delAllStr(vector *a, vector b) {
  if((a->assignment != 1) && (b.assignment != 1)) {
    printf("Wrong Assignment \n Assignments are '%d' and '%d' \n both assignments must be 1", a->assignment, b.assignment);  //error message when one of them or both of them are not string
    return; //terminating function
  }
  for(int n = 0; n < a->size-b.size; ++n) {
    if(a->Base[n].Value == b.Base[0].Value) {  
      int match = 1;  //assigning match to be one aka true
      for(int m = 1; m < b.size; ++m) {
        if(b.Base[m].Value != a->Base[n+m].Value) {
          match = 0;  //if the sequence of the characters in a does'nt match match = 0 aka false
          break;  //terminating loop
        }
      }
      if(match == 1) {
        delRange(a, n, b.size);  //if matched deletiing the part
      }
    }
  }
}

//defining erase to empty a string

void erase(vector *a) {
  if(a->assignment != 1) {
    printf("Wrong Assignment \n Assignment is '%d' \n assignment must be 1", a->assignment);  //error message when one of them or both of them are not string
    return; //terminating function
  }
  assignStr(a, "");
}

//defining replace and replaceStr to replace the first instance of the second argument with the last argument

void replace(vector *a, char b[], char c[]) {
  int index = find(*a, b);  //finding b in a
  if(index > -1) {
    del(a, b);  //if a contains b dleting b
    add(a, c, index);  //adding c at the index of b
  }
}

void replaceStr(vector *a, vector b, vector c) {
  int index = findStr(*a, b);  //finding b in a
  if(index > -1) {
    delStr(a, b);  //if a contains b dleting b
    addStr(a, c, index);  //adding c at the index of b
  }
}

//defining replaceAfterIndex and replaceAfterIndexStr to replace the first instanxe of b after index with c

void replaceAfterIndex(vector *a, char b[], char c[], int Index) {
  int index = findAfterIndex(*a, b, Index);  //finding b in a
  if(index > -1) {
    del(a, b);  //if a contains b dleting b
    add(a, c, index);  //adding c at the index of b
  }
}

void replaceAfterIndexStr(vector *a, vector b, vector c) {
  int index = findStr(*a, b);  //finding b in a
  if(index > -1) {
    delStr(a, b);  //if a contains b dleting b
    addStr(a, c, index);  //adding c at the index of b
  }
}

//defining OutputStr to output string

void outputStr(vector a) {
  if(a.assignment != 1) {
    printf("Wrong Assignment \n Assignment is '%d' \n assignment must be 1\n", a.assignment);  //error message when one of them or both of them are not string
    return; //terminating function
  }
  char slash[] = "\n";
  for(int n = 0; n < a.size; ++n) {
    if((char)a.Base[n].Value == slash[0]) {
        slash[1] = (char)a.Base[++n].Value;
        printf("%s", slash);
    }
    else {
      printf("%c", (char)a.Base[n].Value);
    }
  }
}
