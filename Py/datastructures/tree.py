class TreeNode:
    def __init__(self, data, parent=None, left=None, right=None):
        self.data = data
        self.parent = parent
        self.left = left
        self.right = right
    def __str__(self):
        return str(self.data)

class Tree:
    def __init__(self):
        self.root = None
    def node_insert(self, root, parent, data):
        if root == None:
            return TreeNode(data, parent)
        else:
            if data < root.data:
                root.left = self.node_insert(root.left, root, data)
            elif data > root.data:
                root.right = self.node_insert(root.right, root, data)
            return root
    def insert(self, data):
        self.root = self.node_insert(self.root, None, data)
    def node_search(self, root, data):
        if root == None:
            return False
        if root.data == data:
            return True
        elif root.data > data:
            return self.node_search(root.left)
        else:
            return self.node_search(root.right)
    def search(self, data):
        return self.node_search(self.root, data)
    def node_print(self, root):
        if root == None:
            return ''
        s = ''
        tmp = self.node_print(root.left)
        if tmp != '':
            s += tmp + ' '
        s += str(root.data)
        tmp = self.node_print(root.right)
        if tmp != '':
            s += ' ' + tmp
        return s
    def __str__(self):
        return self.node_print(self.root)
    def clear(self):
        self.root = None

        
