
#include"operations.h"
#define MAXINT 2147483647

t_stack*sort(t_stack* a);

int find_min_pos(t_stack*a){
	
	if(a->head==NULL) return -1;
	
	t_node*p=a->head;
	
	int min=a->head->number;
	int position;
	int i=0;
	
	while(p!=NULL )	{
		
		if(min>p->number){
			min=p->number;
			position=i;
		}
		i++;
		p=p->next;
	}
	
	return position;
}

int is_order(t_stack*a){
	
	t_stack* cp = sort(a);
	t_node* p=cp->head;
	while(p->next!=NULL){
		if(p->number<p->next->number) return 0;
	}
	return 1;
}

static int initia(t_stack*a,t_stack*list,t_stack*num){
	
	t_node* p=a->head;
	
	t_node* list_i;
	t_node* num_i;
	t_node* list_j;
	t_node* num_j;
	int max=0;
	
	
	while(p!=NULL){

		ft_insert(&list,1);
		ft_insert(&num,p->number);
		p=p->next;
	}
	
	list_i=list->head;
	num_i=num->head;
	p=a->head;
	
	while(p!=NULL){
		num_j=num->head;
		list_j=list->head;
		while(num_j->number!=num_i->number){

			if(num_i->number > num_j->number && list_i->number+1 > list_j->number)
				list_i->number=list_j->number +1;
				
			if(list_i->number>max) max=list_i->number;
				num_j=num_j->next;
				list_j=list_j->next;
		}
		list_i=list_i->next;
		num_i=num_i->next;
		p=p->next;
	}
	return max;
}

//largest increasing numbers and put is in sort
void Larg_inc_seq(t_stack*a,t_stack* sort){
	
	t_node* p=a->head;
	int j=0;
	
	t_stack*list=ft_create_stack();
	t_stack*num=ft_create_stack();
	
	j=initia(a,list,num);
	
	t_node* list_i=list->head;
	t_node* num_i=num->head;

	while(list_i->next->number!=j) {
		list_i=list_i->next;
		num_i=num_i->next;
	}
	
	j--;
	ft_insert(&sort,num_i->next->number);	
	while(j>0){
		if(list_i->number==j && sort->head->number > num_i->number ){
			ft_insert_h(&sort,num_i->number);
			j--;
		}
		list_i=list_i->prev;
		num_i=num_i->prev;
	}
}

/*
** push the number from stack a  to b 
** if wasnt in least incresing numbers 
*/
int push_disorder(t_stack* a,t_stack*b){
	
	t_stack* tmp=ft_create_stack();
	
	Larg_inc_seq(sort(a),tmp);
	t_node* p_a=a->head;
	t_node* p_t=NULL;
	
	while(tmp->taille!= a->taille){
			
		p_t=tmp->head;	
		while(p_t!=NULL && p_t->number !=a->head->number) 
			p_t=p_t->next;
		
		if(p_t==NULL){
			push(&b,&a);
			printf("pb\n");
		} 
		else {
				
			free(p_t);
			ft_rot(&a);
			printf("ra\n");
			
		}
	}
}

/*
** solve the problem 
*/
void ft_solve(t_stack *a,t_stack *b){
	if(!is_order(a)){
		
		t_stack** pos;
		push_disorder(a,b);
		while(b->taille!=0){
			pos=best_number(a,b);		
			max_move(&a,&b,pos,best_move(pos,b,a));
		}
	}
	int min_pos=find_min_pos(a);
	
	if(a->taille/2>=min_pos)
		while(min_pos>0){
			printf("ra\n");
			ft_rot(&a);
			min_pos--;
		}
	else
		while(min_pos<a->taille){
			printf("rra\n");
			ft_rev_rot(&a);
			min_pos++;
		}	
}

int ft_isdigit(int c){
	return (c<='9'&&c>='0');
}
int is_error(const char* s,t_stack*a){
	
	t_node*p=a->head;
	unsigned long long i=0;
	int signe=1;
	if(*s=='+'|| *s=='-'){
		signe=(*s++=='+')? 1: -1;
	}
	
	while(*s!='\0'&& s!=NULL && i< MAXINT){
		if(!ft_isdigit(*s)) return 1;	
		i=i*10+*s-'0';
		s++;
	}
	
	if(i>MAXINT ) return 1;
	i*=signe;
	while(p!=NULL){
		if(p->number==i) return 1;
		p=p->next;
	}
	return 0;
	
}
