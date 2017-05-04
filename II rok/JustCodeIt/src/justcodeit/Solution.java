/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package justcodeit;

/**
 *
 * @author Filip
 */
class Solution {

    public int solution(int[] A) {
        int N = A.length;
        int Sum = 0;
        int MaxSum = -1;
        for (int i = 0; i < N; i++) {
            if (A[i] <= 0) {
                Sum=0;
                continue;
            } else {
                Sum += A[i];
            }
            if (Sum >= MaxSum) {
                MaxSum = Sum;
            }
        }
        return MaxSum;
    }
}
