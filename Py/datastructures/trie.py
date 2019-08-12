class TrieNode:
    def __init__(self, valid=False):
        self.valid = valid
        self.links = [None] * 128

class Trie:
    buf = []
    def __init__(self):
        self.root = TrieNode()
    def node_insert(root, s):
        if root == None:
            root = TrieNode()
        if len(s) == 0:
            root.valid = True
        else:
            index = ord(s[0])
            root.links[index] = Trie.node_insert(root.links[index], s[1:])
        return root
    def insert(self, s):
        Trie.node_insert(self.root, s)
    def node_find(root, s):
        if root == None:
            return False
        if len(s) == 0:
            return root.valid
        return Trie.node_find(root.links[ord(s[0])], s[1:])
    def find(self, s):
        return Trie.node_find(self.root, s)
    def node_print_valids(root, prefix):
        if root == None:
            return
        if root.valid:
            Trie.buf.append(prefix)
        for index, link in enumerate(root.links):
            Trie.node_print_valids(link, prefix + chr(index))
    def __str__(self):
        Trie.buf = []
        Trie.node_print_valids(self.root, '')
        return '\n'.join(Trie.buf)


