#include <iostream>
#include <vector>
#include <string>
#include <string.h>
#include <queue>
#include <iterator>
#include <new>
#include <math.h>
#include <set>
#include <algorithm>

class huffmannode;
std::vector<char> v;
std::set<char> set1;





using namespace std;


int btod(int n)
{
    int decimal = 0, i = 0, r;
    while (n!=0)
    {
        r = n%10;
        n /= 10;
        decimal += r*pow(2,i);
        ++i;
    }
    return decimal;
}



class huffmannode {
public:
    string value;
    string route;
    int number;
    huffmannode* right {nullptr};
    huffmannode* left {nullptr};
    huffmannode* parent {nullptr};
    huffmannode(string v,int n,huffmannode * r,huffmannode * l,huffmannode * p= nullptr);
    huffmannode(){};

};

struct cmp{
    bool operator()(huffmannode * hf1,huffmannode* hf2){
        return (hf1->number > hf2->number);
    }
};

vector <huffmannode *> nodes;
vector <huffmannode *>::iterator first=nodes.begin() , last=nodes.end();
priority_queue <huffmannode * , vector<huffmannode *> ,cmp > nodes_queue;


huffmannode::huffmannode(string v,int n,huffmannode * r,huffmannode * l,huffmannode * p) {
    value =v, number=n, right=r, left=l, parent=p;
    //nodes.push_back(this);
    //nodes_queue.push(this);
};

huffmannode * hnp = new huffmannode;

void makenodes(string str){
    string s;

    int n;
    for (int i = 0; i < str.length() ; i+=8) {
        for (int j = 0; j < 8; ++j) {
            s+=str[i+j];
        }
        n=stoi(s);
        v.push_back(char(btod(n)));
        s.erase(s.begin(),s.end());
    }
    set1=set<char>(v.begin(),v.end());
    set<char>::iterator f=set1.begin();
    set<char>::iterator l=set1.end();
    for (f; f != l; f++) {
        string val;
        val+= *f;
        nodes.push_back(new huffmannode(val,int(count(v.begin(),v.end(),*f)), nullptr, nullptr, nullptr));
        nodes_queue.push(new huffmannode(val,int(count(v.begin(),v.end(),*f)), nullptr, nullptr, nullptr));
        val.erase(val.begin(),val.end());
    }
}

void merge() {
    if(nodes_queue.size()>1) {
        huffmannode *ptr1 = nodes_queue.top();
        nodes_queue.pop();
        huffmannode *ptr2 = nodes_queue.top();
        nodes_queue.pop();
        nodes_queue.push(new huffmannode(ptr1->value + ptr2->value, ptr1->number + ptr2->number, ptr2, ptr1, nullptr));
        nodes.push_back(new huffmannode(ptr1->value + ptr2->value, ptr1->number + ptr2->number, ptr2, ptr1, nullptr));
        ptr1->parent = *(nodes.end());
        ptr2->parent = *(nodes.end());
        return merge();
    }
    else
        return;
}

void makeroutes(huffmannode* hfptr){
    if(hfptr->right and hfptr->left){
        hfptr->right->route=hfptr->route+"1";
        hfptr->left->route=hfptr->route+"0";
        makeroutes(hfptr->right);
        makeroutes(hfptr->left);
    }
    else
        cout<<endl<<hfptr->value<<" "<<hfptr->route<<endl;


};

int main() {
    string str12;
    cin>>str12;
    makenodes(str12);
    merge();
    makeroutes(nodes_queue.top());
    //print();
    return 0;
}
