
def recursive_pow (a: int, n: int, plist: list[int]) -> int:
    if n == 0:
        return 1
    elif n == 1:
        return a

    n_half = n // 2

    result_1 = recursive_pow(a, n_half, plist)
    result_2 = recursive_pow(a, n_half, plist)

    if n % 2 != 0:
        result_2 *= a

    if len(plist) <= 0 or result_1 > plist[-1]:
        plist.append(result_1)

    return result_1 * result_2

def main () -> None:
    input_number: int
    input_a: int
    input_b: int

    input_number = int(input())

    for i in range(input_number):
        pow_list: list[int] = []

        input_a, input_b = input().split("\t")
        input_a = int(input_a)
        input_b = int(input_b)

        result = recursive_pow(input_a, input_b, pow_list)
        pow_list.append(result)

        print(*pow_list)

    return


if __name__ == "__main__":
    main()
