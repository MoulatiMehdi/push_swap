#include"solve.h"

void ft_insert_h(t_stack**a,int value);
void ft_print_stacks(t_stack* s_a,char c_a,t_stack* s_b,char c_b);
int is_error(const char*s,t_stack*a);
void ft_solve(t_stack *a,t_stack *b);

int main(int n_arg,char*arg[]){
	
	t_stack*a=ft_create_stack();
	t_stack*b=ft_create_stack();
	
	if(n_arg<2) printf("stack empty\n");
	else
	{
		while(--n_arg>=1){
			if(is_error(arg[n_arg],a)) {
				printf("ERROR\n");
				exit(-1);
			}
			ft_insert_h(&a,atoi(arg[n_arg]));
		}
		ft_solve(a,b);
		ft_print_stacks(a,'a',b,'b');
	}	
	
	return 0;		
}
