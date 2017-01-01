#include "graph/graph.h"
#include "libfdr/fields.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
Graph G;
#include "api.h"

int main(){
	/*
	@ import raw data
	@ also add raw data to graph
	--------------------------------
	*/
	IS is;
	char fn[100] = "testcase.txt";
	int n, i, j, k;
	char *name1, *name2, *name;
	name1 = (char*)malloc(sizeof(char)*10);
	name2 = (char*)malloc(sizeof(char)*10);
	int v1, v2;
	int m;
	int id, *output;
	G = create_graph();

	/*
	@ Nhap file tu ban phim
	--------------------------------
	printf("[+] enter file name:");
	scanf("%s", fn);
	*/

	is = new_inputstruct(fn);
	if(!is){
		printf("error");
		return 1;
	}

	if(get_line(is) >= 0){
		// log("line=%s\n", is->fields[0]);
		n = atoi(is->fields[0]);
	}

	if(G.vertices || G.edges)
		drop_graph(&G);
	G = create_graph();

	for(j=0; j<n; j++){
		get_line(is);

		// add all vertices
		for(i=0; i < is->NF; i++){
			// log("data[%d][%d]='%s'\n", is->line, i, is->fields[i]);
			// name = (char*)malloc(sizeof(char)*10);
			// strcpy(name, is->fields[i]);
			// add_vertex_auto_increment(G, name);
			// log("add vertex: %s\n", name);
		}
		// add all edges
		for(i=0; i < is->NF-1; i++){
			// strcpy(name1, is->fields[i]);
			// strcpy(name2, is->fields[i+1]);
			// add_edge(G, get_vertex_id(G, name1), get_vertex_id(G, name2),1, DIRECTED);
			// log("add edge: '%s'->'%s'\n", name1, name2, count_edges(G, DIRECTED));
		}
	}
	// log("import data success!\n");
	// printf("[+] Summary:\n");
	// printf("   - All vertices:\n");
	// print_all_vertices(G);
	// printf("   - Number of subject:%d\n", count_vertices(G));
	// printf("   - Number of relation:%d\n", count_edges(G, DIRECTED));


	/*
	@ main menu
	*/

	do{
		menu();
		printf("choose:");
		scanf("%d", &m);
		switch(m){
			case 1:
				break;
			case 2:
				break;			
			case 3:
				break;
			case 5:
				break;
			case 6:
				break;
			case 7:
				break;
			default:
				printf("error!\n");
		}
	}while(m!=7);

	jettison_inputstruct(is);
	return 0;
}