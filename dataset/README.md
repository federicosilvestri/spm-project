# Dataset generator

I have created a simple python script to generate synthetic dataset.
The script is needed because after reading the literature about Huffman encoding, we can appreciate better the
result of the algorithm is the probability distribution of symbol is known.

I have implemented a simple python script which very few dependencies (just `numpy` for probability)
that generates a file with a specific probability distribution.

You can also set the desired size of output file, that is expressed in as number of symbols, which basically is
1 byte for each symbol (using ASCII).

### Requirements

To run the script you need `python>=3` and `numpy`.

### Usage

To generate a dataset you can run the script with the following syntax:

```shell
python ds_generator.py <n_symbols: int> [<out_file_name: string>]
```
