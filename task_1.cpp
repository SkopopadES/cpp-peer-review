
#include <iostream>
#include <iomanip>
#include<math.h>
#include <algorithm>
#include <set>
#include <vector>

using namespace std;

static const int MAX_USER_COUNT_ = 100000;
static const int MAX_PAGES_ = 1000;

class SystemControlReading {
public:

    SystemControlReading(){
    }
    
    void SaveUserPage(int user_id, int page_num) {
        
        
        for (int i = user_[user_id-1]; i < page_num; ++i) {
            ++num_page_[i];
        }
        user_[user_id-1] = page_num;
    }
    
    double GetCheerToUser(int user_id) {
        if (user_[user_id-1] == 0){
            return 0;
        } 
        if (num_page_[0] == 1){
            return 1; 
        } 
        return (num_page_[0] - num_page_[user_[user_id-1]-1]) * 1.0 / (num_page_[0]-1) * 1.0;
    }
    
private:    
    vector<int> user_= vector<int>(MAX_USER_COUNT_);
    vector<int> num_page_= vector<int>(MAX_PAGES_); 
};

int main() {
    SystemControlReading system_control_reading;
    int cmd_count;
    cin >> cmd_count;
   
    for (int id = 0; id < cmd_count; ++id) {
        string cmd;      
        cin >>cmd; 

        int user_id;
        cin >> user_id;
        
        if (cmd == "READ") {
            int num_page;
            cin >> num_page;
            system_control_reading.SaveUserPage(user_id, num_page);
        }
        if (cmd == "CHEER") {
            cout << setprecision(6) << system_control_reading.GetCheerToUser(user_id) << "\n";
        }
    }
    
    return 0;
}