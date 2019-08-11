class TreeNode:
    def __init__(self, val, parent=None, left=None, right=None):
        self.val = val
        self.parent = parent
        self.left = left
        self.right = right
    def __str__(self):
        return str(self.val)

class Tree:
    def __init__(self):
        self.root = None
    def node_insert(root, parent, val):
        if root == None:
            return TreeNode(val, parent)
        else:
            if val < root.val:
                root.left = Tree.node_insert(root.left, root, val)
            elif val > root.val:
                root.right = Tree.node_insert(root.right, root, val)
            return root
    def insert(self, val):
        self.root = Tree.node_insert(self.root, None, val)
    def node_search(root, val)
    def search(self, val):
        return Tree.node_search(self.root, val)
    def node_print(root):
        if root == None:
            return ''
        s = ''
        tmp = Tree.node_print(root.left)
        if tmp != '':
            s += tmp + ' '
        s += str(root.val)
        tmp = Tree.node_print(root.right)
        if tmp != '':
            s += ' ' + tmp
        return s
    def __str__(self):
        return Tree.node_print(self.root)
    def clear(self):
        self.root = None

        
