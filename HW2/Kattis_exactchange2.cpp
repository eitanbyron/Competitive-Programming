//
// Created by barbe on 03/06/2023.
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

int main() {
    int num_test_cases;
    cin >> num_test_cases;
    while(num_test_cases--){
        int item_price, bills_num, total_amount_bills = 0;
        cin >> item_price >> bills_num;
        vector<int> bills(bills_num);
        for (int i = 0; i < bills_num; ++i) {
            cin >> bills[i];
            total_amount_bills += bills[i];
        }
        sort(bills.begin(), bills.end());
        vector<int> dp (total_amount_bills + 1, 1e9);
        dp[0] = 0;
        for (int i = 0; i < bills_num; ++i) {
            for (int j = total_amount_bills; j > 0 ; --j) {
                if(j >= bills[i]){
                    dp[j] = min(dp[j-bills[i]] + 1, dp[j]);
                }else{
                    break;
                }
            }
        }
        for (int i = item_price; i <= total_amount_bills; ++i) {
            if(dp[i] != 1e9){
                cout << i << " " << dp[i] << endl;
                break;
            }
        }
    }
    return 0;
}
