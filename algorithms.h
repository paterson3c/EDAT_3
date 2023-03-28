
#include "stack.h"
#include "vertex.h"
#include "graph.h"
#include "stack.h"
#include "file_utils.h"
#include "types.h"
/**
* @brief: Merges two stacks
*
* @param sin1, first input stack
* @param sin2, second input stack
* @param sout, result stack
* @return The function returns OK or ERROR
**/
Status mergeStacks (Stack *sin1, Stack *sin2, Stack *sout, int (*cmp)(const void *, const void *));

/**
* @brief: Makes a search from the origin vertex to the destination vertex
of a graph using the depth-first search algorithm
* using an ADT Stack
*
* The function prints each visited vertex while traversing the graph
*
* @param g, Pointer to graph
* @param from_id, id of the origin Vertex
* @param to_id, id of the destination Vertex
* @return The function returns OK or ERROR
**/
Status graph_depthSearch (Graph *g, long from_id, long to_id);