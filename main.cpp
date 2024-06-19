#include <bits/stdc++.h>
#include <unistd.h>
using namespace std;

int main(){
  cout << "size is pow(2,?)? >> "; cout.flush(); int n; cin >> n;
  cout << "Query type? (0:Point add/Range sum 1:Range add/Point sum) >> ";
  int q; cin >> q;
  vector<int> segtree(1<<n+1);
  auto draw = [&segtree,&n](vector<int>& use) -> void {
    int x = to_string(*max_element(segtree.end()-(1<<n),segtree.end())).size()+2;
    vector<int> dp(segtree.size()); for (int i((1<<n)-1);i;--i) dp[i] = dp[i<<1]+1;
    int b = 99;
    cout << "\e[2J";
    for (int i(1);i < (1<<n+1);++i){
      if (b!=dp[i]) cout << endl;
      b = dp[i];
      if (binary_search(use.begin(),use.end(),i)) cout << "\e[41m";
      string s,t=to_string(segtree[i]); for (int k(0);k < x*(1<<dp[i]);++k) s+=' ';
      s[0] = s.back() = '|';
      for (int i(0);i < t.size();++i) s.end()[i-2] = t.end()[i-1];
      cout << s << "\e[0m";
    }
    cout << endl;
  };
  vector<int> use; int res = 0; bool s = 1; int m = 1<<n;
  while(true){
    sort(use.begin(),use.end()); draw(use);
    if (!s) cout << "Answer: " << res << "   ";
    cout << "Query? (0:get 1:update 2:quit) >> "; int a; cin >> a;
    res = 0,use.clear(),s = 0;
    if (a==2) break;
    else if (a==0){
      if (q==0){
        cout << "left? >> "; int l; cin >> l; l+=m;
        cout << "right? >> "; int r; cin >> r; r+=m;
        for (;l < r;l>>=1,r>>=1){
          if (l&1) use.emplace_back(l),res+=segtree[l++];
          if (r&1) use.emplace_back(--r),res+=segtree[r];
        }
      } else {
        cout << "index? >> "; int l; cin >> l; l+=m;
        for (;l;l>>=1) use.emplace_back(l),res+=segtree[l];
      }
    } else if (a==1){
      if (q==0){
        cout << "index? >> "; int l; cin >> l; l+=m;
        cout << "how much? >> "; int r; cin >> r;
        for (;l;l>>=1) use.emplace_back(l),segtree[l]+=r;
      } else {
        cout << "left? >> "; int l; cin >> l; l+=m;
        cout << "right? >> "; int r; cin >> r; r+=m;
        cout << "how much? >> "; int b; cin >> b;
        for (;l < r;l>>=1,r>>=1){
          if (l&1) use.emplace_back(l),segtree[l++]+=b;
          if (r&1) use.emplace_back(--r),segtree[r]+=b;
        }
      }
      s = 1;
    } else s = 1;
  }
  system("clear");
}