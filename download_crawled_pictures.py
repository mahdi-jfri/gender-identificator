import concurrent
import json
import os
from concurrent.futures import ThreadPoolExecutor
from multiprocessing import Process

import requests


def download_comment_picture(url):
    name = url.split('/')[-1]
    file_path = f'data/pictures/{name}'
    if os.path.exists(file_path) and os.path.getsize(file_path):
        return

    with open(file_path, 'wb') as f:
        request = requests.get(url, stream=True)
        if request.status_code == requests.codes.ok:
            for block in request.iter_content(1024 * 8):
                if not block:
                    break
                f.write(block)
        else:
            raise Exception(f'failed {url}')

    print(f'done for {url}', flush=True)
    return


def main():
    with open('data/comments_result.json') as f:
        comments = json.load(f)
    people = list({(comment['owner']['id']): comment['owner'] for comment in comments}.values())
    print(len(people))
    threads = []
    for person in people:
        p = Process(target=download_comment_picture, args=(person['profile_pic_url'],))
        threads.append(p)
        p.start()

    print('download all started...')
    for thread in threads:
        thread.join()
    print('done')

    with open('data/people.json', 'w') as f:
        json.dump(people, f)


if __name__ == '__main__':
    main()
