class List:
    def __init__(self, data=[]):
        self.data = data.copy()
    def withsize(cls, size):
        return cls([0 for x in range(size)])
    def scan(cls, fd, scanner):
        l = List()
        i = scanner(fd)
        while i != None:
            l.append(i)
            i = scanner(fd)
        return l
    def copy(self):
        return List(self.data.copy())
    def __getitem__(self, key):
        return self.data[key]
    def __add__(self, other):
        return List(self.data + other.data)
    def reverse(self):
        self.data.reverse()
    def push_front(self, data):
        self.data = [data] + self.data
    def push_back(self, data):
        self.data.append(data)
    def pop(self, index):
        self.data.pop(index)
    def pop_front(self):
        self.data.pop(0)
    def pop_back(self):
        self.data.pop(-1)
    def front(self):
        return self.data[0]
    def back(self):
        return self.data[-1]
    def insert(self, index, data):
        self.data.insert(index, data)
    def __len__(self):
        return len(self.data)
    def empty(self):
        return len(self.data) == 0
    def __iter__(self):
        return iter(self.data)
    def __str__(self):
        if len(self.data) == 0:
            return ''
        s = str(self.data[0])
        for i in range(1, len(self.data)):
            s += ' ' + str(self.data[i])
        return s
    def remove(self, item):
        self.data.remove(item)
    def clear(self):
        self.data.clear()
