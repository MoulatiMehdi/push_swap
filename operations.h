#include"stack.h"


#ifndef PUSH_SWAP_H
#define PUSH_SWAP_H
int Max_ab(int a,int b){
	if(a>b) return a;
	return b;
}
int Min_ab(int a,int b){
	if(b>a) return a;
	return b;
}

/*
**sa or sb
*/
void swap(t_stack** a){

	if((*a)->taille<2) return;
	
	int tmp=(*a)->head->number;
	(*a)->head->number=(*a)->head->next->number;
	(*a)->head->next->number=tmp;
	
}
/* 
**  pa or pb
*/
void push(t_stack** a,t_stack **b){
	
	if((*b)->taille<1) return;
	
	int number=(*b)->head->number;
	ft_delete(b);
	ft_insert_h(a,number);
	
}

/* 
** ra or rb
*/
void ft_rot(t_stack** a){
	
	if((*a)->taille<2) return;
	
	t_node* p=(*a)->head;
	
	(*a)->head=p->next;
	p->next->prev=NULL;
	p->next=NULL;
	p->prev=(*a)->foot;
	
	(*a)->foot->next=p;
	(*a)->foot=p;
	
}

/*
** rra or rrb
*/
void ft_rev_rot(t_stack** a){
	
	if((*a)->taille<2) return;
	
	t_node* p=(*a)->foot;
	
	(*a)->foot=p->prev;
	p->prev->next=NULL;
	p->prev=NULL;
	p->next=(*a)->head;
	
	(*a)->head->prev=p;
	(*a)->head=p;
		
}

/*
**ss
*/
void ft_ss(t_stack**a,t_stack**b){
	swap(a);
	swap(b);
}

/*
**rr
*/
void ft_rot_ab(t_stack**a,t_stack**b){
	ft_rot(a);
	ft_rot(b);
}

/*
** rrr
*/
void ft_rev_rot_ab(t_stack**a,t_stack**b){
	ft_rev_rot(a);
	ft_rev_rot(b);
}

/*
**rotate until the first number in stack is the minimum
*/
t_stack*sort(t_stack* a){
	
	t_node* p=a->head;
	t_stack *cp=ft_create_stack();;
	int min=p->number;
	int position=0;
	int i=0;

	while(p!=NULL){
		ft_insert(&cp,p->number);
		if(min > p->number){
			min=p->number;
			position=i;
		} 
		i++;
		p=p->next;
	}
	if(position > cp->taille-position) 
		while (cp->head->number!=min)
			ft_rev_rot(&cp);		
	else
		while(cp->head->number!=min)	
			ft_rot(&cp);
				
	return cp;
}

/*
** find the maximum number in stack that isn'r greater than a number
*/
int find_max_pos(t_stack*a,int num){
	
	t_node* p ;
	
	int max=0;
	int pos=0;
	int i=0;
	
	p=a->head;
	
	while(p!=NULL){
		if(max<p->number && p->number <num) {
			max=p->number;
			pos=i;
		}
		p=p->next;
		i++;
	}
	
	if(pos < a->taille/2) return  pos+1;
	else return -(a->taille - pos -1) ;
}

/*
** find the best number to push in stack b to push in stack a
** using pos as reference 
*/
int best_move(t_stack**pos,t_stack*b,t_stack*a){
	
	t_node*p=pos[0]->head;
	t_node*q=pos[1]->head;

	t_node* r=b->head;
	int num=b->head->number;
	
	int min;
	int move=0;
	int target=r->number;
	
	
	if(p->number>0 ^ q->number >0){
		min= - p->number +  q->number;
	}
	else{
		min=Min_ab(p->number,q->number);
	}
		
	if(min <0)	min *=-1;
	
	 
	while(q!=NULL){
	 	
	 	
	 	if(p->number>0 ^ q->number >0)	move= - p->number +  q->number;
		else 	move=Max_ab(p->number,q->number);
			
		if(move <0)	move *=-1;
		
		if(min>move) {
			min=move;
			target=r->number;
		}

		q=q->next;
		p=p->next;
		r=r->next;
	}

	return target;
}
/*
** push num of stack b in the stack a with minimum moves
*/
void max_move(t_stack**a,t_stack **b,t_stack**pos,int num){
	
	t_node* p=pos[0]->head;
	t_node* q=pos[1]->head;
	t_node* r=(*b)->head;
	
	int max;
	int min;
	while(r->number!=num){
		q=q->next;
		p=p->next;
		r=r->next;
		
	}
	
	min=p->number;
	max=q->number;
	if(q->number*p->number >0){
		if(p->number>=0) {
			max=Max_ab(p->number,q->number);
			min=Min_ab(q->number,p->number);
				
			if(max==q->number)
				while(max!=min){
					printf("rb\n");
					ft_rot(b);
					ft_rot_ab(&pos[0],&pos[1]);
					max--;
				}
			else
				while(max!=min){
					printf("ra\n");
					ft_rot(a);
					max--;
				}
				
			while(min!=0){
				printf("rr\n");
				ft_rot_ab(a,b);
				ft_rot_ab(&pos[0],&pos[1]);
				min--;
			}
			push(a,b);
		}
		else{
			max=Min_ab(p->number,q->number);
			min=Max_ab(p->number,q->number);
				
			if(max=q->number)
				while(max!=min){
	
					printf("rrb\n");
					ft_rev_rot(b);
					ft_rev_rot_ab(&pos[0],&pos[1]);
					max++;
				}
			else
				while(max!=min){
					printf("rra\n");
					ft_rev_rot(a);
					max++;
				}
			
			while(min!=0){
				printf("rrr\n");
				ft_rev_rot_ab(a,b);
				ft_rev_rot_ab(&pos[0],&pos[1]);
				min++;
			}
			push(a,b);
			
		}
	}
	else{
			
				while(p->number >0){
					printf("ra\n");
					ft_rot(a);
					ft_rot_ab(&pos[0],&pos[1]);
					p->number--;
				}
				
				while(q->number >0){
					printf("rb\n");
					ft_rot(b);
					ft_rot_ab(&pos[0],&pos[1]);
					q->number--;
				}
				
				while(p->number<0){
					printf("rra\n");
					ft_rev_rot(a);
					ft_rot_ab(&pos[0],&pos[1]);
					p->number++;
				}
				while(q->number<0){
					printf("rrb\n");
					ft_rev_rot(b);
					ft_rot_ab(&pos[0],&pos[1]);
					q->number++;
				}
			push(a,b);
			printf("pa\n");

	}
}
t_stack **best_number(t_stack*a,t_stack*b){
	
	t_stack** pos=(t_stack**)malloc(sizeof(t_stack*)*2);
	
	pos[0]=ft_create_stack();
	pos[1]=ft_create_stack();
	
	t_node * q=b->head;
	t_node * p;
	int i=0;
	
	while(q!=NULL){

		ft_insert(&pos[0],find_max_pos(a,q->number));
		
		if(i <= b->taille/2) ft_insert(&pos[1],i);
		else ft_insert(&pos[1],-(b->taille - i)) ;	
		
		q=q->next;
		i++;
		
	}
	 p=pos[0]->head;
	 q=pos[1]->head;
	 
	
	return pos;
}
#endif
