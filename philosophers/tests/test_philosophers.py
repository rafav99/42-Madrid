import re
import subprocess
import sys
from collections import Counter
from pathlib import Path

EXECUTABLE = Path(__file__).resolve().parents[1] / 'philo'
CASES = [
    (['1', '120', '60', '60'], 'one philosopher dies', 'death', 2.0),
    (['2', '800', '80', '80', '3'], 'two philosophers complete quota', 'quota', 5.0),
    (['3', '1200', '60', '60', '3'], 'odd number completes quota', 'quota', 5.0),
    (['4', '1200', '70', '70', '3'], 'even number completes quota', 'quota', 5.0),
    (['5', '1400', '60', '60', '3'], 'five philosophers complete quota', 'quota', 5.0),
    (['11', '2500', '30', '30', '2'], 'eleven philosophers complete quota', 'quota', 5.0),
    (['2', '90', '120', '120'], 'death before completing a meal', 'death', 3.0),
    (['0', '800', '100', '100', '3'], 'reject zero population', 'invalid', 2.0),
    (['-2', '800', '100', '100', '3'], 'reject negative population', 'invalid', 2.0),
    (['2', '800', '100', '100', '0'], 'reject zero meal target', 'invalid', 2.0),
    (['2', '800', 'abc', '100'], 'reject invalid number', 'invalid', 2.0),
    (['2', '800', '100', ''], 'reject empty number', 'invalid', 2.0),
    (['2', '800', '2147483648', '100'], 'reject integer overflow', 'invalid', 2.0),
    ([], 'reject missing arguments', 'invalid', 2.0),
]
PATTERN = re.compile(r'^(\d+) (\d+) (has taken a fork|is thinking|is eating|is sleeping|died)$')


def run_case(args, label, expectation, timeout):
    try:
        p = subprocess.run([str(EXECUTABLE), *args], text=True,
                           capture_output=True, timeout=timeout, check=False)
    except subprocess.TimeoutExpired:
        return False, 'timed out'
    if expectation == 'invalid':
        return p.returncode != 0 and not p.stdout, f'exit={p.returncode}'
    if p.returncode != 0:
        return False, f'exit={p.returncode}: {p.stderr[:100]}'
    lines = p.stdout.splitlines()
    records = [PATTERN.match(x) for x in lines]
    if not lines or any(m is None for m in records):
        return False, 'malformed/missing log lines'
    if expectation == 'death':
        dead = [i for i, m in enumerate(records) if m.group(3) == 'died']
        return len(dead) == 1 and dead[-1] == len(lines) - 1, f'deaths={len(dead)}'
    required = int(args[4])
    population = int(args[0])
    if any(m.group(3) == 'died' for m in records):
        return False, 'unexpected death'
    meals = Counter(int(m.group(2)) for m in records if m.group(3) == 'is eating')
    return all(meals[i] >= required for i in range(1, population + 1)), f'eating events={dict(meals)}'


def main():
    if not EXECUTABLE.is_file():
        print('Run make before running tests.', file=sys.stderr)
        return 1
    failed = 0
    for args, label, expectation, timeout in CASES:
        good, detail = run_case(args, label, expectation, timeout)
        print(f'{"PASS" if good else "FAIL"}: {label} ({detail})')
        failed += not good
    for i in range(10):
        good, detail = run_case(['5', '1400', '35', '35', '2'],
                                'repeated concurrent run', 'quota', 5.0)
        if not good:
            print(f'FAIL: repeated concurrent run {i+1} ({detail})')
            failed += 1
            break
    else:
        print('PASS: 10 repeated concurrent runs')
    return 1 if failed else 0


if __name__ == '__main__':
    raise SystemExit(main())
