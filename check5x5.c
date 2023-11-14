#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define SIZE 5
#define WIN_CONDITION 4
#define STEP 10000

int randomMinusOneOrOne()
{
    int randomValue;
    while (1)
    {
        randomValue = rand() % 3;
        if (randomValue != 1)
            return randomValue - 1;
    }
}

int randomMinusOneOrOneOrZero()
{
    int randomValue;
    randomValue = rand() % 3;
    return randomValue - 1;
}

int randomNumMove()
{
    int randomValue = rand() % 25;
    return randomValue + 1;
}

void printZero(int board[SIZE][SIZE])
{
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            if ((board[i][j] == 1) || (board[i][j] == -1))
                continue;
            else
                board[i][j] == 0; // Điền số 0 vào các ô chưa đánh dấu
        }
        printf("\n");
    }
}

void numberMatrix(int number, int *row, int *column)
{
    *row = (number - 1) / 5;
    *column = (number - 1) % 5;
}

int checkTicTacToe(int board[SIZE][SIZE], int player)
{
    // Kiểm tra theo hàng và cột
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j <= SIZE - WIN_CONDITION; j++)
        {
            int row_count = 0;
            int col_count = 0;

            for (int k = 0; k < WIN_CONDITION; k++)
            {
                // Kiểm tra hàng
                if (board[i][j + k] == player)
                    row_count++;

                // Kiểm tra cột
                if (board[j + k][i] == player)
                    col_count++;
            }

            if (row_count == WIN_CONDITION || col_count == WIN_CONDITION)
                return 1; // Người chơi thắng
        }
    }

    // Kiểm tra theo đường chéo chính
    for (int i = 0; i <= SIZE - WIN_CONDITION; i++)
    {
        for (int j = 0; j <= SIZE - WIN_CONDITION; j++)
        {
            int diag_count = 0;

            for (int k = 0; k < WIN_CONDITION; k++)
            {
                // Kiểm tra đường chéo chính
                if (board[i + k][j + k] == player)
                    diag_count++;
            }

            if (diag_count == WIN_CONDITION)
                return 1; // Người chơi thắng
        }
    }

    // Kiểm tra theo đường chéo phụ
    for (int i = 0; i <= SIZE - WIN_CONDITION; i++)
    {
        for (int j = WIN_CONDITION - 1; j < SIZE; j++)
        {
            int diag_count = 0;

            for (int k = 0; k < WIN_CONDITION; k++)
            {
                // Kiểm tra đường chéo phụ
                if (board[i + k][j - k] == player)
                    diag_count++;
            }

            if (diag_count == WIN_CONDITION)
                return 1; // Người chơi thắng
        }
    }

    return 0; // Chưa có ai thắng
}

int main()
{
    srand(time(NULL));
    int a = 0;
    FILE *f = fopen("random5x5.txt", "w");
    fprintf(f, "%s", "m1,m2,m3,m4,m5,m6,m7,m8,m9,m10,m11,m12,m13,m14,m15,m16,m17,m18,m19,m20,m21,m22,m23,m24,m25,result\n");

    while (a < STEP)
    {
        int board[SIZE][SIZE] = {0};
        int matrix[25] = {0};
        int numMtr = 0;
        int x, o, result;
        int win = 0;

        for (int i = 0; i < 13; i++)
        {
            int row, column; // Biến lưu trữ tọa độ
            int dem = 0;
            while (1)
            {
                x = randomNumMove();
                numberMatrix(x, &row, &column);
                if (board[row][column] != 1 && board[row][column] != -1)
                    break;
            }

            board[row][column] = 1;
            matrix[numMtr] = x;

            numMtr++;

            result = checkTicTacToe(board, 1);
            if (result == 0 && numMtr == 25)
            {
                win = 0;
                break;
            }

            if (result == 1)
            {
                win = 1;
                break;
            }

            while (1)
            {
                o = randomNumMove();
                numberMatrix(o, &row, &column);
                if (board[row][column] != 1 && board[row][column] != -1)
                    break;
            }

            board[row][column] = -1;
            matrix[numMtr] = o;

            result = checkTicTacToe(board, -1);
            if (result == 1)
            {
                win = -1;
                break;
            }

            // printf("Numrandom: %d -- O: [%d, %d]\n", o, row, column);
            // printf("NumMatrix2: %d\n", numMtr);
            numMtr++;
        }

        // printf("win = %d\n", win);
        if (win == 0)
        {
            for (int i = 0; i < 25; i++)
            {
                // printf("%d,", matrix[i]);
                fprintf(f, "%d,", matrix[i]);
            }
            // printf("draw\n");
            fprintf(f, "%s", "draw\n");
        }
        else
        {
            for (int i = 0; i < 25; i++)
            {
                // printf("%d,", matrix[i]);
                fprintf(f, "%d,", matrix[i]);
            }

            if (win == 1)
            {
                // printf("win\n");
                fprintf(f, "%s", "win\n");
            }
            else
            {
                // printf("lose\n");
                fprintf(f, "%s", "lose\n");
            }
        }

        // printf("\n");
        // for (int i = 0; i < 5; i++)
        // {
        //     for (int j = 0; j < 5; j++)
        //     {
        //         printf("%2d ", board[i][j]);
        //         if (j == 4)
        //             printf("\t|| %d\n", (5 * i) + 1);
        //     }
        // }

        // if (matrix[24] != 0)
        // {
        //     printf("\n");
        //     for (int i = 0; i < 5; i++)
        //     {
        //         for (int j = 0; j < 5; j++)
        //         {
        //             printf("%2d ", board[i][j]);
        //             if (j == 4)
        //                 printf("\t|| %d\n", (5 * i) + 1);
        //         }
        //     }

        //     if (win == 0)
        //         break;
        // }

        a++;
    }

    fclose(f);

    // #################################################################################################
    // #################################################################################################
    // #################################################################################################
    // #################################################################################################
    // #################################################################################################
    // #################################################################################################

    FILE *f_in = fopen("random5x5.txt", "r");
    FILE *f_out = fopen("data_5x5.txt", "w");
    char line[200];
    char **unique_lines = NULL;
    int num_unique_lines = 0;
    int max_unique_lines = STEP; // Số lượng dòng tối đa bạn muốn hỗ trợ ban đầu
    int x = 0;

    if (f_in == NULL || f_out == NULL)
    {
        printf("Không thể mở tệp.\n");
        return 1;
    }

    // Cấp phát mảng động ban đầu
    unique_lines = (char **)malloc(max_unique_lines * sizeof(char *));

    while (fgets(line, sizeof(line), f_in) != NULL)
    {
        size_t line_length = strlen(line);
        if (line_length > 0 && line[line_length - 1] == '\n')
        {
            line[line_length - 1] = '\0';
        }

        int is_unique = 1;

        // Kiểm tra xem dòng đã xuất hiện trước đó hay chưa
        for (int i = 0; i < num_unique_lines; i++)
        {
            if (strcmp(unique_lines[i], line) == 0)
            {
                is_unique = 0;
                break;
            }
        }

        if (is_unique)
        {
            // Ghi dòng vào tệp đầu ra
            fprintf(f_out, "%s\n", line);

            // Cấp phát bộ nhớ cho dòng duy nhất và thêm vào danh sách
            unique_lines[num_unique_lines] = (char *)malloc((line_length + 1) * sizeof(char));
            strcpy(unique_lines[num_unique_lines], line);
            num_unique_lines++;

            // Kiểm tra xem có cần thay đổi kích thước mảng động
            if (num_unique_lines >= max_unique_lines)
            {
                max_unique_lines *= 2; // Tăng kích thước gấp đôi khi cần
                unique_lines = (char **)realloc(unique_lines, max_unique_lines * sizeof(char *));
            }
        }

        // Dừng sau khi đã đạt đủ số dòng muốn lưu trữ
        // if (num_unique_lines >= STEP)
        // {
        //     break;
        // }
    }

    printf("Num line: %d\n", num_unique_lines - 1);

    fclose(f_in);
    fclose(f_out);

    // Giải phóng bộ nhớ của mảng động
    for (int i = 0; i < num_unique_lines; i++)
    {
        free(unique_lines[i]);
    }
    free(unique_lines);

    return 0;
}
