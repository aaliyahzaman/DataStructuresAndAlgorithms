#include<iostream>
#include <conio.h>
#include <fstream>
#include<vector>
#include<string>
#include <random>
using namespace std;
int random(int min, int max) {
    std::random_device rd;
    std::mt19937 rng(rd());
    int minValue = min;
    int maxValue = max;
    std::uniform_int_distribution<int> distribution(minValue, maxValue);
    int randomNumber = distribution(rng);
    return randomNumber;
}
static const int USER_SIZE = 10;
static const int ADV_SIZE = 10;
int adv_count = 0;

int compute_hash(string name)
{
    int hash = 0;
    for (int i = 0; name[i] != '\0';i++)
    {
        hash += name[i];

    }
    return hash;
}
class User 
{
public:
    string name;
    string password;
    int role;

public:
    User() {}
    User(const string& name, const string& password, const int& role)
        : name(name), password(password), role(role) {}

    friend ostream& operator<<(ostream& os, const User& user) {
        os << user.name << '\n';
        os << user.password << '\n';
        os << user.role << '\n';
        return os;
    }

    friend istream& operator>>(istream& is, User& user) {
        getline(is, user.name);
        getline(is, user.password);
        is >> user.role;
        is.ignore();
        return is;
    }
};

class UserNode {
public:
    User data;
    UserNode* next;
};
class UserList {
public:
    UserNode* head;
    UserList() :head(nullptr) {}
    void clear() {
        head = nullptr;
    }
    int size() {
        int count = 0;
        UserNode* c = head;
        while (c != nullptr) {
            count++;
            c = c->next;
        }
        return count;
    }
    void push_back(User p) {
        UserNode* n = new UserNode;
        n->data = p;
        n->next = nullptr;
        if (head == nullptr) {
            head = n;

        }
        else {
            n->next = head;
            head = n;
        }
    }

    void emplace_back(User p) {
        UserNode* n = new UserNode;
        n->data = p;
        n->next = nullptr;
        if (head == nullptr) {
            head = n;

        }
        else {
            UserNode* c = head;
            while (c->next != nullptr) {
                c = c->next;
            }
            c->next = n;
        }
    }
    class Iterator {
    private:
        UserNode* current;

    public:
        Iterator(UserNode* node) : current(node) {}

        User& operator*() {
            return current->data;
        }

        Iterator& operator++() {
            current = current->next;
            return *this;
        }

        bool operator!=(const Iterator& other) {
            return current != other.current;
        }
    };

    Iterator begin() {
        return Iterator(head);
    }

    Iterator end() {
        return Iterator(nullptr);
    }
};

User logedInUser;
class FriendRequest 
{
public:
    User req_sender;
    User req_reciever;
    int status;
    friend std::ostream& operator<<(std::ostream& os, const FriendRequest& ad) {
        os << ad.req_sender;
        os << ad.req_reciever;
        os << ad.status << '\n';
        return os;
    }

    friend std::istream& operator>>(std::istream& is, FriendRequest& ad) {
        is >> ad.req_sender;
        is >> ad.req_reciever;
        is >> ad.status;
        return is;
    }
};
class FriendRequestNode {
public:
    FriendRequest data;
    FriendRequestNode* next;
};
class FriendRequestList {


public:
    FriendRequestNode* head;
    void emplace_front(FriendRequest p) {
        FriendRequestNode* n = new FriendRequestNode;
        n->data = p;
        n->next = nullptr;
        if (head == nullptr) {
            head = n;

        }
        else {
            n->next = head;
            head = n;
        }
    }

    void emplace_back(FriendRequest p) {
        FriendRequestNode* n = new FriendRequestNode;
        n->data = p;
        n->next = nullptr;
        if (head == nullptr) {
            head = n;

        }
        else {
            FriendRequestNode* c = head;
            while (c->next != nullptr) {
                c = c->next;
            }
            c->next = n;
        }
    }
    class Iterator {
    private:
        FriendRequestNode* current;

    public:
        Iterator(FriendRequestNode* node) : current(node) {}

        FriendRequest& operator*() {
            return current->data;
        }

        Iterator& operator++() {
            current = current->next;
            return *this;
        }

        bool operator!=(const Iterator& other) {
            return current != other.current;
        }
    };

    Iterator begin() {
        return Iterator(head);
    }

    Iterator end() {
        return Iterator(nullptr);
    }
};

class Advertisement
{
public:
    string content;
    string creator;
    string type;
    friend std::ostream& operator<<(std::ostream& os, const Advertisement& ad) {
        os << ad.content << '\n';
        os << ad.creator << '\n';
        os << ad.type << '\n';
        return os;
    }

    friend std::istream& operator>>(std::istream& is, Advertisement& ad) {
        getline(is, ad.content);
        getline(is, ad.creator);
        getline(is, ad.type);
        return is;
    }
};
Advertisement advertisements[ADV_SIZE];
//list<FriendRequest> request_list;
FriendRequestList request_list;

//list<FriendRequest> friend_list;
class AdjacencyNode {
public:
    User user;
    UserList adjacentList;
    AdjacencyNode() {}
   AdjacencyNode(const User& user) : user(user) {}
   friend std::ostream& operator<<(std::ostream& os,  AdjacencyNode& node) {
       os << node.user << '\n';
       os << node.adjacentList.size() << '\n';
       for (const User& neighbor : node.adjacentList) {
           os << neighbor << '\n';
       }
       return os;
   }

   friend std::istream& operator>>(std::istream& is, AdjacencyNode& node) {
       is >> node.user;
       int numNeighbors;
       is >> numNeighbors;
       is.ignore(); // Ignore the newline character

       node.adjacentList.clear();
       for (int i = 0; i < numNeighbors; ++i) {
           User neighbor;
           is >> neighbor;
           node.adjacentList.push_back(neighbor);
           is.ignore(); // Ignore the newline character
       }
       return is;
   }
};
class FriendsGraph {
public:
    vector<AdjacencyNode> adjacencyList;

public:

    friend std::ostream& operator<<(std::ostream& os,  FriendsGraph& graph) {
        os << graph.adjacencyList.size() << '\n';
        for ( AdjacencyNode& node : graph.adjacencyList) {
            os << node << '\n';
        }
        return os;
    }

    friend std::istream& operator>>(std::istream& is, FriendsGraph& graph) {
        graph.adjacencyList.clear();

        int numNodes;
        is >> numNodes;
        is.ignore(); // Ignore the newline character

        for (int i = 0; i < numNodes; ++i) {
            AdjacencyNode node;
            is >> node;
            graph.adjacencyList.push_back(node);
            is.ignore(); // Ignore the newline character
        }
        return is;
    }
    void addUser(const User& user) {
       
        adjacencyList.emplace_back(user);
    }

    void addEdge(const User& src, const User& dest) {
        for (AdjacencyNode& node : adjacencyList) {
            if (node.user.name == src.name) {
                node.adjacentList.push_back(dest);
            }
            else if (node.user.name == dest.name) {
                node.adjacentList.push_back(src);
            }
        }
    }
    void showFriends() {
        for (int i = 0; i < adjacencyList.size(); ++i) {
            const User& user = adjacencyList[i].user;
            if (user.name == logedInUser.name)
            {
                for (const User& neighbor : adjacencyList[i].adjacentList) {
                   cout << "Name : " << neighbor.name << "\n";
                }
                
            }
        }
    }
    vector<User> getFriends() {
        vector<User> users;
        for (int i = 0; i < adjacencyList.size(); ++i) {
            const User& user = adjacencyList[i].user;
            if (user.name == logedInUser.name)
            {
                for (const User& neighbor : adjacencyList[i].adjacentList) {
                    users.push_back(neighbor);
                }

            }
        }
        return users;
    }

    vector<User> suggestFriends() {
        vector<User> suggestions;
        vector<User> friends = getFriends();
        for (const User& friendUser : friends) {
            for ( AdjacencyNode& node : adjacencyList) {
                if ( node.user.name == logedInUser.name) {
                    continue;
                }
                else if (node.user.name == friendUser.name) {
                    bool isFriend = false;
                    for (const User& neighbor : node.adjacentList) {
                        isFriend = false;
                        if (neighbor.name == logedInUser.name || neighbor.name == friendUser.name) {
                            isFriend = true;
                            continue;
                        }
                        if (!isFriend) {
                            bool isAlreadyExists = false;
                            for(int i = 0; i< suggestions.size();i++)
                            {
                                if (suggestions[i].name == neighbor.name)
                                {
                                    isAlreadyExists = true;
                                }
                            }
                            if (!isAlreadyExists)
                            {
                                for (int i = 0; i < friends.size();i++) {
                                    if (friends[i].name == neighbor.name) 
                                    {
                                        isAlreadyExists = true;
                                    }
                                }
                            }
                            if(!isAlreadyExists)
                                suggestions.push_back(neighbor);
                        }
                    }
                }
            }
        }

        return suggestions;
    }
};
class Post
{
public:
    string creator;
    string content;
    int privacy;//0 private,1 public, 2 friends only
    Post() {}
    Post(const string& creator, const string& content, const int& privacy)
        : creator(creator), content(content), privacy(privacy) {}

    friend ostream& operator<<(ostream& os, const Post& p) {
        os << p.creator << '\n';
        os << p.content << '\n';
        os << p.privacy << '\n';
        return os;
    }

    friend istream& operator>>(istream& is, Post& p) {
        getline(is, p.creator);
        getline(is, p.content);
        is >> p.privacy;
        is.ignore();
        return is;
    }

};

class PostNode {
public :
    Post data;
    PostNode * next;
};
class PostLinkedList {
    

public:
    PostNode* head;
    void emplace_front(Post p) {
        PostNode* n = new PostNode;
        n->data = p;
        n->next = nullptr;
        if (head == nullptr) {
            head = n;
            
        }
        else {
            n->next = head;
            head = n;
        }
    }

    void emplace_back(Post p) {
        PostNode* n = new PostNode;
        n->data = p;
        n->next = nullptr;
        if (head == nullptr) {
            head = n;

        }
        else {
            PostNode* c = head;
            while (c->next != nullptr) {
                c = c->next;
            }
            c->next = n;
        }
    }
    class Iterator {
    private:
        PostNode* current;

    public:
        Iterator(PostNode* node) : current(node) {}

        Post& operator*() {
            return current->data;
        }

        Iterator& operator++() {
            current = current->next;
            return *this;
        }

        bool operator!=(const Iterator& other) {
            return current != other.current;
        }
    };

    Iterator begin() {
        return Iterator(head);
    }

    Iterator end() {
        return Iterator(nullptr);
    }
};
class UserHashTable {
private:
    
    UserList table[USER_SIZE];

public:
    int hashFunction(int key) {
        return key % USER_SIZE;
    }

    void insert(int key,User data) {
        table[key].push_back(data);
    }
    bool search(int key, string name, string pwd)
    {
        for (const auto& user : table[key]) {
            if (user.name == name && user.password == pwd) {
                return true;
            }
        }
        return false;
    }
    const User* searchUser(int key, string name)
    {
        for (const User& user : table[key]) {
            if (user.name == name) {
                return &user;
            }
        }
        return nullptr;
    }
    bool search(int key, string name)
    {
        for (const auto& user : table[key]) {
            if (user.name == name) {
                return true;
            }
        }
        return false;
    }
    void display() {
        
    }
    void save()
    {
        // Object to write in file
        ofstream file_obj;

        // Opening file in append mode
        file_obj.open("userdata.txt", ios::trunc);
            for (int i = 0; i < USER_SIZE; i++) {
                for (const User& user : table[i]) {
                   // file_obj.write(reinterpret_cast<const char*>(& user), sizeof(User));
                    file_obj << user;
                }
            }
            file_obj.close();
    }

};
UserHashTable usersTable;
//list<Post> posts;
PostLinkedList posts;
string readPassword() {
  string password;
    char c;
    while ((c = _getch()) != '\r') { // Read characters until Enter (carriage return) is pressed
        if (c == '\b') { // Handle backspace character
            if (!password.empty()) {
                password.pop_back();
                cout << "\b \b"; // Move the cursor back and overwrite the character with a space
            }
        }
        else {
            password += c;
           cout << "*"; // Print a "*" for each character (to mimic password input)
        }
    }

    return password;
}
void show_advertisement()
{
    int rd = random(0, ADV_SIZE);
    if (rd > adv_count) {
        return;
        //rd = random(0, ADV_SIZE);
    }
    cout << "*******************Advertisement*****************" << endl;
    cout << "Content : " << advertisements[rd].content << endl;
    cout << "*************************************************" << endl;
    cout << "------------------------------------------------" << endl;
}
void post_advertisement()
{
    Advertisement ad;
    cout << "-------------------------------------------------" << endl;
    cout << "                 Post Advertisement" << endl;
    cout << "-------------------------------------------------" << endl << endl;
    cout << "Enter content of the advertisement ";
    cin.ignore();
    getline(cin, ad.content);
    ad.creator = logedInUser.name;
    advertisements[adv_count % ADV_SIZE] = ad;
    adv_count++;
    cout << "Post created successfully" << endl;
}
int send_friend_request(FriendsGraph & friendsGraph, string name)
{
    int key = compute_hash(name) % USER_SIZE;
    const User * obj = usersTable.searchUser(key, name);
    if (obj != nullptr)
    {
        bool isFriend = true;
        vector<User> friends = friendsGraph.getFriends();
        int i = 0;
        for (;i < friendsGraph.adjacencyList.size();i++) {
            if (friendsGraph.adjacencyList[i].user.name == name) {
                auto it = find_if(friends.begin(), friends.end(), [&](const User& user) {
                    return user.name == friendsGraph.adjacencyList[i].user.name;
                    });
                if (it != friends.end()) {
                }
                else {
                    isFriend = false;
                    cout << "Id : " << (i + 1) << endl << "Name : " << friendsGraph.adjacencyList[i].user.name << endl;
                }
                break;
            }
        }
        if (isFriend)
        {
            return - 2;
        }
        else {
            return i;
        }
    }
    else
    {
        return -1;
    }
}
void view_accept_request(FriendsGraph& friendsGraph)
{
    cout << "-------------------------------------------------" << endl;
    cout << "                 Friend Requests" << endl;
    cout << "-------------------------------------------------" << endl << endl;
    string name;
    bool isExists = false;
    for (const FriendRequest& neighbor : request_list) {
        if (neighbor.req_reciever.name == logedInUser.name && neighbor.status == 0
            ) {
            cout  << "Name : " << neighbor.req_sender.name << "\n";
            isExists = true;
        }
    }
    
    if (isExists) {
        cout << "--------------------------------\n";
        cout << "enter the name of the person for accepting request, otherwise type no ";
        cin >> name;
        if (name != "no") {
            int key = compute_hash(name);
            key = key % USER_SIZE;
            const User* u = usersTable.searchUser(key, name);
            if (u != nullptr) {
                FriendRequest r;
                r.req_reciever.name = u->name;
                r.req_sender = logedInUser;
                for (FriendRequest& fr : request_list) {
                    if (fr.status == 0 && fr.req_sender.name == name && fr.req_reciever.name == logedInUser.name) {
                        fr.status = 1;

                    }
                }
                friendsGraph.addEdge(logedInUser, r.req_reciever);
                cout << "Friend request sucessfully accepted " << endl;
            }
            else {
                cout << "User not found " << endl;
            }
        }
    }
    else {
        cout << "No friend request found" << endl;
    }
}
void suggest_friends(FriendsGraph & friends) {
    vector<User>  suggestions = friends.suggestFriends();
    cout << "-------------------------------------------------" << endl;
    cout << "                 Friend Suggestions" << endl;
    cout << "-------------------------------------------------" << endl << endl;
    if (suggestions.size() == 0)
    {
        cout << "No friend suggestions found" << endl;
    }
    else 
    {
        for (int i = 0; i < suggestions.size(); i++)
        {
            cout << "Name : " << suggestions[i].name << endl;
        }
    }
}
void show_post_and_advertisement()
{
    for (const auto& post : posts) {
        if (post.creator == logedInUser.name || post.privacy == 1) {
            cout << "------------------------------------------------" << endl;
            cout << "Content : " << post.content << endl;
            cout << "Creator : " << post.creator << endl;
            cout << "------------------------------------------------" << endl;
            int rd = random(0, ADV_SIZE);
            if (rd > adv_count) {
                continue;
                //rd = random(0, ADV_SIZE);
            }
            cout << "*******************Advertisement*****************" << endl;
            cout << "Content : " << advertisements[rd].content << endl;
            cout << "*************************************************" << endl;
            
            cout << endl;
        }
    }
    int rd;
    if (adv_count > ADV_SIZE) {
        rd = random(0, ADV_SIZE);
        while (rd > adv_count) {
            rd = random(0, ADV_SIZE);
            return;
        }
    }
    else {
        rd = random(0, adv_count);
        if (rd > adv_count) {
            rd = random(0, adv_count);
            return;
        }
    }
    if (rd >= 1)
    {
        cout << "*******************Advertisement*****************" << endl;
        cout << "Content : " << advertisements[rd - 1].content << endl;
        cout << "*************************************************" << endl;
    }

}
void main_menu(FriendsGraph &friendsGraph)
{
    while (true)
    {
        cout << endl;
        cout << "*************************************************" << endl;
        cout << "                 Social Application"<<endl;
        cout << "*************************************************" << endl<<endl;
        cout << "Enter 1 view posts\n";
        cout << "Enter 2 to create Post\n";
        cout << "Enter 3 view friend request \n";
        cout << "Enter 4 to add friend \n";
        cout << "Enter 5 to view friends list \n";
        cout << "Enter 6 to view friends suggestions \n";
        if (logedInUser.role == 0) {
            cout << "Enter 7 to add advertisement \n";
        }
        cout << "Enter 0 to log out ";
        
        int choice;
        cin >> choice;
        cout << endl;
        if (choice == 0)
            break;
        else if (choice == 1) {
            cout << "-------------------------------------------------" << endl;
            cout << "                 Posts" << endl;
            cout << "-------------------------------------------------" << endl << endl;
            show_post_and_advertisement();
        }
        else if (choice == 2) {
            Post p;
            
            cout << "-------------------------------------------------" << endl;
            cout << "                 Create Post" << endl;
            cout << "-------------------------------------------------" << endl << endl;
            cout << "Enter content of the post ";
            cin.ignore();
            getline(cin, p.content);
            while (true)
            {
                cout << "Enter visibility of post 1 for public, 2 for private and 3 for friends ";
                cin >> p.privacy;
                if (p.privacy > 3 || p.privacy < 1)
                {
                    cout << "Invalid value, the privacy value must be between 1 and 3" << endl;
                }
                else
                    break;
            }
            p.creator = logedInUser.name;
            posts.emplace_front(p);
            cout << "Post created successfully" << endl;

        }
        else if (choice == 3) {
            view_accept_request(friendsGraph);
        }
        else if (choice == 4) {
            cout << "-------------------------------------------------" << endl;
            cout << "                 List of Users" << endl;
            cout << "-------------------------------------------------" << endl << endl;
            string name;
            cout << "Enter name of user to search ";
            cin >> name;
            int i = send_friend_request(friendsGraph, name); 
            if (i == -1)
            {
                cout << "user not found" << endl;
            }
            else if (i == -2)
            {
                cout << "The " << name << " is already in your friend list" << endl;
            }
            else
            {
                cout << "-------------------------------------------------\n";
                cout << "do you want to add friend? if yes enter the id of that person : ";
                int id;
                cin >> id;
                if (id <= 0 || id > i)
                {
                    cout << "Invalid Id" << endl;
                }
                else
                {
                    FriendRequest req;
                    req.req_reciever = friendsGraph.adjacencyList[id - 1].user;
                    req.req_sender = logedInUser;
                    req.status = 0;
                    request_list.emplace_back(req);
                    cout << "Friend request sent" << endl;

                }
            }
        }
        else if (choice == 5) {
            cout << "-------------------------------------------------" << endl;
            cout << "                 Friends" << endl;
            cout << "-------------------------------------------------" << endl << endl;
            friendsGraph.showFriends();
            cout << "-------------------------------------------------\n";
        }
        else if (choice == 6) {
            suggest_friends(friendsGraph);
        }
        else if (logedInUser.role == 0) {
            if (choice == 7) {
                post_advertisement();

            }
        }
        
        system("pause");
        system("cls");
        cout << endl;
    }
}

void log_in(FriendsGraph & friendsGraph)
{
    string name;
    cout << "Enter user name  : ";
    cin >> name;
    cout << "Enter password  : ";
    string p = readPassword();
    int index = compute_hash(name);
    index = index % USER_SIZE;
    if (name == "admin" && p == "123") {
        logedInUser.name = name;
        logedInUser.password = p;
        logedInUser.role = 0;
        system("cls");
        main_menu(friendsGraph);
    }
    if (usersTable.search(index, name, p))
    {
        cout << endl;
        logedInUser.name = name;
        logedInUser.password = p;
        logedInUser.role = 1;
        system("cls");
        main_menu(friendsGraph);
    }

    else 
    {
        cout << endl<<"Invalid credentials" << endl;
        system("pause");
    }

}

void sign_up(FriendsGraph& friendsGraph)
{
    string name;
    while (true)
    {
        cout << "Enter user name : ";
        cin >> name;
        int hash = compute_hash(name);
        int index = hash % USER_SIZE;
        if (usersTable.search(index, name))
        {
            cout << "name already exists" << endl;
        }
        else 
        {
            cout << "Enter password : ";
            string p;
            p = readPassword();
            User obj;
            obj.name = name;
            obj.password = p;
            obj.role = 1;
            usersTable.insert(index, obj);
            friendsGraph.addUser(obj);
            break;
        }
        
        

    }
}

void read_users(FriendsGraph& friendsGraph)
{
    ifstream file_obj;
    file_obj.open("userdata.txt");
    User obj;
    while (file_obj>>obj) {
        int index = compute_hash(obj.name) % USER_SIZE;
        usersTable.insert(index, obj);
    }
    file_obj.close();
}
void read_advertisement()
{
    ifstream file_obj;
    file_obj.open("advertisement.txt");
    Advertisement obj;
    int i = 0;
    while (file_obj>>obj) {
        advertisements[i] = obj;
        i++;
    }
    file_obj.close();
}
void write_advertisement()
{
    ofstream file_obj;
    file_obj.open("advertisement.txt", ios::trunc);
    for (int i = 0; i < ADV_SIZE; i++) {
        file_obj << advertisements[i];
    }
    file_obj.close();
}
void read_firend_request()
{
    ifstream file_obj;
    file_obj.open("friendreq.txt");
    FriendRequest obj;
    while (file_obj>>obj) {
        request_list.emplace_back(obj);
    }
    file_obj.close();
}
void write_firend_request() {
    ofstream file_obj;
    file_obj.open("friendreq.txt", ios::trunc);
    for (const FriendRequest& p : request_list) {
        file_obj << p;

    }
    file_obj.close();
}
void read_graph(FriendsGraph& friendsGraph)
{
    ifstream file_obj;
    file_obj.open("graph.txt");
    file_obj>>friendsGraph;
    file_obj.close();
}
void write_graph(FriendsGraph& friendsGraph)
{
    ofstream file_obj;
    file_obj.open("graph.txt", ios::trunc);
        file_obj << friendsGraph;

    file_obj.close();
}
void write_post()
{
    ofstream file_obj;
    file_obj.open("post.txt",ios::trunc);
        for (const Post& p : posts) {
            file_obj << p;

        }
    
    file_obj.close();
}
void read_post()
{
    ifstream file_obj;
    file_obj.open("post.txt");
    Post obj;
    while (file_obj>>obj) {
        posts.emplace_back(obj);
    }
    file_obj.close();
}
void load_data(FriendsGraph& friendsGraph)
{
    read_users(friendsGraph);
    read_post();
    read_firend_request();
    read_advertisement();
    read_graph(friendsGraph);
   
}
void save_data(FriendsGraph& friendsGraph)
{
    usersTable.save();
    write_post();
    write_advertisement();
    write_firend_request();
    write_graph(friendsGraph);
}

void menu(FriendsGraph& friendsGraph)
{
    while (true) {
        system("cls");
        cout << endl;
        cout << "*************************************************" << endl;
        cout << "                 Social Application" << endl;
        cout << "*************************************************" << endl << endl;
        cout << "Enter 1 to LogIn\nEnter 2 to SignUp\nEnter any other to exit  ";
        int choice;
        cin >> choice;
        cout << endl;
        if (choice == 1)
        {
            cout << "-------------------------------------------------" << endl;
            cout << "                 Login" << endl;
            cout << "-------------------------------------------------" << endl << endl;
            log_in(friendsGraph);
        }
        else if (choice == 2)
        {
            cout << "-------------------------------------------------" << endl;
            cout << "                 Sign Up" << endl;
            cout << "-------------------------------------------------" << endl << endl;
            sign_up(friendsGraph);
        }
        else {
            return;
        }
    }
}
void main()
{
    FriendsGraph friendsGraph;
    load_data(friendsGraph);
    menu(friendsGraph);
    system("cls");
    save_data(friendsGraph);
	system("pause");
}


