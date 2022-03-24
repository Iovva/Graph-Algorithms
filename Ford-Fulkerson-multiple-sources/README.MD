# Ford-Fulkerson algorithm with multiple sources support

The algorithm computes the maximum flow in a flow network.

in.txt:
The first line contains three numbers: N, S and M: the number of nodes, the number of sources and the number of vertexes for the graph.
The following M lines describe the vertexes with pairs of nodes x, y and m separated by a space, with m representing the flow capacity of a vertex.
The nodes are indexed from 0.
The first S - 1 nodes are sources. So, if S is 6, the sources are 0, 1, 2, 3, 4, 5 are the sources.
The destination is N - 1

The values of the input folder have the following restraints:
• 2 ≤ N ≤ 100;
• 1 ≤ C < N;
• 0 < D ≤ 1000;
• 0 ≤ x < N;
• 0 ≤ y < N;
• 1 ≤ m ≤ 1000. 


output.txt:
The first line represents the maximum flow in the network.
The following line has values coresponding to each of the S sources, representing the max flow for each.