import networkx as nx
import matplotlib.pyplot as plt
import random
import string

G = nx.Graph(name="network")

f = open("orders.txt", "r");
nodes = f.readline().split(' ')
print(nodes)
f.close()

f = open("edges.txt", "r")
edges = f.readline().split(' ')
f.close()
edgelist = []
i = 0
while i < len(edges)-1:
	edgelist.append((int(edges[i]), int(edges[i+1])))
	edgelist.append((int(edges[i+1]), int(edges[i])))
	i = i+3

G.add_edges_from(edgelist)
i = 0
while i <len(edges)-1:
	G[int(edges[i])][int(edges[i+1])]['weight'] = int(edges[i+2])
	i = i+3

color_map = []
for x in range(50):
	if str(x)  in nodes:
		color_map.append('red')
	else:
		color_map.append('green')

color_map[0] = 'blue'
labels = nx.get_edge_attributes(G, 'weight')
nx.draw(G, node_color = color_map, node_size = 1000, with_labels = True)
plot1 = plt.figure(1)

f = open("route.txt", "r")
i = 0
routelist = f.readline().split('.')
while i<len(routelist)-1:
	routes = routelist[i].split(' ')
	print(routes)
	j = 0
	while j < len(routes):
		if color_map[int(routes[j])]=='green':
			color_map[int(routes[j])] = 'yellow'
		j = j+1
	i = i+1
plot2 = plt.figure(2)
nx.draw(G, node_color = color_map, node_size = 1000, with_labels = True)
plt.show()
f.close()
