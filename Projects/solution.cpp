#include <bits/stdc++.h>

using namespace std;

// global variables
fstream file;

class Contributor {
    public:
        string name;
        vector<pair<string, int> > skills; 

        void printSkills() {
            cout << name << ": ";
            
            for (auto p : skills) 
                cout <<"("<< p.first << ", " << p.second << ") ";
        
            cout << endl;
        }
};

class Project {
    public:
        string name;
        int complete_time;
        int score;
        int bb;
        int roles;
        vector<pair<string, int> > skills;
        vector<string> con; 

        void printSkills() {

            cout <<"Project: "<< name;
            cout << " -> Skills: ";
            for (auto p : skills) 
                cout <<"("<< p.first << ", " << p.second << ") ";
            cout << endl;
        }

        void printContributors() {
            cout <<"Project: "<< name;
            cout << " -> Contributors: ";
            
            for (auto c : con) cout << c << " ";
            cout << endl;
        }
};

vector<Project> allocateProjects(vector<Contributor> contributors, vector<Project> projects) {
    vector<Project> accepted;

    for (auto pj : projects) {

        for (auto pj_skill : pj.skills) {
           
            string pj_skill_name = pj_skill.first;
            int pj_lvl = pj_skill.second;

            for (auto con : contributors) {
                for (auto con_skill : con.skills) {
                
                    string con__skill_name = con_skill.first;
                    int con_lvl = con_skill.second;
                    
                    if (pj_skill_name == con__skill_name) {
                        
                        if (con_lvl >= pj_lvl) {
                            pj.con.push_back(con.name);
                        }
                    }
                }
            }
        }
        accepted.push_back(pj);
        pj.printContributors();
    }

    cout << "\nsize: "<< accepted.size() << "\n";

    return accepted;
}

vector<Project> readFile(string filename) {

    int total_cb, total_p; // contributors, projects

    vector<Contributor> contributors;
    vector<Project> projects;

    // read from file
    file.open(filename, ios::in);
    if (file.is_open()) {

        string line;
        getline(file, line); // get first line

        istringstream iss_1(line);
        vector<string> totals { istream_iterator<string>{iss_1},
                    istream_iterator<string>{}};

        total_cb = stoi(totals[0]);
        total_p  = stoi(totals[1]);

        cout << "\nContributors: " << total_cb << " Projects: " << total_p << "\n";

        // get contributors
        for (int t_1 = 0; t_1 < total_cb; t_1++) {
            getline(file, line);

            // convert string to vector
            istringstream iss(line);
            vector<string> cb { istream_iterator<string>{iss},
                            istream_iterator<string>{}};

            Contributor con;
            con.name = cb[0]; 
            int num_skills = stoi(cb[1]);

            for (int i = 0; i < num_skills; i++) {
                getline(file, line);

                istringstream iss_tmp(line);
                vector<string> tmp { istream_iterator<string>{iss_tmp},
                            istream_iterator<string>{}};
                
                pair<string, int> skill(tmp[0], stoi(tmp[1]));
                con.skills.push_back(skill);
            }

            contributors.push_back(con);
        }

        // get projects
        for (int t_2 = 0; t_2 < total_p; t_2++) {
            getline(file, line);

            istringstream iss_tmp(line);
            vector<string> tmp { istream_iterator<string>{iss_tmp},
                        istream_iterator<string>{}};
            
            Project pj;
            pj.name = tmp[0];
            pj.complete_time = stoi(tmp[1]);
            pj.score = stoi(tmp[2]);
            pj.bb = stoi(tmp[3]);
            pj.roles = stoi(tmp[4]);

            for (int i = 0; i < pj.roles; i++) {
                getline(file, line);

                istringstream iss_tmp2(line);
                vector<string> tmp2 { istream_iterator<string>{iss_tmp2},
                            istream_iterator<string>{}};
                
                pair<string, int> skill(tmp2[0], stoi(tmp2[1]));
                pj.skills.push_back(skill);
            }

            projects.push_back(pj);
        }
        file.close();
    }

    return allocateProjects(contributors, projects);
}

void writeFile(vector<Project> projects, string filename) {
       
    // write to file
    file.open(filename, ios::out);
    if (file.is_open()) {

        file << projects.size() << "\n";
        for(auto pj : projects) {
            if (pj.con.size() > 0) {
                file << pj.name << "\n";
            
                for (auto c : pj.con) file << c << " ";
                file << "\n";
            }
        }

        file.close();
    }
}


int main() {

    vector<Project> result = readFile("a_an_example.in.txt");
    writeFile(result, "1.txt");
   // readFile("c_collaboration.in.txt");
    //readFile("d_dense_schedule.in.txt");
    //readFile("e_exceptional_skills.in.txt");
    //readFile("f_find_great_mentors.in.txt");

    return 0;
}
