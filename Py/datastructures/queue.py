class Queue:
    def __init__(self):
        self.data = []
    def push(self, data):
        self.data = [data] + self.data
    def pop(self):
        self.data.pop(-1)
    def top(self):
        self.data[-1]
    def __len__(self):
        return len(self.data)
    def __str__(self):
        if len(self.data) == 0:
            return ''
        s = str(self.data[0])
        for i in range(1, len(self.data)):
            s += ' ' + str(self.data[i])
        return s
    def empty(self):
        return len(self.data) == 0
    def clear(self):
        self.data.clear()
