// disclaimer ! this piece of code sucks
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <conio.h>
#include <time.h>


#define Default_cell ' '
#define row 20
#define food '*'
#define col 60
#define snk '0'
#define boundry '#'
#define board_type char

typedef struct Snake
{
  int x, y;
  struct Snake *next;
} Snake;

struct Snake *snake;
int dir;
char array[row][col];
int speed =30;
int food_on_board = false ;
int p = 2 ;
// general linked list functions
void access_array(board_type (*arr)[col],int x,int y)
{
  printf("%c ",arr[x][y]);
}
int get_length(struct Snake *Node);
void delete_last_element(struct Snake *Node);
void PrintList(struct Snake *Node);

void fill_board(board_type (*array)[col]);
bool isoccupaid(Snake *Node, int x, int y);
void left_move(struct Snake *Node, int (*board)[7]);
void move_snake_left(struct Snake *Node);
void move_snake_up(Snake *Node);
void move_snake_right(Snake *Node);
void move_snake_down(Snake *Node);


void grow(int x ,int y,Snake* Head);
void get_food_coordinates(int *x,int*y);
int consumed_check(int x,int y,Snake* head);
struct Snake *create_();
void HeadtoBody(struct Snake *Modifiedhead, struct Snake *w);
void PrintArray(board_type (*arr)[col]);
void manup_chain(int x,int y,Snake* head);
// void handle_food(int *x,int* y,int xpos,int ypos);


//addtions 
void cut(int len,Snake* snake) ;
void addition_conditons(Snake* snake) ; 
//commands :
int get_key();
void Screen();
// int Pause(int key) {
//   if (pause == 0) pause = 1 ;
//   else if (pause==1 ) pause = 0;
  
  
// }
void handle_food(int* xpos,int* ypos);

void movement(Snake* Node);
int game_over(Snake *head);
int self_collision(Snake* snake);
int main()
{
  
  struct Snake *start;
  struct Snake *two = (struct Snake *)malloc(sizeof(struct Snake));
  struct Snake *three = (struct Snake *)malloc(sizeof(struct Snake));
  start = (struct Snake *)malloc(sizeof(struct Snake));

  snake = start;

  start->x = 4;
  start->y = 4; 
  start->next = two;
  // start->next = two;// remember to add NULL in last link ,Bp function won;t work without that
  two->x = 4;
  two->y = 5;
  two->next = NULL;
  // three->x = 4;
  // three->y = 6;
  // three->next = NULL;
  // start->next = two;
  // two->next = three;

  
  //food items 

  int xpos,ypos;
  int *ptx= &xpos;
  int *pty = &ypos;
  //

  while (game_over(snake)!=1)
  {

    Screen();
    fill_board(array);
    movement(snake);
    handle_food(ptx,pty);
    PrintArray(array);
    addition_conditons(snake);
    Sleep(speed);

  }
  system("cls");
  printf("The Game-over");
  free(snake);
  // system("clear");
  // printf("The Game-over");
  // free(snake);
  // fill_board(array);
  // array[5][35] = food;
  // PrintArray(array);
  // // }
  // handle_food();
  // // fill_board(array);
  // PrintArray(array);
   // two->x = 4;
  // two->y = 5;
  // two->next = NULL;

  // Bp(snake,array);
  // PrintArray(array);
  // delete_last_element(snake);
  // PrintArray(array);
  return 0;
}

int get_length(struct Snake *Node)
{
  int count = 0;
  while (Node != NULL)
  {
    Node = Node->next;
    count += 1;
  }
  // printf("%d ",count);
  return count;
}
void delete_last_element(struct Snake *Node)
{
  for (int i = 1; i < get_length(Node) ; i++)
  {
    Node = Node->next;
  }
  Node->next = NULL;
}
void PrintArray(board_type (*arr)[col]){
  for (int i = 0; i < row; i++)
  {
    for (int k = 0; k < col; k++)
    {
      printf("%c",arr[i][k]);
    }
    printf("\n");
  }

}

void PrintList(struct Snake *Node)
{
  while (Node != NULL)
  {
    printf("The x's -%d ,the y's - %d \n", Node->x, Node->y);
    Node = Node->next;
  }
  printf("\n");
}

void fill_board(board_type (*array)[col])
{
  for (int i = 0; i < row; i++)
  {
    for (int k = 0; k < col; k++)
    {
  

      if (i == 0 || i == row-1 || k == 0 | k== col-1)
      {
        array[i][k] = boundry;
      }
      
      else if (isoccupaid(snake, i, k) == false || array[i][k] != boundry || array[i][k] != food)
      {
        array[i][k] = Default_cell;
      }
    }
  }
}

bool isoccupaid(Snake *Node, int x, int y)
{
  // checking  for snake'body
  while (Node != NULL)
  {
    if (Node->x == x && Node->y == y)
    {
      return true;
    }
    else
    {
      Node = Node->next;
    }
  }
  return false;
}

struct Snake *create_()
{
  struct Snake *node = (struct Snake *)malloc(sizeof(struct Snake));
  return node;
}


void Bp(struct Snake *Node, board_type (*board)[col])
{
  Snake * head = Node;
  board[Node->x][Node->y] = '@';
  Node = Node->next;
  while (Node != NULL)
  {
    board[Node->x][Node->y] = snk;
    Node = Node->next;
  }
  
}         


void changeBody(int x,int y,Snake* Node)
{
  Snake * tmpr = create_();
  tmpr->x = x;
  tmpr->y = y ;
  tmpr->next = Node;
  snake = tmpr;
  delete_last_element(snake);
  // PrintList(snake);
}

void move_snake_left(struct Snake *Node)
{
  // keeping the original value after move
    manup_chain(Node->x,Node->y-1,snake);
    speed = 50;
}

void move_snake_up(Snake *Node)
{
    manup_chain(Node->x -1 ,Node->y,Node);
    speed = 50;
}
void move_snake_right(Snake *Node){
  manup_chain(Node->x,Node->y+1,Node);
  speed = 50;
}
void move_snake_down(Snake *Node){
  // int onest = Node->x  +1 ;
  // printf("the value of node ,moving down %d ",Node->x +1);
  manup_chain(Node->x+1,Node->y,Node);
  speed = 50;

}

int get_key(){
  if(_kbhit()){
      return _getch();
        }
  else{
      return -1;}
}

void Screen() {
  HANDLE hOut;
  COORD Postion;
  hOut = GetStdHandle(STD_OUTPUT_HANDLE);
  Postion.X = 0 ;
  Postion.Y = 0;
  SetConsoleCursorPosition(hOut,Postion);
}


int head_coll_with(Snake* head,board_type obj);
int valid_move(Snake* head, int key){

  if (key=='w')
  {
    if (head->x-1 == head->next->x){return 0;}
    else{return 1;}
  }
  else if (key=='s')
  {
  //   if(head->x+1 == head->next->x){return 0;}
  //   else{return 1;}
    if (head->x+1 != head->next->x){return 1;}}

  else if (key=='a')
  {
    if(head->y-1==head->next->y){return 0;}
    else {return 1;}
  }
  else if (key=='d')
  {
    if(head->y+1==head->next->y){return 0;}
    else{return 1;}
  }
  
  
}
void grow(int x ,int y,Snake* Head)
{
  Snake* nhead = create_();
  nhead->x = x ;
  nhead->y = y ; 
  nhead->next = Head;
  snake = nhead;

}
void movement(Snake* Node)
{

  int key = get_key();

  if(key=='w' || key=='s'|| key=='a' || key=='d') {if(valid_move(snake,key)==1)dir = key;}
  if(dir=='w' ){
    move_snake_up(snake);
  }
  if (dir=='a' )
  {
    move_snake_left(snake);
  }
  if (dir=='s')
  {
    move_snake_down(snake);
  }
  if(dir=='d'){
    move_snake_right(snake);
  }
  
}
int consumed_check(int x,int y,Snake* head)
{
  // printf("%d-%d , %d-%d \n",head->x,x,head->y,y);
  if(array[head->x][head->y] == food){

  return 1 ; 
  }

}

void handle_food(int* xpos,int* ypos)//int *x,int *y,
{
  
  if (food_on_board==false)
  {
    get_food_coordinates(xpos ,ypos);
    food_on_board = true;
    // printf("i if working in your order");
  }
  array[*xpos][*ypos] = food;
  if (consumed_check(*xpos,*ypos,snake)==1)
  {
    grow(*xpos,*ypos,snake);
    p ++ ; 
    array[*xpos][*ypos] = Default_cell;
    food_on_board = false;
    // printf("i if working in your order");
  }
  // printf("i if working in your order");
  printf("the snake has a size of %d ",get_length(snake));
  

  // else food is aleady present 
    // check if consumped 
}
void cut(int len,Snake* Node) {
  Snake * tmpr = Node; 
    for (int i = 0; i < len; i++)
    {
      delete_last_element(Node);
    }
  


    
}
void get_food_coordinates(int *x,int*y)
{
  srand(time(0));
  *x = (rand() % row); 
  *y = (rand() % col);
  // *(x) = row/2;
  // *(y) = 45;
  printf("this is the food %d %d ",*x,*y);
}
  
void manup_chain(int x,int y,Snake* head)
{
  int r,c;
  int inr ,inc; 
  r  = head->x ;
  c = head->y;
  head->x = x ;
  head->y = y ;
  head = head->next;
  while (head!= NULL)
  {
    inr = head->x;
    inc = head->y;
    head->x = r ;
    head->y = c; 
    head= head->next;
    r = inr ;
    c = inc; 
  }
  Bp(snake,array);
}
// Problems 
int game_over(Snake*head) {
  //basic check :
  // if ((head->x == 1  || head->y < 0 ) || (head->x == row-1 || head->y == col-1 )  )
  // {
  //   return 1 ;
  // }
  if (array[head->x][head->y]==boundry){return 1;}
  
  if (self_collision(head)==1) {return 1 ;}

  
  
  else return 0; 
}

int self_collision(Snake* snake){
  if (array[snake->x][snake->y]==snk)
  {
    return 1;
  }
}
void addition_conditons(Snake* snake){
  if (p == 7) cut(3,snake);

  
}
// "-----" "|______"
// "|"     "|"
// "|"     "|"
// "|" "|" "|"
// "|----" "|"
//  [x] - Need to eraswe the previous location of snake
// hel
// for moving both nodes - try 1 =  change pos of head node and second node will take the postion on which first Node positioned

// just need to handle the head ,rest of the body will follow the head .

// 26-7
// [x] take the snake move continously once key is pressed or until one key is pressed

//27-7

//30-july - 31-july
// [x] fix problems in food deploying 
// and [x] fix movement of snake over it's body

// 1 Aug ,3 Aug
//[] fix upper clash detection
