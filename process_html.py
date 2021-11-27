import csv
import json
import re

from names import get_names_data


def main():
    with open('out') as f:
        data = json.load(f)

    d = {}
    cnt_pr = 0
    cnt = 0
    with open('result.csv', 'w') as f:
        writer = csv.writer(f)
        for name_data, response_data in zip(get_names_data(), data):
            if '404 Page Not Found' in response_data:
                continue
            cnt += 1
            match = re.search(r'\(تلفظ:(.+?)\)', response_data)
            if match is None:
                writer.writerow([name_data[1], name_data[-2]])
            else:
                writer.writerow([name_data[1], name_data[-2], match.group(1)])
            # gender = 1 if name_data[-2] == 'پسر' else 0
            # d[name]
        # print(*(name_data for name_data in data if '404 Page Not Found' in name_data), sep='\n')
    print(cnt, cnt_pr)

if __name__ == '__main__':
    main()
