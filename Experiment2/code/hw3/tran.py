with open('text.h', 'w') as fo:
    with open('apue.h') as fi:
        result = fi.read()
        fo.write(result.replace('\xa0', ' '))
