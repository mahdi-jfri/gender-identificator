import csv


def clean_pronounce(row):
    name = row[2].strip()
    name = name.replace('ā', 'a').replace('x', 'kh').replace('č', 'ch').replace('š', 'sh')
    if '(' in name:
        print(row)
        name = ''

    return name


def main():
    with open('result.csv') as f:
        with open('final.csv', 'w') as g:
            writer = csv.writer(g)
            for row in csv.reader(f):
                row[2] = clean_pronounce(row)
                writer.writerow(row)


if __name__ == '__main__':
    main()
