from pathlib import Path
import pandas as pd

P_DEGREE_COLUMN = 'P_DEGREE'


def merge_results(file_pattern: str, p_start: int, p_end, p_step: int, out_file: str):
    dfs = []

    for p in range(p_start, p_end + 1, p_step):
        file_path = Path(f"{file_pattern}{p}.csv")
        temp_df = pd.read_csv(file_path)
        temp_df.insert(0, P_DEGREE_COLUMN, p)
        dfs.append(temp_df)

    final_pd = pd.concat(dfs, ignore_index=True)
    final_pd.to_csv(out_file, sep=',', index=False)


if __name__ == "__main__":
    import sys

    if len(sys.argv) != 6:
        raise ValueError("You must pass file_pattern, p_start, p_end and p_step")

    file_patt = sys.argv[1]
    pp_start = int(sys.argv[2])
    pp_end = int(sys.argv[3])
    pp_step = int(sys.argv[4])
    out = sys.argv[5]
    merge_results(file_patt, pp_start, pp_end, pp_step, out)
