
class TreeNode:
    parent = None
    left = None
    right = None

    key: int

    def __init__ (self, key):
        self.parent = None
        self.left = None
        self.right = None

        self.key = key
        return

    def __str__ (self) -> str:
        if self == None:
            return

        return "{" + \
                str(self.key) + \
                (str(self.left) if self.left != None else "") + \
                (str(self.right) if self.right != None else "") + \
                "}"

    def insert (self, new_node) -> None:
        curr_node = self
        parent_node = None

        while curr_node != None:
            parent_node = curr_node

            if new_node.key < curr_node.key:
                curr_node = curr_node.left
            else:
                curr_node = curr_node.right

        new_node.parent = parent_node
        
        if new_node.key < new_node.parent.key:
            new_node.parent.left = new_node
        else:
            new_node.parent.right = new_node
        
        return

def main () -> None:
    input_list = (int(value) for value in input().strip().split(" "))

    tree: TreeNode = None
    for key in input_list:
        new_node = TreeNode(key)
        
        if tree == None:
            tree = new_node
            continue

        tree.insert(new_node)

    print(tree)
    return

if __name__ == "__main__":
    main()
