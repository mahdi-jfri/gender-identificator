import asyncio
import concurrent
import json
import threading

import requests as requests

from names import get_names


def get_for_one_name(name):
    r = requests.get(f'https://www.vajehyab.com/name/{name}')
    print('done for {}'.format(name))
    return r.text


def get_for_all(names):
    with concurrent.futures.ThreadPoolExecutor() as executor:
        vals = []
        for name in names:
            vals.append(executor.submit(get_for_one_name, name))

        return [val.result() for val in vals]

if __name__ == '__main__':
    with open('out', 'w') as f:
        json.dump(get_for_all(get_names()), f)
