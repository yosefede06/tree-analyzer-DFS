#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

//magic numbers
#define MAX_CHAR 1024
#define MESSAGE_ERROR "Invalid input\n"
#define MESSAGE_INPUT "Usage: TreeAnalyzer <Graph File Path> <First Vertex> <Second Vertex>\n"
#define PI 10
struct Node{
    int visited;
    long int dest;
    struct Node* next;
};
int check_number(char str[]) {
    for (size_t i = 0; i < strlen(str); i++) {
        if (isdigit(str[i]) == 0){
            return EXIT_FAILURE;
        }
    }
    return EXIT_SUCCESS;
}
long int max_function(long int a, long int b){
    if (a < b){
        return b;
    }
    return a;
}
int check_number_space(char *data, int * number_of_children){
    size_t i = 0;
    int count = 0;
    while (i < strlen(data)){
        if (data[i] != ' '){
            if (isdigit(data[i]) == 0){
                return EXIT_FAILURE;
            }
            count ++;
            i++;
        }
        else{
        i++;}
    }
    *number_of_children = count;
    return EXIT_SUCCESS;
}
int check_minus(char *data){
    if (strcmp(data, "-") == 0){
        return EXIT_SUCCESS;
    }
    else{
        return EXIT_FAILURE;
    }
}
int check_valid_argument(int argc, char *buffer) {
    if (argc != 4){
        fprintf(stderr, MESSAGE_INPUT);
        return EXIT_FAILURE;
    }
    if (strcmp(buffer, "") == 0){
        fprintf(stderr, MESSAGE_ERROR);
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
int check_number_vertices(char * data, long int *vertices){
    size_t length_size = strlen(data);
    if (length_size > 0) {
        if (data[length_size - 1] == '\n') {
            data[--length_size] = '\0';
        }
    }
    if (check_number(data) == EXIT_FAILURE){
        fprintf(stderr, MESSAGE_ERROR);
        return EXIT_FAILURE;
    }
    *vertices = strtol(data, NULL, PI);
    if (*vertices == 0){
        fprintf(stderr, MESSAGE_ERROR);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;

}
int extract_data(char data[], FILE *my_file,
                 struct Node** head, long int vertices,
                         long int *arr){
    long int count = 0;
    long int val;
    while (fgets(data, MAX_CHAR, my_file) != NULL){
        size_t length_size = strlen(data);
        if (length_size > 0) {
            if (data[length_size - 1] == '\n') {
                data[--length_size] = '\0';
            }
        }
        int number_of_children = 0;
        if(check_number_space(data,
                              &number_of_children) == EXIT_FAILURE &&
                              check_minus(data) == EXIT_FAILURE){
            return EXIT_FAILURE;}
        size_t i = 0;
        while (i < strlen(data)){
            char curr[MAX_CHAR];
            int j = 0;
            while (i < strlen(data) && data[i] != ' '){
                curr[j] = data[i];
                i++;
                j++;
            }
            curr[j] = ' ';
            struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));
            new_node->visited = 0;
            if (curr[0] == '-'){
                new_node->dest = -1;
                new_node->next = head[count];
                head[count] = new_node;
                break;
            }
            //covers the case in which a node has an edge to itself
            if (strtol(curr, NULL, PI) == count){
                return EXIT_FAILURE;
            }
            val = strtol(curr, NULL, PI);
            if (val >= vertices || 1 == arr[val]){
                return EXIT_FAILURE;
            }
            arr[strtol(curr, NULL, PI)] = 1;
            new_node->dest = val;
            new_node->next = head[count];
            head[count] = new_node;
            i++;
        }
        count++;
    }
    return EXIT_SUCCESS;
}
int dfs_visit(struct Node** head, long int vertices,
        struct Node* curr_node,
        long int *max_branch, long int *min_branch,
        long int count_branch, long int * longest_vertex,
        long int curr_vertex){
    if (curr_node -> dest == -1){
        curr_node->visited = 1;
        if(*max_branch < count_branch){
            *longest_vertex = curr_vertex;
            *max_branch = count_branch;
        }
        if(*min_branch > count_branch){
            *min_branch = count_branch;
        }
        return 0;
    }
    while(curr_node != NULL){
        if (curr_node->visited == 0){
            curr_node->visited = 1;
            curr_vertex = curr_node-> dest;
            dfs_visit(head, vertices, head[curr_node->dest],
                      max_branch, min_branch, count_branch + 1,
                      longest_vertex, curr_vertex);
            }
            curr_node = curr_node->next;
        }
    return 1;
}
int check_is_tree(struct Node** head, long int vertices){
    long int i;
    for (i = 0; i < vertices; i++)
        {
            struct Node* ptr = head[i];
            while (ptr != NULL)
            {
                if(ptr->visited == 0){
                    fprintf(stderr, MESSAGE_ERROR);
                    return EXIT_FAILURE;}
                ptr = ptr->next;
            }
        }
        return EXIT_SUCCESS;
}
int first_path_func(long int *path_1,
                    long int * curr_path,
                    struct Node** head,
                            struct Node* curr_node,
        long int count_branch, char *argv[], long int * pointt){
    if (curr_node -> dest == -1){
        curr_node->visited = 0;
        return 1;
    }
    while(curr_node != NULL){
        if (curr_node->visited == 1){
            curr_node->visited = 0;
            curr_path[count_branch] = curr_node->dest;
            if (strtol(argv[2], NULL, PI) == curr_node->dest){
                for(long int k = 1; k < count_branch + 1; k++){
                    path_1[k] = curr_path[k];
                    *pointt = count_branch + 1;
                }
            }

            first_path_func(path_1, curr_path, head, head[curr_node->dest],
                    count_branch + 1, argv, pointt);
        }
        curr_node = curr_node->next;
    }
    return 1;
}
int second_path_func(long int *path_2,
                     long int * curr_path,
                     struct Node** head,
                             struct Node* curr_node,
        long int count_branch, char *argv[], long int * point){
    if (curr_node -> dest == -1){
        curr_node->visited = 1;
        return 1;
    }
    while(curr_node != NULL){
        if (curr_node->visited == 0){
            curr_node->visited = 1;
            curr_path[count_branch] = curr_node->dest;
            if (strtol(argv[3], NULL, PI) == curr_node->dest){
                for(long int k = 1; k < count_branch + 1; k++){
                    path_2[k] = curr_path[k];
                    *point = count_branch + 1;
                }
            }
            second_path_func(path_2, curr_path,
                             head, head[curr_node->dest],
                            count_branch + 1, argv, point);
        }
        curr_node = curr_node->next;
    }
    return 1;
}
int get_root(long int curr, long int * root,
             long int vertices, long int * arr){
    for (long int j = 0; j < vertices; j++){
        if (arr[j] == 0){
            curr += 1;
            *root = j;
        }
    }
    free(arr);
    if (curr != 1){
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
int check_valid_argv(long int start,
                     long int end, long int vertices){
    if ((0 <= start) && (start < vertices) &&
    (0 <= end) && (end < vertices)){
        return EXIT_SUCCESS;
    }
    return EXIT_FAILURE;
}
void print_data(long int root, long int vertices,
                long int max_branch,
               long int min_branch, long int point_start_path,
               long int point_final_path,
               long int * path_1, long int * path_2,
               long int start, long int end, long int max_max_val){
    fprintf(stdout, "Root Vertex: %ld\n", root);
    fprintf(stdout, "Vertices Count: %ld\n", vertices);
    fprintf(stdout, "Edges Count: %ld\n", vertices - 1);
    fprintf(stdout, "Length of Minimal Branch: %ld\n", min_branch - 1 );
    fprintf(stdout, "Length of Maximal Branch: %ld\n", max_branch - 1);
    fprintf(stdout, "Diameter Length: %ld\n", max_max_val);
    fprintf(stdout, "Shortest Path Between %ld and %ld:", start, end);
    long int common = 0;
    for(long int j= 0; j < point_start_path && j < point_final_path; j++){

        if (path_1[j] == path_2[j]){
            common ++;
        }
        else{
            break;
        }
    }
    for(long int j = point_start_path - 1; j >= common - 1; j--){
        fprintf(stdout, " ");
        fprintf(stdout, "%ld", path_1[j]);

    }
    for(long int j = common; j < point_final_path; j++){
        fprintf(stdout, " ");
        fprintf(stdout, "%ld", path_2[j]);
    }
    fprintf(stdout, "\n");
}

int longest_path(struct Node ** head,
        long int vertices, struct Node* curr_node
        ,long int not_value, long int *new_branch,
        long int new_count_branch, int my_bol){
    if (curr_node -> dest == -1){
        curr_node->visited = my_bol;
        if(*new_branch < new_count_branch){
            *new_branch = new_count_branch;
        }
        return 0;
    }

    while(curr_node != NULL){
        if (curr_node -> dest == not_value){
            curr_node = curr_node ->next;
            if (curr_node == NULL){
                break;
            }
        }
        if (curr_node->visited != my_bol){
            curr_node->visited = my_bol;
            longest_path(head, vertices,
                         head[curr_node->dest], not_value,
                         new_branch,
                         new_count_branch + 1, my_bol);
        }
        curr_node = curr_node->next;
    }
    return 1;
}
int last_path_func(long int *path_1, long int * curr_path,
                   struct Node** head, struct Node* curr_node,
        long int count_branch, long int longest_vertex,
        long int * pointt){
    if (curr_node -> dest == -1){
        curr_node->visited = 0;
        return 1;
    }
    while(curr_node != NULL){
        if (curr_node->visited == 1){
            curr_node->visited = 0;
            curr_path[count_branch] = curr_node->dest;
            if (longest_vertex == curr_node->dest){
                for(long int k = 1; k < count_branch + 1; k++){
                    path_1[k] = curr_path[k];
                    *pointt = count_branch + 1;
                }
            }

            last_path_func(path_1, curr_path,
                           head, head[curr_node->dest],
                            count_branch + 1,
                            longest_vertex, pointt);
        }
        curr_node = curr_node->next;
    }
    return 1;
}
int main(int argc, char *argv[]){
        long int vertices = 0;
        char data[MAX_CHAR];
        FILE *my_file = fopen(argv[1], "r");
        fgets(data, MAX_CHAR, my_file);
        if (check_valid_argument(argc, data) == EXIT_FAILURE ||
        check_number_vertices(data, &vertices) == EXIT_FAILURE) {
            fclose(my_file);
            return EXIT_FAILURE;
        }
        struct Node *(*head);
        head = malloc(vertices * sizeof(struct Node *));
        //in case malloc fails
        if (head == NULL) {
            return EXIT_FAILURE;
        }
        unsigned i;
        for (i = 0; i < vertices; i++) {
            head[i] = NULL;
        }
        long int *arr = (long int*) calloc(vertices, sizeof(long int));
        if (extract_data(data, my_file, head, vertices, arr) == EXIT_FAILURE){
            fprintf(stderr, MESSAGE_ERROR);
            free(arr);
            free(head);
            fclose(my_file);
            return EXIT_FAILURE;
        }
        fclose(my_file);
        long int root;
        long int check = 0;
        if (get_root(check, &root, vertices, arr) == EXIT_FAILURE){
            fprintf(stderr, MESSAGE_ERROR);
            return EXIT_FAILURE;
        }
        long int min_branch = vertices;
        long int max_branch = 0;
        long int count_branch = 1;
        long int longest_vertex = 0;
        long int curr_vertex = 0;

        dfs_visit(head, vertices, head[root],
                  &max_branch, &min_branch, count_branch,
                  &longest_vertex, curr_vertex);
        check_is_tree(head, vertices);
        long int start = strtol(argv[2], NULL, PI);
        long int end = strtol(argv[3], NULL, PI);
        if (check_valid_argv(start, end, vertices) == EXIT_FAILURE){
            fprintf(stderr, MESSAGE_ERROR);
            return EXIT_FAILURE;
        }
        long int *path_1 = (long int*) calloc(vertices, sizeof(long int));
        if (path_1 == NULL){
            fprintf(stderr, MESSAGE_ERROR);
            return EXIT_FAILURE;
        }
        long int *path_2 = (long int*) calloc(vertices, sizeof(long int));
        if (path_2 == NULL){
            fprintf(stderr, MESSAGE_ERROR);
            return EXIT_FAILURE;
        }
        
        path_1[0] = root;
        path_2[0] = root;
        long int point_start_path = 1;
        long int point_final_path = 1;
        long int *curr_path_1 = (long int*) calloc(vertices, sizeof(long int));
        if (curr_path_1 == NULL){
            fprintf(stderr, MESSAGE_ERROR);
            return EXIT_FAILURE;
        }
        first_path_func(path_1, curr_path_1, head ,
                        head[root], count_branch, argv, &point_start_path);
        free(curr_path_1);
        long int *curr_path_2 = (long int*) calloc(vertices, sizeof(long int));
        if (curr_path_2 == NULL){
        fprintf(stderr, MESSAGE_ERROR);
        return EXIT_FAILURE;
        }
        second_path_func(path_2, curr_path_2, head ,
                         head[root], count_branch, argv, &point_final_path);
        free(curr_path_2);
        long int * my_array_long = (long int *) calloc(vertices, sizeof(long int));
        if (my_array_long == NULL){
            fprintf(stderr, MESSAGE_ERROR);
            return EXIT_FAILURE;
        }
        long int * curr_long = (long int *) calloc(vertices, sizeof(long int));
        if (curr_long == NULL){
            fprintf(stderr, MESSAGE_ERROR);
            return EXIT_FAILURE;
        }
        long int point_long_path = 1;
        my_array_long[0] = root;
        last_path_func(my_array_long, curr_long, head ,
                       head[root], count_branch, longest_vertex, &point_long_path);
        free(curr_long);
        int bol_value = 1;
        long int new_branch = 0;
        long int new_count_branch = 0;
        long int max_max_val = 0;
        long int k_val;
        long int count_for_max = 0;
        for (k_val = point_long_path - 2; k_val >= 0; k_val--){
            long int not_value = my_array_long[k_val + 1];
            if (bol_value == 1){
                bol_value = 0;
            }
            else{
                bol_value = 1;
            }
            longest_path(head, vertices, head[my_array_long[k_val]], not_value,
                         &new_branch, new_count_branch, bol_value);
            count_for_max += 1;
            max_max_val = max_function(count_for_max + new_branch,
                                       max_max_val);
            new_branch = 0;
        }
        free(my_array_long);
        free(head);
        print_data(root, vertices, max_branch, min_branch,
                   point_start_path, point_final_path,
                   path_1, path_2, start, end, max_max_val);
        free(path_1);
        free(path_2);
        return EXIT_SUCCESS;
}

