"""
Simple script that parses the output of spm_project measures into csv file.
"""
from pathlib import Path


def parse_file(in_file: Path, out_file: Path) -> None:
    """
    This function parses the output of the program with the following syntax:
        [MEASURE=VALUE]
        [...]
        TOTAL=VALUE
        The last one is the terminator element of the record.
    :param in_file: the input file name
    :param out_file: the output file name
    :return: None
    """
    results = []
    with open(in_file) as fp:
        row = {}
        for line in fp:
            data = line.split('=', 2)
            row[data[0]] = data[1].replace('\n', '')

            if line.startswith("TOTAL="):
                # end of computation
                results.append(row)
                row = {}

    with open(out_file, 'w') as fp:
        # write header
        line = ""
        for ix, (key, _) in enumerate(results[0].items()):
            if ix != 0:
                line += ","
            line += key
        line += "\n"
        fp.write(line)

        # write data
        for rx, row in enumerate(results):
            if rx != 0:
                line = "\n"
            else:
                line = ""
            for ix, (_, value) in enumerate(row.items()):
                if ix != 0:
                    line += ","
                line += value
            fp.write(line)


if __name__ == '__main__':
    import sys

    if len(sys.argv) != 3:
        print("You must pass in_file and out_file as parameters!")
        exit(1)
    parse_file(Path(sys.argv[1]), Path(sys.argv[2]))
