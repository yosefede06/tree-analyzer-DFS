# tree-analyzer-DFS

**The purpose of the program is to analyze a tree up to d-regular, which will be received as input from the user, and display several of its features as output**. The program recieves a txt file that describes the structure of an undirected graph and 2 vertices.
If the input is correct, it will print information about it and about the two vertices captured, such as its `minimum and maximum height`, the `number of vertices` in the tree and the the `shortest path` from the first vertex to the second.

_Input_:

The program will receive three arguments from the user when it is run, through the cli: path to the txt file
containing information about the directed graph and 2 values marking vertices in the graph. If so, the run format
will be:

`$ ./TreeAnalyzer <Graph File Path> <First Vertex> <Second Vertex>`

As mentioned, the first parameter that the program will receive will be a path to a txt file that contains information about a graph
Target that we would like to produce. The file is structured in the following format:

• One number will appear at the beginning of the file, marked {0 ∪ n ∈ N}, which will indicate the number of vertices
in the graph.

• Starting from the second line in the file, each line will represent a vertex. The vertex value (the key) will determine
In ascending order starting from 0) 0, 1, 2 and so on). In other words, every vertex in the graph is represented
by the line where it appears in the file minus 2) because the first line symbolizes the
The number of vertices in the graph, counting from 0, so that _key[T[i - 2]) = i - 2_ for all _i <= numberOfLines < 2_.
(Which means that {0} ∪ i∈N). Thus, the second line will represent vertex number 0, the third row is vertex number 1 and so on and so forth

• In each line will appear a list of numbers (the size of the list ≥ 0 (which are separated by a space. Each member
Such represents a son of the vertex. Alternatively, if this is a leaf, the entire content of the line will be hyphenated
(the character “–”).

_Output_:

If the input is correct, the program should print the following data, in the order of their appearance below (all data will appear in a new line, with a prefix given in advance):
• the value of the root vertex (its key);

• the number of vertices in the tree and the number of edges in the tree (each in a separate row);

• The minimum height in the tree and the maximum height in the tree (each in a separate row);

• The diameter of the tree, i.e. the length of the longest simple path (which has no double vertices);

Note that if a tree has a single vertex then T(D) = 0.

• Note that '/n' must be after each line, especially for the last line
