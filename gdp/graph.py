graph1 = {
    'B' : ['C','K', 'W'],
    'C' : ['B'],
    'F' : ['H','O'],
    'H' : ['F', 'V', 'W'],
    'K' : ['B','P'],
    'N' : ['S','V'],
    'O' : ['F','P'],
    'P' : ['K','O', 'S'],
    'S' : ['N','P'],
    'V' : ['H','N','P', 'W'],
    'W' : ['B','H','V']
}


def dfs(graph, node, visited):
    if node not in visited:
        visited.append(node)
        for n in graph[node]:
            dfs(graph,n, visited)
    return visited


def bfs(graph, root):
    visited = []
    queue = [root]
    while queue:
        node = queue.pop(0)
        if node not in visited:
            visited.append(node)
            neighbours = graph[node]
            for neighbour in neighbours:
                queue.append(neighbour)
    return visited


visited2 = bfs(graph1, 'V')
print(visited2)

visited = dfs(graph1,'V', [])
print(visited)