#include "lanPartyLib.h"

//Citire jucator
void player_read(Nod *nou, FILE *f)
{
    char sir[41];
    double points;
    //Alocarea memoriei si citirea numelor
    nou->value.firstName=(char*)malloc((strlen(sir)+1)*sizeof(char));
    nou->value.secondName=(char*)malloc((strlen(sir)+1)*sizeof(char));
    fscanf(f, "%s %s %lf", nou->value.firstName, nou->value.secondName, &nou->value.points);
}
//Adaugare jucator
void adaugare_player(Nod *head, FILE *f)
{
    Nod *nou=(Nod*)malloc(sizeof(Nod));
    nou->next=head->next;
    player_read(nou, f);
    head->next=nou;
}
//Creare echipa
void adaugare(Node *head, FILE *f) {
    Node *nou = (Node*)malloc(sizeof(Node));
    if (nou == NULL) {
        printf("Nasol\n");
        exit(1);
    }

    nou->value = (Nod*)malloc(sizeof(Nod));
    if (nou->value == NULL) {
        printf("Nasol\n");
        exit(1);
    }
    nou->value->next = NULL;

    char line[101];
    char buffer[1001];
    int nr;
    fgets(buffer, sizeof(buffer), f);
    fgets(line, 101, f);
    // Aflarea numarului de jucatori din echipa și eliminarea numarului pentru a ramane cu numele echipei
    if (line[2] == ' ')
    {
        nou->nr_players = (line[0] - '0') * 10 + (line[1] - '0');
        strcpy(line, line + 3);
    } else
    {
        nou->nr_players = line[0] - '0';
        strcpy(line, line + 2);
    }
    nou->team_name = (char*)malloc((strlen(line) + 1) * sizeof(char));
    if (nou->team_name == NULL)
    {
        printf("Nasol\n");
        exit(1);
    }
    strcpy(nou->team_name, line);
    Nod *aux = nou->value;
    // Crearea jucatorilor
    for (int i = 0; i < nou->nr_players; i++)
    {
        adaugare_player(aux, f);
        aux = aux->next;
    }
    fgets(buffer, sizeof(buffer), f);
    nou->next = head->next;
    head->next = nou;
}
//Afisare lista
void afisare(Node *head, FILE *f)
{
    Node *aux = head->next; 
    while (aux != NULL)
    {
        int n=strlen(aux->team_name);
        if(aux->team_name[n-3]==' ')
            strcpy(aux->team_name+n-3, aux->team_name+n-2);
        fprintf(f, "%s", aux->team_name);
        aux = aux->next;
    }
}

//Determinarea numarului maxim de jucatori
int n_maxim(int nr)
{
    int n=1;
    while(n<=nr)
        n=n*2;
    return n/2;
}

//Eliminarea echipei cu cel mai mic punctaj
void eliminare(Node *head, int points)
{
    Node* prev = head;
    Node* aux = head->next;
    while (aux != NULL && aux->total_points != points)
    {
        prev = aux;
        aux = aux->next;
    }
    if (aux != NULL && aux->total_points == points)
    {
        prev->next = aux->next;
        free(aux);
    }
}

//Numarul de puncte per echipa
double team_points(Node *head)
{   
    // Incepe de la primul jucator din echipa
    Nod *aux = head->value->next;
    double nr = 0;
    for (int i = 0; i < head->nr_players; i++)
    {
        nr = nr + aux->value.points;
        aux = aux->next;
    }
    return nr;
}

//Scrierea numarului de puncte in echipa
void total_points_function(Node* head)
{
    Node *aux=head->next;
    while(aux)
    {
        aux->total_points=team_points(aux);
        aux=aux->next;
    }
}

//Functia de stergere pentru eliminarea echipelor
void stergere(Node *head, int *nr_teams, int n)
{
    double minim;
    while ((*nr_teams) > n && head->next)
    {
        Node *aux = head->next;
        Node *prev = head;
        minim = aux->total_points;
        // Gaseste echipa cu cel mai mic punctaj
        while (aux)
        {
            if (aux->total_points < minim)
            {
                minim = aux->total_points;
            }
            aux = aux->next;
        }
        // Elimina echipa cu cel mai mic punctaj
        eliminare(prev, minim);
        (*nr_teams)--;
    }
}

//Crearea cozii
Queue* createQueue()
{
    Queue *q;
    q=(Queue*)malloc(sizeof(Queue));
    if(q==NULL)
        return NULL;
    q->front=q->rear=NULL;
    return q;
}

//Copierea unui nod in alt nod
void Copy(Node *x, Node *y)
{
    // Copiem campurile simple
    x->nr_players = y->nr_players;
    x->total_points = y->total_points;

    // Copiem numele echipei
    x->team_name = (char*)malloc((strlen(y->team_name) + 1) * sizeof(char));
    strcpy(x->team_name, y->team_name);
    
    x->value = NULL;
    if (y->value != NULL)
    {
        Nod *current_y = y->value->next; 
        while (current_y != NULL)
        {
            Nod* new_node = (Nod*)malloc(sizeof(Nod));
            new_node->value.points = current_y->value.points;
            new_node->value.firstName = (char*)malloc((strlen(current_y->value.firstName) + 1) * sizeof(char));
            strcpy(new_node->value.firstName, current_y->value.firstName);
            new_node->value.secondName = (char*)malloc((strlen(current_y->value.secondName) + 1) * sizeof(char));
            strcpy(new_node->value.secondName, current_y->value.secondName);
            new_node->next = NULL; 
            if (x->value == NULL)
            {
                x->value = new_node;
            }
            else
            {
                Nod* last_node = x->value;
                while (last_node->next != NULL)
                {
                    last_node = last_node->next;
                }
                last_node->next = new_node;
            }
            current_y = current_y->next;
        }
    }
    //freeTeamPlayers(x);
}

// Functia de adaugare in coada
void enQueue(Queue *q, Node *head)
{
    Match *newNode = (Match*)malloc(sizeof(Match));
    newNode->next = NULL;
    newNode->team1 = (Node*)malloc(sizeof(Node));
    newNode->team2 = (Node*)malloc(sizeof(Node));

    Copy(newNode->team1, head);

    Node *nextHead = head->next;
    Copy(newNode->team2, nextHead);

    if(q->rear == NULL)
        q->front = q->rear = newNode;
    else
    {
        q->rear->next = newNode;
        q->rear = newNode;
    }
}

// Afisare coada
void afisare_queue(Queue *q, FILE *f)
{
    Match *aux = q->front;
    while (aux)
    {
        char *aux1 = (char*)malloc(sizeof(char) * (strlen(aux->team1->team_name) + 1));
        char *aux2 = (char*)malloc(sizeof(char) * (strlen(aux->team2->team_name) + 1));
        strncpy(aux1, aux->team1->team_name, strlen(aux->team1->team_name) - 2);
        strncpy(aux2, aux->team2->team_name, strlen(aux->team2->team_name) - 2);
        aux1[strlen(aux->team1->team_name) - 2] = '\0'; 
        aux2[strlen(aux->team2->team_name) - 2] = '\0';
        fprintf(f, "%-*s%c%*s\n", 33, aux1, '-', 33, aux2);
        free(aux1); 
        free(aux2); 
        aux = aux->next;
    }
}

// Adaugare in stiva
void Push(Node **top, Node *team)
{
    Node *new_node=(Node*)malloc(sizeof(Node));
    Copy(new_node, team);
    new_node->next=*top;
    *top=new_node;
}

// Creare stive
void createStacks(Node **topW, Node **topL, Queue *q)
{
    Match *aux=q->front;
    while(aux)
    { 
        if(aux->team1->total_points>aux->team2->total_points)
        {
            Push(topW, aux->team1);
            Push(topL, aux->team2);
        }
        else
        {
            Push(topL, aux->team1);
            Push(topW, aux->team2);
        }
        aux=aux->next;
    }
}

// Corectarea punctajelor echipelor
void corectare_punctaje(Node *top)
{
    Node *aux=top;
    while(aux)
    {
        aux->total_points=aux->total_points/aux->nr_players;
        aux=aux->next;
    }
}

// Afisare stiva
void afisare_stack(Node *top, FILE *f)
{
    Node *aux=top;
    while(aux)
    {
        aux->total_points=aux->total_points+1;
        for(int i=0;i<strlen(aux->team_name)-2;i++)
            fprintf(f, "%c", aux->team_name[i]);
        for(int i=0;i<36-strlen(aux->team_name);i++)
            fprintf(f, " ");
        fprintf(f, "-");
        if(aux->total_points<10)
            fprintf(f, "%6.2lf\n", aux->total_points);
        else
            fprintf(f, "%7.2lf\n", aux->total_points);

        aux=aux->next;
    }
}

// Stergere stiva
void deleteStack(Node **top)
{
    Node *temp;
    while((*top)!=NULL)
    {
        temp=*top;
        *top=(*top)->next;
        free(temp);
    }
}

// Verificare ca stiva este goala
int isEmpty(Queue *q)
{
    return (q->front==NULL);
}


// Stergere coada
void deleteQueue(Queue *q)
{
    Match *aux;
    while(!isEmpty(q))
    {
        aux=q->front;
        q->front=q->front->next;
        //freeTeam(aux->team1); 
        //freeTeam(aux->team2);
        free(aux);
    }
    free(q);
}

// Stergere nodul din varful stivei
void pop(Node **top)
{
    Node *temp;
    temp=(*top);
    *top=(*top)->next;
    free(temp);
}

// Creare lista cu echipe
void creare_lista(Node *head, Queue *q)
{
    Node *auxiliar=head;
    Match *aux=q->front;
    while(aux)
    {
        Node *new_node1=(Node*)malloc(sizeof(Node));
        Copy(new_node1, aux->team1);
        Node *new_node2=(Node*)malloc(sizeof(Node));
        Copy(new_node2, aux->team2);
        auxiliar->next=new_node1;
        auxiliar->next->next=new_node2;
        auxiliar=auxiliar->next->next;
        aux=aux->next;
    }
}

// Afisare lista pe ecran
void afisare_lista(Node *head)
{
    Node *aux = head->next; 
    while (aux != NULL)
    {
        printf("%s %lf\n", aux->team_name, aux->total_points);
        aux = aux->next;
    }
}

// Crearea unui nod pentru BST
Node_bst* newNode_bst(Node *team)
{
    Node_bst *node=(Node_bst*)malloc(sizeof(Node_bst));
    node->val=(Node*)malloc(sizeof(Node));
    Copy(node->val, team);
    node->left=node->right=NULL;
    return node;
}

Node_bst* insert(Node_bst *node, Node *team)
{
    if(node==NULL)
        return newNode_bst(team);
    //printf("%lf\n", node->val->total_points);
    //printf("%lf\n", team->total_points);
    //printf("\n");
    if(team->total_points<node->val->total_points)
        node->left=insert(node->left, team);
    else
        if(team->total_points>node->val->total_points)
            node->right=insert(node->right, team);
        else
            if(strcmp(team->team_name, node->val->team_name)>0)
                node->right=insert(node->right, team);
            else
                node->left=insert(node->left, team);
    return node;    
}

void creare_bst(Node_bst **bst, Node *lista)
{
    Node *aux=lista->next;
    while(aux)
    {
        //printf("%lf\n", aux->total_points);
        //printf("%s", aux->team_name);
        *bst=insert(*bst, aux);
        aux=aux->next;
    }
}

void inorder(Node_bst *root, FILE *f)
{
    if(root)
    {
        inorder(root->right, f);
        for(int i=0;i<strlen(root->val->team_name)-2;i++)
            fprintf(f, "%c", root->val->team_name[i]);
        for(int i=0;i<36-strlen(root->val->team_name);i++)
            fprintf(f, " ");
        fprintf(f, "-");
        if(root->val->total_points<10)
            fprintf(f, "%6.2lf\n", root->val->total_points);
        else
            fprintf(f, "%7.2lf\n", root->val->total_points);
        inorder(root->left, f);
    }
}

int nodeHeight(Node_avl *root)
{
    if(root==NULL)
        return 0;
    else
        return root->height;
}

int max(int a, int b)
{
    if(a>b)
        return a;
    else
        return b;
}

Node_avl* RightRotation(Node_avl *z)
{
    Node_avl *y=z->left;
    Node_avl *T3=y->right;

    y->right=z;
    z->left=T3;

    z->height=max(nodeHeight(z->left), nodeHeight(z->right))+1;
    y->height=max(nodeHeight(y->left), nodeHeight(y->right))+1;

    return y;
}

Node_avl* LeftRotation(Node_avl *z)
{
    Node_avl *y=z->right;
    Node_avl *T2=y->left;

    y->left=z;
    z->right=T2;

    z->height=max(nodeHeight(z->left), nodeHeight(z->right))+1;
    y->height=max(nodeHeight(y->left), nodeHeight(y->right))+1;

    return y;
}

Node_avl* LRRotation(Node_avl *Z)
{
    Z->left=LeftRotation(Z->left);
    return RightRotation(Z);
}

Node_avl* RLRotation(Node_avl *Z)
{
    Z->right=RightRotation(Z->right);
    return LeftRotation(Z);
}

Node_avl* insert_avl(Node_avl *node, Node *key)
{
    if(node==NULL)
    {
        node=(Node_avl*)malloc(sizeof(Node_avl));
        node->val=(Node*)malloc(sizeof(Node));
        Copy(node->val, key);
        // printf("%s", node->val->team_name);
        node->left=node->right=NULL;
        return node;
    }
    if(key->total_points<node->val->total_points)
        node->left=insert_avl(node->left, key);
    else
        if(key->total_points>node->val->total_points)
            node->right=insert_avl(node->right, key);
        else
            if(strcmp(key->team_name, node->val->team_name)>=0 && key->total_points==node->val->total_points)
                node->right=insert_avl(node->right, key);
            else
                if(strcmp(key->team_name, node->val->team_name)<0 && key->total_points==node->val->total_points)
                node->left=insert_avl(node->left, key);
            else
                return node;
    
    node->height=1+max(nodeHeight(node->left), nodeHeight(node->right));
    int k=(nodeHeight(node->left)-nodeHeight(node->right));

    if(k>1 && key->total_points<node->left->val->total_points)
        return RightRotation(node);

    if(k<-1 && key->total_points>node->right->val->total_points)
        return LeftRotation(node);

    if(k>1 && key->total_points>node->left->val->total_points)
        return LRRotation(node);

    if(k<-1 && key->total_points<node->right->val->total_points)
        return RLRotation(node);
    return node;
}

void inorder_selection(Node_bst *root, Node_avl **avl)
{
    if(root)
    {
        inorder_selection(root->right, avl);
        // printf("%s", root->val->team_name);
        *avl=insert_avl(*avl, root->val);
        inorder_selection(root->left, avl);
    }
}

void inorder_afisare(Node_avl *root)
{
    if(root)
    {
        inorder_afisare(root->left);
        printf("%s", root->val->team_name);
        printf("%d\n", root->height);
        inorder_afisare(root->right);
    }
}

void print_nodes(Node_avl *root, int targetDepth, int currentDepth, FILE *f) 
{
    if (root == NULL)
        return ;

    if (currentDepth == targetDepth)
    {
        fprintf(f, "%s", root->val->team_name);
    }
    else
    {
        print_nodes(root->right, targetDepth, currentDepth + 1, f);
        print_nodes(root->left, targetDepth, currentDepth + 1, f);
    }
}

void freePlayer(Nod *player)
{
    free(player->value.firstName);
    free(player->value.secondName);
    free(player);
}

void freeTeamPlayers(Node *team)
{
    Nod *current = team->value;
    while (current != NULL)
    {
        Nod *temp = current;
        current = current->next;
        freePlayer(temp);
    }
}

void freeTeam(Node *team)
{
    free(team->team_name);
    freeTeamPlayers(team);
//    free(team->value);
    free(team);
}

void freeQueue(Queue *q)
{
    while (!isEmpty(q))
    {
        Match *temp = q->front;
        q->front = q->front->next;
        free(temp->team1);
        free(temp->team2);
        free(temp);
    }
    free(q);
}

void freeAVLNode(Node_avl *node)
{
    free(node->val->team_name);
    freeTeamPlayers(node->val);
    free(node->val);
    free(node);
}

void freeAVLTree(Node_avl *root)
{
    if (root == NULL)
        return;
    freeAVLTree(root->left);
    freeAVLTree(root->right);
    freeAVLNode(root);
}

void freeBSTNode(Node_bst *node)
{
    free(node->val->team_name);
    freeTeamPlayers(node->val);
    free(node->val);
    free(node);
}

void freeBST(Node_bst *root)
{
    if (root == NULL)
        return;
    freeBST(root->left);
    freeBST(root->right);
    freeBSTNode(root);
}


