//
// Created by Endon Giant on 28/11/2019.
//

#include "virtual_machine.h"

void    free_carriage(t_corewar *vm)
{
    t_carriage *tmp;
    t_carriage *save_next;

    tmp = vm->start_carriage;
    while(tmp)
    {
        save_next = tmp->next;
        free(tmp->operation);
        free(tmp);
        tmp = save_next;
    }
    vm->start_carriage = NULL;
}

void    free_corewar(t_corewar *vm)
{
    int n;

    n = 0;
    if (vm->cores)
    {
        while (vm->cores[n])
        {
            free(vm->cores[n]->executable_file_name);
            free(vm->cores[n++]);
        }
        free(vm->cores);
    }
    if (vm->start_carriage)
        free_carriage(vm);
    // winner ссылается на структуру в cores?
}