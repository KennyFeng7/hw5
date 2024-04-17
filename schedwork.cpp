#ifndef RECCHECK
#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
// add or remove necessary headers as you please

#endif

#include "schedwork.h"

using namespace std;

// a constant that can be used to indicate an INVALID 
// worker ID if that is useful to your implementation.
// Feel free to not use or delete.
static const Worker_T INVALID_ID = (unsigned int)-1;


// Add prototypes for any helper functions here
bool schedulehelper(int day, int worker, DailySchedule& sched, vector<int>& record, const AvailabilityMatrix& avail, size_t dailyNeed, size_t maxShifts);


// Add your implementation of schedule() and other helper functions here


bool schedule(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched
)
{
    if(avail.size() == 0U){
        return false;
    }
    sched.clear();
    // Add your code below
    vector<int> record(avail[0].size(), 0);
    return schedulehelper(0, 0, sched, record, avail, dailyNeed, maxShifts);
}

bool schedulehelper(int day, int worker, DailySchedule& sched, vector<int>& record, const AvailabilityMatrix& avail, size_t dailyNeed, size_t maxShifts) {
  if (day >= avail.size()) {
        return true; 
  }
  if (sched.size() <= day) sched.resize(day + 1);

  for (int id = 0; id < avail[day].size(); id++) {
    if (record[id] < maxShifts && find(sched[day].begin(), sched[day].end(), id) == sched[day].end() && avail[day][id] == 1) {
        sched[day].push_back(id);
        record[id]++;
        if (worker >= dailyNeed - 1) {
            if (schedulehelper(day + 1, 0, sched, record, avail, dailyNeed, maxShifts)) {
                return true;
            }
        } else {
            if (schedulehelper(day, worker + 1, sched, record, avail, dailyNeed, maxShifts)) {
                return true;
            }
        }
        sched[day].pop_back();
        record[id]--;
    }
  }
  return false;
}
