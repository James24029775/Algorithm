// Reference: https://web.ntnu.edu.tw/~algo/Point2.html#3
// sqrt只會在最後才做
// 使用自己的pow
// 使用scanf
// 小於100個點皆枚舉
#include <bits/stdc++.h>

using namespace std;

typedef pair<double, double> coordinate_t;
vector<coordinate_t> od_by_x, od_by_y;

double square(double x) {
    return x*x;
}

double divideAndConquer(long long start, long long end) {
    // Bound Condition
    long long i, j, k, tmp_index;
    double x_coor_1, y_coor_1, x_coor_2, y_coor_2;
    double min_dist = DBL_MAX, tmp_dist;
    if (end - start + 1 <= 100) {
        for (i = 0; i < end - start + 1; i++) {
            for ( j = i+1; j < end - start + 1; j++) {
                if (i == j) {
                    continue;
                }
                x_coor_1 = od_by_x[start + i].first;
                y_coor_1 = od_by_x[start + i].second;
                x_coor_2 = od_by_x[start + j].first;
                y_coor_2 = od_by_x[start + j].second;
                tmp_dist = square(x_coor_1 - x_coor_2) + square(y_coor_1 - y_coor_2);
                min_dist = min(min_dist, tmp_dist);
            }
        }
        return min_dist;
    } 

    // Divide
    long long index = start + (end - start)/2;
    double dist_left = divideAndConquer(start, index);
    double dist_right = divideAndConquer(index + 1, end);
    min_dist = min(dist_left, dist_right);

    if (min_dist == 0){
        return min_dist;
    }

    // Merge
    vector<coordinate_t> tmp;
    double left_d_bound = od_by_x[index].first - min_dist, right_d_bound = od_by_x[index].first + min_dist;
    for(i = 0 ; i < od_by_y.size() ; i++) {
        if(left_d_bound < od_by_y[i].first &&  od_by_y[i].first < right_d_bound) {
            tmp.push_back(od_by_y[i]);
        }
    }
    double min_dist_across = DBL_MAX;
    for (i=0; i<tmp.size()-1; ++i){
		for (j=1; j<=3 && i+j<tmp.size(); ++j){
            x_coor_1 = tmp[i].first;
            y_coor_1 = tmp[i].second;
            x_coor_2 = tmp[i+j].first;
            y_coor_2 = tmp[i+j].second;
            tmp_dist = square(x_coor_1 - x_coor_2) + square(y_coor_1 - y_coor_2);
            min_dist_across = min(min_dist_across, tmp_dist);
        }
    }
	
    return min(min_dist_across, min_dist);
}

int main() {
    long long case_n, dist_n, i; 
    vector<coordinate_t> tmp;
    // cin >> case_n;
    scanf("%lld", &case_n);
    while (case_n--) {
        // cin >> dist_n;
        scanf("%lld", &dist_n);
        tmp.clear();
        od_by_x.clear();
        od_by_y.clear();
        tmp.resize(dist_n);
        for (i = 0; i < dist_n; i++) {
            // cin >> tmp[i].first >> tmp[i].second;
            scanf("%lf%lf", &tmp[i].first, &tmp[i].second);
        }

        sort(tmp.begin(), tmp.end(), [&](const coordinate_t &a, const coordinate_t &b) {
            return a.first < b.first;
        });

        od_by_x.assign(tmp.begin(), tmp.end());

        sort(tmp.begin(), tmp.end(), [&](const coordinate_t &a, const coordinate_t &b) {
            return a.second < b.second;
        });

        od_by_y.assign(tmp.begin(), tmp.end());
        cout << fixed << setprecision(6) << sqrt(divideAndConquer(0, dist_n - 1)) << endl;
    }
}