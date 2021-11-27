def get_names_data():
    with open('names.sql') as f:
        s = f.readlines()

    t = []
    for line in s:
        loc = {}
        exec('val = ' + line.strip(), globals(), loc)
        t.append(loc['val'][0])

    return t


def get_names():
    return [x[1] for x in get_names_data()]
