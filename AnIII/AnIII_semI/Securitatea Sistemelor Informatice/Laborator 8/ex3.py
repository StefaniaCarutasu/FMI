import json
import hashlib
import requests


f1 = open("ex3_file", "rb")
f2 = open("data.json", "w", encoding="utf-8")


def sha256_file():
    sha256_hash = hashlib.sha256()

    for block in iter(lambda: f1.read(4096), b""):
        sha256_hash.update(block)

    return sha256_hash.hexdigest()


def virustotal_api(sha256_file_key):

    url = 'https://www.virustotal.com/vtapi/v2/file/report'
    params = {'apikey': 'b2d70c91321acc48d9953037fe31ec17972cf88c0615f1737d247232f7cd96ba', 'resource': sha256_file_key}
    response = requests.get(url, params=params)
    json.dump(response.json(), f2, ensure_ascii=False, indent=2)


sha256_file_key = sha256_file()
print(sha256_file_key)
virustotal_api(sha256_file_key)

f1.close()
f2.close()
