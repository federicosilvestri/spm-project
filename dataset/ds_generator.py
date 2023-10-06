import argparse
import string
from pathlib import Path
from scipy.stats import norm
import numpy as np

#
# - - - SETTING - - -
#
# we can also add other symbols, using string.oct_digits, etcs
ALPHABET = string.ascii_letters + string.digits


def generator(n_symbols: int, out_file: Path):
    # Generate 10000 normal random integers with specified mean (loc) and std (scale).
    draw = norm.ppf(np.random.random(n_symbols), loc=0, scale=100).astype(int)

    with open(out_file, 'w') as fp:
        for i in draw:
            r = i % len(ALPHABET)
            fp.write(ALPHABET[r])


if __name__ == "__main__":
    parser = argparse.ArgumentParser(
        prog="ds_generator.py",
        description="SPM - Dataset Generator For Huffman coding",
        epilog="Happy 'random' ascii generator"
    )
    parser.add_argument('n_symbols', type=int)
    parser.add_argument('-M', required=False, action='store_true',
                        help="Use it if you want to specify millions of symbols")
    parser.add_argument('-o', '--output', help="The output file, default out.txt", default="out.txt",
                        type=str)
    args = parser.parse_args()

    # call the generator
    n_symbols: int = args.n_symbols * 10000 if args.M else args.n_symbols
    print(f"Generating a file with {n_symbols} symbols into file {args.output}")
    generator(n_symbols=n_symbols, out_file=Path(args.output))
