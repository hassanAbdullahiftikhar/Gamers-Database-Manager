#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int str_l(string l) {//O(n)
    int i = 0;
    while (l[i] != '\0') {
        i++;
    }
    return i;
}

int decimal_(string i, int b = 2) {//O(n)
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
    games_played* left;
    games_played* right;
public:
    games_played() {
        game_id = "";
        hours = 0.0;
        achievements = 0;
        left = right = nullptr;
    }
    games_played(string i, float h, int a) :game_id(i), hours(h), achievements(a) {}
    float get_h() {
        return hours;
    }
    int get_ach() {
        return achievements;
    }
    string get_id() {
        return game_id;
    }
    games_played*& getleft() {
        return left;
    }
    games_played*& getright() {
        return right;
    }
};
class games_playedT {
    games_played* root;
public:
    games_playedT() {
        root = nullptr;
    }
    games_played*& get_root() {
        return root;
    }
    void gamesp_search(string gid,games_played*&root) {
        if (root == nullptr) {
            cout << "Hasnt played\n";
            return;
        }
        else {
            if (decimal_(gid) < decimal_(root->get_id())) {
                gamesp_search(gid,root->getleft());
            }
            else if (decimal_(gid) > decimal_(root->get_id())) {
                gamesp_search(gid, root->getright());
            }
            else if (decimal_(gid) == decimal_(root->get_id())) {
                cout << "Has played game\n";
                return;
            }
        }
    }
    void postorderTraversal(games_played* root) {
        if (root == nullptr) {
            return;
        }
        else {
            postorderTraversal(root->getleft());
            postorderTraversal(root->getright());
            cout <<"Game id:" << root->get_id() << " Hours:"
                <<root->get_h()<<" Achievements:"<<root->get_ach()<<"\n";
        }
    }
    void insert(games_played*& root, games_played* s) {//O(logn)
        if (root == nullptr) {
            root = s;
            return;
        }
        else {
            if (decimal_(root->get_id()) > decimal_(s->get_id())) {
                insert(root->getleft(), s);
            }
            else if (decimal_(root->get_id()) < decimal_(s->get_id())) {
                insert(root->getright(), s);
            }
        }
    }
};
class player {
    string playerID, name, PhoneNO, email, password;
    games_playedT g;
    player* left, * right;
public:
    player() {
        playerID = name = PhoneNO = email = password="";
        left = right = nullptr;
        //g.get_root() = nullptr;
    }
    games_playedT& get_played_games() {
        return g;
    }
    player(string id,string n,string no,string em,string pass):
        playerID(id),name(n),PhoneNO(no),email(em),password(pass){
        left = right = nullptr;
    }
    player*& getleft() {
        return left;
    }
    player*& getright() {
        return right;
    }
    string get_id() {
        return playerID;
    }
    string get_dets() {
        string s = playerID + " " + name + " " + PhoneNO + " " + email + " "
            + password;
        return s;
    }
};
class Tree_player {
    player* root;
public:
    Tree_player() {
        root = nullptr;
    }
    player*& getroot() {
        return root;
    }
    void display_dets(string id, player*& root) {
        if (root == nullptr) {
            cout << "Player not present\n";
            return;
        }
        else {
            if (decimal_(root->get_id()) > decimal_(id)) {
                display_dets(id, root->getleft());
            }
            else if (decimal_(root->get_id()) < decimal_(id)) {
                display_dets(id, root->getright());
            }
            else if (decimal_(root->get_id()) == decimal_(id)) {
                cout << root->get_dets();
                root->get_played_games()
                    .postorderTraversal(root->get_played_games().get_root());
                return;
            }
        }
    }
    void search_player(string id,player*& root) {
        if (root == nullptr) {
            cout << "Player not present\n";
            return;
        }
        else {
            if (decimal_(root->get_id()) > decimal_(id)) {
                search_player(id, root->getleft());
            }
            else if (decimal_(root->get_id()) < decimal_(id)) {
                search_player(id, root->getright());
            }
            else if (decimal_(root->get_id()) == decimal_(id)) {
                cout << "Player found\n";
                cout << root->get_id() << "\n";
                return;
            }
        }
    }
    void search_p(string id, string game_id, player*&root) {
        if (root == nullptr) {
            cout << "Player not present\n";
            return;
        }
        else {
            if (decimal_(root->get_id()) > decimal_(id)) {
                search_p(id,game_id,root->getleft());
            }
            else if (decimal_(root->get_id()) < decimal_(id)) {
                search_p(id,game_id,root->getright());
            }
            else if (decimal_(root->get_id()) ==decimal_(id)) {
                cout << "Player found\n";
                root->get_played_games().gamesp_search(game_id, root->get_played_games().get_root());
                return;
            }
        }
    }
    void insert(player*&root,player*s) {//O(logn)
        if (root == nullptr) {
            root = s;
            return ;
        }
        else {
            if (decimal_(root->get_id()) > decimal_(s->get_id())) {
                insert(root->getleft(), s);
            }
            else if (decimal_(root->get_id()) < decimal_(s->get_id())) {
                insert(root->getright(), s);
            }
        }
    }
    void postorderTraversal(player* root) {
        if (root == nullptr) {
            return;
        }
        else {
            postorderTraversal(root->getleft());
            postorderTraversal(root->getright());
            cout << root->get_id() << "\n";
        }
    }
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
        : gameID(id), name(nam), developer(dev), publisher(pub), size(s), down(d){
        left = right = nullptr;
    }

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
    void pretorderTraversal(games* root,string id) {
        if (root == nullptr) {
            cout << "Game not found!!";
            return;
        }
        else if(root->get_id()==id) {
            cout << root->get_id() << "\n";
            return;
        }
        else {
            cout << root->get_id() << "\n";
            postorderTraversal(root->gleft());
            postorderTraversal(root->gright());
        }
    }
    games*& get_root() {
        return root;
    }
    void search_games(games*& root,string id) {
        if (root == nullptr) {
            cout << "Game not found!!";
            return;
        }
        else {
            if (decimal_(id) < decimal_(root->get_id())) {
                search_games( root->gleft(),id);
            }
            else if (decimal_(id) > decimal_(root->get_id())) {
                search_games(root->gright(), id);
            }
            else if (decimal_(id) == decimal_(root->get_id())) {
                cout <<"Game present!!";
                return;
            }
        }
    }
    void insert(games*& root, games* s) {//O(n)
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
void load_player(string p,Tree_player &pat,int s) {
    srand(time(0));
    ifstream file(p);
    string line;
    while (getline(file, line)) { // O(n^2)
        int r = rand() % 1000;
        if (s > r) {
            continue;
        }
        string id = "", name = "", phone = "", email = "", pass = "";
        int i = 0;
        while (line[i] != ',' && i < str_l(line)) {
            id += line[i++];
        }
        i++;
        while (line[i] != ',' && i < str_l(line)) {
            name += line[i++];
        }
        i++;
        while (line[i] != ',' && i < str_l(line)) {
            phone += line[i++];
        }
        i++;
        while (line[i] != ',' && i < str_l(line)) {
            email += line[i++];
        }
        i++;
        while (line[i] != ',' && i < str_l(line)) {
            pass += line[i++];
        }
        i++;
        int j = 0;
        player* tp = new player(id, name, phone, email, pass);
        while (i < line.size()) {
            string gd = "", gh = "", ga = "";
            while (line[i] != ',' && i < line.size()) {
                gd += line[i++];
            }
            i++;
            while (line[i] != ',' && i < line.size()) {
                gh += line[i++];
            }
            i++;
            while (line[i] != ',' && i < line.size()) {
                ga += line[i++];
            }
            i++;
            games_played* tempg = new games_played(gd, stof(gh), str_l(ga));
            tp->get_played_games().insert(tp->get_played_games().get_root(), tempg);
        }
        pat.insert(pat.getroot(), tp);
    }
    file.close();
}
void load_game(string s,Tree_game *ga) {
    ifstream file(s);
    string line;

    // Read and output each line
    while (getline(file, line)) {//O(n^2)
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
    string p = "C:\\Users\\user\\OneDrive\\Desktop\\Players.txt";
    Tree_player pat;
    Tree_game ga;
    cout << "Loading games\n";
    load_game(s, &ga);
    int seed = 570;
    cout << "Loading players\n";
    load_player(p, pat, seed);
    string n, pt;
    pat.postorderTraversal(pat.getroot());
    cout << "Insert player";
    while (true) {
        int ch;
        cout << "Enter 1 for game menu,2 for player,0 for exit:";
        cin >> ch;
        if (ch == 2) {
            cout << "Enter 1 for insertion,2 for retrieval,3 for details\n";
            cin >> ch;
            if (ch == 1) {
                string id, name, phon, emai, pass;
                cout << "enter id:\n";
                cin >> id;
                cout << "enter name:\n";
                cin >> name;
                cout << "enter phone:\n";
                cin >> phon;
                cout << "enter email:\n";
                cin >> name;
                cout << "enter pass:\n";
                cin >> pass;
                player* t = new player(id, name, phon, emai, pass);
                int i = 0;
                cout << "Enter no of games\n";
                cin >> i;
                for (int j = 0; j < i; j++) {
                    string gid;
                    float hrs;
                    int ach;
                    cout << "enter gid:\n";
                    cin >> gid;
                    cout << "enter hours:\n";
                    cin >> hrs;
                    cout << "enter achievements:\n";
                    cin >> ach;
                    games_played* te = new games_played(gid, hrs, ach);
                    t->get_played_games().insert(t->get_played_games().get_root(), te);
                }
                pat.insert(pat.getroot(), t);
            }
            else if(ch==2){
                string id;
                cout << "enter id:\n";
                cin >> id;
                pat.search_player(id, pat.getroot());
            }
            else if (ch == 3) {
                string id;
                cout << "enter id:\n";
                cin >> id;
                pat.display_dets(id, pat.getroot());
            }
        }
        else if(ch==0) {
            break;
        }
        else {
            cout << "Enter 1 for insertion,2 for retrieval\n";
            cin >> ch;
            if (ch == 1) {
                string id, name, dev, pub;
                float size;
                int down;
                cout << "enter id:\n";
                cin >> id;
                cout << "enter name:\n";
                cin >> name;
                cout << "enter developer:\n";
                cin >> dev;
                cout << "enter publisher:\n";
                cin >> pub;
                cout << "Enter download size\n";
                cin >> size;
                cout << "Enter downloads\n";
                cin >> down;
                games* temp = new games(id, name, dev, pub, size, down);
                ga.insert(ga.get_root(), temp);
            }
            else {
                string id,ch;
                cout << "enter id:\n";
                cin >> id;
                ga.search_games(ga.get_root(), id);
                cout << "show path taken to find game?(y/n)";
                cin >> ch;
                if (ch == "y") {
                    ga.pretorderTraversal(ga.get_root(), id);
                }
            }
        }
    }
    //ga.postorderTraversal(ga.get_root());
   /* cout << "Enter player id\n";
    cin >> n;
    cout << "Enter game id\n";
    cin >> pt;*/
    //pat.search_p(n, pt, pat.getroot());
    return 0;
}
