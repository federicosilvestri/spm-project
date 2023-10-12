# Measuring the parallelism

The aim of this folder is to collect the measure of the execution of the program and analyze it.
I have mixed python for data analysis and bash scripts for data collection (i.e. running the program).

### Requirements

To run the scripts you need `python>=3` and you have to install all requirements inside `requirements.txt` using
`pip install -r requirements.txt`.

## Dataset generator

I have created a simple python script to generate synthetic dataset.
The script is needed because after reading the literature about Huffman encoding, we can appreciate better the
result of the algorithm is the probability distribution of symbol is known.

I have implemented a simple python script which very few dependencies (just `numpy` for probability)
that generates a file with a specific probability distribution.

You can also set the desired size of output file, that is expressed in as number of symbols, which basically is
1 byte for each symbol (using ASCII).

### Usage

To generate a dataset you can run the script with the following syntax:

```shell
python ds_generator.py <n_symbols: int> [<out_file_name: string>]
```

## Data collection

**BEFORE** starting the script you must compile the program and put the executable file in this
directory, the name of the file must be `spm_project`. You can use directly the `build.sh` script
inside root folder.

### Basic usage

To collect the data you should use the script.