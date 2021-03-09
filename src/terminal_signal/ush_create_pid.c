#include "../../inc/main_dependecy.h" 




static t_pid_list  * create_pid(pid_t pid,int number){
    t_pid_list *new_head = (t_pid_list *) malloc(sizeof(new_head));
    new_head->next = NULL;
    new_head->number = number;
    new_head->pid = pid;
    new_head->parameters = NULL;
  //  printf("\n2: PAR %s\n", new_head->parameters);
  // printf("\nadress: %p\n", (void *)new_head->parameters);
    return new_head;
}

static void push_start(t_pid_list ** head,pid_t pid) {
 
    t_pid_list * new_node;
    new_node = create_pid(pid, (*head)->number + 1);
    new_node->next = (*head); 
    (*head) = new_node;
}



void ush_create_pid(t_pid_list **head,pid_t pid){
    if(*head == NULL){
        (*head) = create_pid(pid,1);
    }else {
        push_start(&(*head),pid);
    }
}



