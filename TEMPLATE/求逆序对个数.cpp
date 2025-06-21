// 求逆序对个数
template<typename T>
int countInversions(std::vector<T> &a) {
    int n = a.size();
    std::vector<T> tmp(n);
    std::function<int(int,int)> merge_count = [&](int l, int r) -> int {
        if (r - l <= 1) return 0;
        int m = (l + r) / 2;
        int inv = merge_count(l, m) + merge_count(m, r);
        int i = l, j = m, k = l;
        while (i < m && j < r) {
            if (a[i] <= a[j]) tmp[k++] = a[i++];
            else {
                tmp[k++] = a[j++];
                inv += m - i;
            }
        }
        while (i < m) tmp[k++] = a[i++];
        while (j < r) tmp[k++] = a[j++];
        for (int t = l; t < r; ++t) a[t] = tmp[t];
        return inv;
    };
    return merge_count(0, n);
}