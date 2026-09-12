int d[N], D[N];

void calOdd(){
    int L = 1, R = 0;
    for(int i=1; i<=n; ++i){
        if(i > R) d[i] = 0;
        else d[i] = min(R - i, d[L + R - i]);
        while(1 <= i - d[i] - 1 && i + d[i] + 1 <= n && s[i-d[i]-1] == s[i+d[i]+1]) d[i]++;
        if(i + d[i] > R) L = i - d[i], R = i + d[i];
    }
}

void CalEven(){
    int L = 1, R = 0;
    for(int i=1; i<n; ++i){
        int j = i + 1;
        if(j > R) D[i] = 0;
        else D[i] = min(R - j + 1, D[L + R - j]);
        while(1 <= i - D[i] && j + D[i] <= n && s[i-D[i]] == s[j+D[i]]) D[i]++;
        if(i + D[i] > R) L = j - D[i], R = i + D[i];
    }
}
