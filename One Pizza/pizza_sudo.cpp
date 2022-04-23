#include <bits/stdc++.h>

using namespace std;

fstream file; 

vector<string> createPizza(string filename) {

    int total_clients;
    vector<string> liked;
    vector<string> disliked;

    // read from file
    file.open(filename, ios::in);
    if (file.is_open()) {

        string line;

        getline(file, line); // get first line
        total_clients = stoi(line);
        cout <<"Total Clients: "<< total_clients <<"\n";
        
        while (getline(file, line)) {
    
            line[0] = ' ';

            // add liked ingredients
            istringstream iss_liked(line);
            copy(istream_iterator<string>(iss_liked),
                istream_iterator<string>(),
                back_inserter(liked));
            

            getline(file, line);
            line[0] = ' ';

            // add disliked ingredients
            istringstream iss_disliked(line);
            copy(istream_iterator<string>(iss_disliked),
                istream_iterator<string>(),
                back_inserter(disliked));

        }

        // remove duplicate ingredients
        sort( liked.begin(), liked.end() );
        liked.erase( unique( liked.begin(), liked.end() ), liked.end() );

        sort( disliked.begin(), disliked.end() );
        disliked.erase( unique( disliked.begin(), disliked.end() ), disliked.end() );

        cout <<"Liked: "<< liked.size() << " ";
        cout <<"Disliked: "<< disliked.size() << "\n\n";

        for (auto i = 0; i < int(liked.size()); i++) {
            for(auto d : disliked){
                if (liked[i] == d) liked.erase(liked.begin() + i);
            }
        } 

        // cout << liked.size() << " ";
        // for (auto l : liked) cout << l << " ";

        file.close();
    }

    return liked;
}

void writeToFile(vector<string> pizza, string filename) {

    // write to file
    file.open(filename, ios::out);
    if (file.is_open()) {

        file << pizza.size() << " ";
        for (auto ingredient : pizza) file << ingredient << " ";

        file.close();
    } 
}


int main() {

   // ios_base::sync_with_stdio(false);
   // cin.tie(NULL);

    vector<string> pizza_1 = createPizza("a_an_example.in.txt");
    writeToFile(pizza_1, "1.txt");

    vector<string> pizza_2 = createPizza("b_basic.in.txt");
    writeToFile(pizza_2, "2.txt");

    vector<string> pizza_3 = createPizza("c_coarse.in.txt");
    writeToFile(pizza_3, "3.txt");

    vector<string> pizza_4 = createPizza("d_difficult.in.txt");
    writeToFile(pizza_4, "4.txt");

    vector<string> pizza_5 = createPizza("e_elaborate.in.txt");
    writeToFile(pizza_5, "5.txt");

    return 0;
}
