// Reference: https://web.ntnu.edu.tw/~algo/Point2.html#3
// 參考上述筆記，尚未做距離中線d的縮圈
#include <bits/stdc++.h>

using namespace std;

class coordinate_t {
   public:
    pair<double, double> point;
    int id;
};

double divideAndConquer(vector<coordinate_t> od_by_x, vector<coordinate_t> od_by_y, int start, int end) {
    int i, j, k, tmp_index;
    double x_coor_1, y_coor_1, x_coor_2, y_coor_2;
    double min_dist = DBL_MAX, tmp_dist;
    if (end - start + 1 == 2) {
        x_coor_1 = od_by_x[start].point.first;
        y_coor_1 = od_by_x[start].point.second;
        x_coor_2 = od_by_x[end].point.first;
        y_coor_2 = od_by_x[end].point.second;

        return sqrt(pow(x_coor_1 - x_coor_2, 2) + pow(y_coor_1 - y_coor_2, 2));

    } else if (end - start + 1 == 3) {
        for (i = 0; i < 3; i++) {
            if (start + i + 1 > end) {
                tmp_index = start;
            } else {
                tmp_index = start + i + 1;
            }
            x_coor_1 = od_by_x[start + i].point.first;
            y_coor_1 = od_by_x[start + i].point.second;
            x_coor_2 = od_by_x[tmp_index].point.first;
            y_coor_2 = od_by_x[tmp_index].point.second;
            tmp_dist = sqrt(pow(x_coor_1 - x_coor_2, 2) + pow(y_coor_1 - y_coor_2, 2));
            if (min_dist > tmp_dist) {
                min_dist = tmp_dist;
            }
        }
        return min_dist;
    }

    int index = (start + end) / 2;
    double dist_left = divideAndConquer(od_by_x, od_by_y, start, index);
    double dist_right = divideAndConquer(od_by_x, od_by_y, index + 1, end);
    min_dist = min(dist_left, dist_right);

    if (min_dist == 0){
        return min_dist;
    }

    double min_dist_across = DBL_MAX;
    for (i=0; i<od_by_y.size()-1; ++i){
		for (int j=1; j<=3 && i+j<od_by_y.size(); ++j){
            x_coor_1 = od_by_y[i].point.first;
            y_coor_1 = od_by_y[i].point.second;
            x_coor_2 = od_by_y[i+j].point.first;
            y_coor_2 = od_by_y[i+j].point.second;
            tmp_dist = sqrt(pow(x_coor_1 - x_coor_2, 2) + pow(y_coor_1 - y_coor_2, 2));
            min_dist_across = min(min_dist_across, tmp_dist);
        }
    }
			

    return min(min_dist_across, min_dist);
}

int main() {
    int case_n, dist_n, i;
    vector<coordinate_t> points, od_by_x, od_by_y, tmp;
    cin >> case_n;
    while (case_n--) {
        cin >> dist_n;
        points.clear();
        od_by_x.clear();
        od_by_y.clear();
        tmp.clear();
        points.resize(dist_n);
        for (i = 0; i < dist_n; i++) {
            cin >> points[i].point.first >> points[i].point.second;
            points[i].id = i;
        }

        tmp.assign(points.begin(), points.end());

        sort(tmp.begin(), tmp.end(), [&](const coordinate_t &a, const coordinate_t &b) {
            return a.point.first < b.point.first;
        });

        od_by_x.assign(tmp.begin(), tmp.end());

        sort(tmp.begin(), tmp.end(), [&](const coordinate_t &a, const coordinate_t &b) {
            return a.point.second < b.point.second;
        });

        od_by_y.assign(tmp.begin(), tmp.end());
        cout << fixed << setprecision(6) << divideAndConquer(od_by_x, od_by_y, 0, dist_n - 1) << endl;
    }
}