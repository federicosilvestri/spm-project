from pathlib import Path
import re
import pandas as pd

# Regex for checking the data
TIME_REGEX = re.compile(r"^[0-9]*[a-z]?s$")


def standardize_time(time_str: str) -> int:
    """
    This function converts a time string into nanoseconds
    :param time_str:
    :return:
    """
    # Check if time is correct with regex
    if not TIME_REGEX.match(time_str):
        raise ValueError(f"The string \"{time_str}\" is not a time string")

    if time_str.endswith('ns'):
        # 10^(-9)s (1GHz CPU clock)
        return int(time_str[0:-2])
    if time_str.endswith('us'):
        # 10^(-6)s
        return int(time_str[0:-2]) / 10 ** 3
    if time_str.endswith('ms'):
        # 10^(-3)s
        return int(time_str[0:-2]) / 10 ** 6
    if time_str.endswith('s'):
        # seconds
        return int(time_str[0:-2]) / 10 ** 9
    else:
        raise ValueError(f"The string \"{time_str}\" is not convertible to time!")


def get_standardized_measures(csv_file: Path, excluded_columns=None) -> pd.DataFrame:
    if excluded_columns is None:
        excluded_columns = []
    df = pd.read_csv(csv_file)

    for col in df.columns:
        if col not in excluded_columns:
            df[col] = df[col].map(standardize_time)

    return df
