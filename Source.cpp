#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int str_l(string l) {
    int i = 0;
    while (l[i] != '\0') {
        i++;
    }
    return i;
}

int decimal_(string i, int b = 2) {
    int power = 1, num = 0;
    for (int j = str_l(i) - 1; j >= 0; j--) {
        num += power * (i[j] - '0');
        power *= b;
    }
    return num;
}

class games_played {
    string game_id;
    float hours;
    int achievements;
};

class player {
    string playerID, name, PhoneNO, email, password;
    games_played g;
};

class games {
    string gameID, name, developer, publisher;
    float size;
    int down;
    games* left, * right;
public:
    games() {
        gameID = name = developer = publisher = "";
        size = 0.0;
        down = 0;
        left = right = nullptr;
    }

    games(string id, string nam, string dev, string pub, float s, int d)
        : gameID(id), name(nam), developer(dev), publisher(pub), size(s), down(d), left(nullptr), right(nullptr) {}

    string get_id() {
        return gameID;
    }

    games*& gleft() {
        return left;
    }

    games*& gright() {
        return right;
    }
};

class Tree_game {
    games* root;
public:
    Tree_game() {
        root = nullptr;
    }

    games*& get_root() {
        return root;
    }

    void insert(games*& root, games* s) {
        if (root == nullptr) {
            root = s;
            return;
        }
        if (decimal_(root->get_id()) > decimal_(s->get_id())) {
            insert(root->gleft(), s);
        }
        else if (decimal_(root->get_id()) < decimal_(s->get_id())) {
            insert(root->gright(), s);
        }
    }
    void postorderTraversal(games* root) {
        if (root == nullptr) {
            return;
        }
        else {
            postorderTraversal(root->gleft());
            postorderTraversal(root->gright());
            cout << root->get_id() << "\n";
        }
    }
};
void load_game(string s,Tree_game *ga) {
    ifstream file(s);
    string line;

    // Read and output each line
    while (getline(file, line)) {
        string id = "", n = "", d = "", p = "";
        float si = 0.0;
        int dow = 0, i = 0;

        // extract the game id
        while (line[i] != ',') {
            id += line[i++];
        }
        i++;
        // extract the game name
        while (line[i] != ',') {
            n += line[i++];
        }
        i++;
        // extract the developer
        while (line[i] != ',') {
            d += line[i++];
        }
        i++;
        // extract the publisher
        while (line[i] != ',') {
            p += line[i++];
        }
        i++;
        // extract size 
        string size_str = "";
        while (line[i] != ',') {
            size_str += line[i++];
        }
        si = stof(size_str);
        i++;
        // extract Downloads (convert string to int)
        string downloads_str = "";
        while (i < line.length()) {
            downloads_str += line[i++];
        }
        dow = decimal_(downloads_str);  // Convert to int
        // Dynamically allocate the game object
        games* tg = new games(id, n, d, p, si, dow);

        ga->insert(ga->get_root(), tg);
    }

    file.close();  // Close the file
}
int main() {
    string s = "C:\\Users\\user\\OneDrive\\Desktop\\Games.txt";  // games file path
    Tree_game ga;

    load_game(s, &ga);
    ga.postorderTraversal(ga.get_root());
    return 0;
}
