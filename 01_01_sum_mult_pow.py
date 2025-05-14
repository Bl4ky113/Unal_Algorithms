
def main ():
    input_number = int(input())
    
    for i in range(input_number):
        str_input = input()

        input_1, input_2 = str_input.split(" ")

        input_1 = int(input_1)
        input_2 = int(input_2)

        print(
            "%d %d %d" % (
                input_1 + input_2,
                input_1 * input_2,
                input_1 ** input_2
            )
        )

    return

if __name__ == "__main__":
    main()
