"""Analysis tool"""
# from pathlib import Path
# import numpy as np
# import scipy.stats as stats
# from .preprocess import get_standardized_measures
#
# # OUTLIER THRESHOLD
# OUTL_THR = 3
#
#
# def prepare_seq_measures(measure_file: str):
#     data = get_standardized_measures(Path(measure_file))
#     z_scores = np.abs(stats.zscore(data))
#     data = data[(z_scores < OUTL_THR).all(axis=1)]
#     return data
