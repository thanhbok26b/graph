import networkx as nx
import matplotlib.pyplot as plt

G = nx.Graph()

G.add_node(1)
G.add_nodes_from([2, 3])
H = nx.path_graph(10)
G.add_nodes_from(H)

G.add_edge(1,2)
e = (2, 3)
G.add_edge(*e)
G.add_edges_from([(4, 5), (1,4)])
G.add_edges_from(H.edges())

# G.remove_node(H)
# G.clear()

nx.draw(G)
plt.show()