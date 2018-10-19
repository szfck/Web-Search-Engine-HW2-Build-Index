from glob import glob
import os.path
import warc

# List any of the WARC files found in the data folder
warc_files = glob('../../wet_files/*.wet.gz')

def isStop(ch):
    if ch == ' ' or ch == '.' or ch == ',' or ch == ':' or ch == '/':
        return True
    if ch >= 'a' and ch <= 'z' or ch >= 'A' and ch <= 'Z':
        return False
    if ch >= '0' and ch <= '9':
        return False
    return True

# Process each of the WARC files we found
files_processed = 0
for fn in warc_files:
    pos = fn.rfind(".warc.wet.gz")
    file_id = fn[pos - 5: pos]
    file_path = '../intermediate-output-1/' + file_id + '.txt'
    if os.path.exists(file_path):
        continue
    file = open(file_path, 'w')
    f = warc.open(fn)
    for record in f:
        url = record.header.get('warc-target-uri', None)
        page_size = record.header.get('content-length', None)
        if not url:
            continue
        if not page_size:
            continue
        text = record.payload.read()
        arr = [url, page_size]
        word = ''
        for c in text:
            if isStop(c):
                if word != '':
                    arr.append(word)
                    word = ''
                continue
            word = word + c
        if word != '':
            arr.append(word)
        file.write(' '.join(arr) + '\n')