from glob import glob
#
import warc

# List any of the WARC files found in the data folder
warc_files = glob('../wet_files/*.wet.gz')

# Process each of the WARC files we found
files_processed = 0
for fn in warc_files:
    f = warc.open(fn)
    for record in f:
        url = record.header.get('warc-target-uri', None)
        if not url:
            continue
        text = record.payload.read()
        #
        print url
        print text
        print
        print
    break