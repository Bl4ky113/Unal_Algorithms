
BUCKETS_NUMBER = 26

def radix_sort (str_list: list[str]):
    bucket_list = {chr(i + 65): [] for i in range(BUCKETS_NUMBER)}
    result_list = str_list.copy()

    for i in range(len(str_list[0])):
        for val in result_list:
            bucket_list[val[len(val) - 1 - i].upper()].append(val)

        result_list.clear()

        for bucket in bucket_list.values():
            result_list.extend(bucket)
            bucket.clear()


        for item in result_list:
            print(item, end=" ", flush=False)

        print("")

    return

def main () -> None:
    input_list = input().strip().split(" ")
    
    radix_sort(input_list)
    return

if __name__ == "__main__":
    main()
