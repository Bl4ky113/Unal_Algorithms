
import math

global num_keys, num_real, size_map

def hash_function (value: int) -> int:
    return math.floor(size_map * ((value * num_real) - math.floor(value * num_real)))

def main () -> None:
    global num_keys, num_real, size_map
    num_keys = int(input().strip())
    num_real = float(input().strip())
    size_map = int(input().strip())

    for _ in range(num_keys):
        new_value = int(input().strip())
        new_key = hash_function(new_value)
        print(new_key)

    return

if __name__ == "__main__":
    main()
