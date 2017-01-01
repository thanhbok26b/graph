#include "graph/graph.h"
#include "libfdr/fields.h"
#include <stdio.h>
#include <stdlib.h>

void add_all_vertex(Graph G, int matrix[][5]);
void add_all_edge(Graph G, int matrix[][5]);
void print_all_vertex(Graph G);
void print_all_adjacent(Graph G, int v);
void print_shortest_path(Graph G, int v, int v2);
int _increase_cmp(const void *a, const void *b);
void menu();

Graph G;

int main(){
	/*
	@ import raw data
	*/
	IS is;
	int i, matrix[5][5];
	is = new_inputstruct("testcase.txt");
	while(get_line(is) >= 0)
		for(i=0; i < is->NF; i++){
			log("matrix[%d][%d]=\"%s\"\n", is->line, i, is->fields[i]);
			matrix[is->line-1][i] = atoi(is->fields[i]);
		}

	/*
	@ add raw data to graph
	*/
	G = create_graph();
	add_all_vertex(G, matrix);
	add_all_edge(G, matrix);
	
	/*
	@ main menu
	*/
	int m;
	int id, *output;
	char s[100];
	char s1[100], s2[100];
	int v1, v2;
	do{
		menu();
		printf("choose:");
		scanf("%d", &m);
		switch(m){
			case 1:
				print_all_vertex(G);
				break;
			case 2:
				printf("total vertices: %d\n", count_vertices(G));
				printf("total edge    : %d\n", count_edges(G, UNDIRECTED));
				break;			
			case 3:
				printf("enter vertex name:");
				scanf("%s", s);
				id = get_vertex_id(G, s);
				if(id < 0)
					printf("    [!] vertex '%s' not existed!\n", s);
				else
					print_all_adjacent(G, id);
				break;
			case 4:
				printf("List of node with more flux:\n");
				output = (int*)malloc(sizeof(int ) * count_vertices(G));
				get_vertices_id(G, output);
				qsort(output, count_vertices(G), sizeof(int), _increase_cmp);
				for(i=0; i < count_vertices(G); i++)
					printf("   - %d %s\n", count_adjacent(G, output[i]), get_vertex_val(G, output[i]));
				free(output);
				break;
			case 5:
				printf("List of node with no flux:\n");
				output = (int*)malloc(sizeof(int ) * count_vertices(G));
				get_vertices_id(G, output);
				for(i=0; i < count_vertices(G); i++)
					if(count_adjacent(G, output[i])==0)
						printf("    - %d %s\n", count_adjacent(G, output[i]), get_vertex_val(G, output[i]));
				free(output);
				break;
			case 6:
				printf("start point:");
				scanf("%s", s1);
				printf("end point:");
				scanf("%s", s2);
				v1 = get_vertex_id(G, s1);
				v2 = get_vertex_id(G, s2);			
				print_shortest_path(G, v1, v2);
			case 8:
				break;
			default:
				printf("error!\n");
		}
	}while(m!=8);	

	jettison_inputstruct(is);
	return 0;
}

void menu(){
	puts("1) Print matrix");
	puts("2) Count total vertices and edges");
	puts("3) Find adjacent");
	puts("4) Node with more flux");
	puts("5) Node with no flux");
	puts("6) Shortest path");
	puts("8) Quit");
}

void _index_to_name(int i, int j, char *name){
	name[0] = i+48;
	name[1] = j+48;
	name[2] = 0;
}

void add_all_vertex(Graph G, int matrix[][5]){
	log("[+] adding all vertex\n");
	int i, j, count=0;
	char *name;
	for(i=0; i<5; i++)
		for(j=0; j<5; j++)
			if(matrix[i][j] == 0){
				name = (char*)malloc(3 * sizeof(char));
				_index_to_name(i, j, name);
				log("    _adding: %d '%s'\n", count, name);
				add_vertex(G, count++, name);
			}
	log("[+] success!\n");
}

void add_all_edge(Graph G, int matrix[][5]){
	log("adding all vertex\n");
	int i, j, k, l, flag;
	char name1[3], name2[3];
	int id1, id2;
	for(i=0; i<5; i++)
		for(j=0; j<4; j++)
			if(!matrix[i][j] && !matrix[i][j+1]){
				_index_to_name(i, j, name1);
				_index_to_name(i, j+1, name2);
				id1 = get_vertex_id(G, name1);
				id2 = get_vertex_id(G, name2);
				if (id1==-1 || id2==-1)
					continue;
				add_edge(G, id1, id2, 1, UNDIRECTED);
				log("    _adding <%d-'%s'> <%d-'%s'> weight'%d'\n", id1, name1, id2, name2, 1);
			}

	for(j=0; j<5; j++)
		for(i=0; i<4; i++)
			if(!matrix[i][j] && !matrix[i+1][j]){
				_index_to_name(i, j, name1);
				_index_to_name(i+1, j, name2);
				id1 = get_vertex_id(G, name1);
				id2 = get_vertex_id(G, name2);
				if (id1==-1 || id2==-1)
					continue;
				add_edge(G, id1, id2, 1, UNDIRECTED);
				log("    _adding <%d-'%s'> <%d-'%s'> weight'%d'\n", id1, name1, id2, name2, 1);
			}
	log("[+] success!\n");
}

void print_all_vertex(Graph G){
	JRB node, tree;
	tree = G.vertices;
	jrb_traverse(node, tree){
		printf("+id:'%d' value: '%s'\n",jval_i(node->key), jval_s(node->val));
		printf("-id:'%d' value: '%s'\n",jval_i(node->key), get_vertex_val(G, jval_i(node->key)));
	}
}

void print_all_adjacent(Graph G, int v){
	int *output, i, n;
	n = count_adjacent(G, v);
	output = (int*)malloc(sizeof(int) * n);
	get_adjacent_vertices(G, v, output);
	printf("adjacent of '%s': ", get_vertex_val(G, v));
	for(i=0; i<n; i++)
		printf("%s ", get_vertex_val(G, output[i]));
	putchar('\n');
	free(output);
}

void print_shortest_path(Graph G, int v, int v2){
	int *path = (int*)malloc(100*sizeof(int));
	double *length = (double*)malloc(100*sizeof(double));
	int ret = shortest_path(G, v, v2, path, length), i;
	for(i=0; path[i]!=-1; i++);
	i--;
	for(; i>0; i--)
		printf("%s->", get_vertex_val(G, path[i]));
	printf("%s\n", get_vertex_val(G, path[0]));
	free(path);
	free(length);
}

int _increase_cmp(const void *a, const void *b){
	int v1 = *(int*)a;
	int v2 = *(int*)b;
	int n1 = count_adjacent(G, v1);
	int n2 = count_adjacent(G, v2);
	if(n1 < n2)
		return 1;
	else if (n1 > n2)
		return -1;
	else
		return 0;
}