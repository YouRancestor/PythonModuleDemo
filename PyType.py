import xx

class PyType:
    def __init__(self):
        self.feature = [22,33]
        self.integer = 233
        self.string = "lol"
        self.tup = (self.feature,self.integer,self.string)

import time
if __name__ == '__main__':
    obj = PyType()
    xx.Pass(obj)
    xx.efficiencyList(0) # PyList
    xx.efficiencyList(1) # std::list
    xx.efficiencyList(2) # std::vector

    # t1 = time.time()
    # l = []
    # for i in range (1000000):
    #     l.append(i)
    #
    # t2 =time.time()
    # print(t2-t1)
