import random
import subprocess
from pathlib import Path

EXE = Path(__file__).resolve().parent / "push_swap"


def check(values):
    result = subprocess.run([str(EXE), *map(str, values)], capture_output=True, check=True, timeout=10)
    a, b = list(values), []
    for action in result.stdout.decode().splitlines():
        if action == "sa" and len(a) > 1:
            a[:2] = a[1::-1]
        elif action == "ra" and a:
            a.append(a.pop(0))
        elif action == "rra" and a:
            a.insert(0, a.pop())
        elif action == "rb" and b:
            b.append(b.pop(0))
        elif action == "rrb" and b:
            b.insert(0, b.pop())
        elif action == "pb" and a:
            b.insert(0, a.pop(0))
        elif action == "pa" and b:
            a.insert(0, b.pop(0))
        else:
            raise AssertionError(f"Invalid action: {action}")
    assert a == sorted(values) and not b
    return len(result.stdout.splitlines())


if __name__ == "__main__":
    rng = random.Random(42)
    for size in (2, 3, 4, 5, 10, 20, 100, 500):
        runs = 100 if size <= 100 else 20
        counts = [check(rng.sample(range(-1000000, 1000000), size)) for _ in range(runs)]
        print(f"{size:3d}: {runs} passed, average {sum(counts)/runs:.1f}, maximum {max(counts)}")
    for args in (["1", "1"], ["2147483648"], ["-2147483649"], ["oops"], [""], ["1x"]):
        result = subprocess.run([str(EXE), *args], capture_output=True, timeout=5)
        assert result.returncode != 0 and result.stderr == b"Error\n"
    print("Invalid argument tests passed")
