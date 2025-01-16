/**
 * Author: Cp Algorithms: https://cp-algorithms.com/
 * Description: nthFibonacci
 * Time: O(\log n)
 */

ll f(ll n) {
    if(n == 0 || n == 1)return dp[n] = 1;
    if(dp[n])return dp[n];
    ll k = n/2;
    if(n % 2 == 0)return dp[n] = (f(k)*f(k) + f(k-1)*f(k-1)) % M;
    return dp[n] = (f(k)*f(k+1) + f(k-1) * f(k)) % M;
}
(n == 0 ? 0 : f(n-1));
