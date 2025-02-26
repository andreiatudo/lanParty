#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
//Structura jucator
struct player
{
    char* firstName;
    char* secondName;
    double points;
};

typedef struct player Player;
//Structura nod din echipa
struct nod
{
    Player value;
    struct nod *next;
};

typedef struct nod Nod;
//Structura Echipa
struct node
{
    Nod *value;
    int nr_players;
    double total_points;
    char* team_name;
    struct node* next;
};

typedef struct node Node;
//Structura meciuri
struct match
{
    Node *team1, *team2;
    struct match *next;
};

typedef struct match Match;
//Structura Coada
struct queue
{
    Match *front, *rear;
};

typedef struct queue Queue;

struct N
{
    Node *val;
    struct N *left;
    struct N *right;
};

typedef struct N Node_bst;

struct avl
{
    Node *val;
    int height;
    struct avl *left;
    struct avl *right;
};

typedef struct avl Node_avl;
//Subprogramre
void player_read(Nod *nou, FILE *f);

void adaugare_player(Nod *head, FILE *f);

void adaugare(Node *head, FILE *f);

void afisare(Node *head, FILE *f);

int n_maxim(int nr);

void eliminare(Node *head, int points);

double team_points(Node *head);

void total_points_function(Node* head);

void stergere(Node *head, int *nr_teams, int n);

Queue* createQueue();

void Copy(Node *x, Node *y);

void enQueue(Queue *q, Node *head);

void afisare_queue(Queue *q, FILE *f);

void Push(Node **top, Node *team);

void createStacks(Node **topW, Node **topL, Queue *q);

void corectare_punctaje(Node *top);

void afisare_stack(Node *top, FILE *f);

void deleteStack(Node **top);

int isEmpty(Queue *q);

void deleteQueue(Queue *q);

void pop(Node **top);

void creare_lista(Node *head, Queue *q);

void afisare_lista(Node *head);

Node_bst* newNode_bst(Node *team);

Node_bst* insert(Node_bst *node, Node *team);

void creare_bst(Node_bst **bst, Node *lista);

void inorder(Node_bst *root, FILE *f);

int nodeHeight(Node_avl *root);

int max(int a, int b);

Node_avl* RightRotation(Node_avl *z);

Node_avl* LeftRotation(Node_avl *z);

Node_avl* LRRotation(Node_avl *Z);

Node_avl* RLRotation(Node_avl *Z);

Node_avl* insert_avl(Node_avl *node, Node *key);

void inorder_selection(Node_bst *root, Node_avl **avl);

void inorder_afisare(Node_avl *root);

void print_nodes(Node_avl *root, int targetDepth, int currentDepth, FILE *f);

void freePlayer(Nod *player);

void freeTeamPlayers(Node *team);

void freeTeam(Node *team);

void freeQueue(Queue *q);

void freeAVLNode(Node_avl *node);

void freeAVLTree(Node_avl *root);

void freeBSTNode(Node_bst *node);

void freeBST(Node_bst *root);