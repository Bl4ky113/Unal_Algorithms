
from enum import Enum

class NodeColor (Enum):
    BLACK = 0
    GRAY = 1
    WHITE = 2

def graph_BFS (graph: dict[str:list[str]], root_key: str) -> dict[str:dict]:
    node_dict = {
        node_key: {
            "color": NodeColor.WHITE, 
            "depth": 0, 
            "parent": None
        } 
        for node_key in graph.keys()
    }

    node_queue = [root_key]
    while len(node_queue) > 0:
        curr_node = node_queue.pop(0)
        for adj_node in graph[curr_node]:
            if node_dict[adj_node]["color"] == NodeColor.WHITE:
                node_dict[adj_node]["color"] = NodeColor.GRAY
                node_dict[adj_node]["depth"] = node_dict[curr_node]["depth"] + 1
                node_dict[adj_node]["parent"] = curr_node
                node_queue.append(adj_node)

        node_dict[curr_node]["color"] = NodeColor.BLACK

    return node_dict

def main () -> None:
    countries_graph: dict[str:list[str]] = {}
    flights_num = -1
    routes_num = 0

    usr_input = input()
    while (flights_num == -1):
        try:
            flights_num = int(usr_input)
        except ValueError:
            countries_graph[usr_input[:2]] = usr_input[6:].split(sep=" ")
            usr_input = input()

    countries_data = graph_BFS(countries_graph, "CO")

    for country, data in countries_data.items():
        if data["depth"] == flights_num:
            routes_num += 1

    print(routes_num)
    return

if __name__ == "__main__":
    main()
