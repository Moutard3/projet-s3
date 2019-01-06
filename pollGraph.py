import networkx as nx
from networkx.algorithms import tournament
import numpy as np
import matplotlib.pyplot as plt
import pylab

G = nx.DiGraph()

G.add_edges_from([(0,2)],weight=42)
G.add_edges_from([(0,3)],weight=44)
G.add_edges_from([(1,0)],weight=48)
G.add_edges_from([(1,3)],weight=42)
G.add_edges_from([(1,5)],weight=45)
G.add_edges_from([(2,1)],weight=46)
G.add_edges_from([(2,3)],weight=48)
G.add_edges_from([(4,0)],weight=50)
G.add_edges_from([(4,1)],weight=46)
G.add_edges_from([(4,2)],weight=45)
G.add_edges_from([(4,3)],weight=44)
G.add_edges_from([(4,5)],weight=54)
G.add_edges_from([(5,0)],weight=43)
G.add_edges_from([(5,2)],weight=44)
G.add_edges_from([(5,3)],weight=43)
G.add_edges_from([(6,0)],weight=51)
G.add_edges_from([(6,1)],weight=48)
G.add_edges_from([(6,2)],weight=48)
G.add_edges_from([(6,3)],weight=48)
G.add_edges_from([(6,4)],weight=43)
G.add_edges_from([(6,5)],weight=50)

print(tournament.is_tournament(G))

edge_labels=dict([((u,v,),d['weight'])
                 for u,v,d in G.edges(data=True)])

pos=nx.circular_layout(G)

nx.draw_networkx_edge_labels(G,pos,edge_labels=edge_labels)
nx.draw_networkx(G,pos, node_size=200)
pylab.show()
