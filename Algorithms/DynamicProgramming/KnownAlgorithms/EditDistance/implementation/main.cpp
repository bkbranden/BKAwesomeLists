#include <vector>
#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

int minThree(int x, int y, int z) {
    int temp = min(x, y);
    return min(temp, z);
}

int editDistance(string compare, string target) {
    int length_one = compare.length();
    int length_two = target.length();

    vector<vector<int>> dp(length_two + 1, vector<int> (length_one + 1, 0));

    // Populating the first column since to convert empty string to any target string, it will
    // need the same number of operations as the target string length
    for (int i = 0; i < dp.size(); i++) {
        dp.at(i).at(0) = i;
    }

    // Same thing as above but for the first row
    for (int j = 0; j < dp.at(0).size(); j++) {
        dp.at(0).at(j) = j;
    }

    // Main bulk for loop, populating each cell of the dynamic programming matrix using the
    // transitions necessary
    for (int i = 1; i < dp.size(); i++) {
        for (int j = 1; j < dp.at(0).size(); j++) {

            // If the characters being compared are the same then don't need to do anything 
            // since the edit distance cost is the same as not including these characters
            if (compare.at(j - 1) == target.at(i - 1)) {
                dp.at(i).at(j) = dp.at(i - 1).at(j - 1);
            }

            // If the characters are not the same, then we need to take the min of the 3
            // possible operations that can be done to turn the current character into
            // the desired target character
            else {

                // Insert cost comes from the idea of if a string of length [0-i] is optimal (the same)
                // as a string of length [0-(j-1)], then just need to take the cost it took to get there
                // and insert any character to get the target character we are comparing to
                int insert_cost_so_far = dp.at(i).at(j - 1);

                // Replace has the same idea, length [0-(i-1)] compared to length [0-(j-1)] and to turn
                // current string into target, just need to replace the current character and add one
                // to the cost it took to get there
                int replace_cost_so_far = dp.at(i - 1).at(j - 1);

                // Delete has the same idea except, you look at length [0-(i-1)] to length [0-j] since
                // you are assuming by deleting the character the result is the same string as
                // desired
                int delete_cost_so_far = dp.at(i - 1).at(j);

                dp.at(i).at(j) = minThree(insert_cost_so_far, replace_cost_so_far, delete_cost_so_far) + 1;
            }
        }
    }

    // The bottom rightmost cell has the minimum number of operations needed
    return dp[length_two][length_one];  
}

/**
 * Optimized implementation where you reduce the row size of the dp array to 2 since you only
 * need the previous row's information to calculate the current row
 */
int editDistanceSpaceOptimized(string compare, string target) {
    int len1 = compare.length();
    int len2 = target.length();

    vector<vector<int>> dp(2, vector<int>(len1 + 1, 0));

    // Populating the case where the target string is the empty string so you need current length
    // of string number of operations to make it the empty string
    for (int i = 0; i < dp.at(0).size(); i++) {
        dp.at(0).at(i) = i;
    }

    // In the main loop, we utilize the mod operator to distiguish between even / odd characters in
    // the target string to create a way totrack states / index into it
    for (int i = 1; i < len2 + 1; i++) {
        for (int j = 0; j < len1 + 1; j++) {
            if (j == 0) {
                dp.at(i % 2).at(j) = i;
            }
            else if (compare[j - 1] == target[i - 1]) {
                dp.at(i % 2).at(j) = dp.at((i - 1) % 2).at(j - 1);
            }
            else {
                int insert_cost_so_far = dp.at(i % 2).at(j - 1);
                int replace_cost_so_far = dp.at((i - 1) % 2).at(j - 1);
                int delete_cost_so_far = dp.at((i - 1) % 2).at(j);

                dp.at(i % 2).at(j) = minThree(insert_cost_so_far, replace_cost_so_far, delete_cost_so_far) + 1;
            }
        }
    }

    return dp[len2 % 2][len1];
}

int main() {

    #ifdef _DEBUG
        freopen("input.txt", "r", stdin);
        // freopen("output.txt", "w", stdout);
    #endif

    string compare, target;
     
    cin >> compare >> target;

    cout << "UNOPTIMIZED DP: " << endl;
    cout << editDistance(compare, target) << endl;
    cout << "\n";

    cout << "OPTIMIZED SPACE DP: " << endl;
    cout << editDistanceSpaceOptimized(compare, target) << endl;

    return 0;
}