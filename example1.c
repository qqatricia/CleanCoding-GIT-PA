/*Determinati daca exista sau nu drum direct intre doua restaurante dintr-o retea de tip graf*/
#include <stdlib.h>
#include <stdio.h>

typedef struct Node {
    int data;
    struct Node *next;
} NODE;
/// pentru simplitate, folosim int uri pt a numi restaurantel/locatiile
/// ex: 1 - restaurantul 1 si tot asa    

typedef struct g {
    int v;
    int *vis;
    NODE **alst;  // Schimbat din struct NODE** în NODE**
} GPH;

typedef struct s {
    int t;
    int scap;
    int *arr;
} STK;

NODE *create_node(int v) {
    NODE *nn = malloc(sizeof(NODE));
    nn->data = v;
    nn->next = NULL;
    return nn;
}

void add_edge(GPH *g, int src, int dest) {
    NODE *nn = create_node(dest);
    nn->next = g->alst[src];
    g->alst[src] = nn;

    nn = create_node(src);
    nn->next = g->alst[dest];
    g->alst[dest] = nn;
}

GPH *create_g(int v) {
    GPH *g = malloc(sizeof(GPH));
    g->v = v;
    g->alst = malloc(v * sizeof(NODE *));
    g->vis = malloc(sizeof(int) * v);

    for (int i = 0; i < v; i++) {
        g->alst[i] = NULL;
        g->vis[i] = 0;
    } 
    return g;
}

STK *create_s(int scap) {
    STK *s = malloc(sizeof(STK));
    s->arr = malloc(scap * sizeof(int));
    s->t = -1;
    s->scap = scap;

    return s;
}

void push(int pshd, STK *s) {
    if (s->t < s->scap - 1) {
        s->t = s->t + 1;
        s->arr[s->t] = pshd;
    }
}

void DFS(GPH *g, STK *s, int v_nr) {
    NODE *aux = g->alst[v_nr];
    g->vis[v_nr] = 1;
    push(v_nr, s);

    while (aux != NULL) {
        int con_ver = aux->data;
        if (g->vis[con_ver] == 0) {
            DFS(g, s, con_ver);
        }
        aux = aux->next;
    }
}

void insert_edges(GPH *g, int edg_nr) {
    int src, dest;
    printf("adauga %d muchii (numerotate de la 0)\n", edg_nr);
    for (int i = 0; i < edg_nr; i++) {
        scanf("%d%d", &src, &dest);
        add_edge(g, src, dest);
    }
}

void wipe(GPH *g) {
    for (int i = 0; i < g->v; i++) {
        g->vis[i] = 0;
    }
}   

int path_exists(GPH *g, int src, int dest) { // 0 sau 1 daca poate fi sau nu ajuns
    STK *stack = create_s(g->v * 2);
    DFS(g, stack, src);
    for (int i = 0; i <= stack->t; i++) {
        if (stack->arr[i] == dest) {
            free(stack->arr);
            free(stack);
            return 1;
        }
    }
    free(stack->arr);
    free(stack);
    return 0;
}

int main() {
    int nrv, edg_nr;
    
    printf("cate noduri are graful? ");
    scanf("%d", &nrv);

    printf("cate muchii are graful? ");
    scanf("%d", &edg_nr);

    GPH *g = create_g(nrv);
    insert_edges(g, edg_nr);

    int src, dest;

    printf("Introdu doua noduri pentru a verifica daca exista drum direct (DFS): ");
    scanf("%d%d", &src, &dest);

    wipe(g);
    if (path_exists(g, src, dest)) {
        printf("Exista drum intre %d si %d.\n", src, dest);
    } 
    else {
        printf("Nu exista drum intre %d si %d.\n", src, dest);
    }
    
    // Eliberare memorie
    for (int i = 0; i < g->v; i++) {
        NODE *node = g->alst[i];
        while (node != NULL) {
            NODE *temp = node;
            node = node->next;
            free(temp);
        }
    }
    free(g->alst);
    free(g->vis);
    free(g);
    
    return 0;
}
