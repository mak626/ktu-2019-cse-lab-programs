/*
Input : mem[]       = {100, 500, 200, 300, 600};
        process[]   = {212, 417, 112, 426};
*/

/*
    mem is an array of containing sizes of each block

    alloted is an array which is initally all initialised to -1 to indicate that the memory location is free. 
    Otherwise it will have the size of the process alloted to it

    processes is an array containing sizes of each process
*/
void bestFit(int mem[], int alloted[], int processes[], int mem_max_size, int process_max_size)
{
    for (int i = 0; i < process_max_size; i++)
    {
        int best_fit_pos = -1;
        int cur_process_size = processes[i];

        for (int j = 0; j < mem_max_size; j++)
        {
            int cur_mem_size = mem[j];

            if (cur_mem_size >= cur_process_size && alloted[j] == -1)
            {
                if (best_fit_pos == -1)
                    best_fit_pos = j;
                else if (cur_mem_size < mem[best_fit_pos])
                    best_fit_pos = j;
            }
        }

        if (best_fit_pos != -1)
        {
            alloted[best_fit_pos] = processes[i];
            prinf("Process of size %d alloted to location %d", processes[i], best_fit_pos);
        }
        else
            prinf("No mem location found for process %d", processes[i]);
    }
}