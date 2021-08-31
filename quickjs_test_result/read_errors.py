path = '/root/Code/litejs/all_test/test262_errors.txt'

s = set()
with open(path, 'r') as f:
    for l in f:
        l = f.readline()
        if l.count('test262/test/') > 0:
            p = l.index('.js:') + 3
            s.add(l[:p])
L = list(s)
L.sort()
for l in L:
    print(l)
