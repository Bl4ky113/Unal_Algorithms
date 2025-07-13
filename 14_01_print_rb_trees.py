
class TreeNode:
    def __init__ (self, key):
        self.key = key
        self.color = 1

        self.left = None
        self.right = None
        self.parent = None
        self.nil = None

    def __str__ (self) -> str:
        return "{" + \
                str(self.key) + \
                ("®" if self.color == 1 else "#") \
                (str(self.left) if self.left != None or self.left != self.nil  else "") + \
                (str(self.right) if self.right != None or self.right != self.nil else "") + \
                "}"

    @classmethod
    def nil (cls):
        node = TreeNode(0)
        node.key = None
        node.color = 0

        return node

class RBTree:
    def __init__ (self): 
        self.NIL: TreeNode = TreeNode.nil()
        self.root: TreeNode = self.NIL

    def __left_rotate (self, x: TreeNode) -> None:
        y = x.right
        x.right = y.left
        if y.left != self.NIL:
            y.left.parent = x

        y.parent = x.parent
        if x.parent is None:
            self.root = y
        elif x == x.parent.left:
            x.parent.left = y
        else:
            x.parent.right = y
        y.left = x
        x.parent = y
        return

    def __right_rotate (self, x: TreeNode) -> None:
        y = x.left
        x.left = y.right
        if y.right != self.NIL:
            y.right.parent = x

        y.parent = x.parent
        if x.parent is None:
            self.root = y
        elif x == x.parent.right:
            x.parent.right = y
        else:
            x.parent.left = y
        y.right = x
        x.parent = y

    def insert (self, key: int) -> None: 
        node = TreeNode(key)
        node.left = self.NIL
        node.right = self.NIL
        node.nil = self.NIL
        node.color = 1

        y = None
        x = self.root

        while x != self.NIL:
            y = x
            if node.key < x.key:
                x = x.left
            else:
                x = x.right

        node.parent = y
        if y is None:
            self.root = node
        elif node.key < y.key:
            y.left = node
        else:
            y.right = node

        if node.parent is None:
            node = 0
            return

        if node.parent.parent is None:
            return

        self.fix_insert(node)

    def fix_insert(self, node: TreeNode) -> None:
        while node.parent.color == 1:
            if node.parent == node.parent.parent.right:
                u = node.parent.parent.left
                if u.color == 1:
                    u.color = 0
                    node.parent.color = 0
                    node.parent.parent.color = 1
                    node = node.parent.parent
                else:
                    if node == node.parent.left:
                        node = node.parent
                        self.__right_rotate(node)
                    node.parent.color = 0
                    node.parent.parent.color = 1
                    self.__left_rotate(node.parent.parent)
            else:
                u = node.parent.parent.right

                if u.color == 1:
                    u.color = 0
                    node.parent.color = 0
                    node.parent.parent.color = 1
                    node = node.parent.parent
                else:
                    if node == node.parent.right:
                        node = node.parent
                        self.__left_rotate(node)
                    node.parent.color = 0
                    node.parent.parent.color = 1
                    self.__right_rotate(node.parent.parent)
            if node == self.root:
                break
        self.root = 0

def main () -> None:
    input_list = (int(value) for value in input().strip().split(" "))

    tree: RBTree = RBTree()
    for key in input_list:
        tree.insert(key)

    print(tree)
    return

if __name__ == "__main__":
    main()
