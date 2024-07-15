def is_winner(board, player):
    for i in range(3):
        if all([board[i][j] == player for j in range(3)]) or all([board[j][i] == player for j in range(3)]):
            return True
    if all([board[i][i] == player for i in range(3)]) or all([board[i][2 - i] == player for i in range(3)]):
        return True
    return False


def is_board_full(board):
    return all(all(cell != '.' for cell in row) for row in board)


def minimax(board, depth, is_maximizing, alpha=-float('inf'), beta=float('inf')):
    if is_winner(board, 'X'):
        return 10 - depth
    if is_winner(board, 'O'):
        return depth - 10
    if is_board_full(board):
        return 0

    if is_maximizing:
        best_score = -float('inf')
        for i in range(3):
            for j in range(3):
                if board[i][j] == '.':
                    board[i][j] = 'X'
                    score = minimax(board, depth + 1, False, alpha, beta)
                    board[i][j] = '.'
                    best_score = max(score, best_score)
                    alpha = max(alpha, best_score)
                    if beta <= alpha:
                        break
        return best_score
    else:
        best_score = float('inf')
        for i in range(3):
            for j in range(3):
                if board[i][j] == '.':
                    board[i][j] = 'O'
                    score = minimax(board, depth + 1, True, alpha, beta)
                    board[i][j] = '.'
                    best_score = min(score, best_score)
                    beta = min(beta, best_score)
                    if beta <= alpha:
                        break
        return best_score


table = [list(input().strip()) for _ in range(3)]
x_count = sum(row.count('X') for row in table)
o_count = sum(row.count('O') for row in table)

if not (0 <= x_count - o_count <= 1) or is_winner(table, 'X') and is_winner(table, 'O'):
    print("invalid configuration")
    exit()

turn = 'X' if x_count == o_count else 'O'
score = minimax(table, 0, turn == 'X')

if score > 0:
    print("X wins")
elif score < 0:
    print("O wins")
else:
    print("draw")
