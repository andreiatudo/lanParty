#include "lanPartyLib.h"

int main (int argc, char* argv[])
{
/*printf("Number of input files: %d\n", argc);
printf("Exec name: %s\n", argv[0]);
printf("File1: %s\n", argv[1]);
printf("File2: %s\n", argv[2]);
printf("File3: %s\n", argv[3]);
// FILE *f_in = fopen( argv[1], "r" );*/

    FILE *c_in = fopen(argv[1], "r");
    FILE *d_in = fopen(argv[2], "r");
    FILE *r_out = fopen(argv[3], "w");

    if (!c_in || !d_in || !r_out) {
        printf("Nasol\n");
        return 1;
    }

    char c;
    int nr_teams;
    int task[5];

    //Citire fisiere
    fscanf(c_in, "%d", &task[0]);
    fscanf(c_in, "%d", &task[1]);
    fscanf(c_in, "%d", &task[2]);
    fscanf(c_in, "%d", &task[3]);
    fscanf(c_in, "%d", &task[4]);
    fscanf(d_in, "%d", &nr_teams);

    //Creare santinela
    Node *head=(Node*)malloc(sizeof(Node));
    head->next=NULL;

    if(task[0]==1)
    {
        for(int i=0;i<nr_teams;i++)
        {
            //Citire echipa
            adaugare(head, d_in);
            fgetc(d_in);
        }
    }

    if(task[1]==1)
    {
        //Calculare numar echipe si punctaje
        int n=0;
        n=n_maxim(nr_teams);
        total_points_function(head);
        //Stergere echipe
        stergere(head, &nr_teams, n);
    }

    afisare(head, r_out);

    
    Node *lista=(Node*)malloc(sizeof(Node));
    if(task[2]==1)
    {
        Queue *q=createQueue();

        Node *aux=head;
        aux=aux->next;
        int nr_teams_now=nr_teams;

        for(int i=0;i<nr_teams_now/2;i++)
        {
            enQueue(q, aux);
            aux=aux->next->next;
        }

        Node *stackW=NULL, *stackL=NULL;
        lista->next=NULL;

        fprintf(r_out, "\n");

        int round_number=0;

        while(nr_teams_now>1)
        {
            round_number++;

            fprintf(r_out, "--- ROUND NO:%d\n", round_number);
            afisare_queue(q, r_out);
            fprintf(r_out, "\n"); 

            Queue *auxiliar=q;

            if(nr_teams_now==8)
            {
                creare_lista(lista, q);
            }

            createStacks(&stackW, &stackL, q);

            deleteStack(&stackL);
            deleteQueue(q);

            q=createQueue();
            nr_teams_now=nr_teams_now/2;

            fprintf(r_out, "WINNERS OF ROUND NO:%d\n", round_number);

            if(round_number==1)
                corectare_punctaje(stackW);
            afisare_stack(stackW, r_out);

            for(int i=0;i<nr_teams_now/2;i++)
            {
                enQueue(q, stackW);
                pop(&stackW);
                pop(&stackW);
            }

            if(nr_teams_now!=1)
                fprintf(r_out, "\n");

            deleteStack(&stackW);
        }
        freeQueue(q);
    }

    Node_bst *bst=NULL;
    if(task[3]==1)
    {
        fprintf(r_out, "\nTOP 8 TEAMS:\n");
        creare_bst(&bst, lista);
        inorder(bst, r_out);
    }

    Node_avl *avl=NULL;
    if(task[4]==1)
    {
        fprintf(r_out, "\nTHE LEVEL 2 TEAMS ARE:\n");
        inorder_selection(bst, &avl);
        int depth = 0;
        print_nodes(avl, 2, depth, r_out);
    }

    Node *aux = head->next;
    while (aux != NULL)
    {
        Node *temp = aux;
        aux = aux->next;
        freeTeam(temp);
    }
    freeAVLTree(avl);
    freeBST(bst);

    fclose(c_in);
    fclose(d_in);
    fclose(r_out);
    return 0;
}

// run date/t15/c.in date/t15/d.in out/out15.in
// make && valgrind --leak-check=full -v ./lanParty ./date/t1/c.in ./date/t1/d.in ./out/out1.out
// make && valgrind --leak-check=full -v ./lanParty ./date/t15/c.in ./date/t15/d.in ./out/out15.out