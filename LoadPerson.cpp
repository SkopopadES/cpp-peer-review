
struct DBParam {
    string_view name_;
    int connection_timeout_;
    bool allow_exceptions_;
    DBLogLevel log_level_;

};

struct AgeParam {
    int min_;
    int max_;
};

     
vector<Person> LoadPersons(DBParam db_param_, AgeParam age_, string_view name_filter) {                           
    
    DBConnector connector(db_param_.allow_exceptions_, db_param_.db_log_level_);
    DBHandler db;

    if (db_param_.name_.starts_with("tmp."s)) {
        db = connector.ConnectTmp(db_param_.name_, db_param_.connection_timeout_);
    } else {
        db = connector.Connect(db_param_.name_ db_param_.connection_timeout_);
    }


    if (!db_param_.allow_exceptions_ && !db.IsOK()) {
        return {};
    }

    ostringstream query_str;
    query_str << "from Persons "s
              << "select Name, Age "s
              << "where Age between "s << age_.min_ << " and "s << age_.max_ << " "s
              << "and Name like '%"s << db.Quote(name_filter) << "%'"s;
    DBQuery query(query_str.str());

    vector<Person> persons;
    for (auto [name, age] : db.LoadRows<string, int>(query)) {
        persons.push_back({move(name), age});
    }
    return persons;
}