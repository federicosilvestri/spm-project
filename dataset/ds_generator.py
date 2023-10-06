import argparse
import string
from pathlib import Path
from scipy.stats import norm
import numpy as np

#
# - - - SETTING - - -
#
# we can also add other symbols, using string.oct_digits, etc...
ALPHABET = string.ascii_letters + string.digits


def generator(n_symbols: int, out_file: Path, uniform):
    if uniform:
        distr = np.random.randint(low=0, high=len(ALPHABET) - 1, size=n_symbols, dtype=int)
    else:
        # Generate normal random integers with specified mean (loc) and std (scale).
        distr = norm.ppf(np.random.random(n_symbols), loc=0, scale=100).astype(int)

    with open(out_file, 'w') as fp:
        for i in distr:
            r = i % len(ALPHABET)
            fp.write(ALPHABET[r])


def run():
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
    parser.add_argument('-U', '--uniform', required=False, action='store_true', default=False,
                        help="Specify this option if you want to generate with a uniform distribution")
    args = parser.parse_args()

    # call the generator
    n_symbols: int = args.n_symbols * 10000 if args.M else args.n_symbols
    print(f"Generating a file with {n_symbols} symbols into file {args.output}")
    print("Distribution is " + ("uniform" if args.uniform else "~gaussian"))
    generator(n_symbols=n_symbols, out_file=Path(args.output), uniform=args.uniform)


if __name__ == "__main__":
    run()
