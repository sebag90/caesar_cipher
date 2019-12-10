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

visited = []

def dfs(graph, node, visited):
    if node not in visited:
        visited.append(node)
        for n in graph[node]:
            dfs(graph,n, visited)
    return visited


def bfs(graph, root):
    visited, queue = [root], [root]
    while queue:
        vertex = queue.pop(0)
        for w in graph[vertex]:
            if w not in visited:
                visited.append(w)
                queue.append(w)
    return visited



visited2 = bfs(graph1, 'P')
print(visited2)

visited = dfs(graph1,'P', [])
print(visited)