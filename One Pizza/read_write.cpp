#include <bits/stdc++.h>

using namespace std;

int main() {

    // ios_base::sync_with_stdio(false);
    // cin.tie(NULL);

    string sentence = "And I feel fine...";
    istringstream iss(sentence);

    // vector<string> tokens { istream_iterator<string>{iss},
    //                 istream_iterator<string>{}};

    vector<string> tokens;
    copy(istream_iterator<string>(iss),
        istream_iterator<string>(),
        back_inserter(tokens));
    
    for (auto t : tokens) cout << t << "\n";

    fstream file;

    // write to file
    file.open("test.txt", ios::out);
    if (file.is_open()) {
        file << "File Content\n";
        file.close();
    }

    // append to file
    file.open("test.txt", ios::app);
    if (file.is_open()) {
        file << "appended Content\n";
        file.close();
    }
    
    // read from file
    file.open("a_an_example.in.txt", ios::in);
    if (file.is_open()) {

        string line;
        getline(file, line); // get first line
        cout << line << "\n";
        
        while (getline(file, line)) {
            
            cout << "liked: " << line << "\n";

            getline(file, line);
            cout << "disliked: " << line << "\n";
        }

        file.close();
    }

    return 0;
}
