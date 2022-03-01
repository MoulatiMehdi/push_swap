#include<stdio.h>
#include<stdlib.h>

typedef struct s_node {
	int number;
	struct s_node * prev;	//prev node
	struct s_node * next; //next node
}t_node;

typedef struct s_stack{
	t_node* head; //first node 
	t_node* foot; //last node 
	int taille;   //number of node 
}t_stack;

//initialize the the stack 
t_stack* ft_create_stack(void){
	
	//create new stack with initialization
	t_stack* new_stack=(t_stack*)malloc(sizeof(t_stack));
	new_stack->head=NULL;
	new_stack->foot=NULL;
	new_stack->taille=0;
	
	return new_stack;
}

//insert the new_node at the end of the stack
void ft_insert(t_stack** s_a,int value){
	
	t_node*new_node;
	new_node=(t_node*)malloc(sizeof(t_node));

	if(new_node==NULL) return;
	
	new_node->number=value;
	new_node->next=NULL;
	new_node->prev=NULL;

	if((*s_a)->head==NULL){
		
		(*s_a)->head=new_node;
		(*s_a)->foot=new_node;
		(*s_a)->taille++;
		return;
	}

	((*s_a)->foot)->next=new_node;
	new_node->prev=((*s_a)->foot);
	
	(*s_a)->foot=new_node;
	(*s_a)->taille++;
}

//insert the node on top of the stack
void ft_insert_h(t_stack** s_a,int value){
	
	t_node*new_node;
	new_node=(t_node*)malloc(sizeof(t_node));

	if(new_node==NULL) return;
	
	new_node->number=value;
	new_node->next=NULL;
	

	if((*s_a)->head==NULL){

		(*s_a)->head=new_node;
		(*s_a)->foot=new_node;
		(*s_a)->taille++;
		return;
	}

	((*s_a)->head)->prev=new_node;
	new_node->next=((*s_a)->head);
	
	(*s_a)->head=new_node;
	(*s_a)->head->prev=NULL;
	
	(*s_a)->taille++;
}

//delete the first node in stack 
void ft_delete(t_stack**s_a){
	
	if((*s_a)->taille<=0) return;
	
	t_node* p=(*s_a)->head;
	
	if((*s_a)->taille >1)((*s_a)->head)->next->prev=NULL;
	(*s_a)->head=((*s_a)->head)->next;	
	(*s_a)->taille--;
	
	p->next=NULL;
	p->prev=NULL;
	p->number=0;
	free(p);
}

// print both stacks
void ft_print_stacks(t_stack* s_a,char c_a,t_stack*s_b,char c_b){

	t_node*p_a;
	t_node*p_b;
	
	p_a=s_a->head;
	p_b=s_b->head;
	
	printf("\t stack %c           stack %c\n",c_a,c_b);
	printf("\t---------         ---------\n");

	while(p_a!=NULL||p_b!=NULL){
		
		printf("\t");
		if(p_a!=NULL){
			printf("%5d",p_a->number);
			p_a=p_a->next;
		}
		else printf("     ");
		printf("             ");
		if(p_b!=NULL){
			
			printf("%5d",p_b->number);
			p_b=p_b->next;
		}
		printf("\n");		
	}
	
	free(p_a);
	free(p_b);
	printf("------------------------------------------------\n");
		
}


