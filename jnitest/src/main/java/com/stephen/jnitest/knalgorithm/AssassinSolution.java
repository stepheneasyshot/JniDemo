package com.stephen.jnitest.knalgorithm;

public class AssassinSolution {

    private static final char EMPTY = '.';

    private static final char OBSTACLE = 'X';

    private static final char ASSASSIN = 'A';

    private static final char LEFT_GUARD = '<';

    private static final char RIGHT_GUARD = '>';

    private static final char UP_GUARD = '^';

    private static final char DOWN_GUARD = 'v';

    public boolean solution(String[] B) {

        int n = B.length;

        int m = B[0].length();

        char[][] board = new char[n][m];

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                board[i][j] = B[i].charAt(j);
            }
        }

        int[] assassinPosition = findAssassinPosition(board);

        if (assassinPosition == null) {
            // Assassin is not on the board
            return false;
        }

        if (isAssassinDetected(board, assassinPosition)) {
            // Assassin is detected by a guard
            return false;
        }

        boolean[][] visited = new boolean[n][m];

        return dfs(board, visited, assassinPosition[0], assassinPosition[1], n - 1, m - 1);

    }

    private int[] findAssassinPosition(char[][] board) {

        int n = board.length;

        int m = board[0].length;

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (board[i][j] == ASSASSIN) {
                    return new int[]{i, j};
                }
            }
        }
        return null;
    }

    private boolean isAssassinDetected(char[][] board, int[] assassinPosition) {

        int n = board.length;

        int m = board[0].length;

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (board[i][j] == LEFT_GUARD && i == assassinPosition[0] && j > assassinPosition[1]) {
                    // Assassin is to the left of the guard
                    return true;
                }
                if (board[i][j] == RIGHT_GUARD && i == assassinPosition[0] && j < assassinPosition[1]) {
                    // Assassin is to the right of the guard
                    return true;
                }

                if (board[i][j] == UP_GUARD && i > assassinPosition[0] && j == assassinPosition[1]) {
                    // Assassin is above the guard
                    return true;
                }

                if (board[i][j] == DOWN_GUARD && i < assassinPosition[0] && j == assassinPosition[1]) {
                    // Assassin is below the guard
                    return true;
                }
            }
        }
        return false;
    }

    private boolean dfs(char[][] board, boolean[][] visited, int i, int j, int n, int m) {
        if (i < 0 || i > n || j < 0 || j > m || board[i][j] == OBSTACLE || visited[i][j]) {
            return false;
        }
        if (i == n && j == m) {
            return true;
        }
        visited[i][j] = true;
        return dfs(board, visited, i + 1, j, n, m) || dfs(board, visited, i - 1, j, n, m) || dfs(board, visited, i, j + 1, n, m) || dfs(board, visited, i, j - 1, n, m);
    }
}