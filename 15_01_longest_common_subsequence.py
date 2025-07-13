
import pdb

DIAGONAL_ARROW = "D"
UP_ARROW = "A"
LEFT_ARROW = "I"

def print_matrix (mat: list[list[any]]) -> None:
    tmp_mat = []

    for i in range(1, len(mat)):
        tmp_mat.append(mat[i][1:])

    for row in tmp_mat:
        for value in row:
            print(value, end="\t")
        print(end="\n")
    return

def lcs_length (str_1, str_2) -> (list[list[int]], list[list[str]]):
    m = len(str_1) + 1
    n = len(str_2) + 1

    lcs_length_mat = [[0 for j in range(0, n)] for i in range(0, m)]
    lcs_sequence_mat = [['X' for j in range(0, n)] for i in range(0, m)]

    for i in range(1, m):
        for j in range(1, n):
            if str_1[i - 1] == str_2[j - 1]:
                lcs_length_mat[i][j] = lcs_length_mat[i - 1][j - 1] + 1
                lcs_sequence_mat[i][j] = DIAGONAL_ARROW
            elif lcs_length_mat[i - 1][j] >= lcs_length_mat[i][j - 1]:
                lcs_length_mat[i][j] = lcs_length_mat[i - 1][j]
                lcs_sequence_mat[i][j] = UP_ARROW
            else:
                lcs_length_mat[i][j] = lcs_length_mat[i][j - 1]
                lcs_sequence_mat[i][j] = LEFT_ARROW
    
    return lcs_length_mat, lcs_sequence_mat

def print_lcs (lcs_mat, str_base, i, j) -> None:
    if i == 0 or j == 0:
        return

    if lcs_mat[i][j] == DIAGONAL_ARROW:
        print_lcs(lcs_mat, str_base, i - 1, j - 1)
        print(str_base[i - 1], end="")
    elif lcs_mat[i][j] == UP_ARROW:
        print_lcs(lcs_mat, str_base, i - 1, j)
    else: # LEFT_ARROW
        print_lcs(lcs_mat, str_base, i, j - 1)
    return


def main () -> None:
    str_1 = input()
    str_2 = input()
    
    lcs_length_mat, lcs_sequence_mat = lcs_length(str_1, str_2)

    print_matrix(lcs_length_mat)
    print()
    print_matrix(lcs_sequence_mat)
    # print()

    # print_lcs(lcs_sequence_mat, str_1, len(str_1), len(str_2))
    return

if __name__ == "__main__":
    main()
