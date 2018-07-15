/**
 * Definition for an interval.
 * struct Interval {
 *     int start;
 *     int end;
 *     Interval() : start(0), end(0) {}
 *     Interval(int s, int e) : start(s), end(e) {}
 * };
 */
class Solution {
public:
    vector<Interval> merge(vector<Interval> &intervals) {
        vector<Interval> res;
        int size = intervals.size();
        if(size == 0)
            return res;
        sort(intervals.begin(),intervals.end(),cmp);
        for(int i = 0; i<size; i++)
        {
            if(res.empty())
                res.push_back(intervals[i]);
            else
            {
                Interval last = res.back();
                if(last.end < intervals[i].start)
                    res.push_back(intervals[i]);
                else//need  Merge
                {
                    res.pop_back();
                    last.end = max(last.end,intervals[i].end);
                    res.push_back(last);
                }
            }
        }
        return res;
    }
    static bool cmp(Interval l,Interval r)
    {
        if(l.start == r.start)
            return l.end < r.end;
        else
            return l.start<r.start;
    }
};
