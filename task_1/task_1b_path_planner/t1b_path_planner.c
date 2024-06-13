
/*
* AstroTinker Bot (AB): Task 1B Path Planner
*
* This program computes the valid path from the start point to the end point.
* Make sure you don't change anything outside the "Add your code here" section.
*/

#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <limits.h>

#ifdef __linux__ // for host pc

    #include <stdio.h>

    void _put_byte(char c) { putchar(c); }

    void _put_str(char *str) {
        while (*str) {
            _put_byte(*str++);
        }
    }

    void print_output(uint8_t num) {
        if (num == 0) {
            putchar('0'); // if the number is 0, directly print '0'
            _put_byte('\n');
            return;
        }

        if (num < 0) {
            putchar('-'); // print the negative sign for negative numbers
            num = -num;   // make the number positive for easier processing
        }

        // convert the integer to a string
        char buffer[20]; // assuming a 32-bit integer, the maximum number of digits is 10 (plus sign and null terminator)
        uint8_t index = 0;

        while (num > 0) {
            buffer[index++] = '0' + num % 10; // convert the last digit to its character representation
            num /= 10;                        // move to the next digit
        }

        // print the characters in reverse order (from right to left)
        while (index > 0) { putchar(buffer[--index]); }
        _put_byte('\n');
    }

    void _put_value(uint8_t val) { print_output(val); }

#else  // for the test device

    void _put_value(uint8_t val) { }
    void _put_str(char *str) { }

#endif

typedef struct {
    uint8_t n_nodes;
    uint8_t **matrix; // adjacency matrix
} Graph;

typedef struct {
    uint8_t *parents;
    uint8_t *distances;
} Paths;

Graph *crt_graph(uint8_t n_nodes) {
    Graph *g = (Graph *) malloc(sizeof(Graph));
    g->n_nodes = n_nodes;
    g->matrix = (uint8_t **) malloc(n_nodes * sizeof(uint8_t *));
    // initializes adjacency matrix
    for (uint8_t i = 0; i < n_nodes; ++i) {
        g->matrix[i] = (uint8_t *) malloc(n_nodes * sizeof(uint8_t));
        for (uint8_t j = 0; j < n_nodes; ++j) {
            g->matrix[i][j] = 0;
        }
    }
    return g;
}


void free_graph(Graph *g) {
    for (uint8_t i = 0; i < g->n_nodes; ++i) {
        free(g->matrix[i]);
    }
    free(g->matrix);
    free(g);
}

void link(Graph *g, uint8_t n_a, uint8_t n_b, uint8_t weight) {
    g->matrix[n_a][n_b] = weight;
    g->matrix[n_b][n_a] = weight;
}

// function is used to find the start node in each iteration
// new st_node is the unvisited node closest to current st_node
uint8_t find_stnode(uint8_t *distances, uint8_t *visited, uint8_t n) {
    // normal version where everything was an int i used -1
    // when compiling i kept getting a seg fault soo using UINT8_MAX instead (255)
    uint8_t min_i = UINT8_MAX;
    for (uint8_t i = 0; i < n; ++i) {
        if (!visited[i] && (min_i == UINT8_MAX || distances[i] < distances[min_i])) {
            min_i = i;
        }
    }
    return min_i;
}

Paths *_dijkstra(Graph *g, uint8_t st_node) {
    uint8_t n = g->n_nodes;
    uint8_t *parents = (uint8_t *) malloc(n * sizeof(uint8_t));
    uint8_t *distances = (uint8_t *) malloc(n * sizeof(uint8_t));
    uint8_t *visited = (uint8_t *) malloc(n * sizeof(uint8_t));
    Paths *paths = (Paths *) malloc(sizeof(Paths));

    // initializes arrays
    for (uint8_t i = 0; i < n; ++i) {
        parents[i] = UINT8_MAX; distances[i] = UINT8_MAX; visited[i] = 0;
    }

    distances[st_node] = 0;
    
    while(1) {
        st_node = find_stnode(distances, visited, n);
        if (st_node == UINT8_MAX) {
            break; // No unvisited nodes left
        }
        
        visited[st_node] = 1; // setting st_node as visited
        
        for (uint8_t i = 0; i < n; ++i) {
            // if connected to st_node and not visited
            if (g->matrix[st_node][i] != 0 && !visited[i]) {
                uint8_t d = distances[st_node] + g->matrix[st_node][i];
                // the distance is smaller than distance saved
                // update distance and parent of node
                if (d <= distances[i]) {distances[i] = d; parents[i] = st_node;}
            }
        }
    }

    paths->parents = parents;
    paths->distances = distances;
    free(visited);
    return paths;
}

// extracts path from Paths variable
uint8_t extract_path(Paths *p, uint8_t st_node, uint8_t end_node, uint8_t *path) {
    uint8_t i = 0;
    // generate path from parents list
    while (st_node != end_node) {
        path[i] = end_node;
        end_node = p->parents[end_node];
        ++i;
    }
    path[i] = st_node;
    ++i;
    uint8_t n = i;
    // reverses the list generated (it is backwards)
    for (uint8_t i = 0; i < n/2; ++i) {
        uint8_t tmp = path[i];
        path[i] = path[n - i - 1]; path[n - i - 1] = tmp;
    }
    return n;
}

// returns nodes to cross to get to end [st_node, .. ,.. ,.. , end_node]
uint8_t dijkstra(Graph *g, uint8_t st_node, uint8_t end_node, uint8_t *path) {
    return extract_path(_dijkstra(g, st_node), st_node, end_node, path);
}

// main function
int main(int argc, char const *argv[]) {

    #ifdef __linux__

        const uint8_t START_POINT   = atoi(argv[1]);
        const uint8_t END_POINT     = atoi(argv[2]);
        uint8_t CPU_DONE            = 0;

    #else

        #define START_POINT         (* (volatile uint8_t * ) 0x20000000)
        #define END_POINT           (* (volatile uint8_t * ) 0x20000001)
        #define CPU_DONE            (* (volatile uint8_t * ) 0x20000003)

    #endif

    // array to store the planned path
    uint8_t path_planned[32];

    // index to keep track of the path_planned array
    uint8_t idx = 0;

    // instead of using printf() function for debugging,
    // use the below function calls to print a number, string or a newline

    // for newline: _put_byte('\n');
    // for string:  _put_str("your string here");
    // for number:  _put_value(your_number_here);

    // Examples:
    // _put_value(START_POINT);
    // _put_value(END_POINT);
    // _put_str("Hello World!");
    // _put_byte('\n');

    // ############# Add your code here #############

    Graph *g = crt_graph(30);

    link(g, 0, 1, 2); link(g, 1, 2, 2); link(g, 1, 29, 2); link(g, 2, 3, 5); link(g, 2, 8, 5);
    link(g, 3, 28, 30); link(g, 3, 4, 6); link(g, 4, 5, 2); link(g, 4, 6, 3); link(g, 6, 7, 7);
    link(g, 7, 8, 2); link(g, 8, 9, 2); link(g, 8, 12, 5); link(g, 9, 10, 5); link(g, 9, 11, 30);
    link(g, 12, 13, 15); link(g, 12, 19, 30); link(g, 13, 14, 5); link(g, 14, 15, 7); link(g, 14, 16, 2);
    link(g, 16, 17, 7); link(g, 16, 18, 5); link(g, 18, 19, 15); link(g, 19, 20, 5); link(g, 20, 21, 2);
    link(g, 20, 24, 2); link(g, 20, 29, 5); link(g, 21, 22, 5); link(g, 21, 23, 5); link(g, 24, 25, 7);
    link(g, 25, 26, 3); link(g, 26, 27, 2); link(g, 26, 28, 6); link(g, 28, 29, 5);

    idx = dijkstra(g, START_POINT, END_POINT, path_planned);

    // ##############################################

    #ifdef __linux__    // for host pc

        _put_str("######### Planned Path #########\n");
        for (int i = 0; i < idx; ++i) {
            _put_value(path_planned[i]);
        }
        _put_str("################################\n");

    #endif

    return 0;
}
