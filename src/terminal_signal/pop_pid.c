#include "../../inc/main_dependecy.h"





void pop_pid(t_pid_list **head) {
    t_pid_list* prev = NULL;
    if (head == NULL) {
        *head = NULL;
        return;
    }
    prev = (*head);
    (*head) = (*head)->next;
    free(prev);
}
