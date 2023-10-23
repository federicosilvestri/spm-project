"""
Analysis script.
"""
from .preprocess import get_standardized_measures


def compute_performances(file_dim: int):
    seq_file_path = f'results/sequential_{file_dim}.csv'
    thr_file_path = f'results/thr_{file_dim}.csv'
    ff_file_path = f'results/ff_{file_dim}.csv'

    seq_data = get_standardized_measures(seq_file_path)
    thr_data = get_standardized_measures(thr_file_path, excluded_columns=['P_DEGREE'])
    ff_data = get_standardized_measures(ff_file_path, excluded_columns=['P_DEGREE'])

    seq_data = seq_data.median()
    thr_data = thr_data.groupby('P_DEGREE', as_index=False).median()
    ff_data = ff_data.groupby('P_DEGREE', as_index=False).median()
    thr_data['SP_IO'] = seq_data['TOTAL'] / thr_data['TOTAL']
    ff_data['SP_IO'] = seq_data['TOTAL'] / ff_data['TOTAL']

    seq_io_exc = seq_data['FREQCALC'] + seq_data['HUFFBUILD'] + seq_data['MAP'] + seq_data['TRANSFORM']
    thr_data['TOTAL_-IO'] = thr_data['TOTAL'] - thr_data['READ'] - thr_data['WRITE']
    thr_data['SP_-IO'] = seq_io_exc / thr_data['TOTAL_-IO']
    ff_data['TOTAL_-IO'] = ff_data['TOTAL'] - ff_data['READ'] - ff_data['WRITE']
    ff_data['SP_-IO'] = seq_io_exc / ff_data['TOTAL_-IO']

    thr_t1 = thr_data[thr_data['P_DEGREE'] == 1]['TOTAL'][0]
    thr_data['SC_IO'] = thr_t1 / thr_data['TOTAL']

    ff_t1 = ff_data[ff_data['P_DEGREE'] == 1]['TOTAL'][0]
    ff_data['SC_IO'] = ff_t1 / ff_data['TOTAL']

    thr_t00 = thr_data[thr_data['P_DEGREE'] == 1]['TOTAL_-IO'][0]
    thr_data['SC_-IO'] = thr_t00 / thr_data['TOTAL_-IO']

    ff_t00 = ff_data[ff_data['P_DEGREE'] == 1]['TOTAL_-IO'][0]
    ff_data['SC_-IO'] = ff_t00 / ff_data['TOTAL_-IO']

    thr_data['EFF_IO'] = thr_data['SP_IO'] / thr_data['P_DEGREE']
    thr_data['EFF_-IO'] = thr_data['SP_-IO'] / thr_data['P_DEGREE']

    ff_data['EFF_IO'] = ff_data['SP_IO'] / ff_data['P_DEGREE']
    ff_data['EFF_-IO'] = ff_data['SP_-IO'] / ff_data['P_DEGREE']

    return seq_data, thr_data, ff_data
