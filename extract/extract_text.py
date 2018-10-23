from glob import glob
import gzip
import os.path
import warc

# List any of the WARC files found in the data folder
warc_files = glob('wet_files/*.wet.gz')

# Process each of the WARC files we found
files_processed = 0
for fn in warc_files:
    pos = fn.rfind(".warc.wet.gz")
    file_id = fn[pos - 5: pos]
    file_path = '../output/intermediate-output-1/' + file_id + '.txt'
    if os.path.exists(file_path):
        continue
    file = open(file_path, 'w')

    for record in warc.WARCFile(fileobj=(gzip.open(fn))):
        url = record.header.get('WARC-Target-URI', None)
        page_size = record.header.get('Content-Length', None)
        if not url:
            continue
        if not page_size:
            continue
        text = record.payload.read()
        file.write(url + '\n')
        file.write(text + '\n')
        file.write('===============\n')
        file.write(str(page_size) + '\n')
